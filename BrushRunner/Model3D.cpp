// 3D���f���ǂݍ��ݗp���ۃC���^�[�t�F�[�X [Model3D.cpp]
//=============================================================================
//
// 3D���f���ǂݍ��ݗp���ۃN���X [Model3D.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Model3D.h"

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	Slip,
	Stop,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// ���[�V�����I��
	e_MotionChange,				// ���[�V������ύX����
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Model3D::Model3D(const char* tag,const char* path)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->Load_xFile(path, tag);

	// �A�j���[�V�����Z�b�g�̏�����
	this->CreateAnimSet();

	this->animSpd = 1.0f;
	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

//=============================================================================
// �A�j���[�V�����Z�b�g�̍쐬
//=============================================================================
void Model3D::CreateAnimSet()
{
	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
	vector<KEYDATA>Keydata;
	Keydata.reserve(Keydata_Max);

	for (int Set_No = 0; Set_No < GetAnimSetNum(); Set_No++)
	{
		switch (Set_No)
		{
		case Idle:

			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Victory:

			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Slip:

			Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
			AnimationSet->SetData("Slip", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Stop:

			AnimationSet->SetData("Stop", NULL, 1.5f, 0.1f, 0.0f);
			break;

		default:
			break;
		}

		this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());

		AnimationSet->SetAnimSetPtr(this->AnimController);

		this->AnimSet.push_back(*AnimationSet);

		Keydata.clear();
	}

	SAFE_DELETE(AnimationSet);
	ReleaseVector(Keydata);
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

