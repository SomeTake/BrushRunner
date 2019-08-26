//=============================================================================
//
// 3D���f���ǂݍ��ݗp���ۃN���X [Model3D.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Model3D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Model3D::Model3D(const char* tag) : D3DXAnimation(tag)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Model3D::~Model3D()
{
}

//=============================================================================
// �X�V
//=============================================================================
void Model3D::Update()
{
	UpdateAnim(TIME_PER_FRAME * this->animSpd);
}

//=============================================================================
// �`��
//=============================================================================
void Model3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX WorldMtx, SclMtx, RotMtx, TransMtx;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtx);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&SclMtx, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&SclMtx, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &TransMtx);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtx);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �����_�����O
	this->DrawAnim(&WorldMtx);

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=====================================================================================================
// �A�j���[�V����CallbackKey�̏����C�x���g
//=====================================================================================================
HRESULT CALLBACK Model3D::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	int eventNo = (int)pCallbackData;

	switch (eventNo)
	{
	case e_MotionEnd:
		animSpd = 0.0f;
		break;
	case e_MotionChange:
		ChangeAnim(Idle);
		break;
	default:
		break;
	}

	return S_OK;
}

