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
#include "Map.h"

#include "PlayerState.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// 読み込むモデル名(ファイルパス名)
#define PLAYER_MAX			(4)											// 操作するプレイヤーの数
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define	RATE_MOVE_PLAYER	(0.025f)									// 移動慣性係数
#define INK_MAX				(50)										// インクの最大量
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)					// 当たり判定を有効にするサイズ
#define JUMP_SPEED			(12.0f)										// ジャンプの初速
#define STANDARD_GRAVITY	(0.98f)										// 重力加速度
#define FALL_VELOCITY_MAX	(30.0f)										// 落下中最大速度

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	AnimMax,			// アニメーションの最大数
};

// インクの種類
enum InkType {
	ColorInk,
	BlackInk,

	// インクの最大数
	InkNum,
};

class PaintManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// メンバ変数
	PlayerState			*state;				// ステータス管理抽象クラス
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	int					ctrlNum;			// 操作するコントローラ番号
	float				animSpd;			// アニメーションの再生スピード
	bool				playable;			// 操作可能
	bool				onCamera;			// 画面内にいるとき

	// ステータス関係
	float				runSpd;				// ダッシュ速度
	float				jumpSpd;			// ジャンプ速度
	int					inkValue[InkNum];	// インクの残量
	int					inkType;			// 使用中のインクの種類(enum ColorInk=カラー, BlackInk=黒)

	// 当たり判定関係のフラグ
	bool				hitGround;			// 地上判定(↓と合わせて両方falseだと空中状態)
	bool				hitPaint;
	bool				hitHorizon;			// 進行方向のオブジェクトとの当たり判定

	// カウンタ
	int					hitObjCnt;			// オブジェクトにあたったときのカウンタ

public:
	// メンバ関数
	Player(int _CtrlNum, D3DXVECTOR3 firstpos);
	~Player();
	void Update();
	void Draw();

	void ChangeInk();		// インクの種類交換
	void Move();			// 移動
	void JumpMove();		// ジャンプ移動
	void CheckOnCamera();	// 画面内判定

	void Debug();			// デバッグ

	// 状態抽象インターフェース
	void UpdateState(int AnimCurtID);
	void ChangeState(PlayerState *NewState);

	// アニメーション
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);

	// 当たり判定
	void GroundCollider(Map *pMap);
	void HorizonCollider(Map *pMap);
	void ObjectCollider(Map *pMap);
	void PaintCollider(PaintManager *pPManager);

	void HitObjectInfluence(int type);

	// ゲッター(なるべく使わない)
	D3DXVECTOR3	GetPos() { return pos; };
	int GetInkValue(int _InkNum) { return inkValue[_InkNum]; };
	int GetInkType() { return inkType; };
	//float GetJumpSpeed() { return jumpSpd; };
	int GetCtrlNum() { return ctrlNum; };
	bool GetPlayable() { return playable; };
	bool GetHitGround() { return hitGround; };
	bool GetHitHorizon() { return hitHorizon; };
	bool GetHitPaint() { return hitPaint; };

	// セッター(なるべく使わない)
	void SetInkValue(int _InkNum, int _InkValue) { inkValue[_InkNum] = _InkValue; };
	void SetJumpSpeed(float _JumpSpeed) { jumpSpd = _JumpSpeed; };
	void SetPlayable(bool _playable) { playable = _playable; };
};

#endif
