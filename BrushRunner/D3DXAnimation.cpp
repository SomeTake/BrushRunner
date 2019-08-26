//=============================================================================
//
// モデルのアニメーション処理 [D3DXAnimation.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "main.h"
#include "D3DXAnimation.h"
#include "AnimationSet.h"
#include "ResourceManager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
D3DXAnimation::D3DXAnimation(const char* tag)
{
	// リソースの参照
	ResourceManager::Instance()->GetMesh(tag, &model);

	// アニメーションセットのメモリを確保
	this->AnimSet.reserve(this->model->AnimController->GetMaxNumAnimationSets());

	// ボーン用のポインタを作成
	SetupBoneMatrixPointers(this->model->FrameRoot, this->model->FrameRoot);

	// アニメーションセットを作成
	this->CreateAnimSet();
}

//=============================================================================
// デストラクタ
//=============================================================================
D3DXAnimation::~D3DXAnimation()
{
	this->AnimSet.clear();
	ReleaseVector(this->AnimSet);

	model = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void D3DXAnimation::UpdateAnim(float Time)
{
	float CurWeightTime = this->AnimSet.at(this->CurrentAnimID)->GetCurWeightTime();
	float ShiftTime = this->AnimSet.at(this->CurrentAnimID)->GetShiftTime();

	// 合成中か否かを判定
	CurWeightTime += Time;
	this->AnimSet.at(this->CurrentAnimID)->SetCurWeightTime(CurWeightTime);

	if (CurWeightTime <= ShiftTime)
	{
		// 合成中。ウェイトを算出
		float Weight = CurWeightTime / ShiftTime;
		// ウェイトを登録
		this->model->AnimController->SetTrackWeight(0, Weight);       // 現在のアニメーション
		this->model->AnimController->SetTrackWeight(1, 1 - Weight);   // 前のアニメーション
	}
	else
	{
		// 合成終了中。通常アニメーションをするTrack0のウェイトを最大値に
		this->model->AnimController->SetTrackWeight(0, 1.0f);			// 現在のアニメーション
		this->model->AnimController->SetTrackEnable(1, false);		// 前のアニメーションを無効にする
	}

	// 時間を更新
	this->model->AnimController->AdvanceTime(Time, this);

	return;
}

//=============================================================================
// 描画処理
//=============================================================================
void D3DXAnimation::DrawAnim(LPD3DXMATRIX WorldMatrix)
{
	UpdateFrameMatrices(this->model->FrameRoot, WorldMatrix);

	DrawFrame(this->model->FrameRoot);

	return;
}

//=============================================================================
// ボーン行列のポインタの準備
//=============================================================================
HRESULT D3DXAnimation::SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
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
void D3DXAnimation::CreateAnimSet()
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

		AnimationSet->SetAnimSetPtr(this->model->AnimController);

		this->AnimSet.push_back(AnimationSet);

		Keydata.clear();
	}

	SAFE_DELETE(AnimationSet);
	ReleaseVector(Keydata);
}

//=============================================================================
// アニメーションを切り替え
//=============================================================================
void D3DXAnimation::ChangeAnim(UINT AnimID)
{
	D3DXTRACK_DESC TD;   // トラックの能力
	ID3DXAnimationSet* CurtAnimSet = this->AnimSet.at(this->CurrentAnimID)->GetAnimSetPtr();
	ID3DXAnimationSet* NextAnimSet = this->AnimSet.at(AnimID)->GetAnimSetPtr();
	float Speed = this->AnimSet.at(AnimID)->GetSpeed();

	// 指定のアニメーションIDの存在をチェック
	if (AnimID > (UINT)this->GetAnimSetNum())
	{
		MessageBox(0, "AnimationSet Don't Exist", "Error", 0);
		return;
	}

	// 異なるアニメーションであるかをチェック
	if (this->CurrentAnimID == AnimID)
	{
		// 更新する必要がない
		return;
	}

	// 現在のアニメーションセットの設定値を取得
	this->model->AnimController->GetTrackDesc(0, &TD);

	// 今のアニメーションをトラック1に移行し
	// トラックの設定値も移行
	this->model->AnimController->SetTrackAnimationSet(1, CurtAnimSet);
	this->model->AnimController->SetTrackDesc(1, &TD);
	this->model->AnimController->SetTrackSpeed(1, 0.0f);

	// 新しいアニメーションセットをトラック0に設定
	this->model->AnimController->SetTrackAnimationSet(0, NextAnimSet);

	// トラック0のスピードの設定
	this->model->AnimController->SetTrackSpeed(0, Speed);

	// トラック0の位置は最初からに設定
	this->model->AnimController->SetTrackPosition(0, 0.0f);

	// トラックの合成を許可
	this->model->AnimController->SetTrackEnable(0, true);
	this->model->AnimController->SetTrackEnable(1, true);

	// ウェイト時間を初期化
	this->AnimSet.at(AnimID)->SetCurWeightTime(0.0f);
	this->model->AnimController->ResetTime();

	// 現在のアニメーション番号を切り替え
	this->PreventAnimID = this->CurrentAnimID;
	this->CurrentAnimID = AnimID;

	return;
}

