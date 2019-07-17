//=============================================================================
//
// �o�g����ʃt���[���\������ [Carsl_obj2.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "carslobj.h"
#include "carsl_obj2.h"
#include "Input.h"
int char02;
bool ao2, aka2, midori2, ki2;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Carsl_obj2::Carsl_obj2(D3DXVECTOR3 _pos, const char *texno)
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
	ao2 = false;
	aka2 = false;
	midori2 = false;
	ki2 = false;
	if (texno == TEXTURE_CARSLOBJ)
	{
		char2 = AO;
		char02 = char2;
	}
	else if (texno == TEXTURE_CARSLOBJ2)
	{
		char2 = AKA;
		char02 = char2;
	}
	else if (texno == TEXTURE_CARSLOBJ3)
	{
		char2 = MIDORI;
		char02 = char2;
	}
	else if (texno == TEXTURE_CARSLOBJ4)
	{
		char2 = KI;
		char02 = char2;
	}

	// ���_���̍쐬
	MakeVertex();
	///////////////////////////////////////////////////////////////////////////////////////

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Carsl_obj2::~Carsl_obj2()
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
void Carsl_obj2::Update()
{
	if (use == true)
	{
		//�e�N�X�`�����W���Z�b�g
		SetTexture(PatternAnim);
	}
	if (Getpnum() == 1)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Setpnum(2);
		}
		else if (pos == CARSL_OBJ2_POS01)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ2_POS02;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ2_POS04;
			}
			if (char2 == AO)
			{
				ao2 = true;
				aka2 = false;
				midori2 = false;
				ki2 = false;
			}
			else if (char2 == AKA)
			{
				aka2 = true;
				ao2 = false;
				midori2 = false;
				ki2 = false;
			}
			else if (char2 == MIDORI)
			{
				midori2 = true;
				aka2 = false;
				ao2 = false;
				ki2 = false;
			}
			else if (char2 == KI)
			{
				ki2 = true;
				ao2 = false;
				aka2 = false;
				midori2 = false;
			}
		}
		else if (pos == CARSL_OBJ2_POS02)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ2_POS03;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ2_POS01;
			}
		}
		else if (pos == CARSL_OBJ2_POS03)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ2_POS04;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ2_POS02;
			}
		}
		else if (pos == CARSL_OBJ2_POS04)
		{
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				pos = CARSL_OBJ2_POS01;
			}
			else if (GetKeyboardTrigger(DIK_LEFT))
			{
				pos = CARSL_OBJ2_POS03;
			}

		}
	}
	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Carsl_obj2::Draw()
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
HRESULT Carsl_obj2::MakeVertex(void)
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
void Carsl_obj2::SetTexture(int cntPattern)
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
void Carsl_obj2::SetVertex(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ2_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CARSL_OBJ2_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CARSL_OBJ2_SIZE.x, pos.y + CARSL_OBJ2_SIZE.y, pos.z);
}

int Getchar2num()
{
	if (ao2 == true)
	{
		return AO;
	}
	else if (aka2 == true)
	{
		return AKA;
	}
	else if (midori2 == true)
	{
		return MIDORI;
	}
	else if (ki2 == true)
	{
		return KI;
	}
}