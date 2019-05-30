//=============================================================================
//
// �o�g����ʃt���[���\������ [Carsl_obj3.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _CARSL_OBJ3_H_
#define _CARSL_OBJ3_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_CARSL_OBJ3	_T("data/texture/charasl_obj3.png")			// �t���[���p�摜
#define CARSL_OBJ3_SIZE		D3DXVECTOR3(114.0f, 114.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define CARSL_OBJ3_POS01		D3DXVECTOR3(400.0f, 350.0f, 0.0f)
#define CARSL_OBJ3_POS02		D3DXVECTOR3(550.0f, 350.0f, 0.0f)
#define CARSL_OBJ3_POS03		D3DXVECTOR3(700.0f, 350.0f, 0.0f)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Carsl_obj3 :
	public _2dobj {
public:
	Carsl_obj3(D3DXVECTOR3 _pos, const char *texno);
	~Carsl_obj3();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();
	float getobjpos();
};
#endif