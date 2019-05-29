//=============================================================================
//
// �J�[�\���\�� [Cursor.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Cursor.h"
#include "Input.h"
#include "Debugproc.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CURSOR::CURSOR(int _ctrlNum, PLAYER *pP)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
		CURSOR_TEXTURE,					// �t�@�C���̖��O
		&D3DTexture);					// �ǂݍ��ރ������̃|�C���^

	use = true;
	pos = CURSOR_FIRST_POS;
	PatternAnim = ctrlNum = _ctrlNum;
	pPlayer = pP;

	// ���_���̍쐬
	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CURSOR::~CURSOR()
{
	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CURSOR::Update()
{
	if (use == true)
	{
		// ����
		Move();

		// �e�N�X�`���̐؂�ւ�
		Change();

		//�e�N�X�`�����W���Z�b�g
		SetTexture(PatternAnim);

	}
	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CURSOR::Draw()
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

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT CURSOR::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertex();

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

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CURSOR::SetTexture(int cntPattern)
{
	int x = cntPattern % CURSOR_DIVIDE_X;
	int y = cntPattern / CURSOR_DIVIDE_X;
	float sizeX = 1.0f / CURSOR_DIVIDE_X;
	float sizeY = 1.0f / CURSOR_DIVIDE_Y;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void CURSOR::SetVertex()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CURSOR_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CURSOR_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CURSOR_SIZE.x, pos.y + CURSOR_SIZE.y, pos.z);
}

//=============================================================================
// ����
//=============================================================================
void CURSOR::Move()
{
	KeyMove();	// �L�[�{�[�h����
	PadMove();	// �R���g���[������
}

//=============================================================================
// �J�[�\���̐؂�ւ�
//=============================================================================
void CURSOR::Change()
{
	if (GetKeyboardTrigger(DIK_P))
	{
		// �e�N�X�`���ƃv���C���[�̃C���N�̐؂�ւ�
		// �J���[����
		if (PatternAnim == ctrlNum)
		{
			PatternAnim = ctrlNum + CURSOR_DIVIDE_X;
		}
		// �����J���[
		else
		{
			PatternAnim = ctrlNum;
		}

	}
}

//=============================================================================
// �L�[�{�[�h����
//=============================================================================
void CURSOR::KeyMove()
{
	// �㉺
	if (GetKeyboardPress(DIK_W))
	{
		// ��ʊO����
		if (pos.y > 0)
		{
			pos.y -= CURSOR_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{
		// ��ʊO����
		if (pos.y < SCREEN_HEIGHT - CURSOR_SIZE.y)
		{
			pos.y += CURSOR_SPEED;
		}
	}

	// ���E
	if (GetKeyboardPress(DIK_D))
	{
		// ��ʊO����
		if (pos.x < SCREEN_WIDTH - CURSOR_SIZE.x)
		{
			pos.x += CURSOR_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{
		// ��ʊO����
		if (pos.x > 0)
		{
			pos.x -= CURSOR_SPEED;
		}
	}
}

//=============================================================================
// �R���g���[������
//=============================================================================
void CURSOR::PadMove()
{
	angle = GetJoyStickAngle(ctrlNum);
	vec = GetJoyStickVec(ctrlNum);

	pos.x += angle * vec * CURSOR_SPEED;
	pos.y += angle * vec * CURSOR_SPEED;
}