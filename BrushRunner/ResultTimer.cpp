//=============================================================================
//
// ���U���g��ʂł̃^�C�}�[�\�� [ResultTimer.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ResultTimer.h"

LPD3DXFONT ResultTimer::Font[2] = { nullptr, nullptr };

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ResultTimer::ResultTimer(DWORD _time, int _rank)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	startTime = 0;
	currentTime = 0;
	elapsedTime = _time;
	this->Rank = _rank;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		digit[i] = 0;
	}

	// �~���b
	digit[0] = (elapsedTime / 10) % 10;
	digit[1] = (elapsedTime / 100) % 10;

	// �b
	digit[2] = (elapsedTime / 1000) % 10;
	digit[3] = (elapsedTime / 10000) % 6;

	// ��
	digit[4] = (elapsedTime / 60000) % 10;
	digit[5] = (elapsedTime / 600000) % 6;

	// �ЂƂ������I�u�W�F�N�g�𐶐�
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new ResultDigit(digit[i], i, _rank);
	}

	// ���\���p�t�H���g�̐ݒ�
	D3DXCreateFont(Device, 108, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Consolas"), &Font[0]);

	D3DXCreateFont(Device, 72, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Consolas"), &Font[1]);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ResultTimer::~ResultTimer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SAFE_DELETE(time[i]);
	}

	SAFE_RELEASE(Font[0]);
	SAFE_RELEASE(Font[1]);
}

//=============================================================================
// �X�V
//=============================================================================
void ResultTimer::Update()
{
	// �ЂƂ������X�V
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void ResultTimer::Draw()
{
	if (Rank == 0)
	{
		// ���ƕb�Ԃ�':'
		RECT Min_Sec = { 620, 55, 715, 205 };
		// �b�ƃ~���b�Ԃ�':'
		RECT Sec_ms = { 790, 55, 885, 205 };
		Font[0]->DrawText(NULL, ":", -1, &Min_Sec, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
		Font[0]->DrawText(NULL, ":", -1, &Sec_ms, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{
		RECT Min_Sec;
		RECT Sec_ms;
		if (Rank == 1)
		{
			Min_Sec = { 585, 395, 650, 485 };
			Sec_ms = { 695, 395, 760, 485 };
		}
		else if (Rank == 2)
		{
			Min_Sec = { 585, 490, 650, 580 };
			Sec_ms = { 695, 490, 760, 580 };
		}
		else if (Rank == 3)
		{
			Min_Sec = { 585, 585, 650, 675 };
			Sec_ms = { 695, 585, 760, 675 };
		}

		Font[1]->DrawText(NULL, ":", -1, &Min_Sec, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
		Font[1]->DrawText(NULL, ":", -1, &Sec_ms, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
	}

	// �ЂƂ������`��
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Draw();
	}
}