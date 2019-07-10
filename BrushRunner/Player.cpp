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
#include "PaintManager.h"
#include "IdleState.h"
#include "MyLibrary.h"
#include "JumpState.h"
#include "StopState.h"
#include "SlipState.h"
#include "Item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 特に調整が必要そうなの
#define OBJECT_HIT_COUNTER	(10)				// オブジェクトにヒットしたとき有効になるまでのフレーム数
#define MOVE_SPEED			(2.0f)				// 動くスピード

// 読み込むキャラクターモデル
static const char* CharaModel[] =
{
	"data/MODEL/Shachiku/Shachiku.x",
	"data/MODEL/Kouhai/Kouhai.x",
};

// キャラクターモデルの番号
enum CharaModelNum
{
	ShachikuModel,
	KouhaiModel,

	// モデルの種類
	MaxModel
};

// モデルの大きさ設定
static D3DXVECTOR3 ModelScl[MaxModel] =
{
	D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	D3DXVECTOR3(0.4f, 0.4f, 0.4f)
};

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// モーション終了
	e_MotionChange,				// モーションを変更する
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
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	animSpd = 1.0f;
	hitObjCnt = 0;
	jumpValue = 1.0f;

	spike = false;
	gun = false;
	blind = false;
	spink = false;

	for (int i = 0; i < InkNum; i++)
	{
		inkValue[i] = INK_MAX;
	}

	// 待機状態からスタートする
	state = new IdleState(this);

	// フィールド上のアイテム管理クラス初期化
	itemManager = new FieldItemManager();
}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
Player::~Player()
{
	delete state;
	delete itemManager;
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

		// アニメーションを更新
		this->UpdateAnim(TIME_PER_FRAME * animSpd);

		// 状態抽象インターフェースの更新
		UpdateState(this->GetAnimCurtID());

		// カメラ内判定
		CheckOnCamera();

		// フィールド上に生成したアイテムの更新
		itemManager->Update();
		
		// フィールド上に生成したアイテムのチェック
		itemManager->Check();
	}

	// デバッグ表示＆操作
	Debug();
}

