//=============================================================================
//
// �X�e�[�W���\�� [StageName.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _STAGENAME_H_
#define _STAGENAME_H_

#include "_2dobj.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class StageName :
	public _2dobj
{
private:
	void MakeVertex();

public:
	StageName();
	~StageName();

	void Update()override;
	void Draw()override;
};

#endif
