//=============================================================================
//
// 3D�r���{�[�h�G�t�F�N�g���� [Effect3D.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Effect3D.h"
#include "MyLibrary.h"
#include "Camera.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �G�t�F�N�g�f�[�^�\����
struct EffectData3D
{
	const char *texture;	// �e�N�X�`���t�@�C��
	D3DXVECTOR3 size;		// �T�C�Y
	int count;				// �X�V�t���[��
	Int2D pattern;			// �e�N�X�`��������(x,y)
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static EffectData3D EffectData3DWk[EffectMax] =
{
	{ "data/EFFECT/anmef000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(5, 1) },
{ "data/EFFECT/anmef001.png", D3DXVECTOR3(500.0f, 100.0f, 0.0f), 7, Int2D(1, 5) },
{ "data/EFFECT/anmef002.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(2, 2) },
{ "data/EFFECT/explo000.png", D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), 3, Int2D(5, 3) },
{ "data/EFFECT/ief001.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 10, Int2D(5, 2) },
{ "data/EFFECT/ief000.png", D3DXVECTOR3(70.0f, 70.0f, 0.0f), 4, Int2D(3, 1) },
{ "data/EFFECT/Charge.png", D3DXVECTOR3(75.0f, 75.0f, 0.0f), 10 ,Int2D(2, 7) },
};

//*****************************************************************************
// �N���X�̃����o������
//*****************************************************************************
LPDIRECT3DTEXTURE9 Effect3D::D3DTexture[EffectMax] = { NULL };

//=============================================================================
// �R���X�g���N�^(�������[�v������ꍇ��INFINITY_LOOP��n��)
//=============================================================================
Effect3D::Effect3D(int Effect3DNum, D3DXVECTOR3 _pos, int _LoopNum)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVtxBuff = NULL;

	TexNo = Effect3DNum;

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture[TexNo] == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			EffectData3DWk[TexNo].texture,	// �t�@�C���̖��O
			&D3DTexture[TexNo]);			// �ǂݍ��ރ������̃|�C���^
	}

	use = true;
	CountAnim = 0;
	PatternAnim = 0;
	size = EffectData3DWk[TexNo].size;
	pos = _pos;
	xPattern = EffectData3DWk[TexNo].pattern.x;
	yPattern = EffectData3DWk[TexNo].pattern.y;
	TexAnimNum = xPattern * yPattern;
	AnimationCnt = EffectData3DWk[TexNo].count;
	loopnum = _LoopNum;
	loopcnt = 0;

	// ���_���̍쐬
	MakeVertex();

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Effect3D::~Effect3D()
{
	if (D3DVtxBuff != NULL)
	{
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}

//=============================================================================
// �e�N�X�`���̊J��
//=============================================================================
void Effect3D::ReleaseTexture()
{
	for (int i = 0; i < EffectMax3D; i++)
	{
		if (D3DTexture[i] != NULL)
		{	// �e�N�X�`���̊J��
			D3DTexture[i]->Release();
			D3DTexture[i] = NULL;
		}
	}
}

//=============================================================================
// �X�V
//=============================================================================
void Effect3D::Update()
{
	if (use == true)
	{
		// �A�j���[�V����
		CountAnim++;

		if ((CountAnim % AnimationCnt) == 0)
		{
			// �p�^�[���̐؂�ւ�
			PatternAnim = LoopCountUp(PatternAnim, 0, TexAnimNum);

			// ���[�v����
			Loop();

			//�e�N�X�`�����W���Z�b�g
			SetTexture();

		}

	}
}

//=============================================================================
// �`��
//=============================================================================
void Effect3D::Draw()
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
		pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(Vertex3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTexture[TexNo]);

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
// �G�t�F�N�g�̃��[�v����
//=============================================================================
void Effect3D::Loop()
{

	// �������[�v�̂Ƃ��ȊO
	if (loopnum != INFINITY_LOOP)
	{
		if (PatternAnim == 0)
		{
			loopcnt++;

			// �w��̃��[�v�񐔂ɒB������G�t�F�N�g���I��
			if (loopcnt == loopnum)
			{
				use = false;
				loopcnt = 0;
			}
		}
	}

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT Effect3D::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(Vertex3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,													// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,														// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,													// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,														// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))																// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		Vertex3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2.0f, size.y / 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2.0f, -size.y / 2.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		int x = PatternAnim % xPattern;
		int y = PatternAnim / xPattern;
		float sizeX = 1.0f / xPattern;
		float sizeY = 1.0f / yPattern;

		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void Effect3D::SetTexture()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		Vertex3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		int x = PatternAnim % xPattern;
		int y = PatternAnim / xPattern;
		float sizeX = 1.0f / xPattern;
		float sizeY = 1.0f / yPattern;

		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void Effect3D::LoadTexture()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int effectNo = 0; effectNo < EffectMax3D; effectNo++)
	{
		if (D3DTexture[effectNo] == NULL)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				EffectData3DWk[effectNo].texture,		// �t�@�C���̖��O
				&D3DTexture[effectNo]);				// �ǂݍ��ރ������̃|�C���^

		}
	}
}