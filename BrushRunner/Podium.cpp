//=============================================================================
//
// 表彰台[Podium.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Podium.h"

#define PODIUM_MODEL	("data/MODEL/Podium/Podium.x")

//=============================================================================
// コンストラクタ
//=============================================================================
Podium::Podium()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->Load_xFile(PODIUM_MODEL, "Podium");

	// アニメーションセットの初期化
	this->CreateAnimSet();
	//this->ChangeAnim(0);

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

//=============================================================================
// デストラクタ
//=============================================================================
Podium::~Podium()
{
}

//=============================================================================
// 更新
//=============================================================================
void Podium::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void Podium::Draw()
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

//=============================================================================
// アニメーションセットの作成
//=============================================================================
void Podium::CreateAnimSet()
{
	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
	vector<KEYDATA>Keydata;
	Keydata.reserve(Keydata_Max);
	AnimationSet->SetData("Idle", NULL, 1.0f, 0.1f, 0.0f);
}

//=====================================================================================================
// アニメーションCallbackKeyの処理イベント
//=====================================================================================================
HRESULT CALLBACK Podium::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
{
	return S_OK;
}
