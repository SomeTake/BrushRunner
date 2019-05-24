//=============================================================================
//
// �J�[�\���\�� [Cursor.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "_2dobj.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CURSOR_TEXTURE	_T("data/TEXTURE/pen.png")				// �e�N�X�`��
#define CURSOR_SIZE D3DXVECTOR2(50.0f, 100.0f)					// �T�C�Y
#define CURSOR_DIVIDE_X	(4)										// ������
#define CURSOR_DIVIDE_Y	(2)										// �c����
#define CURSOR_PATTERN	(CURSOR_DIVIDE_X * CURSOR_DIVIDE_Y)		// ������
#define CURSOR_FIRST_POS	D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
#define CURSOR_SPEED	(10.0f)									// �����X�s�[�h

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CURSOR :
	public _2dobj
{
private:
	int ctrlNum;		// ���삷��R���g���[���ԍ�
	PLAYER *pPlayer;	// �Q�Ƃ���L�����N�^�̃|�C���^

public:
	CURSOR(int _ctrlNum, PLAYER *pP);
	~CURSOR();

	// �I�[�o�[���C�h�֐�
	void Update();						// �X�V
	void Draw();						// �`��
	HRESULT MakeVertex();				// ���_�̍쐬
	void SetTexture(int cntPattern);	// �e�N�X�`�����W�̐ݒ�
	void SetVertex();					// ���_���W�̐ݒ�

	void Move();						// ����
	void Change();						// �؂�ւ�

	void KeyMove();						// �L�[�{�[�h����
	void PadMove();						// �R���g���[������

};

#endif
