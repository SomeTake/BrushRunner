//=============================================================================
//
// ペイント管理クラス [PaintSystem.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "PaintSystem.h"
#include "Input.h"

//=============================================================================
// コンストラクタ
//=============================================================================
PAINTSYSTEM::PAINTSYSTEM(CURSOR *pC, PLAYER *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos = pCursor->GetPos() + (CURSOR_SIZE * 0.5f);

	for (int i = 0; i < MAX_PAINT; i++)
	{
		pPaint[i] = new PAINT();
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
PAINTSYSTEM::~PAINTSYSTEM()
{
	for (int i = 0; i < MAX_PAINT; i++)
	{
		delete pPaint[i];
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void PAINTSYSTEM::Update()
{
	// カーソルに座標を合わせる
	pos = pCursor->GetPos() + (CURSOR_SIZE * 0.5f);

	// 使用しているペイントを更新
	for (int i = 0; i < MAX_PAINT; i++)
	{
		if (pPaint[i]->GetUse())
		{
			pPaint[i]->Update();
		}
	}

	if (GetKeyboardPress(DIK_O))
	{
		Set(pPlayer->GetInkType());
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void PAINTSYSTEM::Draw()
{
	// 使用しているペイントを描画
	for (int i = 0; i < MAX_PAINT; i++)
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
	for (int nCntPaint = 0; nCntPaint < MAX_PAINT; nCntPaint++)
	{
		// 使用していないペイントから検索
		if (!pPaint[nCntPaint]->GetUse())
		{
			// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
			pPaint[nCntPaint]->SetPos(pos);
			pPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			pPaint[nCntPaint]->SetTime(PAINT_DRAW_FRAME);
			pPaint[nCntPaint]->SetUse(true);

			// 使用しているインクの色に合わせてテクスチャをセット
			if (InkType != GAMEPAD_MAX)
			{
				pPaint[nCntPaint]->SetPatternAnim(InkType);
			}
			else
			{
				pPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
			}

			// 頂点座標の設定
			pPaint[nCntPaint]->SetVertex(nCntPaint);

			// 頂点カラーの設定
			pPaint[nCntPaint]->SetColor(nCntPaint);

			break;
		}
	}
}