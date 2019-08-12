//=============================================================================
//
// CharacterAI�N���X[CharacterAI.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "CharacterAI.h"
#include "Map.h"
#include "Item.h"
#include "SceneGame.h"
#include "Input.h"
#include "DebugWindow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
PaintGroup *CharacterAI::paintGroup = nullptr;

#define ScanRange (10)		// �v���b�g�t�H�[���̂ւ肪�T����͈�

// CSV���̔ԍ��̎���
enum e_ChipEvent
{
	eRandomChip = -2,		// �y�C���g�A�����̂ǂ��炩�����_���Ō��߂�
	eJumpChip = -3,			// �W�����v����
	ePaintChip = -4,		// �W�����v����
	ePlatformEdge = -5		// �������̃v���b�g�t�H�[���̂ւ�
};

#if _DEBUG
// 3D�������_�t�H�[�}�b�g( ���_���W[3D] / ���ˌ� )
#define	FVF_LINE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

// 3D��ԂŒ����`��p�\���̂��`
typedef struct
{
	D3DXVECTOR3 Point;
	D3DCOLOR	Color;
} VERTEX_3DLINE;
#endif

//=====================================================================================================
// �R���X�g���N�^
//=====================================================================================================
CharacterAI::CharacterAI(int Owner)
{
	this->Owner = Owner;
}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CharacterAI::~CharacterAI()
{

}

//=====================================================================================================
// �X�V����
//=====================================================================================================
void CharacterAI::Update(D3DXVECTOR3 Pos)
{
	int MapChipNo = Map::GetMapTbl(Pos, eCenterUp);
	this->Action = eNoAction;
#if _DEBUG
	this->DrawLineFlag = false;
#endif

	// �}�b�v�`�b�v�̔ԍ��ɂ���čs������
	MapChipAction(Pos, MapChipNo);

	// ��ʓ��̃y�C���g��T���āA�y�C���g����
	if (CursorState != ePaintPath && GetKeyboardTrigger(DIK_V))
	{
		PaintAction();
	}

	// �A�C�e���������Ă�����A�A�C�e�����g�p����
	if (HaveItem)
	{
		ItemAction();
	}

#if _DEBUG
	ImGui::SetNextWindowPos(ImVec2(5, 330), ImGuiSetCond_Once);

	BeginDebugWindow("AI");

	DebugText("Action : %d", this->Action);
	DebugText("State : %d", this->CursorState);

	EndDebugWindow("AI");
#endif
}

//=====================================================================================================
// �}�b�v�`�b�v�̔ԍ��ɂ���čs������
//=====================================================================================================
void CharacterAI::MapChipAction(D3DXVECTOR3 Pos, int MapChipNo)
{
	// �t���O�̏�����
	if (MapChipNo != eRandomChip)
	{
		RandomOver = false;
		if (MapChipNo != ePaintChip)
		{
			FindEdgeOver = false;
		}
	}

	if (MapChipNo == eRandomChip && !RandomOver)
	{
		int Random = rand() % (1 + 1);

		// �y�C���g
		if (Random == 0)
		{
			// �v���b�g�t�H�[���̂ւ��T��
			this->FindPlatform(Pos);
		}
		// ����
		else if (Random == 1)
		{
			int i = 0;
			;	// ���݂͉������Ȃ�
		}

		RandomOver = true;
	}
	else if (MapChipNo == eJumpChip)
	{
		// �W�����v����
		this->Action = eActJump;
	}
	else if (MapChipNo == ePaintChip)
	{
		// �v���b�g�t�H�[���̂ւ��T��
		this->FindPlatform(Pos);
	}
}

//=====================================================================================================
// ���̃v���C���[�̃y�C���g��T���āA�폜����
//=====================================================================================================
void CharacterAI::PaintAction(void)
{
	if (!FindEnemyPaint)
	{
		if (CharacterAI::paintGroup->GetEnemyPaint(&EnemyPaint, Owner))
		{
			CursorState = eUseBlackPaint;
			if (InkType != BlackInk)
			{
				ChangeInk = true;
				InkType = BlackInk;
			}
			FindEnemyPaint = true;
		}
	}
}

