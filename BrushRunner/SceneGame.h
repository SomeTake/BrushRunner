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
#include "Quadtree.h"
#include "Player.h"
#include "PaintManager.h"
#include "EffectManager.h"

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

	// �A�C�e���\��
	NumItem00,
	NumItem01,
	NumItem02,
	NumItem03,

	// ----- �ő吔 -----
	_2dMax,
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneGame
{
private:
	std::vector<_2dobj*> UIObject;			// UI
	Map		*pMap;							// �}�b�v
	Player	*pPlayer[PLAYER_MAX];			// �v���C���[
	QUADTREE *Quadtree = nullptr;			// �l����
	EffectManager *pEffectManager;			// 2D�G�t�F�N�g�Ǘ�

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

#endif
