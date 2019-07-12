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
	ChargeEffect,

	// エフェクトの個数
	EffectMax,
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
	int				TexNo;

	static LPDIRECT3DTEXTURE9		D3DTexture[EffectMax];		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// 頂点バッファへのポインタ
	int				TexAnimNum;						// アニメーションの分割数
	int				xPattern, yPattern;				// 分割数
	D3DXVECTOR3		size;

public:
	Effect(int EffectNum, D3DXVECTOR3 _pos);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// 頂点情報の作成
	void SetTexture(int cntPattern);			// テクスチャ座標の設定
	void SetVertex();							// 頂点座標の設定

	bool GetUse() { return use; };
	void SetUse(bool _use) { use = _use; };

	static void LoadTexture();
	static void ReleaseTexture();
};

#endif

