//=============================================================================
//
// �X�e�[�W�Z���N�g�p�J�[�\�� [StageSelectCursor.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _STAGESELECTCURSOR_H_
#define _STAGESELECTCURSOR_H_

#include "_2dobj.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class StageSelectCursor :
	public _2dobj
{
private:
	void MakeVertex();
	void SetVertex();

public:
	StageSelectCursor();
	~StageSelectCursor();

	void Update()override;
	void Draw()override;
};

#endif
