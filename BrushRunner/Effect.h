//=============================================================================
//
// �G�t�F�N�g���� [Effect.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

// �G�t�F�N�g�̎��
enum EffectNum{
	HitEffect,
	DeadEffect,
	RunEffect,
	ExplosionEffect,
	ItemEffect,
	Item1Effect,
	ChargeEffect,

	// �G�t�F�N�g�̌�
	EffectMax,
};

#define INFINITY_LOOP	(-1)	// �G�t�F�N�g�𖳌����[�v������

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Effect
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture[EffectMax];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		D3DVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	Vertex2D					vertexWk[NUM_VERTEX];	// ���_���i�[�\����
	D3DXVECTOR3					pos;
	D3DXVECTOR3					rot;
	D3DXVECTOR3					scl;
	bool						use;
	int							CountAnim;
	int							PatternAnim;			// �A�j���[�V�����p�^�[��
	int							AnimationCnt;
	int							TexNo;
	int							TexAnimNum;				// �A�j���[�V�����̕�����
	int							xPattern, yPattern;		// ������
	D3DXVECTOR3					size;					// �\���T�C�Y
	int							loopnum;				// ���[�v�������(�������[�v��-1)
	int							loopcnt;				// ���݂̃��[�v��

	HRESULT MakeVertex();						// ���_���̍쐬
	void SetTexture(int cntPattern);			// �e�N�X�`�����W�̐ݒ�
	void SetVertex();							// ���_���W�̐ݒ�

	void Loop();								// �G�t�F�N�g�̃��[�v����

public:
	Effect(int EffectNum, D3DXVECTOR3 _pos, int _LoopNum);
	~Effect();

	void Update();
	void Draw();

	bool GetUse() { return use; };
	void SetUse(bool _use) { use = _use; };

	static void LoadTexture();
	static void ReleaseTexture();
};

#endif

