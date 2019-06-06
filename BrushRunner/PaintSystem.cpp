//=============================================================================
//
// �y�C���g�Ǘ��N���X [PaintSystem.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "PaintSystem.h"
#include "Input.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PAINTSYSTEM::PAINTSYSTEM(CURSOR *pC, PLAYER *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos = pCursor->GetPos() + (CURSOR_SIZE * 0.5f);

	for (int i = 0; i < MAX_PAINT; i++)
	{
		pPaint[i] = new PAINT();
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PAINTSYSTEM::~PAINTSYSTEM()
{
	for (int i = 0; i < MAX_PAINT; i++)
	{
		delete pPaint[i];
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void PAINTSYSTEM::Update()
{
	// �J�[�\���ɍ��W�����킹��
	pos = pCursor->GetPos() + (CURSOR_SIZE * 0.5f);

	// �g�p���Ă���y�C���g���X�V
	for (int i = 0; i < MAX_PAINT; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Update();
		}
	}

	if (GetKeyboardPress(DIK_O))
	{
		Set(pPlayer->GetInkType());
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void PAINTSYSTEM::Draw()
{
	// �g�p���Ă���y�C���g��`��
	for (int i = 0; i < MAX_PAINT; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Draw();
		}
	}
}

//=============================================================================
// �y�C���g�̃Z�b�g
//=============================================================================
void PAINTSYSTEM::Set(int InkType)
{
	for (int nCntPaint = 0; nCntPaint < MAX_PAINT; nCntPaint++)
	{
		// �g�p���Ă��Ȃ��y�C���g���猟��
		if (!pPaint[nCntPaint]->GetUse())
		{
			// �J�[�\���̃X�N���[�����W�����[���h���W�֕ϊ����č��W���Z�b�g
			pPaint[nCntPaint]->SetPos(pos);
			pPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			pPaint[nCntPaint]->SetTime(PAINT_DRAW_FRAME);
			pPaint[nCntPaint]->SetUse(true);

			// �g�p���Ă���C���N�̐F�ɍ��킹�ăe�N�X�`�����Z�b�g
			if (InkType != GAMEPAD_MAX)
			{
				pPaint[nCntPaint]->SetPatternAnim(InkType);
			}
			else
			{
				pPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
			}

			// ���_���W�̐ݒ�
			pPaint[nCntPaint]->SetVertex(nCntPaint);

			// ���_�J���[�̐ݒ�
			pPaint[nCntPaint]->SetColor(nCntPaint);

			break;
		}
	}
}