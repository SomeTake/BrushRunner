//=============================================================================
//
// �L�����N�^�[�Z���N�g���S [SelectLogo.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _SELECTLOGO_H_
#define _SELECTLOGO_H_

#include "_2dobj.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SelectLogo :
	public _2dobj {
private:
	int cntFlash;
	bool flash;

public:
	SelectLogo();
	~SelectLogo();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
};


#endif