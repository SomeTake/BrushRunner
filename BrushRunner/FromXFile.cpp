//=============================================================================
//
// X�t�@�C���ǂݍ��ݗp�N���X[FromXFile.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "FromXFile.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
FromXFile::FromXFile()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
FromXFile::~FromXFile()
{
	SAFE_RELEASE(this->AnimController);

	D3DXFrameDestroy(this->FrameRoot, this->AllocateHier);

	this->AllocateHier->DestroyFrame(this->FrameRoot);

	SAFE_DELETE(this->AllocateHier);

	this->AnimSet.clear();
	ReleaseVector(this->AnimSet);
}

//=============================================================================
// X�t�@�C���ǂݍ���
//=============================================================================
HRESULT FromXFile::Load(const char* tag, const char* path)
{
	char Message[64];
	LPDIRECT3DDEVICE9 Device = GetDevice();
	this->AllocateHier = new AllocateHierarchy();

	// Xfile�̓ǂݍ���
	if (FAILED(D3DXLoadMeshHierarchyFromX(path,
		D3DXMESH_MANAGED,
		Device,
		this->AllocateHier,
		NULL,
		&this->FrameRoot,
		&this->AnimController)))
	{
		sprintf_s(Message, "Load %s Model Failed�I", tag);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	// �{�[���p�̃|�C���^������
	SetupBoneMatrixPointers(this->FrameRoot, this->FrameRoot);

	// �A�j���[�V�����Z�b�g�̃��������m��
	this->AnimSet.reserve(this->AnimController->GetMaxNumAnimationSets());

	// �A�j���[�V�����Z�b�g���쐬
	this->CreateAnimSet();

	return S_OK;
}

//=============================================================================
// �{�[���s��̃|�C���^�̏���
//=============================================================================
HRESULT FromXFile::SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
{
	if (pFrameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* pFrame = NULL;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;

		// if there is a skinmesh, then setup the bone matrices
		if (pMeshContainer->pSkinInfo != NULL)
		{
			UINT cBones = pMeshContainer->pSkinInfo->GetNumBones();
			pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
				if (pFrame == NULL) return E_FAIL;

				pMeshContainer->ppBoneMatrix[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameSibling, pFrameRoot)))
			return E_FAIL;
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameFirstChild, pFrameRoot)))
			return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �A�j���[�V�����Z�b�g�̍쐬
//=============================================================================
void FromXFile::CreateAnimSet()
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

		this->AnimSet.push_back(AnimationSet);

		Keydata.clear();
	}

	SAFE_DELETE(AnimationSet);
	ReleaseVector(Keydata);
}

//=============================================================================
// �A�j���[�V�����Z�b�g��CallbackKeys��ݒu����
//=============================================================================
HRESULT FromXFile::SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName)
{
	// Keyframe��ݒu����\���AnimationSet
	ID3DXKeyframedAnimationSet* AnimSetTemp = NULL;
	// Keyframe��ݒu�����V����AnimationSet
	ID3DXCompressedAnimationSet* CompressedAnimSet = NULL;
	// ���k���ꂽ����
	ID3DXBuffer* CompressedInfo = NULL;
	// �G���[���b�Z�[�W	
	char Message[256] = { NULL };
	double Ticks = 0.0;
	double Period = 0.0;
	// �ݒu����Callback Keys
	D3DXKEY_CALLBACK *Keys = NULL;
	vector<KEYDATA> KeyVector = *Keydata;
	int CallbacksNum = KeyVector.size();

	if (CallbacksNum == 0)
	{
		goto FunctionExit;
	}

	if (FAILED(this->AnimController->GetAnimationSetByName(SetName, (ID3DXAnimationSet**)&AnimSetTemp)))
	{
		sprintf_s(Message, "Setup Callbacks in %s AnimationSet Failed�I", SetName);
		goto FunctionExit;
	}

	// ���k������n��
	AnimSetTemp->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &CompressedInfo);

	// 1�b�̃L�[�t���C���̐���Ԃ�(1�b = 4800)
	Ticks = AnimSetTemp->GetSourceTicksPerSecond();
	// �A�j���[�V�����̃��[�v����
	Period = AnimSetTemp->GetPeriod();

	// ��������z��
	Keys = (D3DXKEY_CALLBACK*)calloc(CallbacksNum, sizeof(D3DXKEY_CALLBACK));
	if (Keys == NULL)
	{
		sprintf_s(Message, "Alloc Keys in %s AnimationSet Failed�I", SetName);
		goto FunctionExit;
	}

	// Callback Keys��ݒu����
	for (int i = 0; i < CallbacksNum; i++)
	{
		if (KeyVector[i].KeyType == 0)
		{
			sprintf_s(Message, "There is NoEvent Keydata in %s AnimationSet�I", SetName);
			goto FunctionExit;
		}
		Keys[i].Time = (float)(Period * Ticks * KeyVector[i].Time);
		Keys[i].pCallbackData = (void*)KeyVector[i].KeyType;
	}

	// ���k����A�j���[�V�����Z�b�g���쐬����
	D3DXCreateCompressedAnimationSet(AnimSetTemp->GetName(),
		AnimSetTemp->GetSourceTicksPerSecond(),
		AnimSetTemp->GetPlaybackType(), CompressedInfo, CallbacksNum, Keys, &CompressedAnimSet);

	// �Â��A�j���[�V�����Z�b�g(���k����Ȃ�)���폜����
	this->AnimController->UnregisterAnimationSet(AnimSetTemp);

	// �V�����A�j���[�V�����Z�b�g(���k���ꂽ)��ǉ�����
	this->AnimController->RegisterAnimationSet(CompressedAnimSet);

	// �I������
FunctionExit:

	SAFE_RELEASE(CompressedInfo);
	SAFE_RELEASE(AnimSetTemp);
	SAFE_RELEASE(CompressedAnimSet);
	ReleaseVector(KeyVector);
	SAFE_FREE(Keys);

	if (Message[0] == NULL)
	{
		return S_OK;
	}
	else
	{
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}
}
