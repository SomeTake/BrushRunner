//=============================================================================
//
// �}�b�v���� [Map.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Map.h"
#include "Input.h"
#include "Debugproc.h"

using namespace std;

//*****************************************************************************
// �����o�̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9	Map::D3DTexture[MapChipMax] = { NULL };		// �e�N�X�`���ւ̃|�C���^

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3 MapCenterPos;	// �\������Ă���}�b�v�̒��S���W

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Map::Map()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// csv�f�[�^�ǂݍ���
	ReadCsv(MAP_FILE);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = MAP_POS;
	rot = MAP_ROT;	// �c�Ɍ�����
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ���_���̍쐬
	MakeVertex();

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture[0] == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			MAP_TEXTURE0,					// �t�@�C���̖��O
			&D3DTexture[0]);				// �ǂݍ��ރ������[
	}

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture[1] == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			MAP_TEXTURE1,					// �t�@�C���̖��O
			&D3DTexture[1]);				// �ǂݍ��ރ������[
	}

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture[2] == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			MAP_TEXTURE2,					// �t�@�C���̖��O
			&D3DTexture[2]);				// �ǂݍ��ރ������[
	}

	MapCenterPos = pos;
	MapCenterPos.x += CHIP_SIZE * MAP_SIZE_X * 0.5f;
	MapCenterPos.y -= CHIP_SIZE * MAP_SIZE_Y * 0.5f;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Map::~Map()
{
	for (int i = 0; i < MapChipMax; i++)
	{
		if (D3DTexture[i] != NULL)
		{// �e�N�X�`���̊J��
			D3DTexture[i]->Release();
			D3DTexture[i] = NULL;
		}
	}

	if (D3DVtxBuff != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void Map::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void Map::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	D3DXVECTOR3 oldpos = pos;	// ���݃|�W�V�������ꎞ�I�ɕۑ�

	// �c��̕`��
	for (int yNum = 0; yNum < MAP_SIZE_Y; yNum++)
	{
		// ����̕`��
		for (int xNum = 0; xNum < MAP_SIZE_X; xNum++)
		{
			if (maptbl[yNum][xNum] >= 0)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxWorld);

				// �X�P�[���𔽉f
				D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(Vertex3D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, D3DTexture[maptbl[yNum][xNum]]);

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}

			// �}�b�v�`�b�v�̍��W�X�V
			pos.x += CHIP_SIZE;
		}
		// �}�b�v�`�b�v�̍��W�X�V
		pos.y -= CHIP_SIZE;

		// X���W�����߂�
		pos.x = oldpos.x;
	}

	// ���̍��W�ɖ߂�
	pos = oldpos;
}

//=============================================================================
// CSV�t�@�C���̓ǂݍ���
//=============================================================================
void Map::ReadCsv(const char *data)
{
	ifstream stream(data);		// �}�b�v�̓ǂݍ��ݐ�

	int row = 0;
	int col;
	while (getline(stream, line))
	{
		col = 0;
		// delim����؂蕶���Ƃ��Đ؂蕪���Aint�ɕϊ�����maptbl[][]�Ɋi�[����
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;)
		{
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			maptbl[row][col++] = stoi(token);
		}
		++row;
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT Map::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(Vertex3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		Vertex3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, 0.0f, CHIP_SIZE / 2);
		pVtx[1].vtx = D3DXVECTOR3(CHIP_SIZE / 2, 0.0f, CHIP_SIZE / 2);
		pVtx[2].vtx = D3DXVECTOR3(-CHIP_SIZE /2 , 0.0f, -CHIP_SIZE / 2);
		pVtx[3].vtx = D3DXVECTOR3(CHIP_SIZE / 2, 0.0f, -CHIP_SIZE / 2);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �\������Ă���}�b�v�̒��S���W
//=============================================================================
D3DXVECTOR3 GetMapCenterPos()
{
	return MapCenterPos;
}