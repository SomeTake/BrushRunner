//=============================================================================
//
// �J�������� [Camera.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "main.h"
#include "Camera.h"
#include "Input.h"
#include "Debugproc.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#define VIEW_DIST			(4)		// �Œ���̃L�����N�^�[�ƃJ�����̋���
#define VIEW_DIST_RATE		(0.3f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA cameraWk;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	cameraWk.pos = CAMERA_POS;
	cameraWk.at = CAMERA_AT;
	cameraWk.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	cameraWk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = cameraWk.pos.x - cameraWk.at.x;
	vz = cameraWk.pos.z - cameraWk.at.z;
	cameraWk.distance = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(D3DXVECTOR3 _at)
{
	// �Q�Ƃ�����W�ɑ΂��ĕ��s�ړ�����
	//cameraWk.at = _at;
	//cameraWk.pos = _at + CAMERA_POS;

#ifndef _DEBUG_
	PrintDebugProc("CamerAt X:%f Y:%f Z:%f\n", cameraWk.at.x, cameraWk.at.y, cameraWk.at.z);
	PrintDebugProc("CamerPos X:%f Y:%f Z:%f\n", cameraWk.pos.x, cameraWk.pos.y, cameraWk.pos.z);
#endif

	//if (GetKeyboardPress(DIK_A))
	//{
	//	if (GetKeyboardPress(DIK_W))
	//	{// ���O�ړ�
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else if (GetKeyboardPress(DIK_S))
	//	{// ����ړ�
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else
	//	{// ���ړ�
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_D))
	//{
	//	if (GetKeyboardPress(DIK_W))
	//	{// �E�O�ړ�
	//		cameraWk.pos.x += cosf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else if (GetKeyboardPress(DIK_S))
	//	{// �E��ړ�
	//		cameraWk.pos.x += cosf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else
	//	{// �E�ړ�
	//		cameraWk.pos.x += cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_W))
	//{// �O�ړ�
	//	cameraWk.pos.x += sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	cameraWk.pos.z += cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_S))
	//{// ��ړ�
	//	cameraWk.pos.x -= sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	cameraWk.pos.z -= cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}

	//if (GetKeyboardPress(DIK_Z))
	//{// ���_����u���v
	//	cameraWk.rot.y += VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y > D3DX_PI)
	//	{
	//		cameraWk.rot.y -= D3DX_PI * 2.0f;
	//	}

	//	cameraWk.pos.x = cameraWk.at.x - sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.pos.z = cameraWk.at.z - cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_C))
	//{// ���_����u�E�v
	//	cameraWk.rot.y -= VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y < -D3DX_PI)
	//	{
	//		cameraWk.rot.y += D3DX_PI * 2.0f;
	//	}

	//	cameraWk.pos.x = cameraWk.at.x - sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.pos.z = cameraWk.at.z - cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_Y))
	//{// ���_�ړ��u��v
	//	cameraWk.pos.y += VALUE_MOVE_CAMERA;
	//}
	//if (GetKeyboardPress(DIK_N))
	//{// ���_�ړ��u���v
	//	cameraWk.pos.y -= VALUE_MOVE_CAMERA;
	//}

	//if (GetKeyboardPress(DIK_Q))
	//{// �����_����u���v
	//	cameraWk.rot.y -= VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y < -D3DX_PI)
	//	{
	//		cameraWk.rot.y += D3DX_PI * 2.0f;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_E))
	//{// �����_����u�E�v
	//	cameraWk.rot.y += VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y > D3DX_PI)
	//	{
	//		cameraWk.rot.y -= D3DX_PI * 2.0f;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_T))
	//{// �����_�ړ��u��v
	//	cameraWk.at.y += VALUE_MOVE_CAMERA;
	//}
	//if (GetKeyboardPress(DIK_B))
	//{// �����_�ړ��u���v
	//	cameraWk.at.y -= VALUE_MOVE_CAMERA;
	//}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&cameraWk.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&cameraWk.mtxView,
		&cameraWk.pos,		// �J�����̎��_
		&cameraWk.at,		// �J�����̒����_
		&cameraWk.up);		// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &cameraWk.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&cameraWk.mtxProj);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&cameraWk.mtxProj,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &cameraWk.mtxProj);

}

//=============================================================================
//�J�����̏����擾����
//=============================================================================
CAMERA *GetCamera(void)
{
	return &cameraWk;
}