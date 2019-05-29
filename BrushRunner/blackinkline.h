//=============================================================================
//
// �o�g����ʃt���[���\������ [Blackinkline.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _BLACKINKLINE_H_
#define _BLACKINKLINE_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_INKLINEBLACK	_T("data/texture/inkline.black.png")			// �t���[���p�摜
#define TEXTURE_BLACKINKFRAME   _T("data/texture/blackinkframe.png")
#define BLACKINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define BLACKINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Blackinkline :
	public _2dobj {
public:
	Blackinkline(D3DXVECTOR3 _pos, const char *texno); //const�ɂ��萔���𐬂�define�̎g�p�@�|�C���^�ɂ��Ȃ���texture�t�@�C���������Ƃ�Ȃ�
	~Blackinkline();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif