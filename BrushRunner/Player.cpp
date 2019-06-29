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
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"
#include "DebugWindow.h"
#include "Collision.h"
#include "PaintSystem.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
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

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// モーション終了
};

//=====================================================================================================
// コンストラクタ
//=====================================================================================================
Player::Player(int _CtrlNum, D3DXVECTOR3 firstpos) : state(nullptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// xFileを読み込む
	this->Load_xFile(CharaModel[KouhaiModel], "Player");

	// アニメーションセットを設置する
	this->CreateAnimSet();

	// 現在のアニメーションをアイドル状態とする
	this->ChangeAnim(Idle);

	// 位置・回転・スケールの初期設定
	pos = firstpos;
	rot = PLAYER_ROT;
	scl = ModelScl[KouhaiModel];
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hitGround = false;
	hitPaint = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	hitHorizon = true;
	playable = false;
	onCamera = true;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

	// 待機状態からスタートする
	new IdleState(this);
}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
Player::~Player()
{
	delete state;
}

//=====================================================================================================
// 更新
//=====================================================================================================
void Player::Update()
{
	if (onCamera)
	{
		// 移動
		Move();

		// インク変更
		ChangeInk();

		// アニメーション管理
		AnimationManager();

		// カメラ内判定
		CheckOnCamera();

		// 状態抽象インターフェースの更新
		UpdateState(this->GetAnimCurtID());

	}

	// デバッグ表示＆操作
	Debug();
}

//=====================================================================================================
// 描画
//=====================================================================================================
void Player::Draw()
{
	if (onCamera)
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
		this->DrawAnim(&WorldMtx);

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=====================================================================================================
// 状態抽象インターフェースの更新
//=====================================================================================================
void Player::UpdateState(int AnimCurtID)
{
	state->Update(AnimCurtID);
}

//=====================================================================================================
// 状態抽象インターフェースの変更
//=====================================================================================================
void Player::ChangeState(PlayerState *NewState, int NextAnimID)
{
	delete state;
	state = NewState;

	// アニメーション変更
	if (this->GetAnimCurtID() != NextAnimID)
	{
		this->ChangeAnim(NextAnimID);
	}
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
	// マップとペイントどちらかに当たっていれば地上判定
	if(hitGround || hitPaint)
	{
		// ジャンプ
		if (playable)
		{
			if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(ctrlNum, BUTTON_B))
			{
				hitGround = false;
				hitPaint = false;
				hitHorizon = false;
				jumpSpeed = JUMP_SPEED;
				this->ChangeAnim(Jump);
			}
		}
	}
	else
	{
		pos.y += jumpSpeed;
		// 重力
		//Gravity();
	}

	// オート移動
	if (!hitHorizon && playable)
	{
		pos.x += MOVE_SPEED;
	}

#if _DEBUG
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	pos.x += MOVE_SPEED;
	//}
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	pos.x -= MOVE_SPEED;
	//}
#endif
}

//=====================================================================================================
// アニメーション管理
//=====================================================================================================
void Player::AnimationManager()
{
	// 操作不可
	if (!playable)
	{
		if (this->GetAnimCurtID() != Idle)
		{
			this->ChangeAnim(Idle);
		}
	}
	else
	{
		if (hitGround && hitPaint)
		{
			// 歩行中
			if (!hitHorizon)
			{
				if (this->GetAnimCurtID() != Running)
				{
					this->ChangeAnim(Running);
				}
			}
			// 待機中
			else
			{
				if (this->GetAnimCurtID() != Idle)
				{
					this->ChangeAnim(Idle);
				}
			}
		}
	}

	// アニメーションを更新
	this->UpdateAnim(TIME_PER_FRAME);

}

//=====================================================================================================
// アニメーションのセット
//=====================================================================================================
void Player::CreateAnimSet()
{
	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
	vector<KEYDATA>Keydata;
	Keydata.reserve(Keydata_Max);

	for (int Set_No = 0; Set_No < GetAnimSetNum(); Set_No++)
	{
		switch (Set_No)
		{
		case Idle:

			Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Victory:

			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
			break;

		default:
			break;
		}

		this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());

		AnimationSet->SetAnimSetPtr(this->AnimController);

		this->AnimSet.push_back(*AnimationSet);

		Keydata.clear();
	}

	SAFE_DELETE(AnimationSet);
	ReleaseVector(Keydata);
}

//=====================================================================================================
// アニメーションのコールバック
//=====================================================================================================
HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	return S_OK;
}

