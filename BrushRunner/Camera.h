//=============================================================================
//
// カメラ処理 [camera.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DRAW_RANGE	D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f)	// カメラで撮影される範囲（大体）

//*****************************************************************************
// グローバル変数
//*****************************************************************************

typedef struct {
	D3DXVECTOR3			pos;		// カメラの視点
	D3DXVECTOR3			at;			// カメラの注視点
	D3DXVECTOR3			up;			// カメラの上方向ベクトル
	D3DXVECTOR3			rot;		// カメラの回転
	float				distance;	// カメラの注視点と視点との距離
	D3DXMATRIX			mtxView;	// ビューマトリックス
	D3DXMATRIX			mtxProj;	// プロジェクションマトリックス
}CAMERA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera();
void UpdateCamera(D3DXVECTOR3 _at);	// SceneGame用
void UpdateCamera();				// SceneResult用
void UpdateTitleCamera();
CAMERA *GetCamera();
void SetCamera();

#endif
