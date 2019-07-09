//=============================================================================
//
// プレイヤークラス[Player.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "Gravity.h"
#include "SceneGame.h"
#include "D3DXAnimation.h"
#include "Camera.h"
#include "DebugWindow.h"
#include "Map.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CHARA_XFILE			"data/MODEL/Kouhai.x"						// 読み込むモデル名(ファイルパス名)
#define PLAYER_ROT			D3DXVECTOR3(0.0f, D3DXToRadian(-90), 0.0f)	// 初期の向き
#define PLAYER_SCL			D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define JUMP_SPEED			(12.0f)										// ジャンプの初速
#define MOVE_SPEED			(2.0f)										// 動くスピード
#define DefaultPosition		D3DXVECTOR3(45.0f, 0.0f, 0.0f)				// プレイヤー初期位置

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
Player::Player(int _CtrlNum)
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
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	moveFlag = true;
	playable = false;
	use = true;
	this->ActionSpeed = 1.0f;
	this->AI = new CharacterAI(true);
	this->PaintSystem = new PaintManager(_CtrlNum);
	this->PopUp = new Pop(ctrlNum);
}

//=====================================================================================================
// デストラクタ
//=====================================================================================================
Player::~Player()
{
	SAFE_DELETE(this->AI);
	SAFE_DELETE(this->PaintSystem);
	SAFE_DELETE(this->PopUp);
}

//=====================================================================================================
// 更新
//=====================================================================================================
void Player::Update()
{
	if (use)
	{
		// 移動
		Move();

		// AIの更新処理
		AI->Update(this->pos, this->PaintSystem);

		// ペイントシステムの更新処理
		PaintSystem->Update();

		// ポップアップの更新処理
		PopUp->Update(this->pos);

		// アニメーション管理
		AnimationManager();

		// カメラ内判定
		CheckOnCamera();

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
	}
#endif
}

//=====================================================================================================
// 描画
//=====================================================================================================
void Player::Draw()
{
	if (use)
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

		// ペイントの描画
		this->PaintSystem->Draw();

		this->PopUp->Draw();

#if _DEBUG
		this->AI->Draw();
#endif
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
			//jumpSpeed = 100.0f;
			this->ChangeAnim(Jump);
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
		//pos.x += MOVE_SPEED;
	}

#if _DEBUG
	if (GetKeyboardPress(DIK_RIGHT))
	{
		pos.x += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		pos.x -= MOVE_SPEED;
	}
#endif
}

//=====================================================================================================
// アニメーション管理
//=====================================================================================================
void Player::AnimationManager()
{
	// 待機状態
	if (!playable)
	{
		if (this->GetAnimCurtID() != Idle)
		{
			this->ChangeAnim(Idle);
		}
	}
	else
	{
		if (!jumpFlag)
		{
			// 歩行中
			if (moveFlag)
			{
				if (this->GetAnimCurtID() != Running)
				{
					this->ActionSpeed = 1.0f;
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
	this->UpdateAnim(TIME_PER_FRAME * ActionSpeed);
}

void Player::CreateAnimSet(void)
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

			Keydata.push_back(KEYDATA{ 0.8f,e_MotionEnd });
			//Keydata.push_back(KEYDATA{ (23 / 32),e_MotionEnd });
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
// アニメーションCallbackKeyの処理イベント
//=====================================================================================================
HRESULT CALLBACK Player::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	int EventNo = (int)pCallbackData;
	int i = 0;

	switch (EventNo)
	{
	case e_MotionEnd:
		this->ActionSpeed = 0.0f;
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
			use = true;
		}
		else
		{
			use = false;
		}
	}
	else
	{
		use = false;
	}
}