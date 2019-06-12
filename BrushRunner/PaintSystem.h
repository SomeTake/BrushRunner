//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintSystem.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Player.h"
#include "Cursor.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PAINTSYSTEM
{
private:
	PAINT * pPaint[PAINT_MAX];		// ����������y�C���g�̃|�C���^
	CURSOR *pCursor;				// �Q�Ƃ���J�[�\���N���X�̃|�C���^
	PLAYER *pPlayer;				// �Q�Ƃ���v���C���[�N���X�̃|�C���^
	D3DXVECTOR3 pos;

public:
	PAINTSYSTEM(CURSOR *pC, PLAYER *pP);
	~PAINTSYSTEM();

	void Update();
	void Draw();
	void Set(int InkType);

	// �Q�b�^�[
	PAINT *GetPaint(int _num) { return pPaint[_num]; };
};

#endif
