//=============================================================================
//
// モデルのアニメーション処理 [D3DXAnimation.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _D3DXANIMATION_H_
#define _D3DXANIMATION_H_

#define Keydata_Max (15)

#include "FromXFile.h"

class D3DXAnimation : 
	public ID3DXAnimationCallbackHandler
{
protected:
	FromXFile * model;
	LPD3DXANIMATIONCONTROLLER	AnimController;	// アニメーションコントローラーのコピー先

private:
	UINT		CurrentAnimID;					// 現在再生しているアニメーションの番号
	UINT		PreventAnimID;					// 前再生していたアニメーションの番号

	D3DXFRAME_DERIVED* SearchBoneFrame(const char* BoneName, D3DXFRAME* Frame);
	void DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void DrawFrame(LPD3DXFRAME pFrame);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);

public:
	D3DXAnimation(const char* tag);
	virtual ~D3DXAnimation();
	//void CreateAnimSet();

	void ChangeAnim(UINT AnimID);
	//HRESULT SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName);
	void UpdateAnim(float Time);
	void DrawAnim(LPD3DXMATRIX WorldMatrix);

	D3DXMATRIX GetBoneMatrix(const char* BoneName);
	int GetAnimCurtID() { return this->CurrentAnimID; };
	//int GetAnimSetNum() { return this->model->AnimController->GetMaxNumAnimationSets(); };
	int GetAnimCurtFrame();
	int GetAnimPeriodFrame();
	LPCSTR GetCurtAnimName() { return this->model->AnimSet.at(this->CurrentAnimID)->GetSetName(); };

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
