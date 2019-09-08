//=============================================================================
//
// 2DUI�p�p�[�e�B�N�� [UIParticle.cpp]
// Author : HAL���� GP12B332 19 ���J���u
//
//=============================================================================
#include "Main.h"
#include "UIParticle.h"
#include "ResourceManager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UIParticle::UIParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR3 size, int time)
{
	ResourceManager::Instance()->GetTexture("Particle", &D3DTexture);
	
	this->pos = pos;
	this->size = size;
	this->move = move;
	this->col = col;
	this->time = time;
	this->decAlpha = (float)this->col.a / (float)this->time;
	this->use = true;

	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UIParticle::~UIParticle()
{
	this->D3DTexture = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void UIParticle::Update()
{
	if (!use)
		return;

	this->pos += this->move;

	// �����x�̑���
	this->col.a -= this->decAlpha;
	if (this->col.a <= 0)
	{
		this->use = false;
	}

	SetTexture();
	SetVertex();
	SetColor();
}

//=============================================================================
// �`��
//=============================================================================
void UIParticle::Draw()
{
	if (!use)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, D3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void UIParticle::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertex();

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		// rhw�̐ݒ�
		this->vertexWk[i].rhw = 1.0f;
	}

	// ���ˌ��̐ݒ�
	SetColor();

	// �e�N�X�`�����W�̐ݒ�
	SetTexture();
}

//=============================================================================
// ���_���W�̃Z�b�g
//=============================================================================
void UIParticle::SetVertex()
{
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);
}

//=============================================================================
// �e�N�X�`�����W�̃Z�b�g
//=============================================================================
void UIParticle::SetTexture()
{
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// ���ˌ��̃Z�b�g
//=============================================================================
void UIParticle::SetColor()
{
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		this->vertexWk[i].diffuse = this->col;
	}
}