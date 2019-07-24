//=============================================================================
//
// サウンド処理 [sound.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

// サウンドファイル
typedef enum
{
	// BGM（音楽）
	BGM_TITLE,
	BGM_TUTORIAL,
	BGM_CHARSEL,
	BGM_TRAINING,
	//BGM_BATTLE,
	// SE（サウンドエフェクト）
	SE_CHOICE,
	SE_SELECT,
	SE_PICITEM,
	SE_EXP,
	SE_USEITEM,
	SE_PAINT,
	//SE_WINNER0,
	//SE_KO,
	//SE_EFFECT0,
	//SE_CUTIN0,
	//SE_COUNTDOWN,

	//-----------------------------------------------------------------------------
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
