//=============================================================================
//
// ���U���g��ʂł̌� [ResultDigit.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ResultDigit.h"
#include "ResultRank.h"
#include "Player.h"
#include "ResourceManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DIGIT_SPACE	(1.0f)

//*****************************************************************************
// �f�[�^��`
//*****************************************************************************
// �\���ʒu�ƃT�C�Y�i��ԉE�̌�����j
ResultStr ResultData[PLAYER_MAX] = {
	D3DXVECTOR3(950.0f, 135.0f, 0.0f), D3DXVECTOR3(75.0f, 150.0f, 0.0f),
	D3DXVECTOR3(800.0f, 445.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
	D3DXVECTOR3(800.0f, 540.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
	D3DXVECTOR3(800.0f, 635.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ResultDigit::ResultDigit(DWORD _time, int _digit, int _rank) : Digit(_digit)
{
	ResourceManager::Instance()->GetTexture("Digit", &D3DTexture);

	time = _time;
	use = true;
	rank = _rank;
	pos = ResultData[rank].pos;
	pos.x -= _digit * ResultData[rank].size.x;
	// �~���b�ƕb�A�b�ƕ��̊Ԃ�':'�̃X�y�[�X������
	if (_digit >= 2)
	{
		pos.x -= 20.0f;
	}
	if (_digit >= 4)
	{
		pos.x -= 20.0f;
	}
	size = ResultData[rank].size;

	MakeVertex();
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
ResultDigit::~ResultDigit()
{
	D3DTexture = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void ResultDigit::Update()
{
}

//=============================================================================
// �`��
//=============================================================================
void ResultDigit::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// Z�e�X�g
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ���e�X�g��L����
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, TRUE);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		Device->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

	// ���e�X�g�𖳌���
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z��r����
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}