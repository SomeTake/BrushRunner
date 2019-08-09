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
#include "PaintGroup.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_FRAME (240)	// �X�^�[�g����܂ł̃^�C�}�[


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneGame
{
private:
	std::vector<_2dobj*> UIObject;
	Map *pMap;							// �}�b�v�p�̃|�C���^
	Effect *pEffect[EffectMax];			// �G�t�F�N�g�p�̃|�C���^
	Player *pPlayer[PLAYER_MAX];			// �v���C���[�p�̃|�C���^
	QUADTREE *Quadtree = nullptr;
	PaintGroup *paintGroup = nullptr;

	void Collision();

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

};

#endif
