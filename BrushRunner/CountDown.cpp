#include "Main.h"
#include "CountDown.h"

COUNTDOWN::COUNTDOWN()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
		TEXTURE_COUNTDOWN,				// �t�@�C���̖��O
		&D3DTexture);					// �ǂݍ��ރ������̃|�C���^

	use = true;
	pos = COUNTDOWN_POS;
	PatternAnim = 0;
	starttimer = 0;
	startsecond = 0;

	// ���_���̍쐬
	MakeVertex();

}

COUNTDOWN::~COUNTDOWN()
{
	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

}

void COUNTDOWN::Update()
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

void COUNTDOWN::Draw()
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
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}

}

HRESULT COUNTDOWN::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + COUNTDOWN_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + COUNTDOWN_SIZE.x, pos.y + COUNTDOWN_SIZE.y, pos.z);

	// rhw�̐ݒ�
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	return S_OK;
}

void COUNTDOWN::SetTexture()
{
	int x = startsecond % COUNTDOWN_DIVIDE_X;
	int y = startsecond / COUNTDOWN_DIVIDE_X;
	float sizeX = 1.0f / COUNTDOWN_DIVIDE_X;
	float sizeY = 1.0f / COUNTDOWN_DIVIDE_Y;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}