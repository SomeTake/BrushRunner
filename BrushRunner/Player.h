//=============================================================================
//
// �v���C���[�N���X[Player.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Boy.x"							// �ǂݍ��ރ��f����(�t�@�C���p�X��)
#define PLAYER_MAX			(4)											// ���삷��v���C���[�̐�
#define PLAYER_FIRST_POS	D3DXVECTOR3(20.0f, -40.0f, 0.0f)			// �����ʒu
#define PLAYER_FIRST_ROT	D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// �����̌���
#define JUMP_SPEED			(20.0f)										// �W�����v�̏���
#define	RATE_MOVE_PLAYER	(0.025f)									// �ړ������W��
#define INK_MAX				(100)										// �C���N�̍ő��
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)				// �����蔻���L���ɂ���T�C�Y
#define MOVE_SPEED			(5.0f)										// �����X�s�[�h

// �L�����N�^�[�̃A�j���[�V�����ԍ�
static const char* CharaStateAnim[] =
{
	"idle",				// �ҋ@
	"frontwalk",		// �O����
	"backwalk",			// ������
	"rightstep",		// ���ړ�
	"leftstep",			// ���ړ�
	"guard",			// �K�[�h �߂����ዹ����
	"damage",			// �_���[�W�󂯂�
	"down",				// �_�E��
	"downpose",			// �_�E�����
	"getup",			// �N���オ��
	"punchi",			// �p���`
	"straight",			// �p���`�ǌ��P
	"upper",			// �p���`�ǌ��Q
	"kick",				// �L�b�N
	"hadou",			// �g�����B�₽�甭�����x��
	"shoryu",			// �������B�o�b�N�t���b�v
	"SPattack",			// SP�Z�B�߂������]����
	"throw",			// �����B�͂�ŕG����ăA�b�p�[
	"win",				// �K�b�c�|�[�Y�i�������j
	"miss",				// �����X�J��
	"throwedpose"		// �������Ă���Œ��̃|�[�Y
};

// �L�����N�^�[�̃A�j���[�V�����ԍ��ƘA���iCharaStateAnim�j
enum CharaStateNum
{
	Idle,
	Frontwalk,
	Backwalk,
	Rightstep,
	Leftstep,
	Guard,
	Damage,
	Down,
	Downpose,
	Getup,
	Punchi,
	Straight,
	Upper,
	Kick,
	Hadou,
	Shoryu,
	SPattack,
	Throw,
	Win,
	Miss,
	ThrowedPose,
	AnimMax,			// �A�j���[�V�����̍ő吔
};

// �o�g���p�f�[�^�\����
typedef struct
{
	int Damage;					// ���̃��[�V�����ɂ���ė^����_���[�W�ʁiSP�Q�[�W�A�X�R�A�Ȃǂ��j
	float Spd;					// �A�j���[�V�������Đ�����X�s�[�h
	float ShiftTime;			// �A�j���[�V�����̐؂�ւ�����
	int CollisionStartTime;		// �U�������蔻��̔������鎞��
	int CollisionFinishTime;	// �U�������蔻��̏I�����鎞��
}BATTLEDATA;

// �o�g���p�f�[�^�\���̔z��
static BATTLEDATA Data[AnimMax] = {
	{ 0, 1.5f, 0.1f, 0, 0 },		// Idle
{ 0, 2.0f, 0.1f, 0, 0 },		// Frontwalk
{ 0, 2.0f, 0.1f, 0, 0 },		// Backwalk
{ 0, 2.0f, 0.1f, 0, 0 },		// Rightstep
{ 0, 2.0f, 0.1f, 0, 0 },		// Leftstep
{ 0, 1.0f, 0.1f, 0, 0 },		// Guard
{ 0, 1.5f, 0.1f, 0, 0 },		// Damage
{ 0, 1.5f, 0.1f, 0, 0 },		// Down
{ 0, 1.0f, 0.1f, 0, 0 },		// Downpose
{ 0, 1.5f, 0.1f, 0, 0 },		// Getup
{ 40, 2.5f, 0.1f, 10, 20 },		// Punchi
{ 50, 1.5f, 0.1f, 10, 20 },		// Straight
{ 60, 2.0f, 0.1f, 15, 30 },		// Upper
{ 50, 2.5f, 0.1f, 15, 30 },		// Kick
{ 100, 3.0f, 0.1f, 25, 0 },		// Hadou
{ 120, 2.0f, 0.1f, 5, 20 },		// Shoryu
{ 400, 1.5f, 0.1f, 30, 150 },	// SPattack
{ 150, 1.0f, 0.1f, 0, 0 },		// Throw
{ 0, 2.0f, 0.1f, 0, 0 },		// Win
{ 0, 1.5f, 0.1f, 0, 0 },		// Miss
{ 0, 1.0f, 0.1f, 0, 0 },		// Throwpose
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
class PLAYER
{
private:
	// �����o�ϐ�
	D3DXANIMATION * Animation;				// �A�j���[�V�����\����
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			move;				// ���f���̈ړ���
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	bool				jumpFlag;			// �W�����v�t���O
	float				jumpSpeed;			// �W�����v�X�s�[�h
	int					ctrlNum;			// ���삷��R���g���[���ԍ�
	int					inkValue[InkNum];	// �C���N�̎c��
	int					inkType;			// �g�p����C���N�̎��(enum ColorInk=�J���[, BlackInk=��)

public:
	PLAYER(int _CtrlNum);
	~PLAYER();
	void Update();
	void Draw();

	void Change();			// �C���N�̎�ތ���
	void Move();			// �ړ�

	// �Q�b�^�[
	D3DXVECTOR3	GetPos() { return pos; };
	D3DXVECTOR3 GetMove() { return move; };
	bool GetJumpFlag() { return jumpFlag; };
	int GetInkValue(int _InkNum) { return inkValue[_InkNum]; };
	int GetInkType() { return inkType; };
	float GetJumpSpeed() { return jumpSpeed; };

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetJumpFlag(bool _jumpflag) { jumpFlag = _jumpflag; };
	void SetInkValue(int _InkNum, int _InkValue) { inkValue[_InkNum] = _InkValue; };
	void SetInkType(int _InkType) { inkType = _InkType; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpeed = _JumpSpeed; };
};

#endif
