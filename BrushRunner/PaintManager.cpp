//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintSystem.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "PaintManager.h"
#include "Input.h"
#include "MyLibrary.h"
#include "Camera.h"
#include "Collision.h"
#include "Quadtree.h"
#include "DebugWindow.h"
#include "SceneGame.h"
#include "Player.h"

QUADTREE *PaintManager::Quadtree = nullptr;
bool PaintManager::PressMode = true;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PaintManager::PaintManager(int PlayerNo)
{
	this->Owner = PlayerNo;
	this->InkType = ColorInk;
	for (int i = 0; i < InkNum; i++)
	{
		this->InkValue[i] = INK_MAX;
	}
	this->pCursor = new Cursor(this->Owner);
	this->inkGauge.push_back(new InkGauge(ColorInk, PlayerNo));
	this->inkGauge.push_back(new InkGauge(BlackInk, PlayerNo));

	// �y�C���g�x�N�g���̃������̈�m��
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
	// �����������[�X
	SAFE_DELETE(this->pCursor);

	for (auto &Object : this->inkGauge)
	{
		SAFE_DELETE(Object);
	}
	this->inkGauge.clear();
	ReleaseVector(inkGauge);

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
void PaintManager::Update()
{
	// �J�[�\���̍X�V
	this->pCursor->Update();

	// �g�p���Ă��Ȃ��y�C���g���x�N�g������폜
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

	// �C���N�̎�ތ���
	if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(Owner, BUTTON_R1))
	{
		InkType = InkType == BlackInk ? ColorInk : BlackInk;
	}

	// �C���N���g��
	if ((GetKeyboardPress(DIK_O) || IsButtonPressed(this->Owner, BUTTON_C)) && PressMode)
	{
		// �g�p����C���N�̎c�ʃ`�F�b�N
		if (this->InkValue[InkType] > 0)
		{
			// �y�C���g��ݒu����
			SetPaint(InkType);
			// �C���N�����炷
			InkValue[InkType]--;

			//if (!pPlayer->GetSpInk())
			//{
			//	InkValue[InkType]--;
			//}
		}
	}
#if _DEBUG
	else if ((GetKeyboardTrigger(DIK_O) || IsButtonPressed(this->Owner, BUTTON_C)) && !PressMode)
	{
		// �g�p����C���N�̎c�ʃ`�F�b�N
		if (this->InkValue[InkType] > 0)
		{
			// �y�C���g��ݒu����
			SetPaint(InkType);
			// �C���N�����炷
			InkValue[InkType]--;

			//if (!pPlayer->GetSpInk())
			//{
			//	InkValue[InkType]--;
			//}
		}
	}
#endif

	// �C���N�Q�[�W���X�V
	inkGauge.at(ColorInk)->Update(InkValue[ColorInk]);
	inkGauge.at(BlackInk)->Update(InkValue[BlackInk]);

#if _DEBUG
	// �C���N�̎c�ʂ𒲐�
	if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_Z))
	{
		if (InkValue[InkType] > 0)
		{
			InkValue[InkType]--;
		}
	}

	if (GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_X))
	{
		if (InkValue[InkType] < INK_MAX)
		{
			InkValue[InkType]++;
		}
	}

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

	if (this->Owner == 0)
	{
		BeginDebugWindow("Information");

		enum ePaintMode
		{
			ePress,
			eTrigger,
		};
		static int Mode = 0;

		DebugText("PaintMode : ");
		ImGui::SameLine();
		ImGui::RadioButton("Press", &Mode, ePress);
		ImGui::SameLine();
		ImGui::RadioButton("Trigger", &Mode, eTrigger);
		if (Mode == ePress)
		{
			PressMode = true;
		}
		else
		{
			PressMode = false;
		}

		EndDebugWindow("Information");
	}
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void PaintManager::Draw()
{
	// �J�[�\����`��
	this->pCursor->Draw();

	// �g�p���Ă���y�C���g��`��
	for (auto &Black : this->BlackPaint)
	{
		Black->Draw();
	}
	for (auto &Color : this->ColorPaint)
	{
		Color->Draw();
	}

	// �C���N�Q�[�W��`��
	// ���ݎg�p���Ă���C���N�̓J���[�A�J���[�C���N�Q�[�W�͑O
	if (this->InkType == ColorInk)
	{
		inkGauge.at(BlackInk)->Draw();
		inkGauge.at(ColorInk)->Draw();
	}
	// ���ݎg�p���Ă���C���N�͍��A���C���N�Q�[�W�͑O
	else if (this->InkType == BlackInk)
	{
		inkGauge.at(ColorInk)->Draw();
		inkGauge.at(BlackInk)->Draw();
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
	D3DXVECTOR3 CursorPos = pCursor->GetPenPoint();

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
		CalcScreenToWorld(&OutPos1, (int)CursorPos.x, (int)CursorPos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)CursorPos.x, (int)CursorPos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

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
		Object->SetScreenPos((D3DXVECTOR2)CursorPos);
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
		CalcScreenToWorld(&OutPos1, (int)CursorPos.x, (int)CursorPos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
		CalcScreenToWorld(&OutPos2, (int)CursorPos.x, (int)CursorPos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

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
		Object->SetScreenPos((D3DXVECTOR2)CursorPos);
		// �l���؂ɓ����
		PaintManager::Quadtree->InsertObject(Object);

		// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
		Object->SetTime(DRAW_FRAME_COLOR);

		// Vector�ɓ����
		this->ColorPaint.push_back(Object);
	}
}

//=====================================================================================================
// �C���N�̎�ތ���
//=====================================================================================================
//void PaintManager::ChangeInk()
//{
	//InkType = InkType == BlackInk ? ColorInk : BlackInk;
	//// �����J���[
	//if (InkType == BlackInk)
	//{
	//	InkType = ColorInk;
	//}
	//// �J���[����
	//else
	//{
	//	inkType = BlackInk;
	//}

	// �C���N�o�[�̕`�揇�����ւ�
	//ChangeDrawOrder(NumInkblack00 + Owner, NumInkblue + Owner);
	// �t���[���̕`�揇�����ւ�
	//ChangeDrawOrder(NumBlackFrame00 + Owner, NumColorFrame00 + Owner);
//}

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

void CursorMove(D3DXVECTOR3 DestPos)
{

}