//=============================================================================
//
// インクゲージ表示処理 [Ink.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Ink.h"

//=============================================================================
// コンストラクタ
//=============================================================================
INK::INK(PLAYER *pP, D3DXVECTOR3 _pos, const char *texno, int _inktype)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		texno,				// ファイルの名前
		&D3DTexture);				// 読み込むメモリのポインタ

	///////////////////////////////////////////////////////////////////////////////////////
	// インクの初期化
	use = true;
	pos = _pos;
	PatternAnim = 1;
	pPlayer = pP;
	inktype = _inktype;

	// 頂点情報の作成
	MakeVertex();
	///////////////////////////////////////////////////////////////////////////////////////
}

//=============================================================================
// デストラクタ
//=============================================================================
INK::~INK()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void INK::Update()
{
	if (use == true)
	{

		//テクスチャ座標をセット
		SetTexture(PatternAnim);

	}
	SetVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void INK::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定(ポリゴンの描画前に読み込んだテクスチャのセットを行う)
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何もはらないことを指定するpDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT INK::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertex();

	// rhwの設定
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void INK::SetTexture(int cntPattern)
{
	int x = cntPattern;
	int y = cntPattern;
	float sizeX = 1.0f;
	float sizeY = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX * ((float)pPlayer->GetInkValue(inktype) / INK_MAX), (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX * ((float)pPlayer->GetInkValue(inktype) / INK_MAX), (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void INK::SetVertex()
{	
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + INK_SIZE.x * ((float)pPlayer->GetInkValue(inktype) / INK_MAX), pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + INK_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + INK_SIZE.x * ((float)pPlayer->GetInkValue(inktype) / INK_MAX), pos.y + INK_SIZE.y, pos.z);
}