//=====================================================================================================
// カメラ内判定
//=====================================================================================================
void Player::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// 縦
	if ((pos.x > camera->at.x - DRAW_RANGE.x) && (pos.x < camera->at.x + DRAW_RANGE.x))
	{
		// 横
		if ((pos.y > camera->at.y - DRAW_RANGE.y) && (pos.y < camera->at.y + DRAW_RANGE.y))
		{
			onCamera = true;
		}
		else
		{
			onCamera = false;
		}
	}
	else
	{
		onCamera = false;
	}
}

//=====================================================================================================
// マップとの当たり判定
//=====================================================================================================
void Player::GroundCollider(Map *pMap)
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// 当たり判定を確認するマップチップの場所
	D3DXVECTOR3 mappos;
	mappos.x = MAP_POS.x + CHIP_SIZE * x;
	mappos.y = MAP_POS.y + CHIP_SIZE * y;
	mappos.z = 0.0f;

	// プレイヤーの足元のマップチップから右上のマップチップの番号
	int frontx = x + 1;
	int fronty = y + 1;

	// 前方のオブジェクトに引っかかるかチェック(ジャンプ中はチェックしない)
	if (!hitGround && !hitPaint)
	{
		if (pMap->GetMapTbl(frontx, fronty) >= 0)
		{
			hitHorizon = false;
		}
		else
		{
			hitHorizon = true;
		}
		
		return;
	}

	// マップ外判定
	if (!HitCheckBB(pos, GetMapCenterPos(), PLAYER_COLLISION_SIZE, D3DXVECTOR2(MAP_SIZE_X * CHIP_SIZE, MAP_SIZE_Y * CHIP_SIZE)))
	{
		hitHorizon = true;
		hitGround = false;
		return;
	}

	// 現在座標があるところになにかオブジェクトがあればヒットしている
	if (pMap->GetMapTbl(x, y) >= 0)
	{
		// めり込みを修正
		pos.y = mappos.y + (CHIP_SIZE / 2) - 0.01f;
		jumpSpeed = 0.0f;
		hitGround = true;
		return;
	}
	else
	{
		hitGround = false;
	}
}

//=====================================================================================================
// ペイントとの当たり判定
//=====================================================================================================
void Player::PaintCollider(PaintManager *pPManager)
{
	for (auto &Paint : pPManager->GetColorPaint())
	{
		if (!Paint->GetUse())
		{
			continue;
		}

		// ひとつひとつのペイントとプレイヤーの当たり判定を行う
		if (HitSphere(pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// 当たった場合、プレイヤーの座標を修正
			pos.y = Paint->GetPos().y + PAINT_WIDTH * 0.1f;
			jumpSpeed = 0.0f;
			hitPaint = true;
			return;
		}
		else
		{
			hitPaint = false;
		}
	}

}

//=====================================================================================================
// 前方のマップとの当たり判定
//=====================================================================================================
void Player::HorizonCollider(Map *pMap)
{
	
}


//=====================================================================================================
// 重力処理
//=====================================================================================================
void Player::Gravity()
{
	// 落下最大速度よりも遅い場合、落下速度が重力加速度に合わせて加速する
	if (jumpSpeed > -FALL_VELOCITY_MAX)
	{
		jumpSpeed -= STANDARD_GRAVITY;
	}
}

//=====================================================================================================
// デバッグ表示&操作
//=====================================================================================================
void Player::Debug()
{
#ifndef _DEBUG_
	//PrintDebugProc("PLAYER[%d] POS X:%f, Y:%f, Z:%f\n", ctrlNum, pos.x, pos.y, pos.z);
	//PrintDebugProc("PLAYER[%d] MOVE X:%f, Y:%f, Z:%f\n", ctrlNum, move.x, move.y, move.z);
	//PrintDebugProc("PLAYER[%d] INK TYPE %s\n", ctrlNum, inkType ? "Balck" : "Color");
	//PrintDebugProc("PLAYER[%d] INK VALUE COLOR %d\n", ctrlNum, inkValue[ColorInk]);
	//PrintDebugProc("PLAYER[%d] INK VALUE BLACK %d\n", ctrlNum, inkValue[BlackInk]);
	//PrintDebugProc("PLAYER[%d] JUMP FLAG:%d\n", ctrlNum, jumpFlag);
	//PrintDebugProc("PLAYER[%d] JUMP SPEED:%f\n", ctrlNum, jumpSpeed);
	//PrintDebugProc("PLAYER[%d] OnCamera:%s\n", ctrlNum, use ? "OnCamera" : "OffCamera");

	BeginDebugWindow("Player");

	DebugText("[%d] POS X:%f Y:%f Z:%d", ctrlNum, pos.x, pos.y, pos.z);
	DebugText("[%d] HitGround:%s HitPaint:%s", ctrlNum, hitGround ? "True" : "False", hitPaint ? "True" : "False");

	EndDebugWindow("Player");

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