//=====================================================================================================
// �A�C�e�����g�p����
//=====================================================================================================
void CharacterAI::ItemAction(void)
{
	bool ItemTrigger = false;
	static int Count = 0;
	static int Bonus = 0;

	switch (ItemType)
	{
		// �W�F�b�g�p�b�N
	case NumJet:
		// �p���[�A�b�v�o�i�i
	case NumPowerUp:
		// �X�y�V�����C���N
	case NumSpInk:
		// �u���C���h
	case NumBlind:

		Count++;
		// 2�b���Ƃɔ��肷��
		if (Count % 120 == 0)
		{
			int Rand = rand() % (10 + 1);
			if (Rand + Bonus > 5)
			{
				// �A�C�e�����g�p����
				ItemTrigger = true;
			}
			else
			{
				// �g�p���Ȃ����A���Ԃɂ���Ďg�p����m���������Ȃ�
				Bonus++;
			}
		}
		break;

		// �X�p�C�N�u�[�c
	case NumSpike:

		break;

		// �o�i�i�̔�
	case NumKawa:

		// �ŉ��ʂ���Ȃ��āA���ɑ��̃v���C���[������Ȃ�o�i�i�̔���g��
		if (SceneGame::GetTheLastPlayer() != Owner)
		{
			// �A�C�e�����g�p����
			ItemTrigger = true;
		}
		else
		{
			Count++;
			// 2�b���Ƃɔ��肷��
			if (Count % 120 == 0)
			{
				int Rand = rand() % (10 + 1);
				if (Rand + Bonus > 5)
				{
					// �A�C�e�����g�p����
					ItemTrigger = true;
				}
				else
				{
					// �g�p���Ȃ����A���Ԃɂ���Ďg�p����m���������Ȃ�
					Bonus++;
				}
			}
		}

		break;

		// �g�����`�K��
	case NumGun:

		Count++;
		// 1.5�b���Ƃɔ��肷��
		if (Count % 90 == 0 || Bonus >= 10)
		{
			if (ShotBullet)
			{
				// �A�C�e�����g�p����
				ItemTrigger = true;
				ShotBullet = false;
			}
			else
			{
				// �g�p���Ȃ����A���Ԃɂ���Ďg�p����m���������Ȃ�
				Bonus++;
			}
		}
		break;

	default:
		break;
	}

	// �A�C�e�����g�p����
	if (ItemTrigger)
	{
		HaveItem = false;
		UseItem = true;
		Count = 0;
		Bonus = 0;
	}
}

//=====================================================================================================
// �������̃v���b�g�t�H�[����T��
//=====================================================================================================
void CharacterAI::FindPlatform(D3DXVECTOR3 Pos)
{
	int PlayerChip_X = 0;
	int PlayerChip_Y = 0;
	Map::GetMapChipXY(Pos, &PlayerChip_X, &PlayerChip_Y);
	std::vector<D3DXVECTOR3> TempPos;

	if (FindEdgeOver)
	{
		return;
	}

	// �X�L�����ł��鉡���͈̔�
	for (int i = PlayerChip_X + 1; i <= PlayerChip_X + ScanRange; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			int k = Map::GetMapTbl(i, j);
			if (k == ePlatformEdge)
			{
				// �T�����v���b�g�t�H�[���̍��W
				TempPos.push_back(Map::GetMapChipPos(i, j + 1, eLeftUp));
				// �L�����N�^�[���̃`�b�v�̍��W
				PaintStartPos = Map::GetMapChipPos(PlayerChip_X + 1, PlayerChip_Y, eRightUp);
				CursorState = ePaintPath;
				if (InkType != ColorInk)
				{
					ChangeInk = true;
					InkType = ColorInk;
				}
				FindEdgeOver = true;

#if _DEBUG
				DrawLineFlag = true;
#endif
			}
		}
	}

	// ���������̃v���b�g�t�H�[��������΁A�����_���Ō��߂�
	if (TempPos.size() > 1)
	{
		int Random = rand() % TempPos.size();
		PaintEndPos = TempPos.at(Random);
	}
	else if (TempPos.size() == 1)
	{
		PaintEndPos = TempPos.at(0);
	}
}

#if _DEBUG
//=============================================================================
// �`�揈��
//=============================================================================
void CharacterAI::Draw(void)
{
	if (this->DrawLineFlag)
	{
		DrawLine3D(this->PaintStartPos, this->PaintEndPos);
	}
}

//=============================================================================
// 3D�����`��
//=============================================================================
void CharacterAI::DrawLine3D(D3DXVECTOR3 P1, D3DXVECTOR3 P2)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX WorldMatrix;
	LPDIRECT3DVERTEXBUFFER9 LineVtxBuffer;		// �����`��p���_�o�b�t�@
	VERTEX_3DLINE *pVtx;

	// �����`��p���_�o�b�t�@�𐶐�
	Device->CreateVertexBuffer(
		sizeof(VERTEX_3DLINE) * 2,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
		FVF_LINE_3D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&LineVtxBuffer,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);							// NULL�ɐݒ�

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	LineVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].Point = P1;
	pVtx[1].Point = P2;

	// �F�̐ݒ�
	pVtx[0].Color = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].Color = D3DCOLOR_RGBA(0, 0, 0, 255);

	// ���_�f�[�^���A�����b�N����
	LineVtxBuffer->Unlock();

	// ���C���e�B���O�𖳌��ɂ���
	Device->SetRenderState(D3DRS_LIGHTING, false);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	Device->SetStreamSource(0, LineVtxBuffer, 0, sizeof(VERTEX_3DLINE));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_LINE_3D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, NULL);

	// �|���S���̕`��
	Device->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ���C���e�B���O��L���ɂ���
	Device->SetRenderState(D3DRS_LIGHTING, true);

	SAFE_RELEASE(LineVtxBuffer);

	return;
}

#endif
