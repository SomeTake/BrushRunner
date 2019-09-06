//=============================================================================
//
// 矢印 [Arrow.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Arrow.h"
#include "ResourceManager.h"
#include "Tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ARROW_SIZE	D3DXVECTOR3(128.0f, 128.0f, 0.0f)
#define ARROW_POS	D3DXVECTOR3((float)SCREEN_WIDTH - ARROW_SIZE.x / 2, (float)SCREEN_CENTER_Y, 0.0f)
#define ARROW_REVERSE_POS	D3DXVECTOR3(ARROW_SIZE.x / 2, (float)SCREEN_CENTER_Y, 0.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
Arrow::Arrow(bool reverse)
{
	ResourceManager::Instance()->GetTexture("Arrow", &D3DTexture);

	this->reverse = reverse;
	size = ARROW_SIZE;
	reverse ? pos = ARROW_REVERSE_POS : pos = ARROW_POS;
	use = true;
	draw = true;

	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
Arrow::~Arrow()
{
	D3DTexture = NULL;
}

//=============================================================================
// 更新
//=============================================================================
void Arrow::Update()
{
	if (!use)
		return;

	if (reverse)
	{
		if (Tutorial::GetSlideNo() == 0)
		{
			draw = false;
		}
		else
		{
			draw = true;
		}
	}
	else
	{
		if (Tutorial::GetSlideNo() == 2)
		{
			draw = false;
		}
		else
		{
			draw = true;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void Arrow::Draw()
{
	if (!use || !draw)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, D3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void Arrow::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, pos.z);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		// rhwの設定
		vertexWk[i].rhw = 1.0f;
		// 反射光の設定
		vertexWk[i].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// テクスチャ座標の設定
	if (reverse)
	{
		vertexWk[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexWk[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexWk[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		vertexWk[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}
	else
	{
		vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

}