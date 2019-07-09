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
#include "PaintSystem.h"
#include "Pop.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MAX				(4)										// ���삷��v���C���[�̐�
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)					// �����蔻���L���ɂ���T�C�Y

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// �����o�ϐ�
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	CharacterAI			*AI;				// �L�����N�^�[AI
	PaintManager		*PaintSystem;		// �y�C���g�V�X�e��
	Pop					*PopUp;				// �|�b�v�A�b�v
	bool				jumpFlag;			// �W�����v�t���O
	float				jumpSpeed;			// �W�����v�X�s�[�h
	float				ActionSpeed;
	int					ctrlNum;			// ���삷��R���g���[���ԍ�
	bool				moveFlag;			// �ړ��\�t���O�i�i�s�����ɃI�u�W�F�N�g������ꍇ�͈ړ��s�j
	bool				playable;			// �Q�[���������肷��t���O
	bool				use;				// ��ʓ��ɂ���Ƃ�

	// �����o�֐�
	void AnimationManager();		// �A�j���[�V�����Ǘ�
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);
	void Move();			// �ړ�
	void CheckOnCamera();

public:
	// �����o�֐�
	Player(int _CtrlNum);
	~Player();
	void Update();
	void Draw();

	// �Q�b�^�[
	D3DXVECTOR3	GetPos() { return pos; };
	D3DXVECTOR3 GetMove() { return move; };
	bool GetJumpFlag() { return jumpFlag; };
	float GetJumpSpeed() { return jumpSpeed; };
	bool GetMoveFlag() { return moveFlag; };
	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };
	PaintManager* GetPaintManager(void) { return this->PaintSystem; };

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetJumpFlag(bool _jumpflag) { jumpFlag = _jumpflag; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpeed = _JumpSpeed; };
	void SetMoveFlag(bool _moveFlag) { moveFlag = _moveFlag; };
	void SetPlayable(bool _playable) { playable = _playable; };
};

#endif
