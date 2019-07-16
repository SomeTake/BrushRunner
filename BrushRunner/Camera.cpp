//=============================================================================
//
// カメラ処理 [Camera.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "main.h"
#include "Camera.h"
#include "Input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define VIEW_DIST			(4)		// 最低限のキャラクターとカメラの距離
#define VIEW_DIST_RATE		(0.3f)
#define CAMERA_SPD			(0.05f)	// 古いカメラ注視点と新しいカメラ注視点に差がある場合にカメラ位置を更新するスピード

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA cameraWk;

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	cameraWk.pos = CAMERA_POS;
	cameraWk.at = CAMERA_AT;
	cameraWk.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	cameraWk.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = cameraWk.pos.x - cameraWk.at.x;
	vz = cameraWk.pos.z - cameraWk.at.z;
	cameraWk.distance = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(D3DXVECTOR3 _at)
{
	// 一番前にいるキャラクタの座標を新しい注視点とする
	D3DXVECTOR3 newAt = _at;

	// 更新前の注視点と新しい注視点の差をベクトルにする
	D3DXVECTOR3 DistVec = newAt - cameraWk.at;

	// 徐々に新しい注視点に近づける
	cameraWk.at += DistVec * CAMERA_SPD;
	
	// 座標は注視点に対して平行移動する
	cameraWk.pos = cameraWk.at + CAMERA_POS;

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&cameraWk.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&cameraWk.mtxView,
		&cameraWk.pos,		// カメラの視点
		&cameraWk.at,		// カメラの注視点
		&cameraWk.up);		// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &cameraWk.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&cameraWk.mtxProj);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&cameraWk.mtxProj,
		VIEW_ANGLE,			// ビュー平面の視野角
		VIEW_ASPECT,		// ビュー平面のアスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値
		VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &cameraWk.mtxProj);

}

//=============================================================================
//カメラの情報を取得する
//=============================================================================
CAMERA *GetCamera(void)
{
	return &cameraWk;
}