//=============================================================================
//
// リザルト画面でのタイマー表示 [ResultTimer.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ResultTimer.h"
#include "ResourceManager.h"

// 後で要調整
#define RESULTTIMER_POS		D3DXVECTOR3(SCREEN_CENTER_X - 2.0f, 132.0f, 0.0f)
#define RESULTTIMER_SIZE	D3DXVECTOR3(256.0f, 60.0f, 0.0f)

LPD3DXFONT ResultTimer::Font[2] = { nullptr, nullptr };

//=============================================================================
// コンストラクタ
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

	// ミリ秒
	digit[0] = (elapsedTime / 10) % 10;
	digit[1] = (elapsedTime / 100) % 10;

	// 秒
	digit[2] = (elapsedTime / 1000) % 10;
	digit[3] = (elapsedTime / 10000) % 6;

	// 分
	digit[4] = (elapsedTime / 60000) % 10;
	digit[5] = (elapsedTime / 600000) % 6;

	// ひとけたずつオブジェクトを生成
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new ResultDigit(digit[i], i, _rank);
	}

	// 情報表示用フォントの設定
	D3DXCreateFont(Device, 108, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Consolas"), &Font[0]);

	D3DXCreateFont(Device, 72, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Consolas"), &Font[1]);
	ResourceManager::Instance()->GetTexture("Timer", &D3DTexture);
	pos = RESULTTIMER_POS;
	size = RESULTTIMER_SIZE;
	use = true;

	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
ResultTimer::~ResultTimer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SAFE_DELETE(time[i]);
	}

	SAFE_RELEASE(Font[0]);
	SAFE_RELEASE(Font[1]);
	D3DTexture = NULL;
}

//=============================================================================
// 更新
//=============================================================================
void ResultTimer::Update()
{
	// ひとけたずつ更新
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void ResultTimer::Draw()
{
	if (Rank == 0)
	{
		// 分と秒間の':'
		RECT Min_Sec = { 620, 55, 715, 205 };
		// 秒とミリ秒間の':'
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
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定（ポリゴンの描画前に読み込んだテクスチャのセットを行う）
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何も貼らないことを指定するpDevice->SetTexture(0,NULL);
		pDevice->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

	// ひとけたずつ描画
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Draw();
	}
}

