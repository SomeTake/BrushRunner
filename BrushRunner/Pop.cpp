//=============================================================================
//
// ポップアップ表示処理 [Pop.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Pop.h"
#include "Camera.h"

LPDIRECT3DTEXTURE9	POP::D3DTexture = NULL;	// テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
POP::POP(int _ctrlNum, PLAYER *pP)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertex();

	// テクスチャの初期化
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_POP,						// ファイルの名前
			&D3DTexture);					// 読み込むメモリー
	}

	pPlayer = pP;
	pos = pPlayer->GetPos() + POP_POS;
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	width = POP_WIDTH;
	height = POP_HEIGHT;
	patternAnim = _ctrlNum;

}

//=============================================================================
// デストラクタ
//=============================================================================
POP::~POP()
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
// 更新処理
//=============================================================================
void POP::Update()
{
	pos = pPlayer->GetPos() + POP_POS;

}

//=============================================================================
// 描画処理
//=============================================================================
void POP::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX WorldMtx, ViewMtx, SclMtx, TransMtx;
	CAMERA *cameraWk = GetCamera();

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMtx);

	// ビューマトリックスを取得
	ViewMtx = cameraWk->mtxView;

	// ポリゴンを正面に向ける
#if 1
	// 逆行列をもとめる
	D3DXMatrixInverse(&WorldMtx, NULL, &ViewMtx);
	WorldMtx._41 = 0.0f;
	WorldMtx._42 = 0.0f;
	WorldMtx._43 = 0.0f;
#else
	WorldMtx._11 = mtxView._11;
	WorldMtx._12 = mtxView._21;
	WorldMtx._13 = mtxView._31;
	WorldMtx._21 = mtxView._12;
	WorldMtx._22 = mtxView._22;
	WorldMtx._23 = mtxView._32;
	WorldMtx._31 = mtxView._13;
	WorldMtx._32 = mtxView._23;
	WorldMtx._33 = mtxView._33;
#endif

	// スケールを反映
	D3DXMatrixScaling(&SclMtx, scl.x,
		scl.y,
		scl.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// 移動を反映
	D3DXMatrixTranslation(&TransMtx, pos.x,
		pos.y,
		pos.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &TransMtx);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtx);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT POP::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,				// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-POP_WIDTH / 2.0f, POP_HEIGHT / 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(POP_WIDTH / 2.0f, POP_HEIGHT / 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-POP_WIDTH / 2.0f,-POP_HEIGHT / 2.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(POP_WIDTH / 2.0f, -POP_HEIGHT / 2.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		int x = patternAnim % POP_DIVIDE_X;
		int y = patternAnim / POP_DIVIDE_X;
		float sizeX = 1.0f / POP_DIVIDE_X;
		float sizeY = 1.0f / POP_DIVIDE_Y;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}