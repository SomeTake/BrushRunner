//=============================================================================
//
// カウントダウン処理 [CountDown.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "CountDown.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CountDown::CountDown()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_COUNTDOWN,				// ファイルの名前
		&D3DTexture);					// 読み込むメモリのポインタ

	use = true;
	pos = COUNTDOWN_POS;
	PatternAnim = 0;
	starttimer = 0;
	startsecond = 0;

	// 頂点情報の作成
	MakeVertex();

}

//=============================================================================
// デストラクタ
//=============================================================================
CountDown::~CountDown()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}

}

//=============================================================================
// 更新
//=============================================================================
void CountDown::Update()
{
	if (use)
	{
		if (starttimer < START_TIMER)
		{
			starttimer++;
			startsecond = starttimer / SECOND_PER_FRAME;

			SetTexture();
		}
		// カウントダウン終了
		else
		{
			use = false;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CountDown::Draw()
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
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT CountDown::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + COUNTDOWN_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y + COUNTDOWN_SIZE.y, pos.z);

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
// テクスチャ座標のセット
//=============================================================================
void CountDown::SetTexture()
{
	int x = startsecond % COUNTDOWN_DIVIDE_X;
	int y = startsecond / COUNTDOWN_DIVIDE_X;
	float sizeX = 1.0f / COUNTDOWN_DIVIDE_X;
	float sizeY = 1.0f / COUNTDOWN_DIVIDE_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}