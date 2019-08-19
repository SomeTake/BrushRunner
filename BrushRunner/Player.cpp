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
#include "Timer.h"
#include "ResourceManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// 読み込むモデル名(ファイルパス名)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define MOVE_SPEED			(2.0f)										// 動くスピード
//#define DefaultPosition		D3DXVECTOR3(145.0f, 0.0f, 0.0f)				// プレイヤー初期位置
#define DefaultPosition		D3DXVECTOR3(50.0f, 0.0f, 0.0f)				// プレイヤー初期位置
// 特に調整が必要そうなの
#define OBJECT_HIT_COUNTER	(5)											// オブジェクトにヒットしたとき有効になるまでのフレーム数
#define MOVE_SPEED			(2.0f)										// 動くスピード
#define FALL_VELOCITY_MAX	(20.0f)										// 最大の落下速度
#define STANDARD_GRAVITY	(0.98f)										// 重力加速度
#define OBJECT_HIT_SIZE		D3DXVECTOR2(20.0f, 60.0f)					// 当たり判定を取得するサイズ
#define JETPACK_VALUE		(1.5f)										// ジェットパック装備時の上昇値
#define PowerBanana_VALUE	(2.0f)										// パワーバナナ使用時の上昇値

enum CallbackKeyType
{
	e_NoEvent = 0,
	e_MotionEnd,				// モーション終了
	e_MotionChange,				// モーションを変更する
};

//=====================================================================================================
// コンストラクタ
//=====================================================================================================
Player::Player(int _CtrlNum, bool AIUse) : state(nullptr)
{
	// xFileを読み込む
	ResourceManager::Instance()->GetMesh("Player", &model);

	// 現在のアニメーションをアイドル状態とする
	this->model->ChangeAnim(Idle);

	// 位置・回転・スケールの初期設定
	model->pos = DefaultPosition - D3DXVECTOR3(15.0f * _CtrlNum, 0.0f, 0.0f);
	model->rot = PLAYER_ROT;
	model->scl = ModelScl[KouhaiModel];
	hitGround = false;
	hitPaint = false;
	runSpd = 1.0f;
	jumpSpd = 0.0f;
	ctrlNum = _CtrlNum;
	if (AIUse)
	{
		this->AI = new CharacterAI(ctrlNum);
		this->AIUse = true;
		this->PaintSystem = new PaintManager(ctrlNum, true, this->AI);
	}
	else
	{
		this->AI = nullptr;
		this->AIUse = false;
		this->PaintSystem = new PaintManager(ctrlNum, false, nullptr);
	}
	this->playerUI = new PlayerUI(ctrlNum);
	hitHorizon = false;
	playable = false;
	onCamera = true;
	hitItem = false;
	//animSpd = 1.0f;
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
	model = nullptr;
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
		if (AIUse)
		{
			AI->Update(this->model->pos);
		}

		// ペイントシステムの更新処理
		PaintSystem->Update();

		// プレイヤーUIの更新処理
		playerUI->Update(this->model->pos);

		// アニメーションを更新
		model->Update();

		// 状態抽象インターフェースの更新
		UpdateState(this->model->GetAnimCurtID());

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
			// モデルの描画
			model->Draw();
		}

		// プレイヤーUIの描画
		//playerUI->Draw(onCamera, blind);

		// ペイントの描画
		PaintSystem->Draw();

		// プレイヤーUIの描画
		playerUI->Draw(onCamera, blind);

	}
	// プレイヤー死亡のUI
	else
	{
		// プレイヤーUIの描画()
		playerUI->Draw(onCamera, blind);
	}

	// フィールド上に生成したアイテムの描画
	itemManager->Draw();

#if _DEBUG
	if (this->AI != nullptr)
	{
		AI->Draw();
	}
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
		if (!hitHorizon && playable && model->pos.x < GOAL_POS.x && model->GetAnimCurtID() != Slip && model->GetAnimCurtID() != Stop)
		{
			if (!PowerBanana)
			{
				model->pos.x += MOVE_SPEED * runSpd;
			}
			else
			{
				model->pos.x += MOVE_SPEED * 2.0f;
			}
		}
	}

	// 空中判定
	JumpMove();
}

