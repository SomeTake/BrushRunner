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
#define	CAMERA_POS		D3DXVECTOR3(0.0f, 10.0f, -500.0f)				// カメラの初期位置
#define CAMERA_AT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)					// カメラの注視点

#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

#define	INTERVAL_CAMERA_R	(12.5f)										// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)										// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)										// カメラの注視点への補正係数

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
void UpdateCamera(D3DXVECTOR3 _at);
CAMERA *GetCamera();
void SetCamera();

#endif
