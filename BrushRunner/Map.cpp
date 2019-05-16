//=============================================================================
//
// マップ処理 [Map.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Map.h"

using namespace std;

//=============================================================================
// コンストラクタ
//=============================================================================
MAP::MAP()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// csvデータ読み込み
	ReadCsv(MAP_FILE);

	// 位置・回転・スケールの初期設定
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(90.0f, 0.0f, 0.0f);	// 縦に向ける
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// 頂点情報の作成
	MakeVertex();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		MAP_TEXTURE1,			// ファイルの名前
		&D3DTexture);	// 読み込むメモリー

}

//=============================================================================
// デストラクタ
//=============================================================================
MAP::~MAP()
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
void MAP::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void MAP::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	for (int ySize = 0; ySize < MAP_SIZE_Y; ySize++)
	{
		for (int xSize = 0; xSize < MAP_SIZE_X; xSize++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, pos.x + (CHIP_SIZE * xSize), pos.y - (CHIP_SIZE * ySize), pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, D3DTexture);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}

//=============================================================================
// CSVファイルの読み込み
//=============================================================================
void MAP::ReadCsv(const char *data)
{
	ifstream stream(data);		// マップの読み込み先

	int row = 0;
	int col;
	while (getline(stream, line))
	{
		col = 0;
		// delimを区切り文字として切り分け、intに変換してmaptbl[][]に格納する
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;)
		{
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			maptbl[row][col++] = stoi(token);
		}
		++row;
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MAP::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-CHIP_SIZE, 0.0f, CHIP_SIZE);
		pVtx[1].vtx = D3DXVECTOR3(CHIP_SIZE, 0.0f, CHIP_SIZE);
		pVtx[2].vtx = D3DXVECTOR3(-CHIP_SIZE, 0.0f, -CHIP_SIZE);
		pVtx[3].vtx = D3DXVECTOR3(CHIP_SIZE, 0.0f, -CHIP_SIZE);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}