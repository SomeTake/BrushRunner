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
#include "D3DXAnimation.h"
#include "Camera.h"

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
Player::Player(int _CtrlNum, D3DXVECTOR3 firstpos)
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
	jumpFlag = false;
	jumpSpeed = 0;
	ctrlNum = _CtrlNum;
	inkType = ColorInk;
	moveFlag = true;
	playable = false;
	use = true;

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

		// インク変更
		ChangeInk();

		// アニメーション管理
		AnimationManager();

		// カメラ内判定
		CheckOnCamera();

#ifndef _DEBUG_
		PrintDebugProc("PLAYER[%d] POS X:%f, Y:%f, Z:%f\n", ctrlNum, pos.x, pos.y, pos.z);
		//PrintDebugProc("PLAYER[%d] MOVE X:%f, Y:%f, Z:%f\n", ctrlNum, move.x, move.y, move.z);
		//PrintDebugProc("PLAYER[%d] INK TYPE %s\n", ctrlNum, inkType ? "Balck" : "Color");
		//PrintDebugProc("PLAYER[%d] INK VALUE COLOR %d\n", ctrlNum, inkValue[ColorInk]);
		//PrintDebugProc("PLAYER[%d] INK VALUE BLACK %d\n", ctrlNum, inkValue[BlackInk]);
		//PrintDebugProc("PLAYER[%d] JUMP FLAG:%d\n", ctrlNum, jumpFlag);
		//PrintDebugProc("PLAYER[%d] JUMP SPEED:%f\n", ctrlNum, jumpSpeed);
		PrintDebugProc("PLAYER[%d] OnCamera:%s\n", ctrlNum, use ? "OnCamera" : "OffCamera");
#endif

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
	}
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
	// ジャンプ
	if (playable)
	{
		if ((GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(ctrlNum, BUTTON_B)) && (!jumpFlag))
		{
			jumpFlag = true;
			moveFlag = true;
			jumpSpeed = JUMP_SPEED;
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

	PrintDebugProc("Player Animation：%s\n", this->GetCurtAnimName());
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