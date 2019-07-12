//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"
#include "DebugWindow.h"
#include "Map.h"
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
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// 読み込むモデル名(ファイルパス名)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define MOVE_SPEED			(2.0f)										// 動くスピード
#define DefaultPosition		D3DXVECTOR3(145.0f, 0.0f, 0.0f)				// プレイヤー初期位置
// 特に調整が必要そうなの
#define OBJECT_HIT_COUNTER	(10)										// オブジェクトにヒットしたとき有効になるまでのフレーム数
#define MOVE_SPEED			(2.0f)										// 動くスピード
#define FALL_VELOCITY_MAX	(20.0f)										// 最大の落下速度
#define STANDARD_GRAVITY	(0.98f)										// 重力加速度
#define OBJECT_HIT_SIZE		D3DXVECTOR2(20.0f, 60.0f)					// 当たり判定を取得するサイズ
#define JETPACK_VALUE		(1.5f)										// ジェットパック装備時の上昇値

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
Player::Player(int _CtrlNum) : state(nullptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// xFileを読み込む
	this->Load_xFile(CharaModel[KouhaiModel], "Player");

	// アニメーションセットを設置する
	this->CreateAnimSet();

	// 現在のアニメーションをアイドル状態とする
	this->ChangeAnim(Idle);

	// 位置・回転・スケールの初期設定
	pos = DefaultPosition - D3DXVECTOR3(15.0f * _CtrlNum, 0.0f, 0.0f);
	rot = PLAYER_ROT;
	scl = ModelScl[KouhaiModel];
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	this->AI = new CharacterAI(true);
	this->PaintSystem = new PaintManager(ctrlNum, true);
	this->playerUI = new PlayerUI(ctrlNum);
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	animSpd = 1.0f;
	hitObjCnt = 0;
	jumpValue = 1.0f;

	spike = false;
	//gun = false;
	blind = false;

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
	SAFE_DELETE(this->AI);
	SAFE_DELETE(this->PaintSystem);
	SAFE_DELETE(this->state);
	SAFE_DELETE(this->itemManager);
	SAFE_DELETE(this->playerUI);
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

		// AIの更新処理
		AI->Update(this->pos, this->PaintSystem);

		// ペイントシステムの更新処理
		PaintSystem->Update();

		// プレイヤーUIの更新処理
		playerUI->Update(this->pos);

		// アニメーションを更新
		UpdateAnim(TIME_PER_FRAME * animSpd);

		// 状態抽象インターフェースの更新
		UpdateState(this->GetAnimCurtID());

		// カメラ内判定
		CheckOnCamera();

		// フィールド上に生成したアイテムの更新
		itemManager->Update();
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
		if (!blind)
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

		// プレイヤーUIの描画
		playerUI->Draw(onCamera);

		// ペイントの描画
		PaintSystem->Draw();
	}
	else
	{
		// プレイヤーUIの描画(プレイヤー死亡のUI)
		playerUI->Draw(onCamera);
	}

	// フィールド上に生成したアイテムの描画
	itemManager->Draw();

#if _DEBUG
	this->AI->Draw();
#endif
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
// 移動
//=====================================================================================================
void Player::Move()
{
	if (onCamera)
	{
		// オート移動
		if (!hitHorizon && playable && pos.x < GOAL_POS.x && GetAnimCurtID() != Slip && GetAnimCurtID() != Stop)
		{
			pos.x += MOVE_SPEED * runSpd;
		}
	}
		// 空中判定
		JumpMove();

#if _DEBUG
	if (GetKeyboardPress(DIK_RIGHT))
	{
		switch (ctrlNum)
		{
		case 0:
			pos.x += MOVE_SPEED;
			break;
		case 1:
			pos.x += MOVE_SPEED * 0.8f;
			break;
		case 2:
			pos.x += MOVE_SPEED * 0.5f;
			break;
		case 3:
			pos.x += MOVE_SPEED * 0.2f;
			break;
		default:
			break;
		}
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		switch (ctrlNum)
		{
		case 0:
			pos.x -= MOVE_SPEED;
			break;
		case 1:
			pos.x -= MOVE_SPEED * 0.8f;
			break;
		case 2:
			pos.x -= MOVE_SPEED * 0.5f;
			break;
		case 3:
			pos.x -= MOVE_SPEED * 0.2f;
			break;
		default:
			break;
		}
	}
#endif
}

//=====================================================================================================
// ジャンプ移動
//=====================================================================================================
void Player::JumpMove()
{
	pos.y += jumpSpd;
	// 落下最大速度よりも遅い場合、落下速度が重力加速度に合わせて加速する
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
	}

	// ジェットパック装備中はジャンプ力アップ
	if (jet)
	{
		jumpValue = JETPACK_VALUE;
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
// アニメーションCallbackKeyの処理イベント
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
	if (pos.x > camera->at.x - DRAW_RANGE.x)
	{
		onCamera = true;
	}
	else
	{
		onCamera = false;
		playerUI->SetPlayerDeadTexture();

		// エフェクト発生
		D3DXVECTOR3 setpos = pos;
		setpos.z -= 1.0f;
		std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
		Effect3D *effect = new Effect3D(ExplosionEffect3D, setpos, 3);
		Effect3DVector->push_back(effect);
	}
}

