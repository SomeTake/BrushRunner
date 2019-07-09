//=============================================================================
//
// �A�C�e������[Item.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "Item.h"
#include "MyLibrary.h"
#include "Input.h"
#include "BanananoKawaState.h"
#include "BlindState.h"
#include "GunState.h"
#include "JetState.h"
#include "PowerUpBananaState.h"
#include "SpikeState.h"
#include "SpInkState.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Item::Item(D3DXVECTOR3 _pos, Player *ptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_ITEM,						// �t�@�C���̖��O
			&D3DTexture);						// �ǂݍ��ރ������̃|�C���^
	}

	pPlayer = ptr;
	use = false;
	pos = _pos;
	PatternAnim = 0;
	rouletteCnt = 0;
	useCnt = 0;
	active = false;

	// ���_���̍쐬
	MakeVertex();

	// �X�e�[�g�p�^�[���̏�����
	state[NumJet] = new JetState(this);
	state[NumSpike] = new SpikeState(this);
	state[NumPowerUp] = new PowerUpBananaState(this);
	state[NumKawa] = new BanananoKawaState(this);
	state[NumBlind] = new BlindState(this);
	state[NumSpInk] = new SpInkState(this);
	state[NumGun] = new GunState(this);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Item::~Item()
{
	if (D3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	// �X�e�[�g�p�^�[���̍폜
	for (int i = 0; i < NumItemMax; i++)
	{
		delete state[i];
	}
}

//=============================================================================
// �X�V
//=============================================================================
void Item::Update()
{
	// �A�C�e�����擾�����u�Ԃ̏���
	if (!use && pPlayer->GetHitItem() && !active)
	{
		Start();

		//�e�N�X�`�����W���Z�b�g
		SetTexture();
	}

	// �擾���Ă�����
	if (use)
	{
		// �A�C�e�����g�p����
		if (GetKeyboardTrigger(DIK_I) || IsButtonTriggered(pPlayer->GetCtrlNum(), BUTTON_D))
		{
			use = false;
			active = true;
			pPlayer->SetHitItem(false);
			state[PatternAnim]->Start();
		}

		//�e�N�X�`�����W���Z�b�g
		SetTexture();
	}

	// �A�C�e���g�p��
	if (active)
	{
		ActiveState(PatternAnim);
	}
}

//=============================================================================
// �`��
//=============================================================================
void Item::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use || (!use && pPlayer->GetHitItem()) || active)
	{
		// �e�N�X�`���̐ݒ�(�|���S���̕`��O�ɓǂݍ��񂾃e�N�X�`���̃Z�b�g���s��)
		// �e�N�X�`���̃Z�b�g�����Ȃ��ƑO�ɃZ�b�g���ꂽ�e�N�X�`�����\���遨�����͂�Ȃ����Ƃ��w�肷��pDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Item::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertex();

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
	vertexWk[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void Item::SetTexture()
{
	int x = PatternAnim % DIVIDE_ITEM_X;
	int y = PatternAnim / DIVIDE_ITEM_X;
	float sizeX = 1.0f / DIVIDE_ITEM_X;
	float sizeY = 1.0f / DIVIDE_ITEM_Y;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void Item::SetVertex()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + ITEM_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + ITEM_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + ITEM_SIZE.x, pos.y + ITEM_SIZE.y, pos.z);
}

//=============================================================================
// �擾�����Ƃ��̏���
//=============================================================================
void Item::Start()
{
	// ���[���b�g����
	rouletteCnt = LoopCountUp(rouletteCnt, 0, ROULETTE_COUNTER);
	if (rouletteCnt == 0)
	{
		// �e�N�X�`������
		PatternAnim = LoopCountUp(PatternAnim, 0, TEXTURE_DIVIDE_ITEM);
		if (PatternAnim == 0)
		{
			useCnt++;
			// ���񐔉񂵂���g����悤�ɂ���
			if (useCnt == USE_COUNTER)
			{
				use = true;
				rouletteCnt = 0;
				useCnt = 0;
				active = true;

				// �����_���ŃA�C�e���̎�ނ��Z�b�g
				PatternAnim = rand() % (TEXTURE_DIVIDE_ITEM + 1);
			}
		}
	}
}

//=============================================================================
// �A�C�e�����g�p�����Ƃ��̌���
//=============================================================================
void Item::ActiveState(int ItemID)
{
	state[ItemID]->Update();
}

//=============================================================================
// �A�C�e�����ω������Ƃ��ɌĂяo��
//=============================================================================
void Item::ChangeState(int ItemID)
{
	state[ItemID]->Start();
}