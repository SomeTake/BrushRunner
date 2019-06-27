//=============================================================================
//
// �t�B�[���h�I�u�W�F�N�g�`�b�v���� [ObjectChip.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ObjectChip.h"
#include "Map.h"
#include "Camera.h"

//*****************************************************************************
// �����o�̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9	ObjectChip::D3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ObjectChip::ObjectChip(int x, int y, int texnum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos.x = MAP_POS.x + x * CHIP_SIZE;
	pos.y = MAP_POS.y - y * CHIP_SIZE;
	pos.z = -0.01f;
	rot = MAP_ROT;	// �c�Ɍ�����
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;

	// ���_���̍쐬
	MakeVertex(texnum);

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			CHIP_TEXTURE,					// �t�@�C���̖��O
			&D3DTexture);				// �ǂݍ��ރ������[
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ObjectChip::~ObjectChip()
{
	if (D3DTexture != NULL)
	{// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
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
void ObjectChip::Update()
{
	CheckOnCamera();
}

//=============================================================================
// �`��
//=============================================================================
void ObjectChip::Draw()
{
	if (use)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

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
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT ObjectChip::MakeVertex(int texnum)
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
		pVtx[2].vtx = D3DXVECTOR3(-CHIP_SIZE / 2, 0.0f, -CHIP_SIZE / 2);
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
		if (texnum < 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		else
		{
			int x = texnum % CHIP_DIVIDE_X;
			int y = texnum / CHIP_DIVIDE_X;
			float sizeX = 1.0f / CHIP_DIVIDE_X;
			float sizeY = 1.0f / CHIP_DIVIDE_Y;

			pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
			pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �J����������
//=============================================================================
void ObjectChip::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// �`��͈͔���
	// �c
	if ((pos.x > camera->at.x - DRAW_RANGE.x) && (pos.x < camera->at.x + DRAW_RANGE.x))
	{
		// ��
		if ((pos.y > camera->at.y - DRAW_RANGE.y) && (pos.y < camera->at.y + DRAW_RANGE.y))
		{
			use = true;
		}
		else
		{
			use = false;
		}
	}
	else
	{
		use = false;
	}

}