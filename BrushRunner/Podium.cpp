//=============================================================================
//
// 表彰台[Podium.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Podium.h"
#include "ResourceManager.h"
#include "Model3D.h"

#define PODIUM_ROT		D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
Podium::Podium()
{
	ResourceManager::Instance()->GetMesh("Podium", &model);

	model->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->rot = PODIUM_ROT;
	model->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

//=============================================================================
// デストラクタ
//=============================================================================
Podium::~Podium()
{
	model = NULL;
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
	model->Draw();
}

////=============================================================================
//// アニメーションセットの作成
////=============================================================================
//void Podium::CreateAnimSet()
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
//}
//
////=====================================================================================================
//// アニメーションCallbackKeyの処理イベント
////=====================================================================================================
//HRESULT CALLBACK Podium::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	return S_OK;
//}
