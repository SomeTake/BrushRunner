//=============================================================================
//
// �Q�[����ʏ��� [SceneGame.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneGame.h"
#include "Debugproc.h"
#include "Map.h"
#include "Camera.h"
#include "_2dobj.h"
#include "Effect.h"

#include "Player.h"
#include "Collision.h"
#include "Gravity.h"
#include "Input.h"

//2d obj
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
#include "blackinkline.h"
#include "colorinkline.h"
#include "Ink.h"
#include "Cursor.h"


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
static _2dobj *p2dobj[_2dMax];			// 2D�I�u�W�F�N�g�p�̃|�C���^
MAP *pMap;
EFFECT *pEFFECT[EffectMax];
PLAYER *pPlayer[PLAYER_MAX];

static int Draw2dobjBuff[_2dMax];			// UI�̕`�揇��ύX���邽�߂̔z��

//=============================================================================
// ������
//=============================================================================
HRESULT InitSceneGame()
{
	// �v���C���[�̏�����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i] = new PLAYER(i);
	}

	// �}�b�v�̏�����
	pMap = new MAP();

	// 2DUI�̏�����
	// �t���[��
	p2dobj[NumFrame] = new FRAME();

	// ���C���N�̏�����
	p2dobj[NumInkblack00] = new INK(pPlayer[0], INKLINEBLACK_POS01, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack01] = new INK(pPlayer[1], INKLINEBLACK_POS02, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack02] = new INK(pPlayer[2], INKLINEBLACK_POS03, TEXTURE_INKLINEBLACK, BlackInk);
	p2dobj[NumInkblack03] = new INK(pPlayer[3], INKLINEBLACK_POS04, TEXTURE_INKLINEBLACK, BlackInk);

	// ���C���N�p�t���[���̏�����
	p2dobj[NumBlackFrame00] = new INKFRAME(BLACKINKFRAME_POS01, TEXTURE_BLACKINKFRAME);
	p2dobj[NumBlackFrame01] = new INKFRAME(BLACKINKFRAME_POS02, TEXTURE_BLACKINKFRAME);
	p2dobj[NumBlackFrame02] = new INKFRAME(BLACKINKFRAME_POS03, TEXTURE_BLACKINKFRAME);
	p2dobj[NumBlackFrame03] = new INKFRAME(BLACKINKFRAME_POS04, TEXTURE_BLACKINKFRAME);

	// �J���[�C���N�̏�����
	p2dobj[NumInkblue] = new INK(pPlayer[0], INKLINEBLUE_POS, TEXTURE_INKLINEBLUE, ColorInk);
	p2dobj[NumInkred] = new INK(pPlayer[1], INKLINERED_POS, TEXTURE_INKLINERED, ColorInk);
	p2dobj[NumInkyellow] = new INK(pPlayer[2], INKLINEYELLOW_POS, TEXTURE_INKLINEYELLOW, ColorInk);
	p2dobj[NumInkgreen] = new INK(pPlayer[3], INKLINEGREEN_POS, TEXTURE_INKLINEGREEN, ColorInk);

	// �J���[�C���N�p�t���[���̏�����
	p2dobj[NumColorFrame00] = new INKFRAME(COLORINKFRAME_POS01, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame01] = new INKFRAME(COLORINKFRAME_POS02, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame02] = new INKFRAME(COLORINKFRAME_POS03, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorFrame03] = new INKFRAME(COLORINKFRAME_POS04, TEXTURE_COLORINKFRAME);

	// ���\������t���[���̏�����
	p2dobj[NumFaceframe00] = new FACEFRAME(FACEFRAME_POS01);
	p2dobj[NumFaceframe01] = new FACEFRAME(FACEFRAME_POS02);
	p2dobj[NumFaceframe02] = new FACEFRAME(FACEFRAME_POS03);
	p2dobj[NumFaceframe03] = new FACEFRAME(FACEFRAME_POS04);
	
	// �J�[�\���̏�����
	for (int i = Cursor0; i < Cursor0 + PLAYER_MAX; i++)
	{
		p2dobj[i] = new CURSOR(i - Cursor0, pPlayer[i - Cursor0]);
	}

	// �G�t�F�N�g�̏�����
	pEFFECT[HitEffect] = new EFFECT(EFFECT_TEXTURE0, EFFECT0_SIZE, EFFET0_POS, TIME_ANIMATION_EFFECT0, EFFECT_PATTERN_X, EFFECT_PATTERN_Y);
	pEFFECT[Hit1Effect] = new EFFECT(EFFECT_TEXTURE1, EFFECT1_SIZE, EFFET1_POS, TIME_ANIMATION_EFFECT1, EFFECT1_PATTERN_X, EFFECT1_PATTERN_Y);
	pEFFECT[RunEffect] = new EFFECT(EFFECT_TEXTURE2, EFFECT2_SIZE, EFFET2_POS, TIME_ANIMATION_EFFECT2, EFFECT2_PATTERN_X, EFFECT2_PATTERN_Y);
	pEFFECT[ExpEffect] = new EFFECT(EFFECT_TEXTURE3, EFFECT3_SIZE, EFFET3_POS, TIME_ANIMATION_EFFECT3, EFFECT3_PATTERN_X, EFFECT3_PATTERN_Y);
	pEFFECT[ItemEffect] = new EFFECT(EFFECT_TEXTURE4, EFFECT4_SIZE, EFFET4_POS, TIME_ANIMATION_EFFECT4, EFFECT4_PATTERN_X, EFFECT4_PATTERN_Y);

	// �`�揇�̏�����
	for (int i = 0; i < _2dMax; i++)
	{
		Draw2dobjBuff[i] = i;
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneGame()
{
	// �}�b�v�̍폜
	delete pMap;
	for (int i = 0; i < EffectMax; i++)
	{
		delete pEFFECT[i];
	}

	// �v���C���[�̍폜
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete pPlayer[i];
	}

	// 2D�I�u�W�F�N�g�̍폜
	for (int i = 0; i < _2dMax; i++)
	{
		delete p2dobj[i];
	}

}

