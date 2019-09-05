//=============================================================================
//
// �^�C�}�[ [Timer.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Timer.h"
#include "DebugWindow.h"
#include "ResourceManager.h"

#define TIMER_POS	D3DXVECTOR3(SCREEN_CENTER_X - 2.0f, 132.0f, 0.0f)
#define TIMER_SIZE	D3DXVECTOR3(256.0f, 60.0f, 0.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Timer::Timer()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	startTime = 0;
	currentTime = 0;
	elapsedTime = 0;

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		digit[i] = 0;
	}

	// �ЂƂ������I�u�W�F�N�g�𐶐�
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i] = new Digit(i);
	}

	// ���\���p�t�H���g�̐ݒ�
	D3DXCreateFont(Device, 54, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Consolas"), &Font);

	ResourceManager::Instance()->GetTexture("Timer", &D3DTexture);
	pos = TIMER_POS;
	size = TIMER_SIZE;
	use = true;

	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Timer::~Timer()
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SAFE_DELETE(time[i]);
	}

	SAFE_RELEASE(Font);
	D3DTexture = NULL;
}

//=============================================================================
// �X�V
//=============================================================================
void Timer::Update()
{
	Debug();

	if (!use)
		return;

	currentTime = timeGetTime();
	elapsedTime = currentTime - startTime;	// �o�ߎ��Ԃ̎Z�o

	// �~���b
	digit[0] = (elapsedTime / 10) % 10;
	digit[1] = (elapsedTime / 100) % 10;

	// �b
	digit[2] = (elapsedTime / 1000) % 10;
	digit[3] = (elapsedTime / 10000) % 6;

	// ��
	digit[4] = (elapsedTime / 60000) % 10;
	digit[5] = (elapsedTime / 600000) % 6;

	// �ЂƂ������X�V
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		time[i]->Update(digit[i]);
	}
}

//=============================================================================
// �`��
//=============================================================================
void Timer::Draw()
{
	RECT rect = { 660, 105, 725, 155 };
	Font->DrawText(NULL, ":", -1, &rect, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
	rect = { 560, 105, 625, 155 };
	Font->DrawText(NULL, ":", -1, &rect, DT_CENTER | DT_VCENTER, D3DCOLOR_RGBA(255, 0, 0, 255));
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

//=============================================================================
// �X�^�[�g
//=============================================================================
void Timer::Start()
{
	startTime = timeGetTime();
	use = true;
}

//=============================================================================
// �X�g�b�v
//=============================================================================
void Timer::Stop()
{
	use = false;
}

//=============================================================================
// �o�ߎ��Ԃ̊m�F
//=============================================================================
DWORD Timer::Check()
{
	return elapsedTime;
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void Timer::MakeVertex()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, pos.z);

	// rhw�̐ݒ�
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

}

//=============================================================================
// �f�o�b�O
//=============================================================================
void Timer::Debug()
{
#ifndef _DEBUG_
	BeginDebugWindow("Timer");

	DebugText("Start:%d Current:%d Elapsed:%d", startTime, currentTime, elapsedTime);
	DebugText("%d%d%d%d%d%d", digit[5], digit[4], digit[3], digit[2], digit[1], digit[0]);

	EndDebugWindow("Timer");
#endif
}
