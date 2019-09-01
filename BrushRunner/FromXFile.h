//=============================================================================
//
// Xファイル読み込み用クラス[FromXFile.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _FROMXFILE_H_
#define _FROMXFILE_H_

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

#include "AllocateHierarchy.h"
#include "AnimationSet.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class FromXFile
{
public:
	AllocateHierarchy *			AllocateHier;	// xfile保存場所
	LPD3DXFRAME					FrameRoot;		// ルートフレーム	
	LPD3DXANIMATIONCONTROLLER	AnimController;	// アニメーションコントローラー
	std::vector<ANIMATIONSET*>	AnimSet;		// アニメーションセットを保存

	FromXFile();
	~FromXFile();

	void CreateAnimSet();
	HRESULT SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName);
	int GetAnimSetNum() { return this->AnimController->GetMaxNumAnimationSets(); };

	HRESULT Load(const char*tag, const char *path);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);

};

#endif
