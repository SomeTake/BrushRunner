//=============================================================================
//
// バトル画面フレーム表示処理 [Carsl_obj.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "carsl_obj.h"
#include "carsl_obj2.h"
#include "Input.h"
#include "carslobj.h"
int char01;
bool ao,aka,midori,ki;

//=============================================================================
// コンストラクタ
//=============================================================================
Carsl_obj::Carsl_obj(D3DXVECTOR3 _pos, const char *texno)
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
	ao = false;
	aka = false;
	midori = false;
	ki = false;
	if (texno == TEXTURE_CARSLOBJ)
	{
		char1 = AO;
		char01 = char1;
	}
	else if (texno == TEXTURE_CARSLOBJ2)
	{
		char1 = AKA;
		char01 = char1;
	}
	else if (texno == TEXTURE_CARSLOBJ3)
	{
		char1 = MIDORI;
		char01 = char1;
	}
	else if (texno == TEXTURE_CARSLOBJ4)
	{
		char1 = KI;
		char01 = char1;
	}
	PatternAnim = 1;
	// 頂点情報の作成
	MakeVertex();
	///////////////////////////////////////////////////////////////////////////////////////
}

//=============================================================================
// デストラクタ
//=============================================================================
Carsl_obj::~Carsl_obj()
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
void Carsl_obj::Update()
{
	if (use == true)
	{		
		//テクスチャ座標をセット
		SetTexture(PatternAnim);
	}
	if (Getpnum() == 0)
	{
		if (pos == CARSL_OBJ_POS01)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ_POS02;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ_POS04;
			}
			if (char1 == AO)
			{
				ao = true;
				aka = false;
				midori = false;
				ki = false;
			}
			else if (char1 == AKA)
			{
				aka = true;

				ao = false;
				midori = false;
				ki = false;
			}
			else if (char1 == MIDORI)
			{
				midori = true;
				aka = false;
				ao = false;
				ki = false;
			}
			else if (char1 == KI)
			{
				ki = true;
				ao = false;
				aka = false;
				midori = false;
			}
		}
		else if (pos == CARSL_OBJ_POS02)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ_POS03;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ_POS01;
			}
		}
		else if (pos == CARSL_OBJ_POS03)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ_POS04;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ_POS02;
			}
		}
		else if (pos == CARSL_OBJ_POS04)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ_POS01;
			}	
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ_POS03;
			}

		}
			if (GetKeyboardRelease(DIK_RETURN))
			{
				Setpnum(1);
			}
	}
	SetVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void Carsl_obj::Draw()
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
HRESULT Carsl_obj::MakeVertex(void)
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
void Carsl_obj::SetTexture(int cntPattern)
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
void Carsl_obj::SetVertex(void)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CARSL_OBJ_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ_SIZE.x, pos.y + CARSL_OBJ_SIZE.y, pos.z);
}
int Getchar1num(void)
{
	if (ao == true)
	{
		return AO;
	}
	else if (aka == true)
	{
		return AKA;
	}
	else if (midori == true)
	{
		return MIDORI;
	}
	else if (ki == true)
	{
		return KI;
	}
}
