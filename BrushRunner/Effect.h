//=============================================================================
//
// エフェクト処理 [Effect.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "_2dobj.h"

// エフェクトの種類
enum EffectNum{
	HitEffect,
	Hit1Effect,
	RunEffect,
	ExpEffect,
	ItemEffect,
	Item1Effect,

	// エフェクトの個数
	EffectMax,
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// エフェクトデータ構造体
struct EffectData
{
	const char *texture;	// テクスチャファイル
	D3DXVECTOR3 size;		// サイズ
	int count;				// 更新フレーム
	Int2D pattern;			// テクスチャ分割数(x,y)
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static EffectData EffectDataWk[EffectMax] =
{
	{"data/EFFECT/anmef000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(5, 1) },
{ "data/EFFECT/anmef001.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(1, 5) },
{ "data/EFFECT/anmef002.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(2, 2) },
{ "data/EFFECT/explo000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 3, Int2D(5, 3) },
{ "data/EFFECT/ief001.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 10, Int2D(5, 2) },
{ "data/EFFECT/ief000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 10, Int2D(3, 1)},
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Effect {
	//public _2dobj {
private:
	Vertex2D		vertexWk[NUM_VERTEX];			// 頂点情報格納構造体
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		scl;
	bool			use;
	int				CountAnim;
	int				PatternAnim;					// アニメーションパターン
	int				AnimationCnt;

	LPDIRECT3DTEXTURE9		D3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// 頂点バッファへのポインタ
	int				TexAnimNum;						// アニメーションの分割数
	int				xPattern, yPattern;				// 分割数
	D3DXVECTOR3		size;

public:
	Effect(EffectData data, D3DXVECTOR3 _pos);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// 頂点情報の作成
	void SetTexture(int cntPattern);			// テクスチャ座標の設定
	void SetVertex();							// 頂点座標の設定
};

#endif

