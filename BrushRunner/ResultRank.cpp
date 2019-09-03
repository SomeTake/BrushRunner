//=============================================================================
//
// プレイヤー順位 [ResultRank.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ResultRank.h"
#include "Player.h"

//*****************************************************************************
// 構造体データ入力
//*****************************************************************************
ResultStr Rank[PLAYER_MAX] = {
	D3DXVECTOR3(250.0f, 70.0f, 0.0f), D3DXVECTOR3(300.0f, 150.0f, 0.0f),
	D3DXVECTOR3(250.0f, 400.0f, 0.0f), D3DXVECTOR3(180.0f, 90.0f, 0.0f),
	D3DXVECTOR3(260.0f, 510.0f, 0.0f), D3DXVECTOR3(140.0f, 70.0f, 0.0f),
	D3DXVECTOR3(260.0f, 590.0f, 0.0f), D3DXVECTOR3(140.0f, 70.0f, 0.0f),
};

//*****************************************************************************
// メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9	ResultRank::D3DTexture = NULL;	// テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
ResultRank::ResultRank(int rank)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->use = true;
	this->rank = rank;
	pos = Rank[this->rank].pos;
	size = Rank[this->rank].size;

	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			RESULTRANK_TEXTURE,				// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}

	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
ResultRank::~ResultRank()
{
	SAFE_RELEASE(D3DTexture);
}

//=============================================================================
// 更新
//=============================================================================
void ResultRank::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void ResultRank::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定（ポリゴンの描画前に読み込んだテクスチャのセットを行う）
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何も貼らないことを指定するpDevice->SetTexture(0,NULL);
		pDevice->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT ResultRank::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + size.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);

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
	int x = rank % RESULTRANK_DIVIDE_X;
	int y = rank / RESULTRANK_DIVIDE_X;
	float sizeX = 1.0f / RESULTRANK_DIVIDE_X;
	float sizeY = 1.0f / RESULTRANK_DIVIDE_Y;

	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	return S_OK;
}