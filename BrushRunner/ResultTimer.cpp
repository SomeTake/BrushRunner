#include "Main.h"
#include "ResultTimer.h"

ResultTimer::ResultTimer(DWORD _time, int _rank)
{
	startTime = 0;
	currentTime = 0;
	elapsedTime = _time;

	// ミリ秒
	digit[0] = (elapsedTime / 10) % 10;
	digit[1] = (elapsedTime / 100) % 10;

	// 秒
	digit[2] = (elapsedTime / 1000) % 10;
	digit[3] = ((elapsedTime / 1000) % 60) / 10;

	// 分
	digit[4] = ((elapsedTime / 1000) % 600) / 60;
	digit[5] = min(((elapsedTime / 1000) / 600), 5);

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		digit[i] = 0;
	}

	// ひとけたずつオブジェクトを生成
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new ResultDigit(digit[i], i, _rank);
	}
}


ResultTimer::~ResultTimer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		delete time[i];
	}
}

void ResultTimer::Update()
{
	// ひとけたずつ更新
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update();
	}
}