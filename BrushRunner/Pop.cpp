//=============================================================================
//
// �|�b�v�A�b�v�\������ [Pop.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Pop.h"
#include "Camera.h"

LPDIRECT3DTEXTURE9	POP::D3DTexture = NULL;	// �e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
POP::POP(int _ctrlNum, PLAYER *pP)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertex();

	// �e�N�X�`���̏�����
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_POP,						// �t�@�C���̖��O
			&D3DTexture);					// �ǂݍ��ރ������[
	}

	pPlayer = pP;
	pos = pPlayer->GetPos() + POP_POS;
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	width = POP_WIDTH;
	height = POP_HEIGHT;
	patternAnim = _ctrlNum;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
POP::~POP()
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
// �X�V����
//=============================================================================
void POP::Update()
{
	pos = pPlayer->GetPos() + POP_POS;

}

//=============================================================================
// �`�揈��
//=============================================================================
void POP::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX WorldMtx, ViewMtx, SclMtx, TransMtx;
	CAMERA *cameraWk = GetCamera();

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtx);

	// �r���[�}�g���b�N�X���擾
	ViewMtx = cameraWk->mtxView;

	// �|���S���𐳖ʂɌ�����
#if 1
	// �t�s������Ƃ߂�
	D3DXMatrixInverse(&WorldMtx, NULL, &ViewMtx);
	WorldMtx._41 = 0.0f;
	WorldMtx._42 = 0.0f;
	WorldMtx._43 = 0.0f;
#else
	WorldMtx._11 = mtxView._11;
	WorldMtx._12 = mtxView._21;
	WorldMtx._13 = mtxView._31;
	WorldMtx._21 = mtxView._12;
	WorldMtx._22 = mtxView._22;
	WorldMtx._23 = mtxView._32;
	WorldMtx._31 = mtxView._13;
	WorldMtx._32 = mtxView._23;
	WorldMtx._33 = mtxView._33;
#endif

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&SclMtx, scl.x,
		scl.y,
		scl.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMtx, pos.x,
		pos.y,
		pos.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &TransMtx);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtx);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT POP::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,				// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-POP_WIDTH / 2.0f, POP_HEIGHT / 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(POP_WIDTH / 2.0f, POP_HEIGHT / 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-POP_WIDTH / 2.0f,-POP_HEIGHT / 2.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(POP_WIDTH / 2.0f, -POP_HEIGHT / 2.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		int x = patternAnim % POP_DIVIDE_X;
		int y = patternAnim / POP_DIVIDE_X;
		float sizeX = 1.0f / POP_DIVIDE_X;
		float sizeY = 1.0f / POP_DIVIDE_Y;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}