//=============================================================================
// �X�V
//=============================================================================
void UpdateSceneGame()
{
	// �J�����̍X�V
	UpdateCamera(CompareXPos());

	// 2D�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Update();
	}

	// �}�b�v�̍X�V
	pMap->Update();
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Update();
	}

	// �v���C���[�̍X�V
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Update();

		// �n�ʂɐڂ��Ă��邩�m�F
		if (HitCheckPToM(pPlayer[i], pMap))
		{
			pPlayer[i]->SetJumpFlag(false);
		}
		// �n�ʂɐڂ��Ă��Ȃ��̂ŁA��������
		else
		{
			GravityFall(pPlayer[i]);
		}
	}

#ifndef _DEBUG_

#endif
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneGame()
{
	// �}�b�v�̕`��
	pMap->Draw();

	// �v���C���[�̕`��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}

	// 2D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[Draw2dobjBuff[i]]->Draw();
	}

	// �G�t�F�N�g�̕`��
	for (int i = 0; i < EffectMax; i++)
	{
		pEFFECT[i]->Draw();
	}
}

//=============================================================================
// 2D�I�u�W�F�N�g�̕`�揇���擾
//=============================================================================
int GetDraw2dobjBuff(int _num)
{
	return Draw2dobjBuff[_num];
}

//=============================================================================
// 2D�I�u�W�F�N�g�̕`�揇���Z�b�g
//=============================================================================
void SetDraw2dobjBuff(int _BuffNum, int _DrawNum)
{
	Draw2dobjBuff[_BuffNum] = _DrawNum;
}

//=============================================================================
// �`�揇�����ւ���
//=============================================================================
void ChangeDrawOrder(int _NumA, int _NumB)
{
	int change = GetDraw2dobjBuff(_NumA);
	SetDraw2dobjBuff(_NumA, GetDraw2dobjBuff(_NumB));
	SetDraw2dobjBuff(_NumB, change);

}

//=============================================================================
// X���W���r���āA�傫��2�̒��S���W��Ԃ�
//=============================================================================
D3DXVECTOR3 CompareXPos()
{
	float CmpPos[PLAYER_MAX];

	// �v���C���[�̍��W���i�[
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		CmpPos[i] = pPlayer[i]->GetPos().x;
	}

	// QuickSort�֐� ����1 ��r����z��̐擪�v�f
	//				 ����2 �z��̗v�f��
	//				 ����3 �^�̃T�C�Y
	//				 ����4 ��r�p�̊֐�
	qsort(CmpPos, PLAYER_MAX, sizeof(float), CmpDescendf);

	float CmpY[2];

	// 1�߂̗v�f�m��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (CmpPos[0] == pPlayer[i]->GetPos().x)
		{
			CmpY[0] = pPlayer[i]->GetPos().y;
			break;
		}
	}

	// 2�߂̗v�f�m��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (CmpPos[1] == pPlayer[i]->GetPos().x)
		{
			CmpY[1] = pPlayer[i]->GetPos().y;
			break;
		}
	}

	return D3DXVECTOR3((CmpPos[0] + CmpPos[1]) * 0.5f, (CmpY[0] + CmpY[1]) * 0.5f, 0.0f);
}

//=============================================================================
// ��r�֐�(�~��)float�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpDescendf(const void *p, const void *q)
{
	if (*(float*)p < *(float*)q)
	{
		return 1;
	}
	if (*(float*)p > *(float*)q)
	{
		return -1;
	}
	return 0;
}

//=============================================================================
// ��r�֐�(����)float�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpAscendf(const void *p, const void *q)
{
	if (*(float*)p > *(float*)q)
	{
		return 1;
	}
	if (*(float*)p < *(float*)q)
	{
		return -1;
	}
	return 0;
}

//=============================================================================
// ��r�֐�(�~��)int�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpDescend(const void *p, const void *q)
{
	return *(int*)q - *(int*)p;
}

//=============================================================================
// ��r�֐�(����)int�p
// qsort�֐��̑�4�����ɓ���Ďg��
//=============================================================================
int CmpAscend(const void *p, const void *q)
{
	return *(int*)p - *(int*)q;
}
