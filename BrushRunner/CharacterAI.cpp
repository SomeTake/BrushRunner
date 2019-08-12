//=============================================================================
//
// CharacterAIクラス[CharacterAI.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "CharacterAI.h"
#include "Map.h"
#include "Item.h"
#include "SceneGame.h"
#include "Input.h"
#include "DebugWindow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
PaintGroup *CharacterAI::paintGroup = nullptr;

#define ScanRange (10)		// プラットフォームのへりが探せる範囲

// CSV中の番号の事件
enum e_ChipEvent
{
	eRandomChip = -2,		// ペイント、落下のどちらかランダムで決める
	eJumpChip = -3,			// ジャンプする
	ePaintChip = -4,		// ジャンプする
	ePlatformEdge = -5		// 向こうのプラットフォームのへり
};

#if _DEBUG
// 3D直線頂点フォーマット( 頂点座標[3D] / 反射光 )
#define	FVF_LINE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

// 3D空間で直線描画用構造体を定義
typedef struct
{
	D3DXVECTOR3 Point;
	D3DCOLOR	Color;
} VERTEX_3DLINE;
#endif

//=====================================================================================================
// コンストラクタ
//=====================================================================================================
CharacterAI::CharacterAI(int Owner)
{
	this->Owner = Owner;
}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
CharacterAI::~CharacterAI()
{

}

//=====================================================================================================
// 更新処理
//=====================================================================================================
void CharacterAI::Update(D3DXVECTOR3 Pos)
{
	int MapChipNo = Map::GetMapTbl(Pos, eCenterUp);
	this->Action = eNoAction;
#if _DEBUG
	this->DrawLineFlag = false;
#endif

	// マップチップの番号によって行動する
	MapChipAction(Pos, MapChipNo);

	// 画面内のペイントを探して、ペイントする
	if (CursorState != ePaintPath && GetKeyboardTrigger(DIK_V))
	{
		PaintAction();
	}

	// アイテムを持っていたら、アイテムを使用する
	if (HaveItem)
	{
		ItemAction();
	}

#if _DEBUG
	ImGui::SetNextWindowPos(ImVec2(5, 330), ImGuiSetCond_Once);

	BeginDebugWindow("AI");

	DebugText("Action : %d", this->Action);
	DebugText("State : %d", this->CursorState);

	EndDebugWindow("AI");
#endif
}

//=====================================================================================================
// マップチップの番号によって行動する
//=====================================================================================================
void CharacterAI::MapChipAction(D3DXVECTOR3 Pos, int MapChipNo)
{
	// フラグの初期化
	if (MapChipNo != eRandomChip)
	{
		RandomOver = false;
		if (MapChipNo != ePaintChip)
		{
			FindEdgeOver = false;
		}
	}

	if (MapChipNo == eRandomChip && !RandomOver)
	{
		int Random = rand() % (1 + 1);

		// ペイント
		if (Random == 0)
		{
			// プラットフォームのへりを探す
			this->FindPlatform(Pos);
		}
		// 落下
		else if (Random == 1)
		{
			int i = 0;
			;	// 現在は何もしない
		}

		RandomOver = true;
	}
	else if (MapChipNo == eJumpChip)
	{
		// ジャンプする
		this->Action = eActJump;
	}
	else if (MapChipNo == ePaintChip)
	{
		// プラットフォームのへりを探す
		this->FindPlatform(Pos);
	}
}

//=====================================================================================================
// 他のプレイヤーのペイントを探して、削除する
//=====================================================================================================
void CharacterAI::PaintAction(void)
{
	if (!FindEnemyPaint)
	{
		if (CharacterAI::paintGroup->GetEnemyPaint(&EnemyPaint, Owner))
		{
			CursorState = eUseBlackPaint;
			if (InkType != BlackInk)
			{
				ChangeInk = true;
				InkType = BlackInk;
			}
			FindEnemyPaint = true;
		}
	}
}

