//=============================================================================
//
// キャラクターセレクトロゴ [SelectLogo.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "carslobj.h"
#include "SelectLogo.h"
#include "ResourceManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECTLOGO_SIZE		D3DXVECTOR3(512.0f, 128.0f, 0.0f)		// テクスチャサイズ
#define FLASH_TIME			(45)
#define DELETE_TIME			(30)

//=============================================================================
// コンストラクタ
//=============================================================================
SelectLogo::SelectLogo()
{
	ResourceManager::Instance()->GetTexture("SelectLogo", &D3DTexture);

	use = true;
	pos = D3DXVECTOR3((float)SCREEN_CENTER_X - SELECTLOGO_SIZE.x / 2, 0.0f, 0.0f);
	cntFlash = 0;
	flash = true;

	PatternAnim = 1;
	// 頂点情報の作成
	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
SelectLogo::~SelectLogo()
{
	// リソースの開放はリソースマネージャに任せるので、参照をやめるだけ
	D3DTexture = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void SelectLogo::Update()
{
	if (!use)
		return;

	// 点滅処理
	cntFlash++;

	// 表示中に一定フレーム経過で消滅
	if (flash && cntFlash == FLASH_TIME)
	{
		flash = false;
		cntFlash = 0;
	}
	// 消滅中に一定フレーム経過で表示
	else if (!flash && cntFlash == DELETE_TIME)
	{
		flash = true;
		cntFlash = 0;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void SelectLogo::Draw()
{
	// 使用していないor点滅中は表示しない
	if (!use || !flash)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, D3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT SelectLogo::MakeVertex(void)
{
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
	SetTexture(PatternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SelectLogo::SetTexture(int cntPattern)
{
	int x = cntPattern;
	int y = cntPattern;
	float sizeX = 1.0f;
	float sizeY = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SelectLogo::SetVertex(void)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + SELECTLOGO_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + SELECTLOGO_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + SELECTLOGO_SIZE.x, pos.y + SELECTLOGO_SIZE.y, pos.z);
}
