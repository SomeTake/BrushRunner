//=============================================================================
//
// ���C������ [Main.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <time.h>
#include <dshow.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <vector>

#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "dinput.h"

using namespace std;

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define MY_VERTEX_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define SCREEN_WIDTH	(1280)											// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)											// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)								// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)								// �E�C���h�E�̒��S�x���W

#define TIME_PER_FRAME	(1/60.0f)										// 1/60�b

#define	NUM_VERTEX		(4)												// ���_��
#define	NUM_POLYGON		(2)												// �|���S����

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(5000.0f)										// �r���[���ʂ�FarZ�l


// �f�X�g���N�^
#define SAFE_DELETE(object)			{if(object){delete (object);		(object) = NULL;}}
#define SAFE_DELETE_ARRAY(object)	{if(object){delete[] (object);		(object) = NULL;}}
#define SAFE_RELEASE(object)		{if(object){(object)->Release();	(object)=NULL;}}

#define GetMonitorRect(rc) SystemParametersInfo(SPI_GETWORKAREA, 0, rc, 0)	// ���j�^�[��`

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;


//�V�[���J��
enum
{
	SceneTitle,				// �^�C�g��
	SceneCharacterSelect,	// �L�����N�^�[�Z���N�g
	SceneGame,				// �Q�[��
	SceneResult,			// ���U���g
	SceneExit				// �Q�[���I��
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X���擾����
int GetScene();					// ���݂̃Q�[���V�[�����擾����
void SetScene(int _scene);		// �Q�[���V�[����ύX����

#endif