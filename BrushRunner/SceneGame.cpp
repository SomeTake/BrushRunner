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
#include "Player.h"
#include "Collision.h"
#include "Gravity.h"

//2d obje
#include "_2dobj.h"
#include "Frame01.h"
#include "Faceframe.h"
#include "blackinkline.h"
#include "colorinkline.h"
enum
{
	NumFrame01,

	NumFaceframe01,
	NumFaceframe02,
	NumFaceframe03,
	NumFaceframe04,


	NumInklineblack01,
	NumInklineblack02,
	NumInklineblack03,
	NumInklineblack04,

	NumInklineblackframe01,
	NumInklineblackframe02,
	NumInklineblackframe03,
	NumInklineblackframe04,

	NumInklineblue,
	NumInklinered,
	NumInklineyellow,
	NumInklinegreen,

	NumColorinkline01,
	NumColorinkline02,
	NumColorinkline03,
	NumColorinkline04,


	// �ő吔
	_2dMax,
};


static _2dobj *p2dobj[_2dMax];			// 2D�I�u�W�F�N�g�p�̃|�C���^
// �I�u�W�F�N�g�̃|�C���^
MAP *pMap;
PLAYER *pPlayer[PLAYER_MAX];

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
	p2dobj[NumFrame01] = new Frame01();

	// �J���[�C���N�̏�����
	p2dobj[NumInklineblue] = new Colorinkline(INKLINEBLUE_POS, TEXTURE_INKLINEBLUE);
	p2dobj[NumInklinered] = new Colorinkline(INKLINERED_POS, TEXTURE_INKLINERED);
	p2dobj[NumInklineyellow] = new Colorinkline(INKLINEYELLOW_POS, TEXTURE_INKLINEYELLOW);
	p2dobj[NumInklinegreen] = new Colorinkline(INKLINEGREEN_POS, TEXTURE_INKLINEGREEN);

	// �J���[�C���N�p�t���[���̏�����
	p2dobj[NumColorinkline01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_COLORINKFRAME);

	// ���\������t���[���̏�����
	p2dobj[NumFaceframe01] = new Faceframe(FACEFRAME_POS01);
	p2dobj[NumFaceframe02] = new Faceframe(FACEFRAME_POS02);
	p2dobj[NumFaceframe03] = new Faceframe(FACEFRAME_POS03);
	p2dobj[NumFaceframe04] = new Faceframe(FACEFRAME_POS04);

	// ���C���N�̏�����
	p2dobj[NumInklineblack01] = new Colorinkline(INKLINEBLACK_POS01, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack02] = new Colorinkline(INKLINEBLACK_POS02, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack03] = new Colorinkline(INKLINEBLACK_POS03, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack04] = new Colorinkline(INKLINEBLACK_POS04, TEXTURE_INKLINEBLACK);
	
	// ���C���N�p�t���[���̏�����
	p2dobj[NumInklineblackframe01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_BLACKINKFRAME);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneGame()
{
	delete pMap;

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

	// 2D�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Update();
	}
	UpdateCamera();

	pMap->Update();

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

	// �f�o�b�O�\��
#ifndef _DEBUG_

#endif
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneGame()
{

	// 2D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < _2dMax; i++)
	{
		p2dobj[i]->Draw();
	}

	pMap->Draw();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pPlayer[i]->Draw();
	}
}