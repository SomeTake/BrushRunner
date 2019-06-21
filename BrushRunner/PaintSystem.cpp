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
#include "Collision.h"

//=============================================================================
// コンストラクタ
//=============================================================================
PaintManager::PaintManager(Cursor *pC, Player *pP)
{
	pPlayer = pP;
	pCursor = pC;

	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	for (int i = 0; i < INK_MAX; i++)
	{
		pBlackPaint[i] = new Paint();
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		pColorPaint[i] = new Paint();
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
PaintManager::~PaintManager()
{
	for (int i = 0; i < INK_MAX; i++)
	{
		delete pBlackPaint[i];
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		delete pColorPaint[i];
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void PaintManager::Update()
{
	// カーソルの筆先に座標を合わせる
	pos.x = pCursor->GetPos().x;
	pos.y = pCursor->GetPos().y + CURSOR_SIZE.y;
	pos.z = 0.0f;

	// 使用しているペイントを更新
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pBlackPaint[i]->GetUse())
		{
			pBlackPaint[i]->Update();

		}
	}
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pColorPaint[i]->GetUse())
		{
			pColorPaint[i]->Update();
		}
	}


	// インクを使う
	if (GetKeyboardPress(DIK_O) || IsButtonPressed(pPlayer->GetCtrlNum(), BUTTON_C))
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
	
}

//=============================================================================
// 描画処理
//=============================================================================
void PaintManager::Draw()
{
	// 使用しているペイントを描画
	for (int i = 0; i < INK_MAX; i++)
	{
		if (pBlackPaint[i]->GetUse())
		{
			pBlackPaint[i]->Draw();
		}
	}

	for (int i = 0; i < INK_MAX; i++)
	{
		if (pColorPaint[i]->GetUse())
		{
			pColorPaint[i]->Draw();
		}
	}
}

//=============================================================================
// ペイントのセット
//=============================================================================
void PaintManager::Set(int InkType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camerawk = GetCamera();

	D3DXMATRIX ViewMtx, ProjMtx;

	pDevice->GetTransform(D3DTS_VIEW, &ViewMtx);
	pDevice->GetTransform(D3DTS_PROJECTION, &ProjMtx);

	// 黒インクの場合
	if (InkType == BlackInk)
	{
		for (int nCntPaint = 0; nCntPaint < INK_MAX; nCntPaint++)
		{
			// 使用していないペイントから検索
			if (!pBlackPaint[nCntPaint]->GetUse())
			{
				// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
				// スクリーン座標とXZ平面のワールド座標交点算出
				D3DXVECTOR3 OutPos1, OutPos2, SetPos;
				CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
				CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

				// 判定用三角形ポリゴン
				TriangleStr triPos1, triPos2;
				triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

				triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

				// 2点を使って当たった場所をセットする場所とする
				if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
				{
					hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
				}

				pBlackPaint[nCntPaint]->SetPos(SetPos);
				pBlackPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pBlackPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				pBlackPaint[nCntPaint]->SetUse(true);

				// 使用しているインクの色に合わせて表示時間、テクスチャをセット
				if (InkType == BlackInk)
				{
					pBlackPaint[nCntPaint]->SetTime(DRAW_FRAME_BLACK);
					pBlackPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
				}
				else
				{
					pBlackPaint[nCntPaint]->SetTime(DRAW_FRAME_COLOR);
					pBlackPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
				}

				// 頂点座標の設定
				pBlackPaint[nCntPaint]->SetVertex();

				// 頂点カラーの設定
				pBlackPaint[nCntPaint]->SetColor();

				break;
			}
		}
	}
	// カラーインクの場合
	else
	{
		for (int nCntPaint = 0; nCntPaint < INK_MAX; nCntPaint++)
		{
			// 使用していないペイントから検索
			if (!pColorPaint[nCntPaint]->GetUse())
			{
				// カーソルのスクリーン座標をワールド座標へ変換して座標をセット
				// スクリーン座標とXZ平面のワールド座標交点算出
				D3DXVECTOR3 OutPos1, OutPos2, SetPos;
				CalcScreenToWorld(&OutPos1, (int)pos.x, (int)pos.y, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);
				CalcScreenToWorld(&OutPos2, (int)pos.x, (int)pos.y, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, &ViewMtx, &ProjMtx);

				// 判定用三角形ポリゴン
				TriangleStr triPos1, triPos2;
				triPos1 = { camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

				triPos2 = { camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f),
					camerawk->at + D3DXVECTOR3(SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f) };

				// 2点を使って当たった場所をセットする場所とする
				if (!hitCheck(&SetPos, triPos1, OutPos1, OutPos2))
				{
					hitCheck(&SetPos, triPos2, OutPos1, OutPos2);
				}

				pColorPaint[nCntPaint]->SetPos(SetPos);
				pColorPaint[nCntPaint]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pColorPaint[nCntPaint]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

				pColorPaint[nCntPaint]->SetUse(true);

				// 使用しているインクの色に合わせて表示時間、テクスチャをセット
				if (InkType == BlackInk)
				{
					pColorPaint[nCntPaint]->SetTime(DRAW_FRAME_BLACK);
					pColorPaint[nCntPaint]->SetPatternAnim(GAMEPAD_MAX);
				}
				else
				{
					pColorPaint[nCntPaint]->SetTime(DRAW_FRAME_COLOR);
					pColorPaint[nCntPaint]->SetPatternAnim(pPlayer->GetCtrlNum());
				}

				// 頂点座標の設定
				pColorPaint[nCntPaint]->SetVertex();

				// 頂点カラーの設定
				pColorPaint[nCntPaint]->SetColor();

				break;
			}
		}
	}

}