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
	ChargeEffect,

	// �G�t�F�N�g�̌�
	EffectMax,
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
	int				TexNo;

	static LPDIRECT3DTEXTURE9		D3DTexture[EffectMax];		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	int				TexAnimNum;						// �A�j���[�V�����̕�����
	int				xPattern, yPattern;				// ������
	D3DXVECTOR3		size;

public:
	Effect(int EffectNum, D3DXVECTOR3 _pos);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// ���_���̍쐬
	void SetTexture(int cntPattern);			// �e�N�X�`�����W�̐ݒ�
	void SetVertex();							// ���_���W�̐ݒ�

	bool GetUse() { return use; };
	void SetUse(bool _use) { use = _use; };

	static void LoadTexture();
	static void ReleaseTexture();
};

#endif

