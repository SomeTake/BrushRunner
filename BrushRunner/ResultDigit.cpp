#include "Main.h"
#include "ResultDigit.h"
#include "ResultRank.h"
#include "Player.h"

#define DIGIT_SPACE	(1.0f)

LPDIRECT3DTEXTURE9	ResultDigit::D3DTexture = NULL; // テクスチャのポインタ

ResultStr ResultData[PLAYER_MAX] = {
	D3DXVECTOR3(550.0f, 70.0f, 0.0f), D3DXVECTOR3(30.0f, 150.0f, 0.0f),
	D3DXVECTOR3(430.0f, 400.0f, 0.0f), D3DXVECTOR3(20.0f, 90.0f, 0.0f),
	D3DXVECTOR3(390.0f, 510.0f, 0.0f), D3DXVECTOR3(20.0f, 70.0f, 0.0f),
	D3DXVECTOR3(390.0f, 590.0f, 0.0f), D3DXVECTOR3(20.0f, 70.0f, 0.0f),
};

ResultDigit::ResultDigit(DWORD _time, int _digit, int _rank) : Digit(_digit)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	time = _time;
	use = true;
	rank = _rank;
	pos = ResultData[rank].pos;
	pos.x += DIGIT_SPACE * ResultData[rank].size.x;
	size = ResultData[rank].size;

	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			TEXTURE_DIGIT,					// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}

	MakeVertex();
}


ResultDigit::~ResultDigit()
{
	SAFE_RELEASE(D3DTexture);
}

void ResultDigit::Update()
{

}
