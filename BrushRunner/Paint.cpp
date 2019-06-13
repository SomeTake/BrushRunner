//=============================================================================
//
// ペイント [Paint.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Paint.h"
#include "Camera.h"
#include "Debugproc.h"

//*****************************************************************************
// メンバの初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9	PAINT::D3DTexture = NULL;		// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
PAINT::PAINT()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertex();

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_PAINT,					// ファイルの名前
			&D3DTexture);					// 読み込むメモリー
	}
	
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	width = PAINT_WIDTH;
	height = PAINT_HEIGHT;
	use = false;
	time = 0;
	patternAnim = 0;
	DecAlpha = 0.1f;
}

//=============================================================================
// デストラクタ
//=============================================================================
PAINT::~PAINT()
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
void PAINT::Update()
{
	// 使用しているもののみ更新
	if (use)
	{
		// 表示時間の更新
		if (time > 0)
		{
			time--;
		}
		// 表示時間を超えたら消滅処理
		else
		{
			// 透明度を減衰値に合わせて追加
			col.a -= DecAlpha;

			// 色の設定
			SetColor();

			if (col.a <= 0.0f)
			{
				// 透明になったら使用をやめる
				col.a = 0.0f;
				use = false;
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

		}

		SetTexture();

		PrintDebugProc("ペイント座標 X:%f Y:%f Z:%f\n", pos.x, pos.y ,pos.z);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void PAINT::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *cameraWk = GetCamera();
	D3DXMATRIX WorldMtx, ViewMtx, SclMtx, TransMtx;

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 減算合成 レンダリングステートの変更→黒っぽくなる（加算合成は白っぽくなる（255に近づけていくと））
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// 結果 = 転送先(DEST) - 転送元(SRC)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Zテスト
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// 通常ブレンド レンダリングステートをもとに戻す（戻さないと減算合成のままになる）
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (use)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&WorldMtx);

		// ビューマトリックスを取得
		ViewMtx = cameraWk->mtxView;

		// ポリゴンを正面に向ける
		WorldMtx._11 = ViewMtx._11;
		WorldMtx._12 = ViewMtx._21;
		WorldMtx._13 = ViewMtx._31;
		WorldMtx._21 = ViewMtx._12;
		WorldMtx._22 = ViewMtx._22;
		WorldMtx._23 = ViewMtx._32;
		WorldMtx._31 = ViewMtx._13;
		WorldMtx._32 = ViewMtx._23;
		WorldMtx._33 = ViewMtx._33;

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
	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// 通常ブレンド レンダリングステートをもとに戻す（戻さないと減算合成のままになる）
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z比較あり
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT PAINT::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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
		pVtx[0].vtx = D3DXVECTOR3(-PAINT_WIDTH / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-PAINT_WIDTH / 2.0f, PAINT_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAINT_WIDTH / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAINT_WIDTH / 2.0f, PAINT_HEIGHT, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void PAINT::SetVertex()
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

}

//=============================================================================
// 頂点カラーの設定 引数(nIdxParticle = 番号, col = 色)
//=============================================================================
void PAINT::SetColor()
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void PAINT::SetTexture()
{
	int x = patternAnim % PAINT_DIVIDE_X;
	int y = patternAnim / PAINT_DIVIDE_X;
	float sizeX = 1.0f / PAINT_DIVIDE_X;
	float sizeY = 1.0f / PAINT_DIVIDE_Y;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

}