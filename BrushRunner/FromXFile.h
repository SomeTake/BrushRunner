//=============================================================================
//
// X�t�@�C���ǂݍ��ݗp�N���X[FromXFile.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _FROMXFILE_H_
#define _FROMXFILE_H_

#define Keydata_Max (15)

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	Slip,
	Stop,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// ���[�V�����I��
	e_MotionChange,				// ���[�V������ύX����
};

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
	std::vector<ANIMATIONSET*>	AnimSet;		// �A�j���[�V�����Z�b�g��ۑ�

	FromXFile();
	~FromXFile();

	void CreateAnimSet();
	HRESULT SetupCallbackKeys(vector<KEYDATA> *Keydata, LPCSTR SetName);
	int GetAnimSetNum() { return this->AnimController->GetMaxNumAnimationSets(); };

	HRESULT Load(const char*tag, const char *path);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);

};

#endif