//=====================================================================================================
// 描画
//=====================================================================================================
void Player::Draw()
{
	if (onCamera && !blind)
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

	// フィールド上に生成したアイテムの描画
	itemManager->Draw();
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
void Player::ChangeState(PlayerState *NewState)
{
	delete state;
	state = NewState;
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
	// オート移動
	if (!hitHorizon && playable && pos.x < GOAL_POS.x && GetAnimCurtID() != Slip)
	{
		pos.x += MOVE_SPEED * runSpd;
	}

	// 空中判定
	JumpMove();

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
// ジャンプ移動
//=====================================================================================================
void Player::JumpMove()
{
	pos.y += jumpSpd * jumpValue;
	// 落下最大速度よりも遅い場合、落下速度が重力加速度に合わせて加速する
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
	}
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

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Running:

			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Jump:

			Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Victory:

			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Slip:

			Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
			AnimationSet->SetData("Slip", NULL, 1.5f, 0.1f, 0.0f);
			break;

		case Stop:

			AnimationSet->SetData("Stop", NULL, 1.5f, 0.1f, 0.0f);
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
	int eventNo = (int)pCallbackData;

	switch (eventNo)
	{
	case e_MotionEnd:
		animSpd = 0.0f;
		break;
	case e_MotionChange:
		playable = true;
		ChangeAnim(Idle);
		ChangeState(new IdleState(this));
		break;
	default:
		break;
	}

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
	// 上昇中は判定しない
	if (jumpSpd <= 0)
	{
		// キャラクターの座標からマップ配列の場所を調べる
		int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
		int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

		// 当たり判定を確認するマップチップの場所
		D3DXVECTOR3 mappos;
		mappos.x = MAP_POS.x + CHIP_SIZE * x;
		mappos.y = MAP_POS.y + CHIP_SIZE * y;
		mappos.z = 0.0f;

		// マップ外判定
		if (x < 0 || y > 0)
		{
			hitGround = false;
			return;
		}

		// 現在座標があるところになにかオブジェクトがあればヒットしている
		if (pMap->GetMapTbl(x, y) >= 0)
		{
			// めり込みを修正
			pos.y = max(mappos.y + (CHIP_SIZE / 2) - 0.01f, pos.y);
			jumpSpd = 0.0f;
			animSpd = 1.0f;
			hitGround = true;
			return;
		}
		else
		{
			hitGround = false;
		}
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
			continue;

		// ひとつひとつのペイントとプレイヤーの当たり判定を行う
		if (HitSphere(pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
		{
			// 当たった場合、プレイヤーの座標を修正
			pos.y = max(Paint->GetPos().y + PAINT_WIDTH * 0.1f, pos.y);
			jumpSpd = 0.0f;
			animSpd = 1.0f;
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
	// プレイヤーの座標から当たり判定を取得するマップチップの番号を取得
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// 足元から見て右上なので
	x++;
	y++;

	// マップ外
	if (x < 0 || y > 0)
	{
		hitHorizon = false;
		return;
	}

	// テーブルを調べて0以上ならヒット
	if (pMap->GetMapTbl(x,y) >= 0)
	{
		hitHorizon = true;
		return;
	}
	else
	{
		hitHorizon = false;
		return;
	}
}

//=====================================================================================================
// フィールドオブジェクトとの当たり判定
//=====================================================================================================
void Player::ObjectCollider(Map *pMap)
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x = (int)((pos.x + CHIP_SIZE / 2) / CHIP_SIZE);
	int y = (int)((pos.y - CHIP_SIZE / 2) / CHIP_SIZE);

	// マップ外判定
	if (x < 0 || y > 0)
	{
		runSpd = 1.0f;
		hitObjCnt = 0;
		return;
	}

	int objType = pMap->GetObjTbl(x, -y);

	HitObjectInfluence(objType);

}

//=====================================================================================================
// フィールド上に発生したアイテムとの当たり判定
//=====================================================================================================
void Player::FieldItemCollider(FieldItemManager *pFIManager)
{
	for (auto &item : pFIManager->GetItem())
	{
		if (HitCheckBB(pos, item->GetPos(), PLAYER_COLLISION_SIZE, FIELDITEM_SIZE))
		{
			switch (item->GetTexNo())
			{
				// バナナの皮
			case NumKawa:
				playable = false;
				ChangeAnim(Slip);
				ChangeState(new SlipState(this));
				break;
				// トリモチガン
			case NumGun:
				playable = false;
				ChangeAnim(Stop);
				ChangeState(new StopState(this));
				break;
			default:
				break;
			}
			item->SetUse(false);
		}
	}
}

//=====================================================================================================
// オブジェクトにヒットしているときの効果
//=====================================================================================================
void Player::HitObjectInfluence(int type)
{
	// 何も存在しないとき
	if (type == -1)
	{
		runSpd = 1.0f;
		jumpValue = 1.0f;
		hitObjCnt = 0;
		return;
	}

	// オブジェクトの種類に合わせて効果変更
	switch (type)
	{
	case OBJ_NUM_SPDUP:
		if (!spike)
		{
			runSpd = 2.0f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_SPDDOWN:
		if (!spike)
		{
			runSpd = 0.5f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_NUMA:
		if (!spike)
		{
			runSpd = 0.5f;
			jumpValue = 0.5f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		break;

	case OBJ_NUM_JUMP:
		jumpSpd = JUMP_SPEED;
		ChangeAnim(Jump);
		ChangeState(new JumpState(this));

	case OBJ_NUM_DRAIN:
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				inkValue[BlackInk] = max(--inkValue[BlackInk], 0);
				inkValue[ColorInk] = max(--inkValue[ColorInk], 0);
			}
		}

		// 他のステータスはリセット
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_HEAL:
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				inkValue[BlackInk] = min(++inkValue[BlackInk], INK_MAX);
				inkValue[ColorInk] = min(++inkValue[ColorInk], INK_MAX);
			}
		}

		// 他のステータスはリセット
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case OBJ_NUM_ITEM:
		hitItem = true;

		// 他のステータスはリセット
		hitObjCnt = 0;
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;
	default:
		break;
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

	DebugText("[%d] POS X:%f Y:%f Z:%d\n", ctrlNum, pos.x, pos.y, pos.z);
	DebugText("[%d] HitGround:%s HitPaint:%s HitHorizon:%s\n", ctrlNum, hitGround ? "True" : "False", hitPaint ? "True" : "False", hitHorizon ? "True" : "False");
	DebugText("[%d] AnimID:%d",ctrlNum, this->GetAnimCurtID());
	DebugText("[%d] HitObjCnt:%d", ctrlNum, hitObjCnt);

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