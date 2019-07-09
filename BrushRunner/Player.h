//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "CharacterAI.h"
#include "PaintSystem.h"
#include "Pop.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX				(4)										// 操作するプレイヤーの数
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)					// 当たり判定を有効にするサイズ

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	AnimMax,			// アニメーションの最大数
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// メンバ変数
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	CharacterAI			*AI;				// キャラクターAI
	PaintManager		*PaintSystem;		// ペイントシステム
	Pop					*PopUp;				// ポップアップ
	bool				jumpFlag;			// ジャンプフラグ
	float				jumpSpeed;			// ジャンプスピード
	float				ActionSpeed;
	int					ctrlNum;			// 操作するコントローラ番号
	bool				moveFlag;			// 移動可能フラグ（進行方向にオブジェクトがある場合は移動不可）
	bool				playable;			// ゲーム中か判定するフラグ
	bool				use;				// 画面内にいるとき

	// メンバ関数
	void AnimationManager();		// アニメーション管理
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);
	void Move();			// 移動
	void CheckOnCamera();

public:
	// メンバ関数
	Player(int _CtrlNum);
	~Player();
	void Update();
	void Draw();

	// ゲッター
	D3DXVECTOR3	GetPos() { return pos; };
	D3DXVECTOR3 GetMove() { return move; };
	bool GetJumpFlag() { return jumpFlag; };
	float GetJumpSpeed() { return jumpSpeed; };
	bool GetMoveFlag() { return moveFlag; };
	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };
	PaintManager* GetPaintManager(void) { return this->PaintSystem; };

	// セッター
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetJumpFlag(bool _jumpflag) { jumpFlag = _jumpflag; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpeed = _JumpSpeed; };
	void SetMoveFlag(bool _moveFlag) { moveFlag = _moveFlag; };
	void SetPlayable(bool _playable) { playable = _playable; };
};

#endif
