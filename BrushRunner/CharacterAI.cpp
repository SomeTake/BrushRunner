//=============================================================================
//
// CharacterAI�N���X[CharacterAI.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "CharacterAI.h"
#include "Map.h"
#include "PaintManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ScanRange (5)


#if _DEBUG
// �R�c�������_�t�H�[�}�b�g( ���_���W[3D] / ���ˌ� )
#define	FVF_LINE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif

enum e_ChipNo
{
	eJumpChip = -2,
	eDetermineChip = -3,
	ePlatformEdge = -4
};

#if _DEBUG
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
CharacterAI::CharacterAI()
{
}

//=====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CharacterAI::~CharacterAI()
{

}

void CharacterAI::Update(D3DXVECTOR3 Pos)
{
	int MapChipNo = Map::GetMapTbl(Pos, eCenterUp);
	this->Action = eNoAction;
	this->DrawLineFlag = false;

	switch (MapChipNo)
	{
	case eJumpChip:

		this->Action = eActJump;
		break;

	case eDetermineChip:

		this->FindPlatform(Pos);
		break;

	default:
		break;
	}
}

void CharacterAI::FindPlatform(D3DXVECTOR3 Pos)
{
	int PlayerChip_X = 0;
	int PlayerChip_Y = 0;
	Map::GetMapChipXY(Pos, &PlayerChip_X, &PlayerChip_Y);

	// �X�L�����ł��鉡���͈̔�
	for (int i = PlayerChip_X + 1; i <= PlayerChip_X + ScanRange; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			int k = Map::GetMapTbl(i, j);
			if (k == ePlatformEdge)
			{
				// �T�����v���b�g�t�H�[���̍��W
				this->PaintEndPos = Map::GetMapChipPos(i, j + 1, eLeftUp);
				// �L�����N�^�[���̃`�b�v�̍��W
				this->PaintStartPos = Map::GetMapChipPos(PlayerChip_X + 1, PlayerChip_Y, eRightUp);
				this->State = eCursorMove;
#if _DEBUG
				this->DrawLineFlag = true;
#endif
			}
		}
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
