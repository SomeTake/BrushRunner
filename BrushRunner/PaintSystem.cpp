//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "PaintSystem.h"
#include "Input.h"
#include "Debugproc.h"
#include "MyLibrary.h"
#include "Camera.h"

//=============================================================================
// コンストラクタ
//=============================================================================
PAINTSYSTEM::PAINTSYSTEM(CURSOR *pC, PLAYER *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	for (int i = 0; i < PAINT_MAX; i++)
	{
		pPaint[i] = new PAINT();
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
PAINTSYSTEM::~PAINTSYSTEM()
{
	for (int i = 0; i < PAINT_MAX; i++)
	{
		delete pPaint[i];
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void PAINTSYSTEM::Update()
{
	// カーソルの筆先に座標を合わせる
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y/* + CURSOR_SIZE.y*/;
	pos.z = 0.0f;

	// 使用しているペイントを更新
	for (int i = 0; i < PAINT_MAX; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Update();
			PrintDebugProc("Paint[%d]Time%d\n",i, pPaint[i]->GetTime());

		}
	}

	// インクを使う
	if (GetKeyboardPress(DIK_O))
	{
		// 使用するインクの残量チェック
		int type = pPlayer->GetInkType();
		if (pPlayer->GetInkValue(type) > 0)
		{
			Set(pPlayer->GetInkType());
			// インクを減らす
			int value = pPlayer->GetInkValue(type) - 1;
			pPlayer->SetInkValue(type, value);
		}
	}

	// インクの使用数を数える
	int num = 0;
	for (int i = 0; i < PAINT_MAX; i++)
	{
		if (pPaint[i]->GetUse()) num++;
	}
	
#ifndef _DEBUG_
	PrintDebugProc("使用しているインクの数 %d\n", num);
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void PAINTSYSTEM::Draw()
{
	// 使用しているペイントを描画
	for (int i = 0; i < PAINT_MAX; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Draw();
		}
	}
}

//=============================================================================
// ペイントのセット
//=============================================================================
void PAINTSYSTEM::Set(int InkType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camerawk = GetCamera();

	D3DXMATRIX ViewMtx, ProjMtx;

	 pDevice->GetTransform(D3DTS_VIEW, &ViewMtx);
	 pDevice->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	for (int nCntPaint = 0; nCntPaint < PAINT_MAX; nCntPaint++)
	{
		// 使用していないペイントから検索
		if (!pPaint[nCntPaint]->GetUse())
		{
			// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
			//// スクリーン座標とXZ平面のワールド座標交点算出
			//D3DXVECTOR3 OutPos1;
			//CalcScreenToXZ(&OutPos1, (int)pos.x, (int)pos.y, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

			//// カメラの範囲から奥行きを1.0～0.0に変換
			//float viewRange;
			//viewRange = VIEW_FAR_Z - VIEW_NEAR_Z;
			//OutPos1.z -=  (pos.z + VIEW_NEAR_Z);
			//OutPos1.z /= viewRange;

			//D3DXVECTOR3 OutPos2;
			//// スクリーン座標をワールド座標へ変換
			//CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, OutPos1.z, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
			//OutPos2.z = 0.0f;

			//pPaint[nCntPaint]->SetPos(OutPos2);
			
			D3DXVECTOR3 setPos = Pick(pos);
			setPos.z = 0.0f;

			pPaint[nCntPaint]->SetPos(setPos);
			pPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			pPaint[nCntPaint]->SetTime(PAINT_DRAW_FRAME);
			pPaint[nCntPaint]->SetUse(true);

			// 使用しているインクの色に合わせてテクスチャをセット
			if (InkType == BlackInk)
			{
				pPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
			}
			else
			{
				pPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
			}

			// 頂点座標の設定
			pPaint[nCntPaint]->SetVertex();

			// 頂点カラーの設定
			pPaint[nCntPaint]->SetColor();

			break;
		}
	}
}