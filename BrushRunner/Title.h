//=============================================================================
//
// �^�C�g���\������ [Title.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "_2dobj.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TITLE :
	public _2dobj
{
public:
	TITLE(int num);
	~TITLE();


	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
	void SetVertexMove(D3DXVECTOR3 pos);
};

#endif
