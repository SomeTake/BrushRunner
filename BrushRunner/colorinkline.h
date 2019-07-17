//=============================================================================
//
// �o�g����ʃt���[���\������ [Colorinkline.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _COLORINKLINE_H_
#define _COLORINKLINE_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_INKLINEBLUE		_T("data/texture/inkline.blue.png")			// �t���[���p�摜
#define TEXTURE_INKLINERED		_T("data/texture/inkline.red.png")			// �t���[���p�摜
#define TEXTURE_INKLINEYELLOW	_T("data/texture/inkline.yellow.png")			// �t���[���p�摜
#define TEXTURE_INKLINEGREEN	_T("data/texture/inkline.green.png")			// �t���[���p�摜
#define TEXTURE_COLORINKFRAME   _T("data/texture/colorinkframe.png")
#define COLORINKLINE_SIZE		D3DXVECTOR3(100.0f, 30.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define INKLINEBLUE_POS     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define INKLINERED_POS      D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define INKLINEYELLOW_POS   D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define INKLINEGREEN_POS    D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define COLORINKFRAME_POS01 D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS02 D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS03 D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define COLORINKFRAME_POS04 D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Colorinkline :
	public _2dobj {
public:
	Colorinkline(D3DXVECTOR3 _pos, const char *texno); //const�ɂ��萔���𐬂�define�̎g�p�@�|�C���^�ɂ��Ȃ���texture�t�@�C���������Ƃ�Ȃ�
	~Colorinkline();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif