//=============================================================================
//
// CharacterAIクラス[CharacterAI.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "CharacterAI.h"
#include "Map.h"
#include "PaintManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ScanRange (5)


#if _DEBUG
// ３Ｄ直線頂点フォーマット( 頂点座標[3D] / 反射光 )
#define	FVF_LINE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif

enum e_ChipNo
{
	eJumpChip = -2,
	eDetermineChip = -3,
	ePlatformEdge = -4
};

#if _DEBUG
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
CharacterAI::CharacterAI()
{
}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
CharacterAI::~CharacterAI()
{

}

void CharacterAI::Update(D3DXVECTOR3 Pos)
{
	int MapChipNo = Map::GetMapTbl(Pos, eCenterUp);
	this->Action = eNoAction;
	this->DrawLineFlag = false;

	switch (MapChipNo)
	{
	case eJumpChip:

		this->Action = eActJump;
		break;

	case eDetermineChip:

		this->FindPlatform(Pos);
		break;

	default:
		break;
	}
}

void CharacterAI::FindPlatform(D3DXVECTOR3 Pos)
{
	int PlayerChip_X = 0;
	int PlayerChip_Y = 0;
	Map::GetMapChipXY(Pos, &PlayerChip_X, &PlayerChip_Y);

	// スキャンできる横幅の範囲
	for (int i = PlayerChip_X + 1; i <= PlayerChip_X + ScanRange; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			int k = Map::GetMapTbl(i, j);
			if (k == ePlatformEdge)
			{
				// 探したプラットフォームの座標
				this->PaintEndPos = Map::GetMapChipPos(i, j + 1, eLeftUp);
				// キャラクター下のチップの座標
				this->PaintStartPos = Map::GetMapChipPos(PlayerChip_X + 1, PlayerChip_Y, eRightUp);
				this->State = eCursorMove;
#if _DEBUG
				this->DrawLineFlag = true;
#endif
			}
		}
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
