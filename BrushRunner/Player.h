//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Boy.x"							// 読み込むモデル名(ファイルパス名)
#define PLAYER_MAX			(4)											// 操作するプレイヤーの数
#define PLAYER_FIRST_POS	D3DXVECTOR3(20.0f, -40.0f, 0.0f)			// 初期位置
#define PLAYER_FIRST_ROT	D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define JUMP_SPEED			(20.0f)										// ジャンプの初速
#define	RATE_MOVE_PLAYER	(0.025f)									// 移動慣性係数
#define INK_MAX				(100)										// インクの最大量
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)				// 当たり判定を有効にするサイズ
#define MOVE_SPEED			(5.0f)										// 動くスピード

// キャラクターのアニメーション番号
static const char* CharaStateAnim[] =
{
	"idle",				// 待機
	"frontwalk",		// 前歩き
	"backwalk",			// 後ろ歩き
	"rightstep",		// 横移動
	"leftstep",			// 横移動
	"guard",			// ガード めっちゃ胸反る
	"damage",			// ダメージ受けた
	"down",				// ダウン
	"downpose",			// ダウン状態
	"getup",			// 起き上がり
	"punchi",			// パンチ
	"straight",			// パンチ追撃１
	"upper",			// パンチ追撃２
	"kick",				// キック
	"hadou",			// 波動拳。やたら発生が遅い
	"shoryu",			// 昇竜拳。バックフリップ
	"SPattack",			// SP技。めっちゃ回転する
	"throw",			// 投げ。掴んで膝入れてアッパー
	"win",				// ガッツポーズ（勝利時）
	"miss",				// 投げスカり
	"throwedpose"		// 投げられている最中のポーズ
};

// キャラクターのアニメーション番号と連動（CharaStateAnim）
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
class PLAYER
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

public:
	PLAYER(int _CtrlNum);
	~PLAYER();
	void Update();
	void Draw();

	void Change();			// インクの種類交換
	void Move();			// 移動

	// ゲッター
	D3DXVECTOR3	GetPos() { return pos; };
	D3DXVECTOR3 GetMove() { return move; };
	bool GetJumpFlag() { return jumpFlag; };
	int GetInkValue(int _InkNum) { return inkValue[_InkNum]; };
	int GetInkType() { return inkType; };
	float GetJumpSpeed() { return jumpSpeed; };

	// セッター
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetJumpFlag(bool _jumpflag) { jumpFlag = _jumpflag; };
	void SetInkValue(int _InkNum, int _InkValue) { inkValue[_InkNum] = _InkValue; };
	void SetInkType(int _InkType) { inkType = _InkType; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpeed = _JumpSpeed; };
};

#endif
