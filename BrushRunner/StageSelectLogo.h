//=============================================================================
//
// �X�e�[�W�Z���N�g��ʂ̃��S [StageSelectLogo.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _STAGESELECTLOGO_H_
#define _STAGESELECTLOGO_H_

#include "_2dobj.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class StageSelectLogo :
	public _2dobj
{
private:
	int cntFlash;
	bool flash;		// �_�ł�����t���O(true = �\��)

	void MakeVertex();

public:
	StageSelectLogo();
	~StageSelectLogo();

	void Update()override;
	void Draw()override;

};

#endif
