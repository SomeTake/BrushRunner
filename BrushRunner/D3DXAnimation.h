//=============================================================================
//
// モデルのアニメーション処理 [D3DXAnimation.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _D3DXANIMATION_H_
#define _D3DXANIMATION_H_

#define Keydata_Max (15)

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	Slip,
	Stop,
	AnimMax,			// アニメーションの最大数
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// モーション終了
	e_MotionChange,				// モーションを変更する
};

#include "FromXFile.h"

class D3DXAnimation : 
	public ID3DXAnimationCallbackHandler
{
protected:
	FromXFile * model;

private:
	std::vector<ANIMATIONSET*>	AnimSet;		// アニメーションセットを保存
	UINT		CurrentAnimID;					// 現在再生しているアニメーションの番号
	UINT		PreventAnimID;					// 前再生していたアニメーションの番号

	D3DXFRAME_DERIVED* SearchBoneFrame(const char* BoneName, D3DXFRAME* Frame);
	void DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);

public:
	D3DXAnimation(const char* tag);
	virtual ~D3DXAnimation();
	void CreateAnimSet();

	void ChangeAnim(UINT AnimID);
	HRESULT SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName);
	void UpdateAnim(float Time);
	void DrawAnim(LPD3DXMATRIX WorldMatrix);

	D3DXMATRIX GetBoneMatrix(const char* BoneName);
	int GetAnimCurtID() { return this->CurrentAnimID; };
	int GetAnimSetNum() { return this->model->AnimController->GetMaxNumAnimationSets(); };
	int GetAnimCurtFrame();
	int GetAnimPeriodFrame();
	LPCSTR GetCurtAnimName() { return this->AnimSet.at(this->CurrentAnimID)->GetSetName(); };

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
