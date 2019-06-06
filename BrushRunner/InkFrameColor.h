//=============================================================================
//
// �J���[�C���N�p�t���[������ [InkFrameColor.h]
// Author : HAL���� �y�����
//
//=============================================================================
#ifndef _INKFRAMECOLOR_H_
#define _INKFRAMECOLOR_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_COLORINKFRAME   _T("data/texture/colorinkframe.png")
#define COLORINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define COLORINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define COLORINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class INKFRAMECOLOR :
	public _2dobj {
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^

public:
	INKFRAMECOLOR(D3DXVECTOR3 _pos);
	~INKFRAMECOLOR();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif