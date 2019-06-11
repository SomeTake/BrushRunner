//=============================================================================
//
// その他関数まとめ [MyLibrary.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

//=============================================================================
// プロトタイプ宣言
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, 
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout, int Sx, int Sy, int Screen_w, int Screen_h,
	D3DXMATRIX* View, D3DXMATRIX* Prj);

int CmpDescendf(const void *p, const void *q);		// floatの比較（降順）
int CmpAscendf(const void *p, const void *q);		// floatの比較（昇順）
int CmpDescend(const void *p, const void *q);		// intの比較（降順）
int CmpAscend(const void *p, const void *q);		// intの比較（昇順）

D3DXVECTOR3 Pick(D3DXVECTOR3 _pos);

#endif

