//=============================================================================
//
// �o�g����ʃt���[���\������ [Face3.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _FACE3_H_
#define _FACE3_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FACE3_SIZE		D3DXVECTOR3(50.0f, 50.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define FACE3_POS01     D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE3_POS02		D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE3_POS03		D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE3_POS04		D3DXVECTOR3(954.0f, 0.0f, 0.0f)

#define FACE31_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define FACE32_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE33_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE34_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Face3 :
	public _2dobj {
public:
	Face3(D3DXVECTOR3 _pos, const char *texno);
	~Face3();

	int fc;

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif