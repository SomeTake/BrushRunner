//=============================================================================
//
// エフェクト処理 [Effect.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Effect.h"


//=============================================================================
// コンストラクタ
//=============================================================================
EFFECT::EFFECT(const char *texture, D3DXVECTOR3 _size, D3DXVECTOR3 _pos , int _AnimationCnt, int _xPattern, int _yPattern) {
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DTexture = NULL;
	D3DVtxBuff = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		texture,							// ファイルの名前
		&D3DTexture);						// 読み込むメモリのポインタ

	// フレームの初期化
	use = true;
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CountAnim = 0;
	PatternAnim = 0;
	size = _size;
	pos = _pos;
	xPattern = _xPattern;
	yPattern = _yPattern;
	TexAnimNum = xPattern * yPattern;
	AnimationCnt = _AnimationCnt;

	// 頂点情報の作成
	MakeVertex();

}
//=============================================================================
// デストラクタ
//=============================================================================
EFFECT::~EFFECT() {

	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}
//=============================================================================
// 更新
//=============================================================================
void EFFECT::Update() {


	if (use == true)
	{
		// アニメーション
		CountAnim++;

		if ( ( CountAnim % AnimationCnt) == 0)
		{

			// パターンの切り替え
			PatternAnim = (PatternAnim + 1) % TexAnimNum;

			//テクスチャ座標をセット
			SetTexture(PatternAnim);

		}

	}

	// 頂点座標の設定
	SetVertex();

}
//=============================================================================
// 描画
//=============================================================================
void EFFECT::Draw() {

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
// 頂点情報の作成
//=============================================================================
HRESULT EFFECT::MakeVertex(void) {

	// 頂点座標の設定
	SetVertex();

	// テクスチャのパースペクティブコレクト用
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
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;

}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void EFFECT::SetTexture(int cntPattern) {

	int x = cntPattern % xPattern;
	int y = cntPattern / xPattern;
	float sizeX = 1.0f / xPattern;
	float sizeY = 1.0f / yPattern;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void EFFECT::SetVertex(void) {

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + size.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);

}