//=====================================================================================================
// ジャンプ移動
//=====================================================================================================
void Player::JumpMove()
{
	model->pos.y += jumpSpd;
	// 落下最大速度よりも遅い場合、落下速度が重力加速度に合わせて加速する
	if (jumpSpd > -FALL_VELOCITY_MAX)
	{
		jumpSpd -= STANDARD_GRAVITY;
	}

	//// ジェットパック装備中はジャンプ力アップ
	//if (jet)
	//{
	//	jumpValue = JETPACK_VALUE;
	//}
	//else if (PowerBanana)
	//{
	//	jumpValue = PowerBanana_VALUE;
	//}
	//else
	//{
	//	jumpValue = 1.0f;
	//}
}

////=====================================================================================================
//// アニメーションのセット
////=====================================================================================================
//void Player::CreateAnimSet()
//{
//	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
//	vector<KEYDATA>Keydata;
//	Keydata.reserve(Keydata_Max);
//
//	for (int Set_No = 0; Set_No < GetAnimSetNum(); Set_No++)
//	{
//		switch (Set_No)
//		{
//		case Idle:
//
//			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
//			AnimationSet->SetData("Idle", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Running:
//
//			//Keydata.push_back(KEYDATA{ 0.95f,e_MotionEnd });
//			AnimationSet->SetData("Running", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Jump:
//
//			Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
//			AnimationSet->SetData("Jump", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Victory:
//
//			AnimationSet->SetData("Victory", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Slip:
//
//			Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
//			AnimationSet->SetData("Slip", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		case Stop:
//
//			AnimationSet->SetData("Stop", NULL, 1.5f, 0.1f, 0.0f);
//			break;
//
//		default:
//			break;
//		}
//
//		this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());
//
//		AnimationSet->SetAnimSetPtr(this->AnimController);
//
//		this->AnimSet.push_back(*AnimationSet);
//
//		Keydata.clear();
//	}
//
//	SAFE_DELETE(AnimationSet);
//	ReleaseVector(Keydata);
//}
//
////=====================================================================================================
//// アニメーションCallbackKeyの処理イベント
////=====================================================================================================
//HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	int eventNo = (int)pCallbackData;
//
//	switch (eventNo)
//	{
//	case e_MotionEnd:
//		animSpd = 0.0f;
//		break;
//	case e_MotionChange:
//		playable = true;
//		ChangeAnim(Idle);
//		ChangeState(new IdleState(this));
//		break;
//	default:
//		break;
//	}
//
//	return S_OK;
//}

