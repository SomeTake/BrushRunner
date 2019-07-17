//=============================================================================
//
// ミニプレイヤー処理 [MiniPlayer.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MINIPLAYER_H_
#define _MINIPLAYER_H_

#include "_2dobj.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MiniPlayer : public _2dobj
{
private:
	static LPDIRECT3DTEXTURE9		D3DTexture;		// テクスチャへのポインタ

	HRESULT MakeVertex(int PlayerNo);	// 頂点情報の作成
	void SetTexture(int PlayerNo);		// テクスチャ座標の設定
	void SetVertex(void);				// 頂点座標の設定

public:
	MiniPlayer(int PlayerNo);
	~MiniPlayer();
	static void ReleaseTexture(void) { SAFE_RELEASE(MiniPlayer::D3DTexture); };

	void Update(D3DXVECTOR3 PlayerPos);
	void Draw();
};

#endif

