//=============================================================================
//
// �G�t�F�N�g���� [Effect.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Effect.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
EFFECT::EFFECT(const char *texture, D3DXVECTOR3 _size, D3DXVECTOR3 _pos , int _AnimationCnt, int _xPattern, int _yPattern) {
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DTexture = NULL;
	D3DVtxBuff = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		texture,							// �t�@�C���̖��O
		&D3DTexture);						// �ǂݍ��ރ������̃|�C���^

	// �t���[���̏�����
	use = true;
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CountAnim = 0;
	PatternAnim = 0;
	size = _size;
	pos = _pos;
	xPattern = _xPattern;
	yPattern = _yPattern;
	TexAnimNum = xPattern * yPattern;
	AnimationCnt = _AnimationCnt;

	// ���_���̍쐬
	MakeVertex();

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
EFFECT::~EFFECT() {

	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}
//=============================================================================
// �X�V
//=============================================================================
void EFFECT::Update() {


	if (use == true)
	{
		// �A�j���[�V����
		CountAnim++;

		if ( ( CountAnim % AnimationCnt) == 0)
		{

			// �p�^�[���̐؂�ւ�
			PatternAnim = (PatternAnim + 1) % TexAnimNum;

			//�e�N�X�`�����W���Z�b�g
			SetTexture(PatternAnim);

		}

	}

	// ���_���W�̐ݒ�
	SetVertex();

}
//=============================================================================
// �`��
//=============================================================================
void EFFECT::Draw() {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
	}

}
//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT EFFECT::MakeVertex(void) {

	// ���_���W�̐ݒ�
	SetVertex();

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;

}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void EFFECT::SetTexture(int cntPattern) {

	int x = cntPattern % xPattern;
	int y = cntPattern / xPattern;
	float sizeX = 1.0f / xPattern;
	float sizeY = 1.0f / yPattern;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void EFFECT::SetVertex(void) {

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + size.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);

}