//=============================================================================
//
// カーソル表示 [Cursor.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Cursor.h"
#include "Input.h"
#include "Debugproc.h"
#include "MyLibrary.h"

LPDIRECT3DTEXTURE9	Cursor::D3DTexture = NULL;	// テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
Cursor::Cursor(int _ctrlNum, Player *pP)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			CURSOR_TEXTURE,					// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}

	use = true;
	pos = CURSOR_FIRST_POS;
	PatternAnim = ctrlNum = _ctrlNum;
	pPlayer = pP;
	vec = 0.0f;
	moveX = 0.0f;
	moveY = 0.0f;

	// 頂点情報の作成
	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
Cursor::~Cursor()
{
	if (D3DTexture != NULL)
	{	// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Cursor::Update()
{
	if (use == true)
	{
		// 操作
		Move();

		// テクスチャの切り替え
		Change();

		//テクスチャ座標をセット
		SetTexture(PatternAnim);

	}
	SetVertex();

#ifndef _DEBUG_
	PrintDebugProc("CursorPos X:%f Y:%f\n", pos.x, pos.y);
	//PrintDebugProc("CursorMove X:%f Y:%f\n", moveX, moveY);
	//PrintDebugProc("CursorVec %f\n", vec);
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void Cursor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (use == true)
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
HRESULT Cursor::MakeVertex()
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
void Cursor::SetTexture(int cntPattern)
{
	int x = cntPattern % CURSOR_DIVIDE_X;
	int y = cntPattern / CURSOR_DIVIDE_X;
	float sizeX = 1.0f / CURSOR_DIVIDE_X;
	float sizeY = 1.0f / CURSOR_DIVIDE_Y;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void Cursor::SetVertex()
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vertexWk[1].vtx = D3DXVECTOR3(pos.x + CURSOR_SIZE.x, pos.y, pos.z);
	vertexWk[2].vtx = D3DXVECTOR3(pos.x, pos.y + CURSOR_SIZE.y, pos.z);
	vertexWk[3].vtx = D3DXVECTOR3(pos.x + CURSOR_SIZE.x, pos.y + CURSOR_SIZE.y, pos.z);
}

//=============================================================================
// 操作
//=============================================================================
void Cursor::Move()
{
	KeyMove();	// キーボード操作
	PadMove();	// コントローラ操作
}

//=============================================================================
// カーソルの切り替え
//=============================================================================
void Cursor::Change()
{
	if (GetKeyboardTrigger(DIK_P))
	{
		// テクスチャとプレイヤーのインクの切り替え
		// カラー→黒
		if (PatternAnim == ctrlNum)
		{
			PatternAnim = ctrlNum + CURSOR_DIVIDE_X;
		}
		// 黒→カラー
		else
		{
			PatternAnim = ctrlNum;
		}

	}
}

//=============================================================================
// キーボード操作
//=============================================================================
void Cursor::KeyMove()
{
	// 上下
	if (GetKeyboardPress(DIK_W))
	{
		pos.y -= CURSOR_SPEED;

		// 画面外判定
		pos.y = max(pos.y, 0.0f);
	}
	else if (GetKeyboardPress(DIK_S))
	{
		pos.y += CURSOR_SPEED;

		// 画面外判定
		pos.y = min(pos.y, SCREEN_HEIGHT - CURSOR_SIZE.y);

	}

	// 左右
	if (GetKeyboardPress(DIK_D))
	{
		pos.x += CURSOR_SPEED;

		// 画面外判定
		pos.x = min(pos.x, SCREEN_WIDTH - CURSOR_SIZE.x);
	}
	else if (GetKeyboardPress(DIK_A))
	{
		pos.x -= CURSOR_SPEED;

		// 画面外判定
		pos.x = max(pos.x, 0.0f);
	}
}

//=============================================================================
// コントローラ操作
//=============================================================================
void Cursor::PadMove()
{
	vec = GetJoyStickVec(ctrlNum) / 1000.f;
	moveX = (float)GetJoyStickLeftX(ctrlNum) / 1000.0f;
	moveY = (float)GetJoyStickLeftY(ctrlNum) / 1000.0f;

	//oldPos = pos;

	pos.x += vec * moveX * CURSOR_SPEED;
	pos.y += vec * moveY * CURSOR_SPEED;

	// 画面外に出た場合、古い座標に戻す
	pos.x = clamp(pos.x, 0.0f, SCREEN_WIDTH - CURSOR_SIZE.x);
	pos.y = clamp(pos.y, 0.0f, SCREEN_HEIGHT - CURSOR_SIZE.y);

	//if (pos.y < 0 || pos.y > SCREEN_HEIGHT - CURSOR_SIZE.y)
	//{
	//	pos.y = oldPos.y;
	//}
	//if (pos.x > SCREEN_WIDTH - CURSOR_SIZE.x || pos.x < 0)
	//{
	//	pos.x = oldPos.x;
	//}
}