//=============================================================================
//
// デバッグ表示処理 [debugproc.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "debugproc.h"
#include "DebugWindow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPD3DXFONT	g_pD3DXFont = NULL;			// フォントへのポインタ
char				g_aStrDebug[1024] = { "\0" };	// デバッグ情報
// 処理速度計算
LARGE_INTEGER		StartTime;
double				UpdateTime = 0.0;
double				DrawTime = 0.0;

//=============================================================================
// デバッグ表示処理の初期化
//=============================================================================
HRESULT InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	HRESULT hr;

	// 情報表示用フォントを設定
	hr = D3DXCreateFont(Device, 24, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas", &g_pD3DXFont);

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// デバッグ表示処理の終了処理
//=============================================================================
void UninitDebugProc(void)
{
	// 情報表示用フォントの開放
	SAFE_RELEASE(g_pD3DXFont);
}

//=============================================================================
// デバッグ表示処理の更新処理
//=============================================================================
void UpdateDebugProc(void)
{
}

//=============================================================================
// デバッグ表示処理の描画処理
//=============================================================================
void DrawDebugProc(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// 情報表示
	g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// デバッグ表示の登録
//=============================================================================
void PrintDebugProc(const char *fmt, ...)
{
	va_list list;			// 可変引数を処理する為に使用する変数
	char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = (char *)fmt;
	for (; *pCur; ++pCur)
	{
		if (*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch (*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%.2f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

	// 連結
	if ((strlen(g_aStrDebug) + strlen(aBuf)) < ((sizeof g_aStrDebug) - 1))
	{
		strcat(g_aStrDebug, aBuf);
	}
}

//=============================================================================
// 処理開始の時間を記録
//=============================================================================
void ProcessStart(int ProcessPhase)
{
	QueryPerformanceCounter(&StartTime);
	switch (ProcessPhase)
	{
	case Process_Update:
		UpdateTime = 0.0;
		break;
	case Process_Draw:
		DrawTime = 0.0;
		break;
	default:
		break;
	}
}

//=============================================================================
// 処理終了の時間を記録
//=============================================================================
void ProcessEnd(int ProcessPhase)
{
	LARGE_INTEGER e, f;
	QueryPerformanceCounter(&e);
	QueryPerformanceFrequency(&f);
	switch (ProcessPhase)
	{
	case Process_Update:
		UpdateTime = (double)(e.QuadPart - StartTime.QuadPart) / f.QuadPart;
		break;
	case Process_Draw:
		DrawTime = (double)(e.QuadPart - StartTime.QuadPart) / f.QuadPart;
		break;
	default:
		break;
	}
}

//=============================================================================
// FPSと処理時間を表示
//=============================================================================
void DrawProcessTime(int FPSCount)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char ProcessTime[512];

	//sprintf_s(ProcessTime, 512, "FPS = %d\nUpdateTime = %f\nDrawTime = %f\n", FPSCount, UpdateTime, DrawTime);
	//g_pD3DXFont->DrawText(NULL, ProcessTime, -1, &rect, DT_LEFT | DT_BOTTOM, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

	BeginDebugWindow("FrameCount");
	DebugText("FPS = %d\nUpdateTime = %f\nDrawTime = %f\n", FPSCount, UpdateTime, DrawTime);
	EndDebugWindow("FrameCount");
}