//=====================================================================================================
// アイテムを使用する
//=====================================================================================================
void CharacterAI::ItemAction(void)
{
	bool ItemTrigger = false;
	static int Count = 0;
	static int Bonus = 0;

	switch (ItemType)
	{
		// ジェットパック
	case NumJet:
		// パワーアップバナナ
	case NumPowerUp:
		// スペシャルインク
	case NumSpInk:
		// ブラインド
	case NumBlind:

		Count++;
		// 2秒ごとに判定する
		if (Count % 120 == 0)
		{
			int Rand = rand() % (10 + 1);
			if (Rand + Bonus > 5)
			{
				// アイテムを使用する
				ItemTrigger = true;
			}
			else
			{
				// 使用しないが、時間によって使用する確率が高くなる
				Bonus++;
			}
		}
		break;

		// スパイクブーツ
	case NumSpike:

		break;

		// バナナの皮
	case NumKawa:

		// 最下位じゃなくて、後ろに他のプレイヤーがいるならバナナの皮を使う
		if (SceneGame::GetTheLastPlayer() != Owner)
		{
			// アイテムを使用する
			ItemTrigger = true;
		}
		else
		{
			Count++;
			// 2秒ごとに判定する
			if (Count % 120 == 0)
			{
				int Rand = rand() % (10 + 1);
				if (Rand + Bonus > 5)
				{
					// アイテムを使用する
					ItemTrigger = true;
				}
				else
				{
					// 使用しないが、時間によって使用する確率が高くなる
					Bonus++;
				}
			}
		}

		break;

		// トリモチガン
	case NumGun:

		Count++;
		// 1.5秒ごとに判定する
		if (Count % 90 == 0 || Bonus >= 10)
		{
			if (ShotBullet)
			{
				// アイテムを使用する
				ItemTrigger = true;
				ShotBullet = false;
			}
			else
			{
				// 使用しないが、時間によって使用する確率が高くなる
				Bonus++;
			}
		}
		break;

	default:
		break;
	}

	// アイテムを使用する
	if (ItemTrigger)
	{
		HaveItem = false;
		UseItem = true;
		Count = 0;
		Bonus = 0;
	}
}

//=====================================================================================================
// 向こうのプラットフォームを探す
//=====================================================================================================
void CharacterAI::FindPlatform(D3DXVECTOR3 Pos)
{
	int PlayerChip_X = 0;
	int PlayerChip_Y = 0;
	Map::GetMapChipXY(Pos, &PlayerChip_X, &PlayerChip_Y);
	std::vector<D3DXVECTOR3> TempPos;

	if (FindEdgeOver)
	{
		return;
	}

	// スキャンできる横幅の範囲
	for (int i = PlayerChip_X + 1; i <= PlayerChip_X + ScanRange; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			int k = Map::GetMapTbl(i, j);
			if (k == ePlatformEdge)
			{
				// 探したプラットフォームの座標
				TempPos.push_back(Map::GetMapChipPos(i, j + 1, eLeftUp));
				// キャラクター下のチップの座標
				PaintStartPos = Map::GetMapChipPos(PlayerChip_X + 1, PlayerChip_Y, eRightUp);
				CursorState = ePaintPath;
				if (InkType != ColorInk)
				{
					ChangeInk = true;
					InkType = ColorInk;
				}
				FindEdgeOver = true;

#if _DEBUG
				DrawLineFlag = true;
#endif
			}
		}
	}

	// もし複数のプラットフォームがあれば、ランダムで決める
	if (TempPos.size() > 1)
	{
		int Random = rand() % TempPos.size();
		PaintEndPos = TempPos.at(Random);
	}
	else if (TempPos.size() == 1)
	{
		PaintEndPos = TempPos.at(0);
	}
}

#if _DEBUG
//=============================================================================
// 描画処理
//=============================================================================
void CharacterAI::Draw(void)
{
	if (this->DrawLineFlag)
	{
		DrawLine3D(this->PaintStartPos, this->PaintEndPos);
	}
}

//=============================================================================
// 3D直線描画
//=============================================================================
void CharacterAI::DrawLine3D(D3DXVECTOR3 P1, D3DXVECTOR3 P2)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX WorldMatrix;
	LPDIRECT3DVERTEXBUFFER9 LineVtxBuffer;		// 直線描画用頂点バッファ
	VERTEX_3DLINE *pVtx;

	// 直線描画用頂点バッファを生成
	Device->CreateVertexBuffer(
		sizeof(VERTEX_3DLINE) * 2,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
		FVF_LINE_3D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&LineVtxBuffer,					// 頂点バッファインターフェースへのポインタ
		NULL);							// NULLに設定

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	LineVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].Point = P1;
	pVtx[1].Point = P2;

	// 色の設定
	pVtx[0].Color = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].Color = D3DCOLOR_RGBA(0, 0, 0, 255);

	// 頂点データをアンロックする
	LineVtxBuffer->Unlock();

	// ラインティングを無効にする
	Device->SetRenderState(D3DRS_LIGHTING, false);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMatrix);

	// ワールドマトリックスの設定
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// 頂点バッファをレンダリングパイプラインに設定
	Device->SetStreamSource(0, LineVtxBuffer, 0, sizeof(VERTEX_3DLINE));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_LINE_3D);

	// テクスチャの設定
	Device->SetTexture(0, NULL);

	// ポリゴンの描画
	Device->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ラインティングを有効にする
	Device->SetRenderState(D3DRS_LIGHTING, true);

	SAFE_RELEASE(LineVtxBuffer);

	return;
}

#endif
