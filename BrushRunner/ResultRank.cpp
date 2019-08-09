//=============================================================================
//
// �v���C���[���� [ResultRank.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ResultRank.h"
#include "Player.h"

//*****************************************************************************
// �\���̃f�[�^����
//*****************************************************************************
ResultStr Rank[PLAYER_MAX] = {
	D3DXVECTOR3(250.0f, 70.0f, 0.0f), D3DXVECTOR3(300.0f, 150.0f, 0.0f),
	D3DXVECTOR3(250.0f, 400.0f, 0.0f), D3DXVECTOR3(180.0f, 90.0f, 0.0f),
	D3DXVECTOR3(260.0f, 510.0f, 0.0f), D3DXVECTOR3(140.0f, 70.0f, 0.0f),
	D3DXVECTOR3(260.0f, 590.0f, 0.0f), D3DXVECTOR3(140.0f, 70.0f, 0.0f),
};

//*****************************************************************************
// �����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9	ResultRank::D3DTexture = NULL;	// �e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ResultRank::ResultRank(int rank)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->use = true;
	this->rank = rank;
	pos = Rank[this->rank].pos;
	size = Rank[this->rank].size;

	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			RESULTRANK_TEXTURE,				// �t�@�C���̖��O
			&D3DTexture);					// �ǂݍ��ރ������̃|�C���^
	}

	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ResultRank::~ResultRank()
{
	SAFE_RELEASE(D3DTexture);
}

//=============================================================================
// �X�V
//=============================================================================
void ResultRank::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void ResultRank::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�i�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s���j
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����\��Ȃ����Ƃ��w�肷��pDevice->SetTexture(0,NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT ResultRank::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + size.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);

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
	int x = rank % RESULTRANK_DIVIDE_X;
	int y = rank / RESULTRANK_DIVIDE_X;
	float sizeX = 1.0f / RESULTRANK_DIVIDE_X;
	float sizeY = 1.0f / RESULTRANK_DIVIDE_Y;

	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	return S_OK;
}