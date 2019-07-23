#ifndef _RESULTTIMER_H_
#define  RESULTTIMER_H_

#include "Timer.h"
#include "ResultDigit.h"

class ResultTimer :
	public Timer
{
private:
	ResultDigit * time[DIGIT_MAX];		// それぞれの桁を表示するオブジェクトのポインタ

public:
	ResultTimer(DWORD _time, int _rank);
	~ResultTimer();

	void Update()override;
};

#endif
