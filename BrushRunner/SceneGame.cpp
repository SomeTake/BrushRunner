//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Map.h"
#include "Camera.h"
#include "_2dobj.h"
#include "Effect.h"

enum {
	HitEffect,
	Hit1Effect,
	RunEffect,
	ExpEffect,
	ItemEffect,

	// �G�t�F�N�g�̌�
	EffectMax,
};

// �I�u�W�F�N�g�̃|�C���^
MAP *pMap;
EFFECT *pEFFECT[EffectMax];
//=============================================================================
// ������
//=============================================================================
HRESULT InitSceneGame()
{
	pMap = new MAP();

	pEFFECT[HitEffect] = new EFFECT(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEFFECT[Hit1Effect] = new EFFECT(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEFFECT[RunEffect] = new EFFECT(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEFFECT[ExpEffect] = new EFFECT(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEFFECT[ItemEffect] = new EFFECT(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneGame()
{
	delete pMap;
	for (int i = 0; i < EffectMax; i++)
	{
		delete pEFFECT[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateSceneGame()
{
	UpdateCamera();

	pMap->Update();
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneGame()
{
	pMap->Draw();
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Draw();
	}
}