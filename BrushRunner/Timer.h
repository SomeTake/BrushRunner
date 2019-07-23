//=============================================================================
//
// �^�C�}�[ [Timer.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "_2dobj.h"
#include "Digit.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Timer :
	public _2dobj
{
protected:
	Digit *time[DIGIT_MAX];		// ���ꂼ��̌���\������I�u�W�F�N�g�̃|�C���^

	DWORD startTime;			// �Q�[���̊J�n����
	DWORD currentTime;			// ���݂̎��ԁi= timeGetTime()�j
	DWORD elapsedTime;			// �o�ߎ��ԁicurrentTime - startTime�j
	DWORD digit[DIGIT_MAX];		// �o�ߎ��Ԃ����ꂼ��̌��ɕ���
	bool use;

	void Debug();

public:
	Timer();
	~Timer();

	virtual void Update();
	void Draw();

	void Start();			// �^�C�}�[�X�^�[�g
	void Stop();			// �^�C�}�[�X�g�b�v
	DWORD Check();			// �o�ߎ��Ԃ̊m�F

};

#endif
