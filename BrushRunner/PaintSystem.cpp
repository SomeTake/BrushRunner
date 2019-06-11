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
	pos.y = pCursor->GetPos().y/* + CURSOR_SIZE.y*/;
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
	if (GetKeyboardPress(DIK_O))
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
			//// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
			//D3DXVECTOR3 OutPos1;
			//CalcScreenToXZ(&OutPos1, (int)pos.x, (int)pos.y, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

			//// �J�����͈̔͂��牜�s����1.0�`0.0�ɕϊ�
			//float viewRange;
			//viewRange = VIEW_FAR_Z - VIEW_NEAR_Z;
			//OutPos1.z -=  (pos.z + VIEW_NEAR_Z);
			//OutPos1.z /= viewRange;

			//D3DXVECTOR3 OutPos2;
			//// �X�N���[�����W�����[���h���W�֕ϊ�
			//CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, OutPos1.z, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
			//OutPos2.z = 0.0f;

			//pPaint[nCntPaint]->SetPos(OutPos2);
			
			D3DXVECTOR3 setPos = Pick(pos);
			setPos.z = 0.0f;

			pPaint[nCntPaint]->SetPos(setPos);
			pPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			pPaint[nCntPaint]->SetTime(PAINT_DRAW_FRAME);
			pPaint[nCntPaint]->SetUse(true);

			// �g�p���Ă���C���N�̐F�ɍ��킹�ăe�N�X�`�����Z�b�g
			if (InkType == BlackInk)
			{
				pPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
			}
			else
			{
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