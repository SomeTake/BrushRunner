//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

// �T�E���h�t�@�C��
typedef enum
{
	// SE�i�T�E���h�G�t�F�N�g�j
	SE_DEFEND0,
	SE_HIT0,
	SE_HIT1,
	SE_SWING0,
	SE_SELECT0,
	SE_SELECT1,
	SE_WINNER0,
	SE_KO,
	SE_EFFECT0,
	SE_CUTIN0,
	SE_COUNTDOWN,
	// BGM�i���y�j
	BGM_TITLE,
	BGM_TUTORIAL,
	BGM_TRAINING,
	BGM_BATTLE,

	//-----------------------------------------------------------------------------
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
