//=============================================================================
//
// �g���t�B�[[Trophy.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Trophy.h"
#include "Model3D.h"
#include "ResourceManager.h"

#define TROPHY_POS		D3DXVECTOR3(0.0f, 150.0f, 0.0f)
#define TROPHY_ROT		D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30))
#define TROPHY_MOVE		D3DXVECTOR3(0.0f, D3DXToRadian(1), 0.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Trophy::Trophy()
{
	ResourceManager::Instance()->GetMesh("Trophy", &model);

	model->pos = TROPHY_POS;
	model->rot = D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30));
	model->scl = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Trophy::~Trophy()
{
	model = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void Trophy::Update()
{
	// ��]������
	model->rot += TROPHY_MOVE;
	if (model->rot.y >= D3DX_PI)
	{
		model->rot.y = -D3DX_PI;
	}
}

//=============================================================================
// �`��
//=============================================================================
void Trophy::Draw()
{
	model->Draw();
}

////=============================================================================
//// �A�j���[�V�����Z�b�g�̍쐬
////=============================================================================
//void Trophy::CreateAnimSet()
//{
//	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
//	vector<KEYDATA>Keydata;
//	Keydata.reserve(Keydata_Max);
//	AnimationSet->SetData("Idle", NULL, 1.0f, 0.1f, 0.0f);
//	this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());
//	AnimationSet->SetAnimSetPtr(this->AnimController);
//	this->AnimSet.push_back(*AnimationSet);
//	Keydata.clear();
//	SAFE_DELETE(AnimationSet);
//	ReleaseVector(Keydata);
//
//}
//
////=====================================================================================================
//// �A�j���[�V����CallbackKey�̏����C�x���g
////=====================================================================================================
//HRESULT CALLBACK Trophy::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	return S_OK;
//}
