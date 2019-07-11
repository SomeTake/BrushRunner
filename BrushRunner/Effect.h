//=============================================================================
//
// �G�t�F�N�g���� [Effect.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "_2dobj.h"

// �G�t�F�N�g�̎��
enum EffectNum{
	HitEffect,
	Hit1Effect,
	RunEffect,
	ExpEffect,
	ItemEffect,
	Item1Effect,

	// �G�t�F�N�g�̌�
	EffectMax,
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �G�t�F�N�g�f�[�^�\����
struct EffectData
{
	const char *texture;	// �e�N�X�`���t�@�C��
	D3DXVECTOR3 size;		// �T�C�Y
	int count;				// �X�V�t���[��
	Int2D pattern;			// �e�N�X�`��������(x,y)
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static EffectData EffectDataWk[EffectMax] =
{
	{"data/EFFECT/anmef000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(5, 1) },
{ "data/EFFECT/anmef001.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(1, 5) },
{ "data/EFFECT/anmef002.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 7, Int2D(2, 2) },
{ "data/EFFECT/explo000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 3, Int2D(5, 3) },
{ "data/EFFECT/ief001.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 10, Int2D(5, 2) },
{ "data/EFFECT/ief000.png", D3DXVECTOR3(100.0f, 100.0f, 0.0f), 10, Int2D(3, 1)},
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Effect {
	//public _2dobj {
private:
	Vertex2D		vertexWk[NUM_VERTEX];			// ���_���i�[�\����
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		scl;
	bool			use;
	int				CountAnim;
	int				PatternAnim;					// �A�j���[�V�����p�^�[��
	int				AnimationCnt;

	LPDIRECT3DTEXTURE9		D3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	int				TexAnimNum;						// �A�j���[�V�����̕�����
	int				xPattern, yPattern;				// ������
	D3DXVECTOR3		size;

public:
	Effect(EffectData data, D3DXVECTOR3 _pos);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// ���_���̍쐬
	void SetTexture(int cntPattern);			// �e�N�X�`�����W�̐ݒ�
	void SetVertex();							// ���_���W�̐ݒ�
};

#endif

