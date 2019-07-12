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
// �N���X��`
//*****************************************************************************
class FaceFrame : public _2dobj 
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^

	HRESULT MakeVertex(void);
	void SetVertex(void);

public:
	FaceFrame(int PlayerNo);
	~FaceFrame();
	static void ReleaseTexture(void);

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	void SetPlayerDeadTexture(void);
};

#endif