//=============================================================================
//
// リザルト画面での桁 [ResultDigit.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ResultDigit.h"
#include "ResultRank.h"
#include "Player.h"
#include "ResourceManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DIGIT_SPACE	(1.0f)

//*****************************************************************************
// データ定義
//*****************************************************************************
// 表示位置とサイズ（一番右の桁が基準）
ResultStr ResultData[PLAYER_MAX] = {
	D3DXVECTOR3(950.0f, 135.0f, 0.0f), D3DXVECTOR3(75.0f, 150.0f, 0.0f),
	D3DXVECTOR3(800.0f, 445.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
	D3DXVECTOR3(800.0f, 540.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
	D3DXVECTOR3(800.0f, 635.0f, 0.0f), D3DXVECTOR3(45.0f, 90.0f, 0.0f),
};

//=============================================================================
// コンストラクタ
//=============================================================================
ResultDigit::ResultDigit(DWORD _time, int _digit, int _rank) : Digit(_digit)
{
	ResourceManager::Instance()->GetTexture("Digit", &D3DTexture);

	time = _time;
	use = true;
	rank = _rank;
	pos = ResultData[rank].pos;
	pos.x -= _digit * ResultData[rank].size.x;
	// ミリ秒と秒、秒と分の間に':'のスペースがある
	if (_digit >= 2)
	{
		pos.x -= 20.0f;
	}
	if (_digit >= 4)
	{
		pos.x -= 20.0f;
	}
	size = ResultData[rank].size;

	MakeVertex();
}


//=============================================================================
// デストラクタ
//=============================================================================
ResultDigit::~ResultDigit()
{
	D3DTexture = NULL;
}

//=============================================================================
// 更新
//=============================================================================
void ResultDigit::Update()
{
}

//=============================================================================
// 描画
//=============================================================================
void ResultDigit::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// Zテスト
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// αテストを有効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, TRUE);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	if (use == true)
	{
		// テクスチャの設定(ポリゴンの描画前に読み込んだテクスチャのセットを行う)
		// テクスチャのセットをしないと前にセットされたテクスチャが貼られる→何もはらないことを指定するpDevide->SetTexture(0, NULL);
		Device->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(Vertex2D));
	}

	// αテストを無効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z比較あり
	Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}