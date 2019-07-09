//=============================================================================
//
// カウントダウン処理 [CountDown.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "CountDown.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_COUNTDOWN	("data/TEXTURE/countdown.png")
#define COUNTDOWN_SIZE		D3DXVECTOR2(360.0f, 360.0f)
#define COUNTDOWN_DIVIDE_Y	(4)
#define COUNTDOWN_POS		D3DXVECTOR3(SCREEN_WIDTH / 2 - COUNTDOWN_SIZE.x / 2, SCREEN_HEIGHT / 2 - COUNTDOWN_SIZE.y / 2, 0.0f)
#define START_TIMER			(240)
#define SECOND_PER_FRAME	(60)


//=============================================================================
// コンストラクタ
//=============================================================================
CountDown::CountDown()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
		TEXTURE_COUNTDOWN,				// ファイルの名前
		&D3DTexture);					// 読み込むメモリのポインタ

	use = true;
	pos = COUNTDOWN_POS;
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
	// テクスチャの開放
	SAFE_RELEASE(D3DTexture);
}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void CountDown::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定(ポリゴンの描画前に読み込んだテクスチャのセットを行う)
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何もはらないことを指定するpDevide->SetTexture(0, NULL);
		Device->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT CountDown::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, 1.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y, 1.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + COUNTDOWN_SIZE.y, 1.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y + COUNTDOWN_SIZE.y, 1.0f);

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
	SetTexture();

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void CountDown::SetTexture()
{
	float sizeY = 1.0f / COUNTDOWN_DIVIDE_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, (float)(startsecond)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, (float)(startsecond)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, (float)(startsecond)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, (float)(startsecond)* sizeY + sizeY);
}