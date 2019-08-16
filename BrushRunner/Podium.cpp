//=============================================================================
//
// �\����[Podium.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Podium.h"
#include "ResourceManager.h"
#include "Model3D.h"

#define PODIUM_ROT		D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Podium::Podium()
{
	ResourceManager::Instance()->GetMesh("Podium", &model);

	model->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->rot = PODIUM_ROT;
	model->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Podium::~Podium()
{
	model = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void Podium::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void Podium::Draw()
{
	model->Draw();
}

////=============================================================================
//// �A�j���[�V�����Z�b�g�̍쐬
////=============================================================================
//void Podium::CreateAnimSet()
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
//}
//
////=====================================================================================================
//// �A�j���[�V����CallbackKey�̏����C�x���g
////=====================================================================================================
//HRESULT CALLBACK Podium::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	return S_OK;
//}
