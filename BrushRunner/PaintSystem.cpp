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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PAINTSYSTEM::PAINTSYSTEM(CURSOR *pC, PLAYER *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	for (int i = 0; i < PAINT_MAX; i++)
	{
		pPaint[i] = new PAINT();
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PAINTSYSTEM::~PAINTSYSTEM()
{
	for (int i = 0; i < PAINT_MAX; i++)
	{
		delete pPaint[i];
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void PAINTSYSTEM::Update()
{
	// �J�[�\���̕M��ɍ��W�����킹��
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	// �g�p���Ă���y�C���g���X�V
	for (int i = 0; i < PAINT_MAX; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Update();
			PrintDebugProc("Paint[%d]Time%d\n",i, pPaint[i]->GetTime());

		}
	}

	// �C���N���g��
	if (GetKeyboardPress(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C))
	{
		// �g�p����C���N�̎c�ʃ`�F�b�N
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			Set(pPlayer->GetInkType());
			// �C���N�����炷
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}

	// �C���N�̎g�p���𐔂���
	int num = 0;
	for (int i = 0; i < PAINT_MAX; i++)
	{
		if (pPaint[i]->GetUse()) num++;
	}
	
#ifndef _DEBUG_
	PrintDebugProc("�g�p���Ă���C���N�̐� %d\n", num);
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void PAINTSYSTEM::Draw()
{
	// �g�p���Ă���y�C���g��`��
	for (int i = 0; i < PAINT_MAX; i++)
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camerawk = GetCamera();

	D3DXMATRIX ViewMtx, ProjMtx;

	 pDevice->GetTransform(D3DTS_VIEW, &ViewMtx);
	 pDevice->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	for (int nCntPaint = 0; nCntPaint < PAINT_MAX; nCntPaint++)
	{
		// �g�p���Ă��Ȃ��y�C���g���猟��
		if (!pPaint[nCntPaint]->GetUse())
		{
			// �J�[�\���̃X�N���[�����W�����[���h���W�֕ϊ����č��W���Z�b�g
			// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
			D3DXVECTOR3 OutPos1, OutPos2, SetPos;
			CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
			CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

			// ����p�O�p�`�|���S��
			TRIANGLE_STR triPos1, triPos2;
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

			pPaint[nCntPaint]->SetPos(SetPos);
			pPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

			pPaint[nCntPaint]->SetUse(true);

			// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
			if (InkType == BlackInk)
			{
				pPaint[nCntPaint]->SetTime(DRAW_FRAME_BLACK);
				pPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
			}
			else
			{
				pPaint[nCntPaint]->SetTime(DRAW_FRAME_COLOR);
				pPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
			}

			// ���_���W�̐ݒ�
			pPaint[nCntPaint]->SetVertex();

			// ���_�J���[�̐ݒ�
			pPaint[nCntPaint]->SetColor();

			break;
		}
	}
}