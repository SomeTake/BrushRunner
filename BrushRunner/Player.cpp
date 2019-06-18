//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Debugproc.h"
#include "Input.h"
#include "Gravity.h"
#include "SceneGame.h"

//=====================================================================================================
// コンストラクタ
//=====================================================================================================
Player::Player(int _CtrlNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//オブジェクトの初期化
	Animation = CreateAnimationObject();

	// xFileの読み込み
	Load_xFile(Animation, CharaModel[KouhaiModel], "Player");

	// アニメーションの最終フレームをセットする
	// 待機
	SetupCallbackKeyframes(Animation, CharaStateAnim[Idle]);
	// 前歩き
	SetupCallbackKeyframes(Animation, CharaStateAnim[Running]);
	// 後ろ歩き
	SetupCallbackKeyframes(Animation, CharaStateAnim[Jump]);
	// 右ステップ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Victory]);

	// アニメーションセットの初期化
	for (int i = 0; i < Animation->AnimSetNum; i++)
	{
		Animation->InitAnimation(Animation, CharaStateAnim[i], i);
	}

	// 現在のアニメーションをアイドル状態とする
	Animation->CurrentAnimID = Idle;

	// アニメーション間の補完を設定
	for (int i = 0; i < Animation->AnimSetNum; i++)
	{
		Animation->SetShiftTime(Animation, i, Data[i].ShiftTime);
	}

	// 位置・回転・スケールの初期設定
	pos = PLAYER_FIRST_POS;
	rot = PLAYER_ROT;
	scl = ModelScl[KouhaiModel];
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	moveFlag = true;
	playable = false;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
Player::~Player()
{
	// アニメーションをリリース
	Animation->UninitAnimation(Animation);

}

//=====================================================================================================
// 更新
//=====================================================================================================
void Player::Update()
{
	// アニメーションを更新
	Animation->UpdateAnimation(Animation, TIME_PER_FRAME);

	// 移動
	Move();

	// インク変更
	ChangeInk();

	// アニメーション管理
	ChangeAnim();

#ifndef _DEBUG_
	PrintDebugProc("PLAYER[%d] POS X:%f, Y:%f, Z:%f\n", ctrlNum, pos.x, pos.y, pos.z);
	//PrintDebugProc("PLAYER[%d] MOVE X:%f, Y:%f, Z:%f\n", ctrlNum, move.x, move.y, move.z);
	//PrintDebugProc("PLAYER[%d] INK TYPE %s\n", ctrlNum, inkType ? "Balck" : "Color");
	//PrintDebugProc("PLAYER[%d] INK VALUE COLOR %d\n", ctrlNum, inkValue[ColorInk]);
	//PrintDebugProc("PLAYER[%d] INK VALUE BLACK %d\n", ctrlNum, inkValue[BlackInk]);
	//PrintDebugProc("PLAYER[%d] JUMP FLAG:%d\n", ctrlNum, jumpFlag);
	//PrintDebugProc("PLAYER[%d] JUMP SPEED:%f\n", ctrlNum, jumpSpeed);

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (inkValue[inkType] > 0)
		{
			inkValue[inkType]--;
		}
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		if (inkValue[inkType] < INK_MAX)
		{
			inkValue[inkType]++;
		}
	}
#endif
}

//=====================================================================================================
// 描画
//=====================================================================================================
void Player::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX WorldMtx, SclMtx, RotMtx, TransMtx;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMtx);

	// スケールを反映
	D3DXMatrixScaling(&SclMtx, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&SclMtx, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &SclMtx);

	// 移動を反映
	D3DXMatrixTranslation(&TransMtx, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &TransMtx);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &WorldMtx);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// レンダリング
	Animation->DrawAnimation(Animation, &WorldMtx);

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=====================================================================================================
// インクの種類交換
//=====================================================================================================
void Player::ChangeInk()
{
	if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(ctrlNum, BUTTON_R1))
	{
		// 黒→カラー
		if (inkType == BlackInk)
		{
			inkType = ColorInk;
		}
		// カラー→黒
		else
		{
			inkType = BlackInk;
		}

		// インクバーの描画順を入れ替え
		ChangeDrawOrder(NumInkblack00 + ctrlNum, NumInkblue + ctrlNum);
		// フレームの描画順を入れ替え
		ChangeDrawOrder(NumBlackFrame00 + ctrlNum, NumColorFrame00 + ctrlNum);
	}
}

//=====================================================================================================
// 移動
//=====================================================================================================
void Player::Move()
{
	// ジャンプ
	if (playable)
	{
		if ((GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(ctrlNum, BUTTON_B)) && (!jumpFlag))
		{
			jumpFlag = true;
			moveFlag = true;
			jumpSpeed = JUMP_SPEED;
			Animation->ChangeAnimation(Animation, Jump, Data[Jump].Spd);
		}
	}

	// 地上にいるとき
	if (!jumpFlag)
	{
		jumpSpeed = 0;
	}
	// 空中にいるとき
	else
	{
		pos.y += jumpSpeed;
	}

	// オート移動
	if (moveFlag && playable)
	{
		pos.x += MOVE_SPEED;
	}
}

//=====================================================================================================
// アニメーション管理
//=====================================================================================================
void Player::ChangeAnim()
{
	// 待機状態
	if (!playable)
	{
		if (Animation->CurrentAnimID != Idle)
		{
			Animation->ChangeAnimation(Animation, Idle, Data[Idle].Spd);
		}
	}

	if (playable)
	{
		if (!jumpFlag)
		{
			// 歩行中
			if (moveFlag)
			{
				if (Animation->CurrentAnimID != Running)
				{
					Animation->ChangeAnimation(Animation, Running, Data[Running].Spd);
				}
			}
			// 待機中
			else
			{
				if (Animation->CurrentAnimID != Idle)
				{
					Animation->ChangeAnimation(Animation, Idle, Data[Idle].Spd);
				}
			}
		}
	}
}