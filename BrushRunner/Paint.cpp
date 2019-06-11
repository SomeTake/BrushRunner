//=============================================================================
//
// �y�C���g [Paint.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Paint.h"
#include "Camera.h"
#include "Debugproc.h"

//*****************************************************************************
// �����o�̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9	PAINT::D3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PAINT::PAINT()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertex();

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PAINT,					// �t�@�C���̖��O
			&D3DTexture);					// �ǂݍ��ރ������[
	}
	
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	width = PAINT_WIDTH;
	height = PAINT_HEIGHT;
	use = false;
	time = 0;
	patternAnim = 0;
	DecAlpha = 0.1f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PAINT::~PAINT()
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
void PAINT::Update()
{
	// �g�p���Ă�����̂̂ݍX�V
	if (use)
	{
		// �\�����Ԃ̍X�V
		if (time > 0)
		{
			time--;
		}
		// �\�����Ԃ𒴂�������ŏ���
		else
		{
			// �����x�������l�ɍ��킹�Ēǉ�
			col.a -= DecAlpha;

			// �F�̐ݒ�
			SetColor();

			if (col.a <= 0.0f)
			{
				// �����ɂȂ�����g�p����߂�
				col.a = 0.0f;
				use = false;
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

		}

		SetTexture();

		PrintDebugProc("�y�C���g���W X:%f Y:%f Z:%f\n", pos.x, pos.y ,pos.z);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void PAINT::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *cameraWk = GetCamera();
	D3DXMATRIX WorldMtx, ViewMtx, SclMtx, TransMtx;

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���Z���� �����_�����O�X�e�[�g�̕ύX�������ۂ��Ȃ�i���Z�����͔����ۂ��Ȃ�i255�ɋ߂Â��Ă����Ɓj�j
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// ���� = �]����(DEST) - �]����(SRC)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	// �ʏ�u�����h �����_�����O�X�e�[�g�����Ƃɖ߂��i�߂��Ȃ��ƌ��Z�����̂܂܂ɂȂ�j
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (use)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&WorldMtx);

		// �r���[�}�g���b�N�X���擾
		ViewMtx = cameraWk->mtxView;

		// �|���S���𐳖ʂɌ�����
		WorldMtx._11 = ViewMtx._11;
		WorldMtx._12 = ViewMtx._21;
		WorldMtx._13 = ViewMtx._31;
		WorldMtx._21 = ViewMtx._12;
		WorldMtx._22 = ViewMtx._22;
		WorldMtx._23 = ViewMtx._32;
		WorldMtx._31 = ViewMtx._13;
		WorldMtx._32 = ViewMtx._23;
		WorldMtx._33 = ViewMtx._33;

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
	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ʏ�u�����h �����_�����O�X�e�[�g�����Ƃɖ߂��i�߂��Ȃ��ƌ��Z�����̂܂܂ɂȂ�j
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT PAINT::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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
		pVtx[0].vtx = D3DXVECTOR3(-PAINT_WIDTH / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-PAINT_WIDTH / 2.0f, PAINT_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAINT_WIDTH / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAINT_WIDTH / 2.0f, PAINT_HEIGHT, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void PAINT::SetVertex()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-width / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-width / 2.0f, height, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(width / 2.0f, height, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

}

//=============================================================================
// ���_�J���[�̐ݒ� ����(nIdxParticle = �ԍ�, col = �F)
//=============================================================================
void PAINT::SetColor()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void PAINT::SetTexture()
{
	int x = patternAnim % PAINT_DIVIDE_X;
	int y = patternAnim / PAINT_DIVIDE_X;
	float sizeX = 1.0f / PAINT_DIVIDE_X;
	float sizeY = 1.0f / PAINT_DIVIDE_Y;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

}