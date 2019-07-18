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
#include "PlayerUI.h"
#include "PlayerState.h"
#include "FieldItemManager.h"
#include "PaintManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX				(1)										// 操作するプレイヤーの数
#define PLAYER_COLLISION_SIZE	D3DXVECTOR2(5.0f, 5.0f)					// 当たり判定を有効にするサイズ
#define JUMP_SPEED				(12.0f)									// ジャンプの初速

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Running,
	Jump,
	Victory,
	Slip,
	Stop,
	AnimMax,			// アニメーションの最大数
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player : public D3DXANIMATION
{
private:
	// メンバ変数
	PlayerState			*state;				// ステータス管理抽象クラス
	FieldItemManager	*itemManager;		// フィールドアイテム管理クラス

	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	CharacterAI			*AI;				// キャラクターAI
	PaintManager		*PaintSystem;		// ペイントシステム
	PlayerUI			*playerUI;

	// メンバ関数
	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet(void);
	void Move();			// 移動
	void CheckOnCamera();
	void JumpMove();		// ジャンプ移動
	void Debug();			// デバッグ

	int					ctrlNum;			// 操作するコントローラ番号
	float				animSpd;			// アニメーションの再生スピード
	bool				playable;			// 操作可能
	bool				onCamera;			// 画面内にいるとき

	// ステータス関係
	float				runSpd;				// ダッシュ速度(0.0-1.0-2.0)
	float				jumpSpd;			// ジャンプ速度
	float				jumpValue;			// ジャンプ速度に掛けて使う(0.0-1.0-2.0)
	int					inkValue[InkNum];	// インクの残量
	int					inkType;			// 使用中のインクの種類(enum ColorInk=カラー, BlackInk=黒)

	// 当たり判定関係のフラグ
	bool				hitGround;			// 地上判定(↓と合わせて両方falseだと空中状態)
	bool				hitPaint;
	bool				hitHorizon;			// 進行方向のオブジェクトとの当たり判定
	bool				hitItem;			// アイテムとの当たり判定

	// カウンタ
	int					hitObjCnt;			// オブジェクトにあたったときのカウンタ

	// アイテム関連のステータス
	bool				spike;				// スパイクブーツ装備中
	bool				gun;				// トリモチガン装備中
	bool				blind;				// ブラインド中
	bool				spink;				// SPインク

public:
	// メンバ関数
	Player(int _CtrlNum,bool AIUse);
	~Player();
	void Update();
	void Draw();

	// 状態抽象インターフェース
	void UpdateState(int AnimCurtID);
	void ChangeState(PlayerState *NewState);

	// 当たり判定
	void GroundCollider();
	void HorizonCollider();
	void ObjectCollider();
	void PaintCollider();
	void FieldItemCollider(FieldItemManager *pFIManager);

	void HitObjectInfluence(int type);	// フィールドオブジェクトに接触したときの効果

	// ゲッター(なるべく使わない)
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

	// セッター
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
