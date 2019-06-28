//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "PaintSystem.h"
#include "Input.h"
#include "Debugproc.h"
#include "MyLibrary.h"
#include "Camera.h"
#include "Collision.h"
#include "Quadtree.h"
#include "Player.h"

QUADTREE *PaintManager::Quadtree = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
PaintManager::PaintManager(Cursor *pC, Player *pP, QUADTREE *Quadtree)
{
	pPlayer = pP;
	pCursor = pC;
	this->Owner = pP->GetCtrlNum();

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

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
void PaintManager::Update(bool PressMode)
{
	// カーソルの筆先に座標を合わせる
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	// 使用していないペイントがVectorから削除
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

	// インクを使う
	if ((GetKeyboardPress(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C)) && PressMode)
	{
		// 使用するインクの残量チェック
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			// ペイントを設置する
			SetPaint(pPlayer->GetInkType());
			// インクを減らす
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}
	else if ((GetKeyboardTrigger(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C)) && !PressMode)
	{
		// 使用するインクの残量チェック
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			// ペイントを設置する
			SetPaint(pPlayer->GetInkType());
			// インクを減らす
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}

#if _DEBUG
	//PrintDebugProc("Player %d BlackPaintNum：%d\n", this->Owner, this->BlackPaint.size());
	//PrintDebugProc("Player %d ColorPaintNum：%d\n", this->Owner, this->ColorPaint.size());

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
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void PaintManager::Draw()
{
	// 使用しているペイントを描画
	for (auto &Black : this->BlackPaint)
	{
		Black->Draw();
	}
	for (auto &Color : this->ColorPaint)
	{
		Color->Draw();
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
		CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

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
		Object->SetScreenPos((D3DXVECTOR2)this->pos);
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
		CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

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
		Object->SetScreenPos((D3DXVECTOR2)this->pos);
		// 四分木に入れる
		PaintManager::Quadtree->InsertObject(Object);

		// 使用しているインクの色に合わせて表示時間、テクスチャをセット
		Object->SetTime(DRAW_FRAME_COLOR);

		// Vectorに入れる
		this->ColorPaint.push_back(Object);
	}
}

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
