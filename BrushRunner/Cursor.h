//=============================================================================
//
// �J�[�\���\�� [Cursor.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "_2dobj.h"
#include "CharacterAI.h"


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Cursor : public _2dobj
{
private:
	int		ctrlNum;			// ���삷��R���g���[���ԍ�
	float	vec = 0.0f;			// �W���C�X�e�B�b�N�̃x�N�g����1/1000�ɂ��ĕۑ�(1.0f-0.0f)
	float	moveX = 0.0f;		// �W���C�X�e�B�b�N��X�l��1/1000�ɂ��ĕۑ�(1.0f-0.0f)
	float	moveY = 0.0f;		// �W���C�X�e�B�b�N��Y�l��1/1000�ɂ��ĕۑ�(1.0f-0.0f)

	// AI�p
	CharacterAI		*AIptr = nullptr;
	bool			AIUse = false;
	D3DXVECTOR3		WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	void PaintPath(void);					// �C���N�Œʂ�铹�����
	void DeletePath(void);					// ���̃v���C���[�̃y�C���g���폜
	void PaintObjChip(void);				// �I�u�W�F�N�g�`�b�v���y�C���g����

	HRESULT MakeVertex();				// ���_�̍쐬
	void SetTexture();					// �e�N�X�`�����W�̐ݒ�
	void SetVertex();					// ���_���W�̐ݒ�
	void KeyMove();						// �L�[�{�[�h����
	void PadMove();						// �R���g���[������
	void Move();						// ����
	void CalWorldPos();

public:
	Cursor(int PlayerNo, bool AIUse, CharacterAI *AIptr);
	~Cursor();

	// �X�V
	void Update();
	// �`��
	void Draw();	
	// �C���N��؂�ւ�
	void ChangeInk();						

	// �J�[�\���̍��W���擾
	D3DXVECTOR3 GetPos(void) { return this->pos; };
	D3DXVECTOR3 GetWorldPos(void) { return this->WorldPos; };
};

#endif
