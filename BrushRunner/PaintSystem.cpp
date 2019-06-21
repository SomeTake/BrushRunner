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
PaintManager::PaintManager(Cursor *pC, Player *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	for (int i = 0; i < INK_MAX; i++)
	{
		pBlackPaint[i] = new Paint();
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		pColorPaint[i] = new Paint();
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PaintManager::~PaintManager()
{
	for (int i = 0; i < INK_MAX; i++)
	{
		delete pBlackPaint[i];
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		delete pColorPaint[i];
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void PaintManager::Update()
{
	// �J�[�\���̕M��ɍ��W�����킹��
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	// �g�p���Ă���y�C���g���X�V
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pBlackPaint[i]->GetUse())
		{
			pBlackPaint[i]->Update();

		}
	}
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pColorPaint[i]->GetUse())
		{
			pColorPaint[i]->Update();
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
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void PaintManager::Draw()
{
	// �g�p���Ă���y�C���g��`��
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pBlackPaint[i]->GetUse())
		{
			pBlackPaint[i]->Draw();
		}
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		if (pColorPaint[i]->GetUse())
		{
			pColorPaint[i]->Draw();
		}
	}
}

//=============================================================================
// �y�C���g�̃Z�b�g
//=============================================================================
void PaintManager::Set(int InkType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camerawk = GetCamera();

	D3DXMATRIX ViewMtx, ProjMtx;

	pDevice->GetTransform(D3DTS_VIEW, &ViewMtx);
	pDevice->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	// ���C���N�̏ꍇ
	if (InkType == BlackInk)
	{
		for (int nCntPaint = 0; nCntPaint < INK_MAX; nCntPaint++)
		{
			// �g�p���Ă��Ȃ��y�C���g���猟��
			if (!pBlackPaint[nCntPaint]->GetUse())
			{
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

				pBlackPaint[nCntPaint]->SetPos(SetPos);
				pBlackPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pBlackPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				pBlackPaint[nCntPaint]->SetUse(true);

				// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
				if (InkType == BlackInk)
				{
					pBlackPaint[nCntPaint]->SetTime(DRAW_FRAME_BLACK);
					pBlackPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
				}
				else
				{
					pBlackPaint[nCntPaint]->SetTime(DRAW_FRAME_COLOR);
					pBlackPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
				}

				// ���_���W�̐ݒ�
				pBlackPaint[nCntPaint]->SetVertex();

				// ���_�J���[�̐ݒ�
				pBlackPaint[nCntPaint]->SetColor();

				break;
			}
		}
	}
	// �J���[�C���N�̏ꍇ
	else
	{
		for (int nCntPaint = 0; nCntPaint < INK_MAX; nCntPaint++)
		{
			// �g�p���Ă��Ȃ��y�C���g���猟��
			if (!pColorPaint[nCntPaint]->GetUse())
			{
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

				pColorPaint[nCntPaint]->SetPos(SetPos);
				pColorPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pColorPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				pColorPaint[nCntPaint]->SetUse(true);

				// �g�p���Ă���C���N�̐F�ɍ��킹�ĕ\�����ԁA�e�N�X�`�����Z�b�g
				if (InkType == BlackInk)
				{
					pColorPaint[nCntPaint]->SetTime(DRAW_FRAME_BLACK);
					pColorPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
				}
				else
				{
					pColorPaint[nCntPaint]->SetTime(DRAW_FRAME_COLOR);
					pColorPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
				}

				// ���_���W�̐ݒ�
				pColorPaint[nCntPaint]->SetVertex();

				// ���_�J���[�̐ݒ�
				pColorPaint[nCntPaint]->SetColor();

				break;
			}
		}
	}

}