#include "Main.h"
#include "ResultPlayer.h"
#include "Player.h"
#include "ResourceManager.h"

D3DXVECTOR3 ResultPos[PLAYER_MAX] = {
	D3DXVECTOR3(0.0f, 60.0f, 0.0f),
	//D3DXVECTOR3(-100.0f, 40.0f, 0.0f),
	//D3DXVECTOR3(80.0f, 30.0f, 0.0f),
	//D3DXVECTOR3(160.0f, 0.0f, 0.0f)
};

ResultPlayer::ResultPlayer(int rank, int owner)
{
	ResourceManager::Instance()->GetMesh("Player", &model);

	// 現在のアニメーションを順位によって決定する
	if (rank == 0)
	{
		this->model->ChangeAnim(Victory);
	}
	else
	{
		this->model->ChangeAnim(Idle);
	}

	model->pos = ResultPos[rank];
	model->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->scl = ModelScl[KouhaiModel];
}


ResultPlayer::~ResultPlayer()
{
	model = NULL;
}

void ResultPlayer::Update()
{
	model->UpdateAnim(TIME_PER_FRAME);
}

void ResultPlayer::Draw()
{
	model->Draw();
}

//HRESULT CALLBACK ResultPlayer::HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)
//{
//	return S_OK;
//}
//
//void ResultPlayer::CreateAnimSet()
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
//			//Keydata.push_back(KEYDATA{ 0.80f, e_MotionEnd });
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
//			//Keydata.push_back(KEYDATA{ 0.95f, e_MotionChange });
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
//
//}