//=====================================================================================================
// カメラ内判定
//=====================================================================================================
void Player::CheckOnCamera()
{
	CAMERA *camera = GetCamera();

	// 縦
	if (model->pos.x > camera->at.x - DRAW_RANGE.x)
	{
		onCamera = true;
	}
	else
	{
		onCamera = false;
		playerUI->SetPlayerDeadTexture();

		// エフェクト発生
		D3DXVECTOR3 setpos = model->pos;
		setpos.z -= 1.0f;
		setpos.x += 150.0f;
		std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
		Effect3D *effect = new Effect3D(DeadEffect3D, setpos, 1);
		Effect3DVector->push_back(effect);

		// PlaySound(爆発音)
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
		Map::GetMapChipXY(model->pos, &x, &y);

		D3DXVECTOR3 mappos = Map::GetMapChipPos(x, y, eCenterUp);

		// 現在座標があるところになにかオブジェクトがあればヒットしている
		if (Map::GetMapTbl(x, y) >= 0)
		{
			// めり込みを修正
			model->pos.y = max(mappos.y - 0.01f, model->pos.y);
			jumpSpd = 0.0f;
			model->SetAnimSpd(1.0f);
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
	// 上昇中は判定しない
	if (jumpSpd <= 0)
	{
		for (auto &Paint : PaintSystem->GetColorPaint())
		{
			if (!Paint->GetUse())
				continue;

			// ひとつひとつのペイントとプレイヤーの当たり判定を行う
			if (HitSphere(model->pos, Paint->GetPos(), PLAYER_COLLISION_SIZE.x * 0.5f, PAINT_WIDTH * 0.5f))
			{
				// 当たった場合、プレイヤーの座標を修正
				model->pos.y = max(Paint->GetPos().y + PAINT_WIDTH * 0.1f, model->pos.y);
				jumpSpd = 0.0f;
				model->SetAnimSpd(1.0f);
				hitPaint = true;
				return;
			}
			else
			{
				hitPaint = false;
			}
		}
	}
	else
	{
		hitPaint = false;
	}
}

//=====================================================================================================
// 前方のマップとの当たり判定
//=====================================================================================================
void Player::HorizonCollider()
{
	// キャラクターの座標からマップ配列の場所を調べる
	int x, y;
	Map::GetMapChipXY(model->pos, &x, &y);

	// 足元から見て右上なので
	x++;
	y--;

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
	Map::GetMapChipXY(model->pos, &x, &y);

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
	{
		return;
	}

	D3DXVECTOR3 colliderpos = model->pos;
	colliderpos.y += OBJECT_HIT_SIZE.y * 0.5f;

	for (auto &Obj : pMap->GetObjectChip())
	{
		if (Obj->GetTextureNum() != eObjItem)
		{
			continue;
		}

		if (HitCheckBB(colliderpos, Obj->GetPos(), OBJECT_HIT_SIZE, D3DXVECTOR2(CHIP_SIZE, CHIP_SIZE)))
		{
			hitItem = true;
			// PlaySound(アイテム取得音)
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
		if (HitCheckBB(model->pos, item->GetPos(), PLAYER_COLLISION_SIZE, FIELDITEM_SIZE))
		{
			switch (item->GetTexNo())
			{
				// バナナの皮
			case NumKawa:
				playable = false;
				model->ChangeAnim(Slip);
				ChangeState(new SlipState(this));
				break;
				// トリモチガン
			case NumGun:
				playable = false;
				model->ChangeAnim(Stop);
				ChangeState(new StopState(this));
				break;
			default:
				break;
			}
			item->SetUse(false);

			// エフェクトを発生
			std::vector<Effect3D*> *Effect3DVector = GetEffect3DVector();
			Effect3D *effect = new Effect3D(ExplosionEffect3D, model->pos, 1);
			Effect3DVector->push_back(effect);

			// PlaySound(アイテムヒット音)
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
		model->ChangeAnim(Jump);
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

				// PlaySound(インクが減る音)
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

				// PlaySound(インクが回復する音)
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
#if _DEBUG

	if (!AIUse)
	{
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
	}

	ImGui::SetNextWindowPos(ImVec2(5, 120), ImGuiSetCond_Once);

	BeginDebugWindow("Player");

	ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
	if (ImGui::TreeNode((void*)(intptr_t)ctrlNum, "Player %d", ctrlNum))
	{
		if (ImGui::TreeNode("Position"))
		{
			DebugText("Pos X:%.2f\nPos Y:%.2f\nPos Z:%.2f\n", model->pos.x, model->pos.y, model->pos.z);
			ImGui::TreePop();
		}

		DebugText("AnimSetName:%s\nCurrentFrame:%d / %d", this->model->GetCurtAnimName(), this->model->GetAnimCurtFrame(), this->model->GetAnimPeriodFrame());

		int x = 0, y = 0;
		Map::GetMapChipXY(model->pos, &x, &y);
		DebugText("X : %d  Y : %d", x, y);
		DebugText("MapTable : %d\nMapTable_Up : %d", Map::GetMapTbl(model->pos, eCenter), Map::GetMapTbl(model->pos, eCenterUp));

		ImGui::TreePop();
	}

	EndDebugWindow("Player");

#endif

}