//=============================================================================
// 特定のボーンを探す
//=============================================================================
D3DXFRAME_DERIVED* D3DXAnimation::SearchBoneFrame(const char* BoneName, D3DXFRAME* Frame)
{
	D3DXFRAME_DERIVED* pFrame = NULL;

	if (Frame == NULL)
	{
		return NULL;
	}

	if (Frame->Name != NULL && strcmp(Frame->Name, BoneName) == 0)
	{
		pFrame = (D3DXFRAME_DERIVED*)Frame;
		return pFrame;
	}

	if (Frame->pFrameSibling != NULL)
	{
		pFrame = SearchBoneFrame(BoneName, Frame->pFrameSibling);
		if (pFrame != NULL && strcmp(pFrame->Name, BoneName) == 0)
		{
			return pFrame;
		}
	}

	if (Frame->pFrameFirstChild != NULL)
	{
		pFrame = SearchBoneFrame(BoneName, Frame->pFrameFirstChild);
		if (pFrame != NULL && strcmp(pFrame->Name, BoneName) == 0)
		{
			return pFrame;
		}
	}

	return NULL;
}

//=============================================================================
// 特定のボーンマトリックスを取得
//=============================================================================
D3DXMATRIX D3DXAnimation::GetBoneMatrix(const char* BoneName)
{
	char Message[64];
	D3DXFRAME_DERIVED* pFrame = SearchBoneFrame(BoneName, this->model->FrameRoot);

	// ボーンが見つかれば
	if (pFrame != NULL && pFrame->Name != NULL && strcmp(pFrame->Name, BoneName) == 0)
	{
		return pFrame->CombinedTransformationMatrix;
	}
	// ボーンが見つからなければ
	else
	{
		sprintf_s(Message, "Find %s Bone Failed！", BoneName);
		MessageBox(0, Message, "Error", 0);
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//=============================================================================
// アニメーションセットのCallbackKeysを設置する
//=============================================================================
HRESULT D3DXAnimation::SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName)
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

	if (FAILED(this->model->AnimController->GetAnimationSetByName(SetName, (ID3DXAnimationSet**)&AnimSetTemp)))
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
	this->model->AnimController->UnregisterAnimationSet(AnimSetTemp);

	// 新しいアニメーションセット(圧縮された)を追加する
	this->model->AnimController->RegisterAnimationSet(CompressedAnimSet);

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
//=============================================================================
// フレームの描画
//=============================================================================
void D3DXAnimation::DrawFrame(LPD3DXFRAME pFrame)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	LPD3DXMESHCONTAINER pMeshContainer;

	if (pFrame == NULL)
	{
		return;
	}
	pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(pMeshContainer, pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	DrawFrame(pFrame->pFrameSibling);
	DrawFrame(pFrame->pFrameFirstChild);
}


//=============================================================================
// メッシュコンテナの描画
//=============================================================================
void D3DXAnimation::DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	Device->GetDeviceCaps(&d3dCaps);

	// first check for skinning
	if (pMeshContainer->pSkinInfo != NULL)
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

		// Draw using default vtx processing of the device (typically HW)
		for (iAttrib = 0; iAttrib < pMeshContainer->BoneNum; iAttrib++)
		{
			NumBlend = 0;
			for (DWORD i = 0; i < pMeshContainer->BoneWeightNum; ++i)
			{
				if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
				{
					NumBlend = i;
				}
			}

			if (d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1)
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for (DWORD i = 0; i < pMeshContainer->BoneWeightNum; ++i)
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrix[iMatrixIndex]);
						Device->SetTransform(D3DTS_WORLDMATRIX(i), &matTemp);
					}
				}

				Device->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

				// lookup the material used for this subset of faces
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					Device->SetMaterial(&pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D);
					Device->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}
		Device->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	else  // standard mesh, just draw it after setting material properties
	{
		Device->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			Device->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D);
			Device->SetTexture(0, pMeshContainer->ppTextures[iMaterial]);
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

//=============================================================================
// フレーム行列の更新
//=============================================================================
void D3DXAnimation::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	LPDIRECT3DDEVICE9 Device = GetDevice();

	if (pFrameBase == NULL || pParentMatrix == NULL)
	{
		return;
	}

	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
}

int D3DXAnimation::GetAnimCurtFrame(void)
{
	// 60 FPS
	double TrackTime = this->model->AnimController->GetTime() * 60;
	double SetPeriod = GetAnimPeriodFrame();
	return (int)(fmod(TrackTime, SetPeriod));
}

int D3DXAnimation::GetAnimPeriodFrame(void)
{
	return (int)(this->AnimSet.at(this->CurrentAnimID)->GetPeriod() * 60);
}
