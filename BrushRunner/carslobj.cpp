//=============================================================================
//
// �o�g����ʃt���[���\������ [Carslobj.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "carslobj.h"
#include "Input.h"
int pnum=0;
bool canch = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Carslobj::Carslobj(D3DXVECTOR3 _pos, const char *texno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		texno,				// �t�@�C���̖��O
		&D3DTexture);				// �ǂݍ��ރ������̃|�C���^

									///////////////////////////////////////////////////////////////////////////////////////
									// �t���[���̏�����
	use = true;
	pos = _pos;
	PatternAnim = 1;
	// ���_���̍쐬
	MakeVertex();
	///////////////////////////////////////////////////////////////////////////////////////
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Carslobj::~Carslobj()
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
void Carslobj::Update()
{
	if (use == true)
	{
		//�e�N�X�`�����W���Z�b�g
		SetTexture(PatternAnim);
	}
	if (GetKeyboardTrigger(DIK_RIGHT))
	{
		if (pos == CARSLOBJ_POS01)
		{
			pos = CARSLOBJ_POS02;
		}
		else if (pos == CARSLOBJ_POS02)
		{
			pos = CARSLOBJ_POS03;
		}
		else if (pos == CARSLOBJ_POS03)
		{
			pos = CARSLOBJ_POS01;
		}
	}
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		if (pos == CARSLOBJ_POS03)
		{
			pos = CARSLOBJ_POS02;
		}
		else if (pos == CARSLOBJ_POS02)
		{
			pos = CARSLOBJ_POS01;
		}
		else if (pos == CARSLOBJ_POS01)
		{
			pos = CARSLOBJ_POS03;
		}
	}
	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Carslobj::Draw()
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
HRESULT Carslobj::MakeVertex(void)
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
void Carslobj::SetTexture(int cntPattern)
{
	int x = cntPattern;
	int y = cntPattern;
	float sizeX = 1.0f;
	float sizeY = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void Carslobj::SetVertex(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CARSLOBJ_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CARSLOBJ_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CARSLOBJ_SIZE.x, pos.y + CARSLOBJ_SIZE.y, pos.z);
}

int Getpnum()
{
	return pnum;
}
void Setpnum(int no)
{
	pnum = no;
	return;
}
bool Getch()
{
	return canch;
}
void Setch(bool ch)
{
	canch = ch;
	return;
}
