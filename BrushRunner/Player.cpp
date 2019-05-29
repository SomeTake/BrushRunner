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

//=====================================================================================================
// コンストラクタ
//=====================================================================================================
PLAYER::PLAYER(int _CtrlNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//オブジェクトの初期化
	Animation = CreateAnimationObject();

	// xFileの読み込み
	Load_xFile(Animation, CHARA_XFILE, "Player");

	// アニメーションの最終フレームをセットする
	// 前歩き
	SetupCallbackKeyframes(Animation, CharaStateAnim[Frontwalk]);
	// 後ろ歩き
	SetupCallbackKeyframes(Animation, CharaStateAnim[Backwalk]);
	// 右ステップ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Rightstep]);
	// 左ステップ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Leftstep]);
	// 被ダメージ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Damage]);
	// ダウン
	SetupCallbackKeyframes(Animation, CharaStateAnim[Down]);
	// ダウンポーズ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Downpose]);
	// 起き上がり
	SetupCallbackKeyframes(Animation, CharaStateAnim[Getup]);
	// パンチ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Punchi]);
	// ストレート（追撃パンチ１）
	SetupCallbackKeyframes(Animation, CharaStateAnim[Straight]);
	// アッパー（追撃パンチ２）
	SetupCallbackKeyframes(Animation, CharaStateAnim[Upper]);
	// キック
	SetupCallbackKeyframes(Animation, CharaStateAnim[Kick]);
	// 波動
	SetupCallbackKeyframes(Animation, CharaStateAnim[Hadou]);
	// 昇竜
	SetupCallbackKeyframes(Animation, CharaStateAnim[Shoryu]);
	// SP技
	SetupCallbackKeyframes(Animation, CharaStateAnim[SPattack]);
	// 投げ
	SetupCallbackKeyframes(Animation, CharaStateAnim[Throw]);
	// 投げスカり
	SetupCallbackKeyframes(Animation, CharaStateAnim[Miss]);

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
	rot = PLAYER_FIRST_ROT;
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
PLAYER::~PLAYER()
{
	// アニメーションをリリース
	Animation->UninitAnimation(Animation);

}

//=====================================================================================================
// 更新
//=====================================================================================================
void PLAYER::Update()
{
	// アニメーションを更新
	Animation->UpdateAnimation(Animation, TIME_PER_FRAME);

	// ジャンプ
	if (GetKeyboardTrigger(DIK_UP))
	{
		jumpFlag = true;
		jumpSpeed = JUMP_SPEED;
	}

	// ジャンプ中または落下中は重力が加わる
	if (jumpFlag)
	{
		pos.y += jumpSpeed;
		if (jumpSpeed > 0)
		{
			jumpSpeed -= STANDARD_GRAVITY;
		}
	}

	pos.x += MOVE_SPEED;

	//// 移動処理
	//pos.x += move.x;
	//pos.y += move.y;
	//pos.z += move.z;

	//// 移動量に慣性をかける
	//move.x += (0.0f - move.x) * RATE_MOVE_PLAYER;
	//move.y += (0.0f - move.y) * RATE_MOVE_PLAYER;
	//move.z += (0.0f - move.z) * RATE_MOVE_PLAYER;

	PrintDebugProc("PLAYER POS X:%f, Y:%f, Z:%f\n", pos.x, pos.y, pos.z);
	PrintDebugProc("PLAYER MOVE X:%f, Y:%f, Z:%f\n", move.x, move.y, move.z);
}

//=====================================================================================================
// 描画
//=====================================================================================================
void PLAYER::Draw()
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
