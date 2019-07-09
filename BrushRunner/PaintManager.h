//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintSystem.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Cursor.h"
#include "Quadtree.h"

class Player;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PaintManager
{
private:
	std::vector<Paint*> BlackPaint;
	std::vector<Paint*> ColorPaint;
	Cursor				*pCursor;				// �Q�Ƃ���J�[�\���N���X�̃|�C���^
	Player				*pPlayer;				// �Q�Ƃ���v���C���[�N���X�̃|�C���^
	D3DXVECTOR3			pos;
	int					Owner;
	static QUADTREE		*Quadtree;

	void CheckPaintUse(void);

public:
	PaintManager(Cursor *pC, Player *pP, QUADTREE *Quadtree);
	~PaintManager();

	void Update(bool PressMode);
	void Draw();
	void SetPaint(int InkType);

	// �Q�b�^�[
	int GetOwner(void) { return this->Owner; };
	std::vector<Paint*> GetBlackPaint(void) { return this->BlackPaint; };
	std::vector<Paint*> GetColorPaint(void) { return this->ColorPaint; };
	// �l���؂���Փˉ\�ȃI�u�W�F�N�g��T��
	std::vector<Paint*> GetCollisionList(int NodeID);
};

#endif
