//=============================================================================
//
// �o�g����ʃt���[���\������ [Face.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Face.h"
#include "Faceframe.h"
#include "carsl_obj.h"
#include "carsl_obj2.h"
#include "carsl_obj3.h"
#include "carsl_obj4.h"
#include "carslobj.h"
int fc1;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Face::Face(D3DXVECTOR3 _pos, const char *texno)
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
Face::~Face()
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
void Face::Update()
{
	if (use == true)
	{
			fc1 = Getchar1num();
		//�e�N�X�`�����W���Z�b�g
		SetTexture(PatternAnim);

	}
	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Face::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		if (fc1 == AO)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_FACE1,				// �t�@�C���̖��O
				&D3DTexture);				// �ǂݍ��ރ������̃|�C���^
		}
		else if (fc1 == AKA)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_FACE2,				// �t�@�C���̖��O
				&D3DTexture);				// �ǂݍ��ރ������̃|�C���^
		}
		else if (fc1 == MIDORI)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_FACE3,				// �t�@�C���̖��O
				&D3DTexture);				// �ǂݍ��ރ������̃|�C���^
		}
		else if (fc1 == KI)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_FACE4,				// �t�@�C���̖��O
				&D3DTexture);				// �ǂݍ��ރ������̃|�C���^
		}

		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Face::MakeVertex(void)
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
void Face::SetTexture(int cntPattern)
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
void Face::SetVertex(void)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + FACE_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + FACE_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + FACE_SIZE.x, pos.y + FACE_SIZE.y, pos.z);
}