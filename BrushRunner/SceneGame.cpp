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
#include "Player.h"

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
PLAYER *pPlayer;

//=============================================================================
// ������
//=============================================================================
HRESULT InitSceneGame()
{

	pMap = new MAP();
	p2dobj[NumFrame01] = new Frame01();


	p2dobj[NumInklineblue] = new Colorinkline(INKLINEBLUE_POS, TEXTURE_INKLINEBLUE);
	p2dobj[NumInklinered] = new Colorinkline(INKLINERED_POS, TEXTURE_INKLINERED);
	p2dobj[NumInklineyellow] = new Colorinkline(INKLINEYELLOW_POS, TEXTURE_INKLINEYELLOW);
	p2dobj[NumInklinegreen] = new Colorinkline(INKLINEGREEN_POS, TEXTURE_INKLINEGREEN);

	p2dobj[NumColorinkline01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_COLORINKFRAME);
	p2dobj[NumColorinkline04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_COLORINKFRAME);


	p2dobj[NumFaceframe01] = new Faceframe(FACEFRAME_POS01);
	p2dobj[NumFaceframe02] = new Faceframe(FACEFRAME_POS02);
	p2dobj[NumFaceframe03] = new Faceframe(FACEFRAME_POS03);
	p2dobj[NumFaceframe04] = new Faceframe(FACEFRAME_POS04);


	p2dobj[NumInklineblack01] = new Colorinkline(INKLINEBLACK_POS01, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack02] = new Colorinkline(INKLINEBLACK_POS02, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack03] = new Colorinkline(INKLINEBLACK_POS03, TEXTURE_INKLINEBLACK);
	p2dobj[NumInklineblack04] = new Colorinkline(INKLINEBLACK_POS04, TEXTURE_INKLINEBLACK);
	
	p2dobj[NumInklineblackframe01] = new Colorinkline(COLORINKFRAME_POS01, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe02] = new Colorinkline(COLORINKFRAME_POS02, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe03] = new Colorinkline(COLORINKFRAME_POS03, TEXTURE_BLACKINKFRAME);
	p2dobj[NumInklineblackframe04] = new Colorinkline(COLORINKFRAME_POS04, TEXTURE_BLACKINKFRAME);

	
	pMap = new MAP();

	pPlayer = new PLAYER();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneGame()
{
	delete pMap;

	// 2D�I�u�W�F�N�g�̍폜
	for (int i = 0; i < _2dMax; i++)
	{
		delete p2dobj[i];
	}

	delete pPlayer;
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

	pPlayer->Update();
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

	pPlayer->Draw();
}