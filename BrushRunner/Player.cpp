//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Player.h"

//=====================================================================================================
// �R���X�g���N�^
//=====================================================================================================
PLAYER::PLAYER()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = PLAYER_FIRST_POS;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�I�u�W�F�N�g�̏�����
	Animation = CreateAnimationObject();

	// xFile�̓ǂݍ���
	Load_xFile(Animation, CHARA_XFILE, "Player");

	// �A�j���[�V�����̍ŏI�t���[�����Z�b�g����
	// �O����
	SetupCallbackKeyframes(Animation, CharaStateAnim[Frontwalk]);
	// ������
	SetupCallbackKeyframes(Animation, CharaStateAnim[Backwalk]);
	// �E�X�e�b�v
	SetupCallbackKeyframes(Animation, CharaStateAnim[Rightstep]);
	// ���X�e�b�v
	SetupCallbackKeyframes(Animation, CharaStateAnim[Leftstep]);
	// ��_���[�W
	SetupCallbackKeyframes(Animation, CharaStateAnim[Damage]);
	// �_�E��
	SetupCallbackKeyframes(Animation, CharaStateAnim[Down]);
	// �_�E���|�[�Y
	SetupCallbackKeyframes(Animation, CharaStateAnim[Downpose]);
	// �N���オ��
	SetupCallbackKeyframes(Animation, CharaStateAnim[Getup]);
	// �p���`
	SetupCallbackKeyframes(Animation, CharaStateAnim[Punchi]);
	// �X�g���[�g�i�ǌ��p���`�P�j
	SetupCallbackKeyframes(Animation, CharaStateAnim[Straight]);
	// �A�b�p�[�i�ǌ��p���`�Q�j
	SetupCallbackKeyframes(Animation, CharaStateAnim[Upper]);
	// �L�b�N
	SetupCallbackKeyframes(Animation, CharaStateAnim[Kick]);
	// �g��
	SetupCallbackKeyframes(Animation, CharaStateAnim[Hadou]);
	// ����
	SetupCallbackKeyframes(Animation, CharaStateAnim[Shoryu]);
	// SP�Z
	SetupCallbackKeyframes(Animation, CharaStateAnim[SPattack]);
	// ����
	SetupCallbackKeyframes(Animation, CharaStateAnim[Throw]);
	// �����X�J��
	SetupCallbackKeyframes(Animation, CharaStateAnim[Miss]);

	// �A�j���[�V�����Z�b�g�̏�����
	for (int i = 0; i < Animation->AnimSetNum; i++)
	{
		Animation->InitAnimation(Animation, CharaStateAnim[i], i);
	}

	// ���݂̃A�j���[�V�������A�C�h����ԂƂ���
	Animation->CurrentAnimID = Idle;

	// �A�j���[�V�����Ԃ̕⊮��ݒ�
	for (int i = 0; i < Animation->AnimSetNum; i++)
	{
		Animation->SetShiftTime(Animation, i, Data[i].ShiftTime);
	}

}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
PLAYER::~PLAYER()
{
}

//=====================================================================================================
// �X�V
//=====================================================================================================
void PLAYER::Update()
{
	// �A�j���[�V�������X�V
	Animation->UpdateAnimation(Animation, TIME_PER_FRAME);
}

//=====================================================================================================
// �`��
//=====================================================================================================
void PLAYER::Draw()
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
	Animation->DrawAnimation(Animation, &WorldMtx);

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
