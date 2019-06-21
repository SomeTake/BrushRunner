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
class PaintManager
{
private:
	Paint * pBlackPaint[INK_MAX];	// ���p�̃|�C���^
	Paint * pColorPaint[INK_MAX];	// �J���[�p�̃|�C���^
	Cursor *pCursor;				// �Q�Ƃ���J�[�\���N���X�̃|�C���^
	Player *pPlayer;				// �Q�Ƃ���v���C���[�N���X�̃|�C���^
	D3DXVECTOR3 pos;

public:
	PaintManager(Cursor *pC, Player *pP);
	~PaintManager();

	void Update();
	void Draw();
	void Set(int InkType);

	// �Q�b�^�[
	Paint *GetBlackPaint(int _num) { return pBlackPaint[_num]; };
	Paint *GetColorPaint(int _num) { return pColorPaint[_num]; };
};

#endif
