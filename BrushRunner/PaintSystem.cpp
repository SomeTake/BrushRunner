//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintSystem.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "PaintSystem.h"
#include "Input.h"
#include "Debugproc.h"
#include "MyLibrary.h"
#include "Camera.h"
#include "Collision.h"
#include "Quadtree.h"
#include "Player.h"

QUADTREE *PaintManager::Quadtree = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PaintManager::PaintManager(Cursor *pC, Player *pP, QUADTREE *Quadtree)
{
	pPlayer = pP;
	pCursor = pC;
	this->Owner = pP->GetCtrlNum();

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	BlackPaint.reserve(INK_MAX);
	ColorPaint.reserve(INK_MAX);

	if (PaintManager::Quadtree == nullptr)
	{
		PaintManager::Quadtree = Quadtree;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PaintManager::~PaintManager()
{
	for (auto &Paint : this->BlackPaint)
	{
		SAFE_DELETE(Paint);
	}
	this->BlackPaint.clear();
	ReleaseVector(BlackPaint);

	for (auto &Paint : this->ColorPaint)
	{
		SAFE_DELETE(Paint);
	}
	this->ColorPaint.clear();
	ReleaseVector(ColorPaint);
}

//=============================================================================
// �X�V����
//=============================================================================
void PaintManager::Update(bool PressMode)
{
	// �J�[�\���̕M��ɍ��W�����킹��
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	// �g�p���Ă��Ȃ��y�C���g��Vector����폜
	CheckPaintUse();

	// �g�p���Ă���y�C���g���X�V
	for (auto &Black : this->BlackPaint)
	{
		// �I�u�W�F�N�g����ʓ����A�m�[�h�͈͓̔�����Ȃ��Ȃ�A������x�l���؂ɓ����
		if (Black->GetInScreen() && !PaintManager::Quadtree->CheckObjectInNode(Black))
		{
			PaintManager::Quadtree->InsertObject(Black);
		}
		Black->Update();
	}
	for (auto &Color : this->ColorPaint)
	{
		if (Color->GetInScreen() && !PaintManager::Quadtree->CheckObjectInNode(Color))
		{
			PaintManager::Quadtree->InsertObject(Color);
		}
		Color->Update();
	}

	// �C���N���g��
	if ((GetKeyboardPress(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C)) && PressMode)
	{
		// �g�p����C���N�̎c�ʃ`�F�b�N
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			// �y�C���g��ݒu����
			SetPaint(pPlayer->GetInkType());
			// �C���N�����炷
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}
	else if ((GetKeyboardTrigger(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C)) && !PressMode)
	{
		// �g�p����C���N�̎c�ʃ`�F�b�N
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			// �y�C���g��ݒu����
			SetPaint(pPlayer->GetInkType());
			// �C���N�����炷
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}

#if _DEBUG
	//PrintDebugProc("Player %d BlackPaintNum�F%d\n", this->Owner, this->BlackPaint.size());
	//PrintDebugProc("Player %d ColorPaintNum�F%d\n", this->Owner, this->ColorPaint.size());

	if (GetKeyboardTrigger(DIK_L))
	{
		for (auto Paint = this->BlackPaint.begin(); Paint != this->BlackPaint.end(); Paint++)
		{
			(*Paint)->SetUse(false);
			SAFE_DELETE((*Paint));
		}
		this->BlackPaint.clear();

		for (auto Paint = this->ColorPaint.begin(); Paint != this->ColorPaint.end(); Paint++)
		{
			(*Paint)->SetUse(false);
			SAFE_DELETE((*Paint));
		}
		this->ColorPaint.clear();
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void PaintManager::Draw()
{
	// �g�p���Ă���y�C���g��`��
	for (auto &Black : this->BlackPaint)
	{
		Black->Draw();
	}
	for (auto &Color : this->ColorPaint)
	{
		Color->Draw();
	}
}

//=============================================================================
// �y�C���g�̃Z�b�g
//=============================================================================
void PaintManager::SetPaint(int InkType)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	CAMERA *camerawk = GetCamera();
	D3DXMATRIX ViewMtx, ProjMtx;

	Device->GetTransform(D3DTS_VIEW, &ViewMtx);
	Device->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	// ���C���N�̏ꍇ
	if (InkType == BlackInk)
	{
		if (this->BlackPaint.size() >= INK_MAX)
		{
			return;
		}

		Paint *Object = new Paint(this->Owner, BlackInkColor);

		// �J�[�\���̃X�N���[�����W�����[���h���W�֕ϊ����č��W���Z�b�g
		// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
		D3DXVECTOR3 OutPos1, OutPos2, SetPos;
		CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

		// ����p�O�p�`�|���S��
		TriangleStr triPos1, triPos2;
		triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		// 2�_���g���ē��������ꏊ���Z�b�g����ꏊ�Ƃ���
		if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
		{
			hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
		}

		Object->SetPos(SetPos);
		Object->SetUse(true);

		// �X�N���[�����W��ۑ�����
		Object->SetScreenPos((D3DXVECTOR2)this->pos);
		// �l���؂ɓ����
		PaintManager::Quadtree->InsertObject(Object);

		// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
		Object->SetTime(DRAW_FRAME_BLACK);

		// Vector�ɓ����
		this->BlackPaint.push_back(Object);
	}
	// �J���[�C���N�̏ꍇ
	else
	{
		if (this->ColorPaint.size() >= INK_MAX)
		{
			return;
		}

		Paint *Object = new Paint(this->Owner, this->Owner);

		// �J�[�\���̃X�N���[�����W�����[���h���W�֕ϊ����č��W���Z�b�g
		// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
		D3DXVECTOR3 OutPos1, OutPos2, SetPos;
		CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

		// ����p�O�p�`�|���S��
		TriangleStr triPos1, triPos2;
		triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
			camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

		// 2�_���g���ē��������ꏊ���Z�b�g����ꏊ�Ƃ���
		if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
		{
			hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
		}

		Object->SetPos(SetPos);
		Object->SetUse(true);

		// �X�N���[�����W��ۑ�����
		Object->SetScreenPos((D3DXVECTOR2)this->pos);
		// �l���؂ɓ����
		PaintManager::Quadtree->InsertObject(Object);

		// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
		Object->SetTime(DRAW_FRAME_COLOR);

		// Vector�ɓ����
		this->ColorPaint.push_back(Object);
	}
}

//=============================================================================
// �g�p���Ă��Ȃ��y�C���g��Vector����폜
//=============================================================================
void PaintManager::CheckPaintUse(void)
{
	for (auto Paint = this->BlackPaint.begin(); Paint != this->BlackPaint.end();)
	{
		if ((*Paint)->GetUse() == false)
		{
			SAFE_DELETE((*Paint));
			Paint = this->BlackPaint.erase(Paint);
		}
		else
		{
			Paint++;
		}
	}

	for (auto Paint = this->ColorPaint.begin(); Paint != this->ColorPaint.end();)
	{
		if ((*Paint)->GetUse() == false)
		{
			SAFE_DELETE((*Paint));
			Paint = this->ColorPaint.erase(Paint);
		}
		else
		{
			Paint++;
		}
	}
}

//=============================================================================
// �l���؂���Փˉ\�ȃI�u�W�F�N�g��T��
//=============================================================================
std::vector<Paint*> PaintManager::GetCollisionList(int NodeID)
{
	return PaintManager::Quadtree->GetObjectsAt(NodeID);
}
