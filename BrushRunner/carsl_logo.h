//=============================================================================
//
// �o�g����ʃt���[���\������ [Carsl_logo.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _CARSL_LOGO_H_
#define _CARSL_LOGO_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_CARSL_LOGO	_T("data/texture/charasl_logo.png")			// �t���[���p�摜
#define CARSL_LOGO_SIZE		D3DXVECTOR3(1280.0f, 114.0f, 0.0f)		// �e�N�X�`���T�C�Y

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Carsl_logo :
	public _2dobj {
public:
	Carsl_logo();
	~Carsl_logo();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
};


#endif