//=============================================================================
//
// バトル画面フレーム表示処理 [Faceframe.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Faceframe.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FACEFRAME	_T("data/texture/faceframe.png")		// フレーム用画像
#define FACEFRAME_SIZE		D3DXVECTOR3(100.0f, 88.0f, 0.0f)		// テクスチャサイズ
#define FACEFRAME_POS		D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define FACEFRAME_INTERVAL	(318.0f)

LPDIRECT3DTEXTURE9	FaceFrame::D3DTexture = NULL;	// テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
FaceFrame::FaceFrame(int PlayerNo)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	pos = FACEFRAME_POS + D3DXVECTOR3(FACEFRAME_INTERVAL * PlayerNo, 0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertex();

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_FACEFRAME,				// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
FaceFrame::~FaceFrame()
{

}

void FaceFrame::ReleaseTexture(void)
{
	SAFE_RELEASE(FaceFrame::D3DTexture);
}

//=============================================================================
// 更新処理
//=============================================================================
void FaceFrame::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void FaceFrame::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTexture);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT FaceFrame::MakeVertex(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点座標の設定
	SetVertex();

	// rhwの設定
	vertexWk[0].rhw = 1.0f;
	vertexWk[1].rhw = 1.0f;
	vertexWk[2].rhw = 1.0f;
	vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void FaceFrame::SetPlayerDeadTexture(void)
{
	vertexWk[0].tex = D3DXVECTOR2(0.5f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void FaceFrame::SetVertex(void)
{
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + FACEFRAME_SIZE.x, pos.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + FACEFRAME_SIZE.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + FACEFRAME_SIZE.x, pos.y + FACEFRAME_SIZE.y, 0.0f);
}
