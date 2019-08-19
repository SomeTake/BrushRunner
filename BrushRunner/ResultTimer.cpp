//=============================================================================
//
// ���U���g��ʂł̃^�C�}�[�\�� [ResultTimer.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ResultTimer.h"
#include "ResourceManager.h"

// ��ŗv����
#define RESULTTIMER_POS		D3DXVECTOR3(SCREEN_CENTER_X - 2.0f, 132.0f, 0.0f)
#define RESULTTIMER_SIZE	D3DXVECTOR3(256.0f, 60.0f, 0.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ResultTimer::ResultTimer(DWORD _time, int _rank)
{

	startTime = 0;
	currentTime = 0;
	elapsedTime = _time;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		digit[i] = 0;
	}

	// �~���b
	digit[0] = (elapsedTime / 10) % 10;
	digit[1] = (elapsedTime / 100) % 10;

	// �b
	digit[2] = (elapsedTime / 1000) % 10;
	digit[3] = (elapsedTime / 10000) % 6;

	// ��
	digit[4] = (elapsedTime / 60000) % 10;
	digit[5] = (elapsedTime / 600000) % 6;

	// �ЂƂ������I�u�W�F�N�g�𐶐�
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new ResultDigit(digit[i], i, _rank);
	}

	ResourceManager::Instance()->GetTexture("Timer", &D3DTexture);
	pos = RESULTTIMER_POS;
	size = RESULTTIMER_SIZE;
	use = true;

	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ResultTimer::~ResultTimer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		delete time[i];
	}

	D3DTexture = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void ResultTimer::Update()
{
	// �ЂƂ������X�V
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void ResultTimer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// �e�N�X�`���̐ݒ�i�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s���j
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����\��Ȃ����Ƃ��w�肷��pDevice->SetTexture(0,NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

	// �ЂƂ������`��
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Draw();
	}
}

