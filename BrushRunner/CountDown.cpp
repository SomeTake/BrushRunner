//=============================================================================
//
// �J�E���g�_�E������ [CountDown.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "CountDown.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_COUNTDOWN	("data/TEXTURE/countdown.png")
#define COUNTDOWN_SIZE		D3DXVECTOR2(360.0f, 360.0f)
#define COUNTDOWN_DIVIDE_Y	(4)
#define COUNTDOWN_POS		D3DXVECTOR3(SCREEN_WIDTH / 2 - COUNTDOWN_SIZE.x / 2, SCREEN_HEIGHT / 2 - COUNTDOWN_SIZE.y / 2, 0.0f)
#define START_TIMER			(240)
#define SECOND_PER_FRAME	(60)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CountDown::CountDown()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,	// �f�o�C�X�̃|�C���^
		TEXTURE_COUNTDOWN,				// �t�@�C���̖��O
		&D3DTexture);					// �ǂݍ��ރ������̃|�C���^

	use = true;
	pos = COUNTDOWN_POS;
	starttimer = 0;
	startsecond = 0;

	// ���_���̍쐬
	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CountDown::~CountDown()
{
	// �e�N�X�`���̊J��
	SAFE_RELEASE(D3DTexture);
}

//=============================================================================
// �X�V����
//=============================================================================
void CountDown::Update()
{
	if (use)
	{
		if (starttimer < START_TIMER)
		{
			starttimer++;
			startsecond = starttimer / SECOND_PER_FRAME;

			SetTexture();
		}
		// �J�E���g�_�E���I��
		else
		{
			use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CountDown::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

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
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT CountDown::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, 1.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y, 1.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + COUNTDOWN_SIZE.y, 1.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y + COUNTDOWN_SIZE.y, 1.0f);

	// rhw�̐ݒ�
	vertexWk[0].rhw = 1.0f;
	vertexWk[1].rhw = 1.0f;
	vertexWk[2].rhw = 1.0f;
	vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTexture();

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CountDown::SetTexture()
{
	float sizeY = 1.0f / COUNTDOWN_DIVIDE_Y;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, (float)(startsecond)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, (float)(startsecond)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, (float)(startsecond)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, (float)(startsecond)* sizeY + sizeY);
}