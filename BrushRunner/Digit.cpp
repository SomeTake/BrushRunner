//=============================================================================
//
// 桁 [Digit.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Digit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DIGIT_SIZE		D3DXVECTOR3(30.0f, 50.0f, 0.0f)
#define DIGIT_POS		D3DXVECTOR3(SCREEN_CENTER_X + ((DIGIT_SIZE.x / 2) * DIGIT_MAX), 135.0f, 0.0f)	// 表示場所（1番右、1桁目を基準とする）
#define DIGIT_SPACE		(40.0f)	// 表示間隔（横）

//*****************************************************************************
// クラスのメンバ初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9	Digit::D3DTexture = NULL; // テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
Digit::Digit(int digit)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	use = true;
	time = 0;
	pos = DIGIT_POS;
	pos.x -= digit * DIGIT_SPACE;
	size = DIGIT_SIZE;

	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_DIGIT,					// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}

	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
Digit::~Digit()
{
	SAFE_RELEASE(Digit::D3DTexture);
}

//=============================================================================
// 更新
//=============================================================================
void Digit::Update(DWORD time)
{
	this->time = time;
	SetTexture();
}

//=============================================================================
// 描画
//=============================================================================
void Digit::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// Zテスト
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// αテストを有効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, TRUE);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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

	// αテストを無効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z比較あり
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT Digit::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z);

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
// テクスチャのセット
//=============================================================================
void Digit::SetTexture()
{
	int x = time % DIGIT_DIVIDE_X;
	int y = time / DIGIT_DIVIDE_X;
	float sizeX = 1.0f / DIGIT_DIVIDE_X;
	float sizeY = 1.0f / DIGIT_DIVIDE_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}