//=============================================================================
//
// エフェクト処理 [Effect.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "_2dobj.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_TEXTURE0				_T("data/EFFECT/anmef000.png")			// 画像0
#define EFFECT_TEXTURE1				_T("data/EFFECT/anmef001.png")			// 画像1
#define EFFECT_TEXTURE2				_T("data/EFFECT/anmef002.png")			// 画像2(Runエフェクト)
#define EFFECT_TEXTURE3				_T("data/EFFECT/explo000.png")			// 画像2(爆発エフェクト)
#define EFFECT_TEXTURE4				_T("data/EFFECT/ief001.png")			// 画像2(アイテムエフェクト)



#define EFFET0_POS					D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// テクスチャ0の表示位置
#define EFFECT0_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// テクスチャ0のサイズ

#define EFFET1_POS					D3DXVECTOR3(200.0f, 0.0f, 0.0f)			// テクスチャ1の表示位置
#define EFFECT1_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// テクスチャ1のサイズ

#define EFFET2_POS					D3DXVECTOR3(400.0f, 0.0f, 0.0f)			// テクスチャ2の表示位置
#define EFFECT2_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// テクスチャ2のサイズ

#define EFFET3_POS					D3DXVECTOR3(600.0f, 0.0f, 0.0f)			// テクスチャ3の表示位置
#define EFFECT3_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// テクスチャ3のサイズ

#define EFFET4_POS					D3DXVECTOR3(800.0f, 0.0f, 0.0f)			// テクスチャ4の表示位置
#define EFFECT4_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// テクスチャ4のサイズ



#define EFFECT_PATTERN_X			(5)										// テクスチャ0内分割数(X)
#define EFFECT_PATTERN_Y			(1)										// テクスチャ0内分割数(Y)

#define EFFECT1_PATTERN_X			(1)										// テクスチャ1内分割数(X)
#define EFFECT1_PATTERN_Y			(5)										// テクスチャ1内分割数(Y)

#define EFFECT2_PATTERN_X			(2)										// テクスチャ2内分割数(X)
#define EFFECT2_PATTERN_Y			(2)										// テクスチャ2内分割数(Y)

#define EFFECT3_PATTERN_X			(5)										// テクスチャ3内分割数(X)
#define EFFECT3_PATTERN_Y			(3)										// テクスチャ3内分割数(Y)

#define EFFECT4_PATTERN_X			(5)										// テクスチャ4内分割数(X)
#define EFFECT4_PATTERN_Y			(2)										// テクスチャ4内分割数(Y)


#define ANIME_PATTERN_NUM_EFFECT0	(EFFECT_PATTERN_X*EFFECT_PATTERN_Y)		// アニメーションパターン数

#define ANIME_PATTERN_NUM_EFFECT1	(EFFECT1_PATTERN_X*EFFECT1_PATTERN_Y)	// アニメーションパターン数

#define ANIME_PATTERN_NUM_EFFECT2	(EFFECT2_PATTERN_X*EFFECT2_PATTERN_Y)	// アニメーションパターン数

#define ANIME_PATTERN_NUM_EFFECT3	(EFFECT3_PATTERN_X*EFFECT3_PATTERN_Y)	// アニメーションパターン数

#define ANIME_PATTERN_NUM_EFFECT4	(EFFECT4_PATTERN_X*EFFECT4_PATTERN_Y)	// アニメーションパターン数


#define TIME_ANIMATION_EFFECT0		(7)										// アニメーションカウント

#define TIME_ANIMATION_EFFECT1		(7)										// アニメーションカウント

#define TIME_ANIMATION_EFFECT2		(7)										// アニメーションカウント

#define TIME_ANIMATION_EFFECT3		(3)										// アニメーションカウント

#define TIME_ANIMATION_EFFECT4		(10)									// アニメーションカウント


#define EFFECT_MAX					(16)									// エフェクトの最大数


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
	Effect(const char * texture, D3DXVECTOR3 _size, D3DXVECTOR3 _pos, int _AnimationCnt, int _xPattern, int _yPattern);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// 頂点情報の作成
	void SetTexture(int cntPattern);			// テクスチャ座標の設定
	void SetVertex();							// 頂点座標の設定
};

#endif

