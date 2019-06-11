//=============================================================================
//
// ���̑��֐��܂Ƃ� [MyLibrary.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, 
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout, int Sx, int Sy, int Screen_w, int Screen_h,
	D3DXMATRIX* View, D3DXMATRIX* Prj);

int CmpDescendf(const void *p, const void *q);		// float�̔�r�i�~���j
int CmpAscendf(const void *p, const void *q);		// float�̔�r�i�����j
int CmpDescend(const void *p, const void *q);		// int�̔�r�i�~���j
int CmpAscend(const void *p, const void *q);		// int�̔�r�i�����j

D3DXVECTOR3 Pick(D3DXVECTOR3 _pos);

#endif

