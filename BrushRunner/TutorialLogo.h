//=============================================================================
//
// �`���[�g���A����ʂ̃��S [TitleLogo.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "_2dobj.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TutorialLogo :
	public _2dobj
{
private:
	int cntFlash;
	bool flash;		// �_�ł�����t���O(true = �\��)

	void MakeVertex();

public:
	TutorialLogo();
	~TutorialLogo();

	void Update()override;
	void Draw()override;
};

#endif
