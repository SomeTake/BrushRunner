//=============================================================================
//
// フィールドオブジェクトチップ処理 [ObjectChip.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ObjectChip.h"
#include "Map.h"
#include "Camera.h"

//*****************************************************************************
// メンバの初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9	ObjectChip::D3DTexture = NULL;		// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
ObjectChip::ObjectChip(int x, int y, int texnum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・回転・スケールの初期設定
	pos.x = MAP_POS.x + x * CHIP_SIZE;
	pos.y = MAP_POS.y - y * CHIP_SIZE;
	pos.z = -0.01f;
	rot = MAP_ROT;	// 縦に向ける
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;

	// 頂点情報の作成
	MakeVertex(texnum);

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			CHIP_TEXTURE,					// ファイルの名前
			&D3DTexture);				// 読み込むメモリー
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
ObjectChip::~ObjectChip()
{
	if (D3DTexture != NULL)
	{// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{// 頂点バッファの開放
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}

//=============================================================================
// 更新
//=============================================================================
void ObjectChip::Update()
{
	CheckOnCamera();
}

//=============================================================================
// 描画
//=============================================================================
void ObjectChip::Draw()
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
		pDevice->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT ObjectChip::MakeVertex(int texnum)
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
		pVtx[0].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, 0.0f, CHIP_SIZE / 2);
		pVtx[1].vtx = D3DXVECTOR3(CHIP_SIZE / 2, 0.0f, CHIP_SIZE / 2);
		pVtx[2].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, 0.0f, -CHIP_SIZE / 2);
		pVtx[3].vtx = D3DXVECTOR3(CHIP_SIZE / 2, 0.0f, -CHIP_SIZE / 2);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
			int x = texnum % CHIP_DIVIDE_X;
			int y = texnum / CHIP_DIVIDE_X;
			float sizeX = 1.0f / CHIP_DIVIDE_X;
			float sizeY = 1.0f / CHIP_DIVIDE_Y;

			pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		}

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// カメラ内判定
//=============================================================================
void ObjectChip::CheckOnCamera()
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