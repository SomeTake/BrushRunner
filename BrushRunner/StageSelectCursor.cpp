//=============================================================================
//
// �X�e�[�W�Z���N�g�p�J�[�\�� [StageSelectCursor.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "StageSelectCursor.h"
#include "Input.h"

#define STAGESELECTCURSOR_POS	D3DXVECTOR3(SCREEN_CENTER_X / 2, 447.0f, 0.0f)
#define CURSOR_MOVE_VALUE		(93.0f)
#define CURSOR_SIZE				D3DXVECTOR3(480.0f, 90.0f, 0.0f)
#define MAXPOS_Y				(STAGESELECTCURSOR_POS.y + CURSOR_MOVE_VALUE * 2)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
StageSelectCursor::StageSelectCursor()
{
	pos = STAGESELECTCURSOR_POS;
	size = CURSOR_SIZE;
	use = true;

	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
StageSelectCursor::~StageSelectCursor()
{
	D3DTexture = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void StageSelectCursor::Update()
{
	if (use)
	{
		for (int ctrNo = 0; ctrNo < GAMEPAD_MAX; ctrNo++)
		{
			if (GetKeyboardRepeat(DIK_S) || IsButtonRepeated(ctrNo, STICK_DOWN))
			{
				pos.y == MAXPOS_Y ? pos.y = STAGESELECTCURSOR_POS.y : pos.y += CURSOR_MOVE_VALUE;
				break;
			}
			else if (GetKeyboardRepeat(DIK_W) || IsButtonRepeated(ctrNo, STICK_UP))
			{
				pos.y == STAGESELECTCURSOR_POS.y ? pos.y = MAXPOS_Y : pos.y -= CURSOR_MOVE_VALUE;
				break;
			}
		}

		SetVertex();
	}
}

//=============================================================================
// �`��
//=============================================================================
void StageSelectCursor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void StageSelectCursor::MakeVertex()
{
	// ���_���W�̐ݒ�
	SetVertex();

	// rhw�̐ݒ�
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);

}

//=============================================================================
// ���_���W�̃Z�b�g
//=============================================================================
void StageSelectCursor::SetVertex()
{
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, pos.z);
}