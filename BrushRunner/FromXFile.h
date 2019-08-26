//=============================================================================
//
// X�t�@�C���ǂݍ��ݗp�N���X[FromXFile.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _FROMXFILE_H_
#define _FROMXFILE_H_

#define Keydata_Max (15)

#include "AllocateHierarchy.h"
#include "AnimationSet.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FromXFile
{
public:
	AllocateHierarchy *			AllocateHier;	// xfile�ۑ��ꏊ
	LPD3DXFRAME					FrameRoot;		// ���[�g�t���[��	
	LPD3DXANIMATIONCONTROLLER	AnimController;	// �A�j���[�V�����R���g���[���[


	FromXFile();
	~FromXFile();

	HRESULT Load(const char*tag, const char *path);

};

#endif
