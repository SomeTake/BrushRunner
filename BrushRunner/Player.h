//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "Struct.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"			// �ǂݍ��ރ��f����(�t�@�C���p�X��)
#define PLAYER_MAX			(4)											// ���삷��v���C���[�̐�
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// �����̌���
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define JUMP_SPEED			(12.0f)										// �W�����v�̏���
#define	RATE_MOVE_PLAYER	(0.025f)									// �ړ������W��
#define INK_MAX				(50)										// �C���N�̍ő��
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)				// �����蔻���L���ɂ���T�C�Y
#define MOVE_SPEED			(2.0f)										// �����X�s�[�h

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

// �C���N�̎��
enum InkType {
	ColorInk,
	BlackInk,

	// �C���N�̍ő吔
	InkNum,
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// �����o�ϐ�
	//D3DXANIMATION		*Animation;			// �A�j���[�V�����\����
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	bool				jumpFlag;			// �W�����v�t���O
	float				jumpSpeed;			// �W�����v�X�s�[�h
	int					ctrlNum;			// ���삷��R���g���[���ԍ�
	int					inkValue[InkNum];	// �C���N�̎c��
	int					inkType;			// �g�p����C���N�̎��(enum ColorInk=�J���[, BlackInk=��)
	bool				moveFlag;			// �ړ��\�t���O�i�i�s�����ɃI�u�W�F�N�g������ꍇ�͈ړ��s�j
	bool				playable;			// �Q�[���������肷��t���O
	bool				use;				// ��ʓ��ɂ���Ƃ�

	// �����o�֐�
	void AnimationManager();		// �A�j���[�V�����Ǘ�
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);

	void ChangeInk();		// �C���N�̎�ތ���
	void Move();			// �ړ�
	void CheckOnCamera();

public:
	// �����o�֐�
	Player(int _CtrlNum, D3DXVECTOR3 firstpos);
	~Player();
	void Update();
	void Draw();

	// �Q�b�^�[
	D3DXVECTOR3	GetPos() { return pos; };
	D3DXVECTOR3 GetMove() { return move; };
	bool GetJumpFlag() { return jumpFlag; };
	int GetInkValue(int _InkNum) { return inkValue[_InkNum]; };
	int GetInkType() { return inkType; };
	float GetJumpSpeed() { return jumpSpeed; };
	bool GetMoveFlag() { return moveFlag; };
	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetJumpFlag(bool _jumpflag) { jumpFlag = _jumpflag; };
	void SetInkValue(int _InkNum, int _InkValue) { inkValue[_InkNum] = _InkValue; };
	void SetInkType(int _InkType) { inkType = _InkType; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpeed = _JumpSpeed; };
	void SetMoveFlag(bool _moveFlag) { moveFlag = _moveFlag; };
	void SetPlayable(bool _playable) { playable = _playable; };
};

#endif
