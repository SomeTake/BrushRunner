//=============================================================================
//
// »ΜΌΦάΖί [MyLibrary.h]
// Author : HAL GP12B332-19 80277 υJu
//
//=============================================================================
#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

//=============================================================================
// vg^CvιΎ
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, 
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout, int Sx, int Sy, int Screen_w, int Screen_h,
	D3DXMATRIX* View, D3DXMATRIX* Prj);

int CmpDescendf(const void *p, const void *q);		// floatΜδri~j
int CmpAscendf(const void *p, const void *q);		// floatΜδriΈj
int CmpDescend(const void *p, const void *q);		// intΜδri~j
int CmpAscend(const void *p, const void *q);		// intΜδriΈj

#endif

