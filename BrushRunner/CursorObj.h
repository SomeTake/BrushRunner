//=============================================================================
//
// �L�����N�^�[�Z���N�g�J�[�\�� [CursorObj.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _CURSOROBJ_H_
#define _CURSOROBJ_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_CURSOROBJ	("data/TEXTURE/CharSelectCursor.png")		// �t���[���p�摜
#define CURSOROBJ_DIVIDE_X	(4)											// ������
#define CURSOROBJ_MAX		(4)											// 1�v���C���[������̃J�[�\����

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CursorObj :
	public _2dobj
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;	// �e�N�X�`���̃|�C���^

	HRESULT MakeVertex();
	void SetTexture();
	void SetVertex();

	void Move();	// �J�[�\���̈ړ�

public:
	int playerNo;	// �Q�Ƃ���v���C���[�ԍ�
	int cursorNo;	// ���W���Q�Ƃ���ԍ�
	int selectNo;	// �I�������L�����N�^�[�̔ԍ�

	CursorObj(int playerNo, int cursorNo);
	~CursorObj();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();

	int GetCursorNo() { return cursorNo; };
	int GetSelectNo() { return selectNo; };

};

#endif