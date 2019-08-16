//=============================================================================
//
// トロフィー[Trophy.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Trophy.h"
#include "Model3D.h"
#include "ResourceManager.h"

#define TROPHY_POS		D3DXVECTOR3(0.0f, 150.0f, 0.0f)
#define TROPHY_ROT		D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30))
#define TROPHY_MOVE		D3DXVECTOR3(0.0f, D3DXToRadian(1), 0.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
Trophy::Trophy()
{
	ResourceManager::Instance()->GetMesh("Trophy", &model);

	model->pos = TROPHY_POS;
	model->rot = D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30));
	model->scl = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
}

//=============================================================================
// デストラクタ
//=============================================================================
Trophy::~Trophy()
{
	model = NULL;
}

//=============================================================================
// 更新
//=============================================================================
void Trophy::Update()
{
	// 回転させる
	model->rot += TROPHY_MOVE;
	if (model->rot.y >= D3DX_PI)
	{
		model->rot.y = -D3DX_PI;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Trophy::Draw()
{
	model->Draw();
}

////=============================================================================
//// アニメーションセットの作成
////=============================================================================
//void Trophy::CreateAnimSet()
//{
//	ANIMATIONSET *AnimationSet = new ANIMATIONSET();
//	vector<KEYDATA>Keydata;
//	Keydata.reserve(Keydata_Max);
//	AnimationSet->SetData("Idle", NULL, 1.0f, 0.1f, 0.0f);
//	this->SetupCallbackKeys(&Keydata, AnimationSet->GetSetName());
//	AnimationSet->SetAnimSetPtr(this->AnimController);
//	this->AnimSet.push_back(*AnimationSet);
//	Keydata.clear();
//	SAFE_DELETE(AnimationSet);
//	ReleaseVector(Keydata);
//
//}
//
////=====================================================================================================
//// アニメーションCallbackKeyの処理イベント
////=====================================================================================================
//HRESULT CALLBACK Trophy::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	return S_OK;
//}
