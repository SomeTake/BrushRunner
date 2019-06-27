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
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);	// �X�N���[�����W�����[���h���W�֕ϊ�

int CmpDescendf(const void *p, const void *q);		// float�̔�r�i�~���j
int CmpAscendf(const void *p, const void *q);		// float�̔�r�i�����j
int CmpDescend(const void *p, const void *q);		// int�̔�r�i�~���j
int CmpAscend(const void *p, const void *q);		// int�̔�r�i�����j

template<typename T> T clamp(T x, T low, T high)	// ����A�����̃`�F�b�N
{
	return min(max(x, low), high);
}

void ReadCsv(const char *data, int **table);		// CSV�t�@�C���̓ǂݍ���

#endif

