//=============================================================================
//
// �L�����N�^�[�Z���N�g��ʏ��� [SceneCharacterSelect.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "SceneCharacterSelect.h"
#include "Input.h"
//2d obje
#include "_2dobj.h"
#include "carsl_logo.h"
#include "carsl_obj.h"
#include "carsl_obj2.h"
#include "carsl_obj3.h"
enum
{
	logo,
	obj01,
	obj02,
	obj03,
	//NumColorinkline02,
	//NumColorinkline03,
	//NumColorinkline04,


	// �ő吔
	_2dMx,
};


static _2dobj *c2dobj[_2dMx];			// 2D�I�u�W�F�N�g�p�̃|�C���^
float a, b, c;
//=============================================================================
// ������
//=============================================================================
HRESULT InitSceneCharacterSelect()
{
	c2dobj[logo] = new Carsl_logo();
	c2dobj[obj01] = new Carsl_obj(CARSL_OBJ_POS01, TEXTURE_CARSL_OBJ);
	c2dobj[obj02] = new Carsl_obj2(CARSL_OBJ_POS02,TEXTURE_CARSL_OBJ2);
	c2dobj[obj03] = new Carsl_obj3(CARSL_OBJ_POS03,TEXTURE_CARSL_OBJ3);
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void UninitSceneCharacterSelect()
{
	// 2D�I�u�W�F�N�g�̍폜
	for (int i = 0; i < _2dMx; i++)
	{
		delete c2dobj[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UpdateSceneCharacterSelect()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetScene(SceneGame);
	}

	// 2D�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void DrawSceneCharacterSelect()
{
	// 2D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < _2dMx; i++)
	{
		c2dobj[i]->Draw();
	}
}

