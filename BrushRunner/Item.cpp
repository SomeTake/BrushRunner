//=============================================================================
//
// アイテム処理[Item.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Item.h"
#include "MyLibrary.h"
#include "Input.h"
#include "BanananoKawaState.h"
#include "BlindState.h"
#include "GunState.h"
#include "JetState.h"
#include "PowerUpBananaState.h"
#include "SpikeState.h"
#include "SpInkState.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Item::Item(D3DXVECTOR3 _pos, Player *ptr)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_ITEM,						// ファイルの名前
			&D3DTexture);						// 読み込むメモリのポインタ
	}

	pPlayer = ptr;
	use = false;
	pos = _pos;
	PatternAnim = 0;
	rouletteCnt = 0;
	useCnt = 0;
	active = false;

	// 頂点情報の作成
	MakeVertex();

	// ステートパターンの初期化
	state[NumJet] = new JetState(this);
	state[NumSpike] = new SpikeState(this);
	state[NumPowerUp] = new PowerUpBananaState(this);
	state[NumKawa] = new BanananoKawaState(this);
	state[NumBlind] = new BlindState(this);
	state[NumSpInk] = new SpInkState(this);
	state[NumGun] = new GunState(this);
}

//=============================================================================
// デストラクタ
//=============================================================================
Item::~Item()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	// ステートパターンの削除
	for (int i = 0; i < NumItemMax; i++)
	{
		delete state[i];
	}
}

//=============================================================================
// 更新
//=============================================================================
void Item::Update()
{
	// アイテムを取得した瞬間の処理
	if (!use && pPlayer->GetHitItem() && !active)
	{
		Start();

		//テクスチャ座標をセット
		SetTexture();
	}

	// 取得している状態
	if (use)
	{
		// アイテムを使用する
		if (GetKeyboardTrigger(DIK_I) || IsButtonTriggered(pPlayer->GetCtrlNum(), BUTTON_D))
		{
			use = false;
			active = true;
			pPlayer->SetHitItem(false);
			state[PatternAnim]->Start();
		}

		//テクスチャ座標をセット
		SetTexture();
	}

	// アイテム使用中
	if (active)
	{
		ActiveState(PatternAnim);
	}
}

//=============================================================================
// 描画
//=============================================================================
void Item::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use || (!use && pPlayer->GetHitItem()) || active)
	{
		// テクスチャの設定(ポリゴンの描画前に読み込んだテクスチャのセットを行う)
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何もはらないことを指定するpDevide->SetTexture(0, NULL);
		pDevice->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Item::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertex();

	// rhwの設定
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void Item::SetTexture()
{
	int x = PatternAnim % DIVIDE_ITEM_X;
	int y = PatternAnim / DIVIDE_ITEM_X;
	float sizeX = 1.0f / DIVIDE_ITEM_X;
	float sizeY = 1.0f / DIVIDE_ITEM_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void Item::SetVertex()
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + ITEM_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + ITEM_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + ITEM_SIZE.x, pos.y + ITEM_SIZE.y, pos.z);
}

//=============================================================================
// 取得したときの処理
//=============================================================================
void Item::Start()
{
	// ルーレットを回す
	rouletteCnt = LoopCountUp(rouletteCnt, 0, ROULETTE_COUNTER);
	if (rouletteCnt == 0)
	{
		// テクスチャも回す
		PatternAnim = LoopCountUp(PatternAnim, 0, TEXTURE_DIVIDE_ITEM);
		if (PatternAnim == 0)
		{
			useCnt++;
			// 一定回数回したら使えるようにする
			if (useCnt == USE_COUNTER)
			{
				use = true;
				rouletteCnt = 0;
				useCnt = 0;
				active = true;

				// ランダムでアイテムの種類をセット
				PatternAnim = rand() % (TEXTURE_DIVIDE_ITEM + 1);
			}
		}
	}
}

//=============================================================================
// アイテムを使用したときの効果
//=============================================================================
void Item::ActiveState(int ItemID)
{
	state[ItemID]->Update();
}

//=============================================================================
// アイテムが変化したときに呼び出す
//=============================================================================
void Item::ChangeState(int ItemID)
{
	state[ItemID]->Start();
}