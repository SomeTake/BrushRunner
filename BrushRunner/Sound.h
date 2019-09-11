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
	BGM_STAGESELECT,
	BGM_CHARSEL,
	BGM_STAGE01,
	BGM_STAGE02,
	BGM_STAGE03,
	BGM_RESULT,
	// SE（サウンドエフェクト）
	SE_CHOICE,
	SE_SELECT,
	SE_PICITEM,
	SE_EXP,
	SE_USEITEM,
	SE_JUMP,
	SE_COUNT,
	SE_ITEMRU,
	SE_DAMAGE,
	SE_GOAL,

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
