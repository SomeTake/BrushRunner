//=============================================================================
//
// バトル画面フレーム表示処理 [Carsl_obj3.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Input.h"
#include "carslobj.h"
#include "carsl_obj3.h"
bool ao3, aka3, midori3, ki3;
//=============================================================================
// コンストラクタ
//=============================================================================
Carsl_obj3::Carsl_obj3(D3DXVECTOR3 _pos, const char *texno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		texno,				// ファイルの名前
		&D3DTexture);				// 読み込むメモリのポインタ

									///////////////////////////////////////////////////////////////////////////////////////
									// フレームの初期化
	use = true;
	pos = _pos;
	char3 = AO;
	PatternAnim = 1;
	ao3 = false;
	aka3 = false;
	midori3 = false;
	ki3 = false;
	if (texno == TEXTURE_CARSLOBJ)
	{
		char3 = AO;
	}
	else if (texno == TEXTURE_CARSLOBJ2)
	{
		char3 = AKA;
	}
	else if (texno == TEXTURE_CARSLOBJ3)
	{
		char3 = MIDORI;
	}
	else if (texno == TEXTURE_CARSLOBJ4)
	{
		char3 = KI;
	}
	// 頂点情報の作成
	MakeVertex();
	///////////////////////////////////////////////////////////////////////////////////////

}

//=============================================================================
// デストラクタ
//=============================================================================
Carsl_obj3::~Carsl_obj3()
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
void Carsl_obj3::Update()
{
	if (use == true)
	{
		//テクスチャ座標をセット
		SetTexture(PatternAnim);
	}
	if (Getpnum() == 2)
	{
		if (pos == CARSL_OBJ3_POS01)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				Setch(true);
				pos = CARSL_OBJ3_POS02;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				Setch(true);
				pos = CARSL_OBJ3_POS04;
			}
			if (char3 == AO)
			{
				ao3 = true;
				aka3 = false;
				midori3 = false;
				ki3 = false;
			}
			else if (char3 == AKA)
			{
				aka3 = true;
				ao3 = false;
				midori3 = false;
				ki3 = false;
			}
			else if (char3 == MIDORI)
			{
				midori3 = true;
				aka3 = false;
				ao3 = false;
				ki3 = false;
			}
			else if (char3 == KI)
			{
				ki3 = true;
				ao3 = false;
				aka3 = false;
				midori3 = false;
			}
		}
		else if (pos == CARSL_OBJ3_POS02)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ3_POS03;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ3_POS01;
			}
		}
		else if (pos == CARSL_OBJ3_POS03)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ3_POS04;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ3_POS02;
			}
		}
		else if (pos == CARSL_OBJ3_POS04)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ3_POS01;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ3_POS03;
			}
		}
	}
	SetVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void Carsl_obj3::Draw()
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
// 頂点の作成
//=============================================================================
HRESULT Carsl_obj3::MakeVertex(void)
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
void Carsl_obj3::SetTexture(int cntPattern)
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
void Carsl_obj3::SetVertex(void)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ3_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CARSL_OBJ3_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ3_SIZE.x, pos.y + CARSL_OBJ3_SIZE.y, pos.z);
}

int Getchar3num()
{
	if (ao3 == true)
	{
		return AO;
	}
	else if (aka3 == true)
	{
		return AKA;
	}
	else if (midori3 == true)
	{
		return MIDORI;
	}
	else if (ki3 == true)
	{
		return KI;
	}
}