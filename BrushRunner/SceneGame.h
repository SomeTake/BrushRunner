//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "Scene.h"

// �|�C���^�Ƃ��Ď擾����K�v�̂���N���X
#include "Map.h"
#include "_2dobj.h"
#include "Quadtree.h"
#include "Player.h"
#include "PaintManager.h"
#include "EffectManager.h"
#include "Sky.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_FRAME (240)	// �X�^�[�g����܂ł̃^�C�}�[

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneGame :
	public Scene
{
private:
	std::vector<_2dobj*> UIObject;			// UI
	Map		*pMap;							// �}�b�v
	Player	*pPlayer[PLAYER_MAX];			// �v���C���[
	QUADTREE *Quadtree = nullptr;			// �l����
	EffectManager *pEffectManager;			// 2D�G�t�F�N�g�Ǘ�
	Sky		*pSky;							// ��
	int		startframe;						// �J�n�J�E���g�_�E��
	bool	result;							// �I���t���O

	void Start();
	void Collision();
	void CheckResult();
	void InsertResult(int pNo);

	void Debug();

public:
	SceneGame();
	~SceneGame();
	void Update(int SceneID);
	void Draw();

};

int *GetResultRank(int no);					// ���ʌ��ʂ��擾

#endif
