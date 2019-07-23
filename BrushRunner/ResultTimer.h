#ifndef _RESULTTIMER_H_
#define  RESULTTIMER_H_

#include "Timer.h"
#include "ResultDigit.h"

class ResultTimer :
	public Timer
{
private:
	ResultDigit * time[DIGIT_MAX];		// ���ꂼ��̌���\������I�u�W�F�N�g�̃|�C���^

public:
	ResultTimer(DWORD _time, int _rank);
	~ResultTimer();

	void Update()override;
};

#endif
