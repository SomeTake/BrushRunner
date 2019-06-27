//=============================================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "debugproc.h"
#include "DebugWindow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPD3DXFONT	g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^
char				g_aStrDebug[1024] = { "\0" };	// �f�o�b�O���
// �������x�v�Z
LARGE_INTEGER		StartTime;
double				UpdateTime = 0.0;
double				DrawTime = 0.0;

//=============================================================================
// �f�o�b�O�\�������̏�����
//=============================================================================
HRESULT InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(Device, 24, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas", &g_pD3DXFont);

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// �f�o�b�O�\�������̏I������
//=============================================================================
void UninitDebugProc(void)
{
	// ���\���p�t�H���g�̊J��
	SAFE_RELEASE(g_pD3DXFont);
}

//=============================================================================
// �f�o�b�O�\�������̍X�V����
//=============================================================================
void UpdateDebugProc(void)
{
}

//=============================================================================
// �f�o�b�O�\�������̕`�揈��
//=============================================================================
void DrawDebugProc(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// ���\��
	g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
//=============================================================================
void PrintDebugProc(const char *fmt, ...)
{
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
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
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if ((strlen(g_aStrDebug) + strlen(aBuf)) < ((sizeof g_aStrDebug) - 1))
	{
		strcat(g_aStrDebug, aBuf);
	}
}

//=============================================================================
// �����J�n�̎��Ԃ��L�^
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
// �����I���̎��Ԃ��L�^
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
// FPS�Ə������Ԃ�\��
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
