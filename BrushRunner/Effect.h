//=============================================================================
//
// �G�t�F�N�g���� [Effect.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEXTURE0				_T("data/EFFECT/anmef000.png")			// �摜0
#define EFFECT_TEXTURE1				_T("data/EFFECT/anmef001.png")			// �摜1
#define EFFECT_TEXTURE2				_T("data/EFFECT/anmef002.png")			// �摜2(Run�G�t�F�N�g)
#define EFFECT_TEXTURE3				_T("data/EFFECT/explo000.png")			// �摜2(�����G�t�F�N�g)
#define EFFECT_TEXTURE4				_T("data/EFFECT/ief001.png")			// �摜2(�A�C�e���G�t�F�N�g)



#define EFFET0_POS					D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// �e�N�X�`��0�̕\���ʒu
#define EFFECT0_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// �e�N�X�`��0�̃T�C�Y

#define EFFET1_POS					D3DXVECTOR3(200.0f, 0.0f, 0.0f)			// �e�N�X�`��1�̕\���ʒu
#define EFFECT1_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// �e�N�X�`��1�̃T�C�Y

#define EFFET2_POS					D3DXVECTOR3(400.0f, 0.0f, 0.0f)			// �e�N�X�`��2�̕\���ʒu
#define EFFECT2_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// �e�N�X�`��2�̃T�C�Y

#define EFFET3_POS					D3DXVECTOR3(600.0f, 0.0f, 0.0f)			// �e�N�X�`��3�̕\���ʒu
#define EFFECT3_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// �e�N�X�`��3�̃T�C�Y

#define EFFET4_POS					D3DXVECTOR3(800.0f, 0.0f, 0.0f)			// �e�N�X�`��4�̕\���ʒu
#define EFFECT4_SIZE				D3DXVECTOR3(100.0f, 100.0f, 0.0f)		// �e�N�X�`��4�̃T�C�Y



#define EFFECT_PATTERN_X			(5)										// �e�N�X�`��0��������(X)
#define EFFECT_PATTERN_Y			(1)										// �e�N�X�`��0��������(Y)

#define EFFECT1_PATTERN_X			(1)										// �e�N�X�`��1��������(X)
#define EFFECT1_PATTERN_Y			(5)										// �e�N�X�`��1��������(Y)

#define EFFECT2_PATTERN_X			(2)										// �e�N�X�`��2��������(X)
#define EFFECT2_PATTERN_Y			(2)										// �e�N�X�`��2��������(Y)

#define EFFECT3_PATTERN_X			(5)										// �e�N�X�`��3��������(X)
#define EFFECT3_PATTERN_Y			(3)										// �e�N�X�`��3��������(Y)

#define EFFECT4_PATTERN_X			(5)										// �e�N�X�`��4��������(X)
#define EFFECT4_PATTERN_Y			(2)										// �e�N�X�`��4��������(Y)


#define ANIME_PATTERN_NUM_EFFECT0	(EFFECT_PATTERN_X*EFFECT_PATTERN_Y)		// �A�j���[�V�����p�^�[����

#define ANIME_PATTERN_NUM_EFFECT1	(EFFECT1_PATTERN_X*EFFECT1_PATTERN_Y)	// �A�j���[�V�����p�^�[����

#define ANIME_PATTERN_NUM_EFFECT2	(EFFECT2_PATTERN_X*EFFECT2_PATTERN_Y)	// �A�j���[�V�����p�^�[����

#define ANIME_PATTERN_NUM_EFFECT3	(EFFECT3_PATTERN_X*EFFECT3_PATTERN_Y)	// �A�j���[�V�����p�^�[����

#define ANIME_PATTERN_NUM_EFFECT4	(EFFECT4_PATTERN_X*EFFECT4_PATTERN_Y)	// �A�j���[�V�����p�^�[����


#define TIME_ANIMATION_EFFECT0		(7)										// �A�j���[�V�����J�E���g

#define TIME_ANIMATION_EFFECT1		(7)										// �A�j���[�V�����J�E���g

#define TIME_ANIMATION_EFFECT2		(7)										// �A�j���[�V�����J�E���g

#define TIME_ANIMATION_EFFECT3		(3)										// �A�j���[�V�����J�E���g

#define TIME_ANIMATION_EFFECT4		(10)									// �A�j���[�V�����J�E���g


#define EFFECT_MAX					(16)									// �G�t�F�N�g�̍ő吔


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
	Effect(const char * texture, D3DXVECTOR3 _size, D3DXVECTOR3 _pos, int _AnimationCnt, int _xPattern, int _yPattern);
	~Effect();

	void Update();
	void Draw();

	HRESULT MakeVertex();						// ���_���̍쐬
	void SetTexture(int cntPattern);			// �e�N�X�`�����W�̐ݒ�
	void SetVertex();							// ���_���W�̐ݒ�
};

#endif

