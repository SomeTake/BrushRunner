//=============================================================================
//
// �o�g����ʃt���[���\������ [Face.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _FACE_H_
#define _FACE_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FACE_SIZE		D3DXVECTOR3(50.0f, 50.0f, 0.0f)		// �e�N�X�`���T�C�Y

#define FACE_POS01     D3DXVECTOR3(22.0f, 22.0f, 0.0f)
#define FACE_POS02		D3DXVECTOR3(340.0f, 22.0f, 0.0f)
#define FACE_POS03		D3DXVECTOR3(657.0f, 22.0f, 0.0f)
#define FACE_POS04		D3DXVECTOR3(975.0f, 22.0f, 0.0f)

#define FACE1_POS			D3DXVECTOR3(50.0f, 50.0f, 0.0f)
#define FACE2_POS			D3DXVECTOR3(318.0f, 0.0f, 0.0f)
#define FACE3_POS			D3DXVECTOR3(636.0f, 0.0f, 0.0f)
#define FACE4_POS			D3DXVECTOR3(954.0f, 0.0f, 0.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Face :
	public _2dobj {
public:
	Face(D3DXVECTOR3 _pos, const char *texno);
	~Face();

	int fc;

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif