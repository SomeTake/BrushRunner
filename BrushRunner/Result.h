//=============================================================================
//
// �^�C�g���\������ [Result.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_RESULT01 _T("data/texture/result.png")											// �^�C�g���̃e�N�X�`��
#define RESULT_SIZE01			D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)					// �e�N�X�`���T�C�Y
#define RESULT_POS01				D3DXVECTOR3(0.0f,0.0f,0.0f)									// �e�N�X�`�����W



//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RESULT :
	public _2dobj
{
public:
	RESULT(D3DXVECTOR3 _pos, D3DXVECTOR3 _size, const char *texno);
	~RESULT();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
};

#endif
