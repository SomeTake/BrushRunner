//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_FRAME (240)	// �X�^�[�g����܂ł̃^�C�}�[

// 2dobj�̌�(�`�揇�恨��)
enum Num2dobj
{
	// ��ԊO�̃t���[��
	NumFrame,

	// ���C���N
	NumInkblack00,
	NumInkblack01,
	NumInkblack02,
	NumInkblack03,

	// ���C���N�̃t���[��
	NumBlackFrame00,
	NumBlackFrame01,
	NumBlackFrame02,
	NumBlackFrame03,

	// �J���[�C���N
	NumInkblue,
	NumInkred,
	NumInkyellow,
	NumInkgreen,

	// �J���[�C���N�̃t���[��
	NumColorFrame00,
	NumColorFrame01,
	NumColorFrame02,
	NumColorFrame03,

	// ��̃t���[��
	NumFaceframe00,
	NumFaceframe01,
	NumFaceframe02,
	NumFaceframe03,

	// �J�E���g�_�E��
	NumCountDown,

	// ----- �ő吔 -----
	_2dMax,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSceneGame();
void UninitSceneGame();
void UpdateSceneGame();
void DrawSceneGame();

int GetDraw2dobjBuff(int _num);						// 2D�I�u�W�F�N�g�̕`�揇���擾
void SetDraw2dobjBuff(int _BuffNum, int _DrawNum);	// 2D�I�u�W�F�N�g�̕`�揇���Z�b�g
void ChangeDrawOrder(int _NumA, int _NumB);			// �`�揇�����ւ���

D3DXVECTOR3 CompareXPos();							// X���W���r���đ傫��2�̒��S���W��Ԃ�

#endif
