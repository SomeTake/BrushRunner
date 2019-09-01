//=============================================================================
//
// Xファイル読み込み用クラス[FromXFile.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "FromXFile.h"

//=============================================================================
// コンストラクタ
//=============================================================================
FromXFile::FromXFile()
{
}

//=============================================================================
// デストラクタ
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
// Xファイル読み込み
//=============================================================================
HRESULT FromXFile::Load(const char* tag, const char* path)
{
	char Message[64];
	LPDIRECT3DDEVICE9 Device = GetDevice();
	this->AllocateHier = new AllocateHierarchy();

	// Xfileの読み込み
	if (FAILED(D3DXLoadMeshHierarchyFromX(path,
		D3DXMESH_MANAGED,
		Device,
		this->AllocateHier,
		NULL,
		&this->FrameRoot,
		&this->AnimController)))
	{
		sprintf_s(Message, "Load %s Model Failed！", tag);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	// ボーン用のポインタを準備
	SetupBoneMatrixPointers(this->FrameRoot, this->FrameRoot);

	// アニメーションセットのメモリを確保
	this->AnimSet.reserve(this->AnimController->GetMaxNumAnimationSets());

	// アニメーションセットを作成
	this->CreateAnimSet();

	return S_OK;
}

//=============================================================================
// ボーン行列のポインタの準備
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
// アニメーションセットの作成
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
// アニメーションセットのCallbackKeysを設置する
//=============================================================================
HRESULT FromXFile::SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName)
{
	// Keyframeを設置する予定のAnimationSet
	ID3DXKeyframedAnimationSet* AnimSetTemp = NULL;
	// Keyframeを設置した新しいAnimationSet
	ID3DXCompressedAnimationSet* CompressedAnimSet = NULL;
	// 圧縮された資料
	ID3DXBuffer* CompressedInfo = NULL;
	// エラーメッセージ	
	char Message[256] = { NULL };
	double Ticks = 0.0;
	double Period = 0.0;
	// 設置するCallback Keys
	D3DXKEY_CALLBACK *Keys = NULL;
	vector<KEYDATA> KeyVector = *Keydata;
	int CallbacksNum = KeyVector.size();

	if (CallbacksNum == 0)
	{
		goto FunctionExit;
	}

	if (FAILED(this->AnimController->GetAnimationSetByName(SetName, (ID3DXAnimationSet**)&AnimSetTemp)))
	{
		sprintf_s(Message, "Setup Callbacks in %s AnimationSet Failed！", SetName);
		goto FunctionExit;
	}

	// 圧縮資料を渡す
	AnimSetTemp->Compress(D3DXCOMPRESS_DEFAULT, 0.5f, 0, &CompressedInfo);

	// 1秒のキーフレイムの数を返す(1秒 = 4800)
	Ticks = AnimSetTemp->GetSourceTicksPerSecond();
	// アニメーションのループ時間
	Period = AnimSetTemp->GetPeriod();

	// メモリを配る
	Keys = (D3DXKEY_CALLBACK*)calloc(CallbacksNum, sizeof(D3DXKEY_CALLBACK));
	if (Keys == NULL)
	{
		sprintf_s(Message, "Alloc Keys in %s AnimationSet Failed！", SetName);
		goto FunctionExit;
	}

	// Callback Keysを設置する
	for (int i = 0; i < CallbacksNum; i++)
	{
		if (KeyVector[i].KeyType == 0)
		{
			sprintf_s(Message, "There is NoEvent Keydata in %s AnimationSet！", SetName);
			goto FunctionExit;
		}
		Keys[i].Time = (float)(Period * Ticks * KeyVector[i].Time);
		Keys[i].pCallbackData = (void*)KeyVector[i].KeyType;
	}

	// 圧縮するアニメーションセットを作成する
	D3DXCreateCompressedAnimationSet(AnimSetTemp->GetName(),
		AnimSetTemp->GetSourceTicksPerSecond(),
		AnimSetTemp->GetPlaybackType(), CompressedInfo, CallbacksNum, Keys, &CompressedAnimSet);

	// 古いアニメーションセット(圧縮されない)を削除する
	this->AnimController->UnregisterAnimationSet(AnimSetTemp);

	// 新しいアニメーションセット(圧縮された)を追加する
	this->AnimController->RegisterAnimationSet(CompressedAnimSet);

	// 終了処理
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
