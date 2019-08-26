//=============================================================================
//
// Xファイル読み込み用クラス[FromXFile.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _FROMXFILE_H_
#define _FROMXFILE_H_

#define Keydata_Max (15)

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


	FromXFile();
	~FromXFile();

	HRESULT Load(const char*tag, const char *path);

};

#endif
