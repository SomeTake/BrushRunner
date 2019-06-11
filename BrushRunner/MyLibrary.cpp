//=============================================================================
//
// ���̑��֐��܂Ƃ� [MyLibrary.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "MyLibrary.h"

//=============================================================================
// �X�N���[�����W�����[���h���W�ɕϊ�
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
) {
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)Sx, (float)Sy, (float)fZ), &tmp);

	return pout;
}

//=============================================================================
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
//=============================================================================
D3DXVECTOR3* CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
) {
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	// ���Ƃ̌������N���Ă���ꍇ�͌�_��
	// �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= 0) {
		// ����_
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}

//=============================================================================
// ��r�֐�(�~��)float�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpDescendf(const void *p, const void *q)
{
	if (*(float*)p < *(float*)q)
	{
		return 1;
	}
	if (*(float*)p > *(float*)q)
	{
		return -1;
	}
	return 0;
}

//=============================================================================
// ��r�֐�(����)float�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpAscendf(const void *p, const void *q)
{
	if (*(float*)p > *(float*)q)
	{
		return 1;
	}
	if (*(float*)p < *(float*)q)
	{
		return -1;
	}
	return 0;
}

//=============================================================================
// ��r�֐�(�~��)int�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpDescend(const void *p, const void *q)
{
	return *(int*)q - *(int*)p;
}

//=============================================================================
// ��r�֐�(����)int�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpAscend(const void *p, const void *q)
{
	return *(int*)p - *(int*)q;
}

//=============================================================================
// �X�N���[�����W�����[���h���W�֕ϊ�
//=============================================================================
D3DXVECTOR3 Pick(D3DXVECTOR3 _pos)
{
	D3DXVECTOR3 vPickRayDir;
	D3DXVECTOR3 vPickRayOrig;
	IDirect3DDevice9* pD3Device = GetDevice();
	//const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetD3D9BackBufferSurfaceDesc();

	D3DXMATRIX ProjMtx, ViewMtx, WorldMtx;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtx);

	pD3Device->GetTransform(D3DTS_PROJECTION, &ProjMtx);
	pD3Device->GetTransform(D3DTS_VIEW, &ViewMtx);

	//POINT ptCursor;
	//GetCursorPos(&ptCursor);
	//ScreenToClient(DXUTGetHWND(), &ptCursor);

	// �X�N���[�����W����s�b�N���C�̃x�N�g�������߂�
	// Compute the vector of the pick ray in screen space
	D3DXVECTOR3 v;
	v.x = (((2.0f * _pos.x) / SCREEN_WIDTH) - 1) / ProjMtx._11 * (SCREEN_WIDTH / ProjMtx._22);
	v.y = -(((2.0f * _pos.y) / SCREEN_HEIGHT) - 1) / ProjMtx._22 * (SCREEN_HEIGHT / ProjMtx._11);
	v.z = 1.0f;

	// �t�r���[�s��Ń��[���h���W�֖߂�
	// Get the inverse view matrix
	D3DXMATRIX mWorldView = WorldMtx * ViewMtx;
	D3DXMATRIX m;
	D3DXMatrixInverse(&m, NULL, &mWorldView);

	// �X�N���[�����W�̃s�b�N���C��3D���W�ɕϊ�����
	// Transform the screen space pick ray into 3D space
	vPickRayDir.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	vPickRayDir.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	vPickRayDir.z = v.x * m._13 + v.y * m._23 + v.z * m._33;
	vPickRayOrig.x = m._41;
	vPickRayOrig.y = m._42;
	vPickRayOrig.z = m._43;

	return vPickRayDir;
}