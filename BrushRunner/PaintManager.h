//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintManager.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PAINTSYSTEM_H_
#define _PAINTSYSTEM_H_

#include "Paint.h"
#include "Cursor.h"
#include "Quadtree.h"
#include "InkGauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INK_MAX	(50)	// �C���N�̍ő��

class Player;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PaintManager
{
private:
	std::vector<Paint*>		BlackPaint;
	std::vector<Paint*>		ColorPaint;
	std::vector<InkGauge*>	inkGauge;
	Cursor					*pCursor;				// �Q�Ƃ���J�[�\���N���X�̃|�C���^
	int						Owner;
	int						InkValue[InkNum];		// �C���N�̎c��
	int						InkType;				// �g�p����C���N�̎��(enum ColorInk=�J���[, BlackInk=��)
	bool					SpInk;					// true�̂Ƃ��C���N������Ȃ�

	static QUADTREE			*Quadtree;
#if _DEBUG
	static bool				PressMode;
#endif

	void CheckPaintUse(void);

public:
	PaintManager(int PlayerNo);
	~PaintManager();

	void Update();
	void Draw();
	void SetPaint(int InkType);
	void CursorMove(D3DXVECTOR3 DestPos);
	static void SetQuadtreePtr(QUADTREE *Quadtree) { if (!PaintManager::Quadtree) { PaintManager::Quadtree = Quadtree; } };

	// �Q�b�^�[
	bool GetSpInk() { return SpInk; };
	int GetOwner(void) { return this->Owner; };
	std::vector<Paint*> GetBlackPaint(void) { return this->BlackPaint; };
	std::vector<Paint*> GetColorPaint(void) { return this->ColorPaint; };
	// �l���؂���Փˉ\�ȃI�u�W�F�N�g��T��
	std::vector<Paint*> GetCollisionList(int NodeID);

	// �Z�b�^�[
	void SetSpInk(bool _SpInk) { SpInk = _SpInk; };
};

#endif
