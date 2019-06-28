//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

// �|�C���^�Ƃ��Ď擾����K�v�̂���N���X
#include "Map.h"
#include "_2dobj.h"
#include "Effect.h"
#include "Quadtree.h"
#include "Player.h"
#include "PaintSystem.h"
#include "Pop.h"

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
// �N���X��`
//*****************************************************************************
class SceneGame
{
private:
	_2dobj *p2dobj[_2dMax];				// 2D�I�u�W�F�N�g�p�̃|�C���^
	Map *pMap;							// �}�b�v�p�̃|�C���^
	Effect *pEffect[EffectMax];			// �G�t�F�N�g�p�̃|�C���^
	Player *pPlayer[PLAYER_MAX];			// �v���C���[�p�̃|�C���^
	Cursor *pCursor[PLAYER_MAX];			// �J�[�\���p�̃|�C���^
	PaintManager *pPManager[PLAYER_MAX];	// �y�C���g�V�X�e���p�̃|�C���^
	Pop *pPop[PLAYER_MAX];				// �|�b�v�A�b�v�p�̃|�C���^
	QUADTREE *Quadtree = nullptr;

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

int GetDraw2dobjBuff(int _num);						// 2D�I�u�W�F�N�g�̕`�揇���擾
void SetDraw2dobjBuff(int _BuffNum, int _DrawNum);	// 2D�I�u�W�F�N�g�̕`�揇���Z�b�g
void ChangeDrawOrder(int _NumA, int _NumB);			// �`�揇�����ւ���


#endif
