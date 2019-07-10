//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "PaintManager.h"
#include "Input.h"
#include "MyLibrary.h"
#include "Camera.h"
#include "Collision.h"
#include "Quadtree.h"
#include "DebugWindow.h"
#include "SceneGame.h"
#include "Player.h"

QUADTREE *PaintManager::Quadtree = nullptr;
bool PaintManager::PressMode = true;

//=============================================================================
// コンストラクタ
//=============================================================================
PaintManager::PaintManager(int PlayerNo)
{
	this->Owner = PlayerNo;
	this->InkType = ColorInk;
	for (int i = 0; i < InkNum; i++)
	{
		this->InkValue[i] = INK_MAX;
	}
	this->pCursor = new Cursor(this->Owner);
	this->inkGauge.push_back(new InkGauge(ColorInk, PlayerNo));
	this->inkGauge.push_back(new InkGauge(BlackInk, PlayerNo));

	// ペイントベクトルのメモリ領域確保
	BlackPaint.reserve(INK_MAX);
	ColorPaint.reserve(INK_MAX);

	if (PaintManager::Quadtree == nullptr)
	{
		PaintManager::Quadtree = Quadtree;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
PaintManager::~PaintManager()
{
	// メモリリリース
	SAFE_DELETE(this->pCursor);

	for (auto &Object : this->inkGauge)
	{
		SAFE_DELETE(Object);
	}
	this->inkGauge.clear();
	ReleaseVector(inkGauge);

	for (auto &Paint : this->BlackPaint)
	{
		SAFE_DELETE(Paint);
	}
	this->BlackPaint.clear();
	ReleaseVector(BlackPaint);

	for (auto &Paint : this->ColorPaint)
	{
		SAFE_DELETE(Paint);
	}
	this->ColorPaint.clear();
	ReleaseVector(ColorPaint);
}

//=============================================================================
// 更新処理
//=============================================================================
void PaintManager::Update()
{
	// カーソルの更新
	this->pCursor->Update();

	// 使用していないペイントがベクトルから削除
	CheckPaintUse();

	// 使用しているペイントを更新
	for (auto &Black : this->BlackPaint)
	{
		// オブジェクトが画面内かつ、ノードの範囲内じゃないなら、もう一度四分木に入れる
		if (Black->GetInScreen() && !PaintManager::Quadtree->CheckObjectInNode(Black))
		{
			PaintManager::Quadtree->InsertObject(Black);
		}
		Black->Update();
	}
	for (auto &Color : this->ColorPaint)
	{
		if (Color->GetInScreen() && !PaintManager::Quadtree->CheckObjectInNode(Color))
		{
			PaintManager::Quadtree->InsertObject(Color);
		}
		Color->Update();
	}

	// インクの種類交換
	if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(Owner, BUTTON_R1))
	{
		InkType = InkType == BlackInk ? ColorInk : BlackInk;
	}

	// インクを使う
	if ((GetKeyboardPress(DIK_O) || IsButtonPressed(this->Owner, BUTTON_C)) && PressMode)
	{
		// 使用するインクの残量チェック
		if (this->InkValue[InkType] > 0)
		{
			// ペイントを設置する
			SetPaint(InkType);
			// インクを減らす
			InkValue[InkType]--;

			//if (!pPlayer->GetSpInk())
			//{
			//	InkValue[InkType]--;
			//}
		}
	}
#if _DEBUG
	else if ((GetKeyboardTrigger(DIK_O) || IsButtonPressed(this->Owner, BUTTON_C)) && !PressMode)
	{
		// 使用するインクの残量チェック
		if (this->InkValue[InkType] > 0)
		{
			// ペイントを設置する
			SetPaint(InkType);
			// インクを減らす
			InkValue[InkType]--;

			//if (!pPlayer->GetSpInk())
			//{
			//	InkValue[InkType]--;
			//}
		}
	}
#endif

	// インクゲージを更新
	inkGauge.at(ColorInk)->Update(InkValue[ColorInk]);
	inkGauge.at(BlackInk)->Update(InkValue[BlackInk]);

#if _DEBUG
	// インクの残量を調整
	if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_Z))
	{
		if (InkValue[InkType] > 0)
		{
			InkValue[InkType]--;
		}
	}

	if (GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_X))
	{
		if (InkValue[InkType] < INK_MAX)
		{
			InkValue[InkType]++;
		}
	}

	if (GetKeyboardTrigger(DIK_L))
	{
		for (auto Paint = this->BlackPaint.begin(); Paint != this->BlackPaint.end(); Paint++)
		{
			(*Paint)->SetUse(false);
			SAFE_DELETE((*Paint));
		}
		this->BlackPaint.clear();

		for (auto Paint = this->ColorPaint.begin(); Paint != this->ColorPaint.end(); Paint++)
		{
			(*Paint)->SetUse(false);
			SAFE_DELETE((*Paint));
		}
		this->ColorPaint.clear();
	}

	if (this->Owner == 0)
	{
		BeginDebugWindow("Information");

		enum ePaintMode
		{
			ePress,
			eTrigger,
		};
		static int Mode = 0;

		DebugText("PaintMode : ");
		ImGui::SameLine();
		ImGui::RadioButton("Press", &Mode, ePress);
		ImGui::SameLine();
		ImGui::RadioButton("Trigger", &Mode, eTrigger);
		if (Mode == ePress)
		{
			PressMode = true;
		}
		else
		{
			PressMode = false;
		}

		EndDebugWindow("Information");
	}
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void PaintManager::Draw()
{
	// カーソルを描画
	this->pCursor->Draw();

	// 使用しているペイントを描画
	for (auto &Black : this->BlackPaint)
	{
		Black->Draw();
	}
	for (auto &Color : this->ColorPaint)
	{
		Color->Draw();
	}

	// インクゲージを描画
	// 現在使用しているインクはカラー、カラーインクゲージは前
	if (this->InkType == ColorInk)
	{
		inkGauge.at(BlackInk)->Draw();
		inkGauge.at(ColorInk)->Draw();
	}
	// 現在使用しているインクは黒、黒インクゲージは前
	else if (this->InkType == BlackInk)
	{
		inkGauge.at(ColorInk)->Draw();
		inkGauge.at(BlackInk)->Draw();
	}
}

