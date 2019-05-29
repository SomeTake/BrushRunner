//=============================================================================
//
// �o�g����ʃt���[���\������ [Faceframe.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _FACEFRAME_H_
#define _FACEFRAME_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FACEFRAME	_T("data/texture/faceframe.png")			// �t���[���p�摜
#define FACEFRAME_SIZE		D3DXVECTOR3(200.0f, 88.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define FACEFRAME_POS01     D3DXVECTOR3(10.0f, 10.0f, 0.0f)
#define FACEFRAME_POS02		D3DXVECTOR3(328.0f, 10.0f, 0.0f)
#define FACEFRAME_POS03		D3DXVECTOR3(646.0f, 10.0f, 0.0f)
#define FACEFRAME_POS04		D3DXVECTOR3(964.0f, 10.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FACEFRAME :
	public _2dobj {
public:
	FACEFRAME(D3DXVECTOR3 _pos);
	~FACEFRAME();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif