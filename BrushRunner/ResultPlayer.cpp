#include "Main.h"
#include "ResultPlayer.h"
#include "Player.h"
#include "ResourceManager.h"

D3DXVECTOR3 ResultPos[PLAYER_MAX] = {
	D3DXVECTOR3(0.0f, 60.0f, 0.0f),
	D3DXVECTOR3(-100.0f, 40.0f, 0.0f),
	D3DXVECTOR3(80.0f, 30.0f, 0.0f),
	D3DXVECTOR3(160.0f, 0.0f, 0.0f)
};

ResultPlayer::ResultPlayer(int rank, int owner, const char* tag) : Model3D(tag)
{
	ResourceManager::Instance()->GetMesh(tag, &model);

	// 現在のアニメーションを順位によって決定する
	if (rank == 0)
	{
		this->ChangeAnim(Victory);
	}
	else
	{
		this->ChangeAnim(Idle);
	}

	pos = ResultPos[rank];
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = ModelScl[KouhaiModel];
}


ResultPlayer::~ResultPlayer()
{
	model = NULL;
}

void ResultPlayer::Update()
{
	UpdateAnim(TIME_PER_FRAME);
}

//void ResultPlayer::Draw()
//{
//	Draw();
//}