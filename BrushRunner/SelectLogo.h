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
// �}�N����`
//*****************************************************************************
#define TEXTURE_SELECTLOGO	_T("data/TEXTURE/CharSelectLogo.png")			// �t���[���p�摜
#define SELECTLOGO_SIZE		D3DXVECTOR3(1280.0f, 114.0f, 0.0f)		// �e�N�X�`���T�C�Y

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SelectLogo :
	public _2dobj {
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