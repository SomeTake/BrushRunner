//=============================================================================
//
// 2DUI用パーティクル [UIParticle.h]
// Author : HAL東京 GP12B332 19 染谷武志
//
//=============================================================================
#ifndef _UIPARTICLE_H_
#define _UIPARTICLE_H_

#include "_2dobj.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class UIParticle :
	public _2dobj
{
private:
	void MakeVertex();
	void SetVertex();
	void SetColor();
	void SetTexture();

	D3DXVECTOR3 move;
	D3DXCOLOR col;
	int time;
	float decAlpha;

public:
	UIParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR3 size, int time);
	~UIParticle();

	void Update()override;
	void Draw()override;

	bool GetUse() { return use; };
};

#endif
