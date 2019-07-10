//=============================================================================
//
// チップ処理 [Chip.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Chip.h"
#include "Camera.h"
#include "Map.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHIP_TEXTURE	("data/MAP/tilea5.png")
#define OBJECT_TEXTURE	("data/MAP/mapchip_object.png")
//#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 表示場所
//#define MAP_ROT			D3DXVECTOR3(D3DXToRadian(-90), 0.0f, 0.0f)	// 回転
#define CHIP_DIVIDE_X	(8)
#define CHIP_DIVIDE_Y	(16)

#define OBJ_DIVIDE_X	(7)
#define OBJ_DIVIDE_Y	(1)

#define REVERSE_TIME	(300)	// 反転時間

//*****************************************************************************
// メンバの初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9	Chip::D3DTextureMap = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9	Chip::D3DTextureObj = NULL;		// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
Chip::Chip(int x, int y, int _texnum, int ChipType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・回転・スケールの初期設定
	pos.x = x * CHIP_SIZE;
	pos.y = -(y * CHIP_SIZE);
	pos.z = 0.0f;
	//rot = MAP_ROT;	// 縦に向ける
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;
	this->ChipType = ChipType;
	texnum = _texnum;
	cnt = 0;
	reverse = false;
	mapX = x;
	mapY = y;

	// 頂点情報の作成
	MakeVertex();

	// テクスチャの読み込み
	if (D3DTextureMap == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			CHIP_TEXTURE,					// ファイルの名前
			&D3DTextureMap);				// 読み込むメモリー
	}
	if (D3DTextureObj == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			OBJECT_TEXTURE,					// ファイルの名前
			&D3DTextureObj);				// 読み込むメモリー
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
Chip::~Chip()
{
	// 頂点バッファの開放
	SAFE_RELEASE(this->D3DVtxBuff);
}

//=============================================================================
// 更新
//=============================================================================
void Chip::Update()
{
	CheckOnCamera();

	// 反転中の処理
	if (use && reverse)
	{
		cnt++;

		if (cnt == REVERSE_TIME)
		{
			cnt = 0;
			reverse = false;
			ReverseTexture();
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void Chip::Draw()
{
	if (use)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(Vertex3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		if (ChipType == eMapChip)
		{
			pDevice->SetTexture(0, D3DTextureMap);
		}
		else if (ChipType == eObjectChip)
		{
			pDevice->SetTexture(0, D3DTextureObj);
		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT Chip::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(Vertex3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		Vertex3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, CHIP_SIZE / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(CHIP_SIZE / 2, CHIP_SIZE / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, -CHIP_SIZE / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(CHIP_SIZE / 2, -CHIP_SIZE / 2, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		if (texnum < 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		else
		{
			if (ChipType == eMapChip)
			{
				int x = texnum % CHIP_DIVIDE_X;
				int y = texnum / CHIP_DIVIDE_X;
				float sizeX = 1.0f / CHIP_DIVIDE_X;
				float sizeY = 1.0f / CHIP_DIVIDE_Y;

				pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
				pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
				pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
				pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			}
			else if (ChipType == eObjectChip)
			{
				float sizeX = 1.0f / OBJ_DIVIDE_X;

				pVtx[0].tex = D3DXVECTOR2((float)texnum * sizeX, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((float)texnum * sizeX + sizeX, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((float)texnum * sizeX, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((float)texnum * sizeX + sizeX, 1.0f);
			}
		}

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標のセット
//=============================================================================
void Chip::SetTexture()
{
	{//頂点バッファの中身を埋める
		Vertex3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標の設定
		if (texnum < 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		else
		{
			if (ChipType == eMapChip)
			{
				int x = texnum % CHIP_DIVIDE_X;
				int y = texnum / CHIP_DIVIDE_X;
				float sizeX = 1.0f / CHIP_DIVIDE_X;
				float sizeY = 1.0f / CHIP_DIVIDE_Y;

				pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
				pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
				pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
				pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			}
			else if (ChipType == eObjectChip)
			{
				float sizeX = 1.0f / OBJ_DIVIDE_X;

				pVtx[0].tex = D3DXVECTOR2((float)texnum * sizeX, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((float)texnum * sizeX + sizeX, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((float)texnum * sizeX, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((float)texnum * sizeX + sizeX, 1.0f);
			}
		}

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

}

//=============================================================================
// カメラ内判定
//=============================================================================
void Chip::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// 描画範囲判定
	// 縦
	if ((pos.x > camera->at.x - DRAW_RANGE.x) && (pos.x < camera->at.x + DRAW_RANGE.x))
	{
		// 横
		if ((pos.y > camera->at.y - DRAW_RANGE.y) && (pos.y < camera->at.y + DRAW_RANGE.y))
		{
			use = true;
		}
		else
		{
			use = false;
		}
	}
	else
	{
		use = false;
	}
}

//=============================================================================
// テクスチャを反転させる
//=============================================================================
void Chip::ReverseTexture()
{
	switch (texnum)
	{
	case eObjSpdup:
		texnum = eObjSpddown;
		break;
	case eObjSpddown:
		texnum = eObjSpdup;
		break;
	case eObjDrain:
		texnum = eObjHeal;
		break;
	case eObjHeal:
		texnum = eObjDrain;
		break;

	default:
		break;
	}

	// オブジェクトテーブルの中身も変更する
	Map::SetObjTbl(mapX, mapY, texnum);
	SetTexture();
}