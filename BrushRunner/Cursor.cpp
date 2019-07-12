//=============================================================================
//
// カーソル表示 [Cursor.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Cursor.h"
#include "Input.h"
#include "MyLibrary.h"

LPDIRECT3DTEXTURE9	Cursor::D3DTexture = NULL;	// テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
Cursor::Cursor(int PlayerNo, bool AIFlag)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	use = true;
	this->AIFlag = AIFlag;
	pos = CURSOR_FIRST_POS;
	PatternAnim = ctrlNum = PlayerNo;
	vec = 0.0f;
	moveX = 0.0f;
	moveY = 0.0f;

	// テクスチャの読み込み
	if (D3DTexture == NULL)
	{
		D3DXCreateTextureFromFile(Device,	// デバイスのポインタ
			CURSOR_TEXTURE,					// ファイルの名前
			&D3DTexture);					// 読み込むメモリのポインタ
	}

	// 頂点情報の作成
	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
Cursor::~Cursor()
{
	// テクスチャの開放
	SAFE_RELEASE(Cursor::D3DTexture)
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

		if (GetKeyboardTrigger(DIK_P))
		{
			// テクスチャの切り替え
			Change();
		}

		// 頂点座標の設定
		SetVertex();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Cursor::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// Zテスト
	//Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

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
	//Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Cursor::MakeVertex()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点座標の設定
	SetVertex();

	// rhwの設定
	vertexWk[0].rhw = 1.0f;
	vertexWk[1].rhw = 1.0f;
	vertexWk[2].rhw = 1.0f;
	vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	SetTexture();

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void Cursor::SetTexture()
{
	int x = PatternAnim % CURSOR_DIVIDE_X;
	int y = PatternAnim / CURSOR_DIVIDE_X;
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
	//if (!AIFlag)
	//{
		KeyMove();	// キーボード操作
		PadMove();	// コントローラ操作
	//}
	//else
	//{
		AIMove();
	//}
}

//=============================================================================
// カーソルの切り替え
//=============================================================================
void Cursor::Change()
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

	//テクスチャ座標をセット
	SetTexture();
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

	pos.x += vec * moveX * CURSOR_SPEED;
	pos.y += vec * moveY * CURSOR_SPEED;

	// 画面外に出た場合、古い座標に戻す
	pos.x = clamp(pos.x, 0.0f, SCREEN_WIDTH - CURSOR_SIZE.x);
	pos.y = clamp(pos.y, 0.0f, SCREEN_HEIGHT - CURSOR_SIZE.y);
}

//=============================================================================
// カーソルの筆先の座標を取得
//=============================================================================
D3DXVECTOR3 Cursor::GetPenPoint()
{
	return D3DXVECTOR3(pos.x, pos.y + CURSOR_SIZE.y, 0.0f);
}

void Cursor::AIMove()
{

}
