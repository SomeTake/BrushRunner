//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "Struct.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"			// 読み込むモデル名(ファイルパス名)
#define PLAYER_MAX			(4)											// 操作するプレイヤーの数
#define PLAYER_FIRST_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// 初期位置
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define JUMP_SPEED			(12.0f)										// ジャンプの初速
#define	RATE_MOVE_PLAYER	(0.025f)									// 移動慣性係数
#define INK_MAX				(100)										// インクの最大量
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)				// 当たり判定を有効にするサイズ
#define MOVE_SPEED			(2.0f)										// 動くスピード

// 読み込むキャラクターモデル
static const char* CharaModel[] = 
{
	"data/MODEL/Boy.x",
	"data/MODEL/Shachiku/Shachiku.x",
	"data/MODEL/Kouhai/Kouhai.x",
};

// キャラクターモデルの番号
enum CharaModelNum
{
	BoyModel,
	ShachikuModel,
	KouhaiModel,

	// モデルの種類
	MaxModel
};

// モデルの大きさ設定
static D3DXVECTOR3 ModelScl[MaxModel] = 
{
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.4f, 0.4f, 0.4f)
};

// キャラクターのアニメーション番号
static const char* CharaStateAnim[] =
{
	"idle",				// 待機
	"Running",			// ダッシュ
	"Jump",				// ジャンプ
	"Victory"			// ガッツポーズ
};

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	AnimMax,			// アニメーションの最大数
};

// バトル用データ構造体
typedef struct
{
	int Damage;					// そのモーションによって与えるダメージ量（SPゲージ、スコアなども）
	float Spd;					// アニメーションを再生するスピード
	float ShiftTime;			// アニメーションの切り替え時間
	int CollisionStartTime;		// 攻撃当たり判定の発生する時間
	int CollisionFinishTime;	// 攻撃当たり判定の終了する時間
}BATTLEDATA;

// バトル用データ構造体配列
static BATTLEDATA Data[AnimMax] = {
	{ 0, 1.5f, 0.1f, 0, 0 },		// Idle
{ 0, 1.0f, 0.1f, 0, 0 },		// Running
{ 0, 1.0f, 0.1f, 0, 0 },		// Jump
{ 0, 1.0f, 0.1f, 0, 0 },		// Victory
};

// インクの種類
enum InkType {
	ColorInk,
	BlackInk,

	// インクの最大数
	InkNum,
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player
{
private:
	// メンバ変数
	D3DXANIMATION * Animation;				// アニメーション構造体
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	bool				jumpFlag;			// ジャンプフラグ
	float				jumpSpeed;			// ジャンプスピード
	int					ctrlNum;			// 操作するコントローラ番号
	int					inkValue[InkNum];	// インクの残量
	int					inkType;			// 使用するインクの種類(enum ColorInk=カラー, BlackInk=黒)
	bool				moveFlag;			// 移動可能フラグ（進行方向にオブジェクトがある場合は移動不可）
	bool				playable;			// ゲーム中か判定するフラグ

	// メンバ関数
	void ChangeInk();		// インクの種類交換
	void Move();			// 移動
	void ChangeAnim();		// アニメーション管理

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
	int GetInkValue(int _InkNum) { return inkValue[_InkNum]; };
	int GetInkType() { return inkType; };
	float GetJumpSpeed() { return jumpSpeed; };
	bool GetMoveFlag() { return moveFlag; };
	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };

	// セッター
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