//=====================================================================================================
// マップとの当たり判定
//=====================================================================================================
void Player::GroundCollider()
{
	// 上昇中は判定しない
	if (jumpSpd <= 0)
	{
		// キャラクターの座標からマップ配列の場所を調べる
		int x, y;
		Map::GetMapChipXY(pos, &x, &y);

		D3DXVECTOR3 mappos = Map::GetMapChipPos(x, y, eCenterUp);

		//// マップ外判定
		//if (x < 0 || y > 0)
		//{
		//	hitGround = false;
		//	return;
		//}

		// 現在座標があるところになにかオブジェクトがあればヒットしている
		if (Map::GetMapTbl(x, y) >= 0)
		{
			// めり込みを修正
			pos.y = max(mappos.y - 0.01f, pos.y);
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
void Player::PaintCollider()
{
	for (auto &Paint : PaintSystem->GetColorPaint())
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
void Player::HorizonCollider()
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x, y;
	Map::GetMapChipXY(pos, &x, &y);

	// 足元から見て右上なので
	x++;
	y--;

	// マップ外
	//if (x < 0 || y > 0)
	//{
	//	hitHorizon = false;
	//	return;
	//}

	// テーブルを調べて0以上ならヒット
	if (Map::GetMapTbl(x, y) >= 0)
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
// フィールドオブジェクト（足元）との当たり判定
//=====================================================================================================
void Player::ObjectCollider()
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x, y;
	Map::GetMapChipXY(pos, &x, &y);

	int objType = Map::GetObjTbl(x, y);

	HitObjectInfluence(objType);

}

//=====================================================================================================
// フィールドオブジェクト（アイテム）との当たり判定
//=====================================================================================================
void Player::ObjectItemCollider(Map *pMap)
{
	// アイテムを取得している状態なら判定しない
	if (hitItem)
		return;

	D3DXVECTOR3 colliderpos = pos;
	colliderpos.y += OBJECT_HIT_SIZE.y * 0.5f;

	for (auto &Obj : pMap->GetObjectChip())
	{
		if (Obj->GetTextureNum() != eObjItem)
			continue;

		if (HitCheckBB(colliderpos, Obj->GetPos(), OBJECT_HIT_SIZE, D3DXVECTOR2(CHIP_SIZE, CHIP_SIZE)))
		{
			hitItem = true;
			return;
		}
	}

	hitItem = false;
	return;
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
	case eObjSpdup:
		if (!spike)
		{
			runSpd = 2.0f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case eObjSpddown:
		if (!spike)
		{
			runSpd = 0.5f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		jumpValue = 1.0f;
		break;

	case eObjNuma:
		if (!spike)
		{
			runSpd = 0.5f;
			jumpValue = 0.5f;
		}

		// 他のステータスはリセット
		hitObjCnt = 0;
		break;

	case eObjJump:
		jumpSpd = JUMP_SPEED * jumpValue;
		ChangeAnim(Jump);
		ChangeState(new JumpState(this));

	case eObjDrain:
		// 時間経過でインク減少
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				int ink = PaintSystem->GetInkValue(BlackInk);
				PaintSystem->SetInkValue(max(--ink, 0), BlackInk);
				ink = PaintSystem->GetInkValue(ColorInk);
				PaintSystem->SetInkValue(max(--ink, 0), ColorInk);
			}
		}

		// 他のステータスはリセット
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case eObjHeal:
		// 時間経過でインク増加
		if (!spike)
		{
			hitObjCnt = LoopCountUp(hitObjCnt, 0, OBJECT_HIT_COUNTER);
			if (hitObjCnt == 0)
			{
				int ink = PaintSystem->GetInkValue(BlackInk);
				PaintSystem->SetInkValue(min(++ink, INK_MAX), BlackInk);
				ink = PaintSystem->GetInkValue(ColorInk);
				PaintSystem->SetInkValue(min(++ink, INK_MAX), ColorInk);
			}
		}

		// 他のステータスはリセット
		runSpd = 1.0f;
		jumpValue = 1.0f;
		break;

	case eObjItem:
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

	ImGui::SetNextWindowPos(ImVec2(5, 120), ImGuiSetCond_Once);

	BeginDebugWindow("Player");

	ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
	if (ImGui::TreeNode((void*)(intptr_t)ctrlNum, "Player %d", ctrlNum))
	{
		if (ImGui::TreeNode("Position"))
		{
			DebugText("Pos X:%.2f\nPos Y:%.2f\nPos Z:%.2f\n", pos.x, pos.y, pos.z);
			ImGui::TreePop();
		}

		DebugText("AnimSetName:%s\nCurrentFrame:%d / %d", this->GetCurtAnimName(), this->GetAnimCurtFrame(), this->GetAnimPeriodFrame());

		int x = 0, y = 0;
		Map::GetMapChipXY(pos, &x, &y);
		DebugText("X : %d  Y : %d", x, y);
		DebugText("MapTable : %d\nMapTable_Up : %d", Map::GetMapTbl(pos, eCenter), Map::GetMapTbl(pos, eCenterUp));

		ImGui::TreePop();
	}

	EndDebugWindow("Player");

#endif

}