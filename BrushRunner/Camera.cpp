//=============================================================================
//
// �J�������� [Camera.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "main.h"
#include "Camera.h"
#include "Input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#define VIEW_DIST			(4)		// �Œ���̃L�����N�^�[�ƃJ�����̋���
#define VIEW_DIST_RATE		(0.3f)
#define CAMERA_SPD			(0.05f)	// �Â��J���������_�ƐV�����J���������_�ɍ�������ꍇ�ɃJ�����ʒu���X�V����X�s�[�h

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
	// ��ԑO�ɂ���L�����N�^�̍��W��V���������_�Ƃ���
	D3DXVECTOR3 newAt = _at;

	// �X�V�O�̒����_�ƐV���������_�̍����x�N�g���ɂ���
	D3DXVECTOR3 DistVec = newAt - cameraWk.at;

	// ���X�ɐV���������_�ɋ߂Â���
	cameraWk.at += DistVec * CAMERA_SPD;
	
	// ���W�͒����_�ɑ΂��ĕ��s�ړ�����
	cameraWk.pos = cameraWk.at + CAMERA_POS;

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