//=============================================================================
// ペイントのセット
//=============================================================================
void PaintManager::SetPaint(int InkType)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	CAMERA *camerawk = GetCamera();
	D3DXMATRIX ViewMtx, ProjMtx;
	D3DXVECTOR3 CursorPos = pCursor->GetPenPoint();

	Device->GetTransform(D3DTS_VIEW, &ViewMtx);
	Device->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	// 黒インクの場合
	if (InkType == BlackInk)
	{
		if (this->BlackPaint.size() >= INK_MAX)
		{
			return;
		}

		Paint *Object = new Paint(this->Owner, BlackInkColor);

		// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
		// スクリーン座標とXZ平面のワールド座標交点算出
		D3DXVECTOR3 OutPos1, OutPos2, SetPos;
		CalcScreenToWorld(&OutPos1, (int)CursorPos.x, (int)CursorPos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)CursorPos.x, (int)CursorPos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

		// 判定用三角形ポリゴン
		TriangleStr triPos1, triPos2;
		triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		// 2点を使って当たった場所をセットする場所とする
		if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
		{
			hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
		}

		Object->SetPos(SetPos);
		Object->SetUse(true);

		// スクリーン座標を保存する
		Object->SetScreenPos((D3DXVECTOR2)CursorPos);
		// 四分木に入れる
		PaintManager::Quadtree->InsertObject(Object);

		// 使用しているインクの色に合わせて表示時間、テクスチャをセット
		Object->SetTime(DRAW_FRAME_BLACK);

		// Vectorに入れる
		this->BlackPaint.push_back(Object);
	}
	// カラーインクの場合
	else
	{
		if (this->ColorPaint.size() >= INK_MAX)
		{
			return;
		}

		Paint *Object = new Paint(this->Owner, this->Owner);

		// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
		// スクリーン座標とXZ平面のワールド座標交点算出
		D3DXVECTOR3 OutPos1, OutPos2, SetPos;
		CalcScreenToWorld(&OutPos1, (int)CursorPos.x, (int)CursorPos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)CursorPos.x, (int)CursorPos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

		// 判定用三角形ポリゴン
		TriangleStr triPos1, triPos2;
		triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		// 2点を使って当たった場所をセットする場所とする
		if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
		{
			hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
		}

		Object->SetPos(SetPos);
		Object->SetUse(true);

		// スクリーン座標を保存する
		Object->SetScreenPos((D3DXVECTOR2)CursorPos);
		// 四分木に入れる
		PaintManager::Quadtree->InsertObject(Object);

		// 使用しているインクの色に合わせて表示時間、テクスチャをセット
		Object->SetTime(DRAW_FRAME_COLOR);

		// Vectorに入れる
		this->ColorPaint.push_back(Object);
	}
}

//=====================================================================================================
// インクの種類交換
//=====================================================================================================
//void PaintManager::ChangeInk()
//{
	//InkType = InkType == BlackInk ? ColorInk : BlackInk;
	//// 黒→カラー
	//if (InkType == BlackInk)
	//{
	//	InkType = ColorInk;
	//}
	//// カラー→黒
	//else
	//{
	//	inkType = BlackInk;
	//}

	// インクバーの描画順を入れ替え
	//ChangeDrawOrder(NumInkblack00 + Owner, NumInkblue + Owner);
	// フレームの描画順を入れ替え
	//ChangeDrawOrder(NumBlackFrame00 + Owner, NumColorFrame00 + Owner);
//}

//=============================================================================
// 使用していないペイントがVectorから削除
//=============================================================================
void PaintManager::CheckPaintUse(void)
{
	for (auto Paint = this->BlackPaint.begin(); Paint != this->BlackPaint.end();)
	{
		if ((*Paint)->GetUse() == false)
		{
			SAFE_DELETE((*Paint));
			Paint = this->BlackPaint.erase(Paint);
		}
		else
		{
			Paint++;
		}
	}

	for (auto Paint = this->ColorPaint.begin(); Paint != this->ColorPaint.end();)
	{
		if ((*Paint)->GetUse() == false)
		{
			SAFE_DELETE((*Paint));
			Paint = this->ColorPaint.erase(Paint);
		}
		else
		{
			Paint++;
		}
	}
}

//=============================================================================
// 四分木から衝突可能なオブジェクトを探す
//=============================================================================
std::vector<Paint*> PaintManager::GetCollisionList(int NodeID)
{
	return PaintManager::Quadtree->GetObjectsAt(NodeID);
}

void CursorMove(D3DXVECTOR3 DestPos)
{

}