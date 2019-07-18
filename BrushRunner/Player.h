//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "CharacterAI.h"
#include "PlayerUI.h"
#include "PlayerState.h"
#include "FieldItemManager.h"
#include "PaintManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MAX				(1)										// ���삷��v���C���[�̐�
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)					// �����蔻���L���ɂ���T�C�Y
#define JUMP_SPEED				(12.0f)									// �W�����v�̏���

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	Slip,
	Stop,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// �����o�ϐ�
	PlayerState			*state;				// �X�e�[�^�X�Ǘ����ۃN���X
	FieldItemManager	*itemManager;		// �t�B�[���h�A�C�e���Ǘ��N���X

	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	CharacterAI			*AI;				// �L�����N�^�[AI
	PaintManager		*PaintSystem;		// �y�C���g�V�X�e��
	PlayerUI			*playerUI;

	// �����o�֐�
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);
	void Move();			// �ړ�
	void CheckOnCamera();
	void JumpMove();		// �W�����v�ړ�
	void Debug();			// �f�o�b�O

	int					ctrlNum;			// ���삷��R���g���[���ԍ�
	float				animSpd;			// �A�j���[�V�����̍Đ��X�s�[�h
	bool				playable;			// ����\
	bool				onCamera;			// ��ʓ��ɂ���Ƃ�

	// �X�e�[�^�X�֌W
	float				runSpd;				// �_�b�V�����x(0.0-1.0-2.0)
	float				jumpSpd;			// �W�����v���x
	float				jumpValue;			// �W�����v���x�Ɋ|���Ďg��(0.0-1.0-2.0)
	int					inkValue[InkNum];	// �C���N�̎c��
	int					inkType;			// �g�p���̃C���N�̎��(enum ColorInk=�J���[, BlackInk=��)

	// �����蔻��֌W�̃t���O
	bool				hitGround;			// �n�㔻��(���ƍ��킹�ė���false���Ƌ󒆏��)
	bool				hitPaint;
	bool				hitHorizon;			// �i�s�����̃I�u�W�F�N�g�Ƃ̓����蔻��
	bool				hitItem;			// �A�C�e���Ƃ̓����蔻��

	// �J�E���^
	int					hitObjCnt;			// �I�u�W�F�N�g�ɂ��������Ƃ��̃J�E���^

	// �A�C�e���֘A�̃X�e�[�^�X
	bool				spike;				// �X�p�C�N�u�[�c������
	bool				gun;				// �g�����`�K��������
	bool				blind;				// �u���C���h��
	bool				spink;				// SP�C���N

public:
	// �����o�֐�
	Player(int _CtrlNum,bool AIUse);
	~Player();
	void Update();
	void Draw();

	// ��Ԓ��ۃC���^�[�t�F�[�X
	void UpdateState(int AnimCurtID);
	void ChangeState(PlayerState *NewState);

	// �����蔻��
	void GroundCollider();
	void HorizonCollider();
	void ObjectCollider();
	void PaintCollider();
	void FieldItemCollider(FieldItemManager *pFIManager);

	void HitObjectInfluence(int type);	// �t�B�[���h�I�u�W�F�N�g�ɐڐG�����Ƃ��̌���

	// �Q�b�^�[(�Ȃ�ׂ��g��Ȃ�)
	FieldItemManager *GetFieldItemManager() { return itemManager; };
	D3DXVECTOR3	GetPos() { return pos; };
	float GetJumpSpeed() { return jumpSpd; };
	PaintManager* GetPaintManager(void) { return this->PaintSystem; };

	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };
	bool GetHitGround() { return hitGround; };
	bool GetHitHorizon() { return hitHorizon; };
	bool GetHitPaint() { return hitPaint; };
	bool GetHitItem() { return hitItem; };

	bool GetSpike() { return spike; };
	bool GetGun() { return gun; };
	bool GetBlind() { return blind; };
	bool GetSpInk() { return spink; };

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpd = _JumpSpeed; };
	void SetPlayable(bool _playable) { playable = _playable; };
	void SetHitItem(bool _hitItem) { hitItem = _hitItem; };

	void SetSpike(bool _spike) { spike = _spike; };
	void SetGun(bool _gun) { gun = _gun; };
	void SetBlind(bool _blind){ blind = _blind; };
	void SetRunSpd(float _runSpd) { runSpd = _runSpd; };
	void SetJumpValue(float _jumpValue) { jumpValue = _jumpValue; };
	void SetSpInk(bool _spink) { spink = spink; };
};

#endif
