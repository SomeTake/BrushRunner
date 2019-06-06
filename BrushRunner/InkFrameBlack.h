//=============================================================================
//
// ���C���N�p�t���[������ [InkFrameBlack.h]
// Author : HAL���� �y�����
//
//=============================================================================
#ifndef _INKFRAMEBLACK_H_
#define _INKFRAMEBLACK_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BLACKINKFRAME   _T("data/texture/blackinkframe.png")
#define BLACKINKLINE_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define BLACKINKFRAME_POS01 D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS02 D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS03 D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define BLACKINKFRAME_POS04 D3DXVECTOR3(964.0f, 10.0f, 0.0f)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class INKFRAMEBLACK :
	public _2dobj {
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^

public:
	INKFRAMEBLACK(D3DXVECTOR3 _pos);
	~INKFRAMEBLACK();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif