//=============================================================================
//
// カメラ処理 [Camera.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "main.h"
#include "Camera.h"
#include "Input.h"
#include "Debugproc.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define VIEW_DIST			(4)		// 最低限のキャラクターとカメラの距離
#define VIEW_DIST_RATE		(0.3f)

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
	// 参照する座標に対して平行移動する
	//cameraWk.at = _at;
	//cameraWk.pos = _at + CAMERA_POS;

#ifndef _DEBUG_
	PrintDebugProc("CamerAt X:%f Y:%f Z:%f\n", cameraWk.at.x, cameraWk.at.y, cameraWk.at.z);
	PrintDebugProc("CamerPos X:%f Y:%f Z:%f\n", cameraWk.pos.x, cameraWk.pos.y, cameraWk.pos.z);
#endif

	//if (GetKeyboardPress(DIK_A))
	//{
	//	if (GetKeyboardPress(DIK_W))
	//	{// 左前移動
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else if (GetKeyboardPress(DIK_S))
	//	{// 左後移動
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else
	//	{// 左移動
	//		cameraWk.pos.x -= cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z += sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_D))
	//{
	//	if (GetKeyboardPress(DIK_W))
	//	{// 右前移動
	//		cameraWk.pos.x += cosf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else if (GetKeyboardPress(DIK_S))
	//	{// 右後移動
	//		cameraWk.pos.x += cosf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
	//	}
	//	else
	//	{// 右移動
	//		cameraWk.pos.x += cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//		cameraWk.pos.z -= sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_W))
	//{// 前移動
	//	cameraWk.pos.x += sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	cameraWk.pos.z += cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//else if (GetKeyboardPress(DIK_S))
	//{// 後移動
	//	cameraWk.pos.x -= sinf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;
	//	cameraWk.pos.z -= cosf(cameraWk.rot.y) * VALUE_MOVE_CAMERA;

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}

	//if (GetKeyboardPress(DIK_Z))
	//{// 視点旋回「左」
	//	cameraWk.rot.y += VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y > D3DX_PI)
	//	{
	//		cameraWk.rot.y -= D3DX_PI * 2.0f;
	//	}

	//	cameraWk.pos.x = cameraWk.at.x - sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.pos.z = cameraWk.at.z - cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_C))
	//{// 視点旋回「右」
	//	cameraWk.rot.y -= VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y < -D3DX_PI)
	//	{
	//		cameraWk.rot.y += D3DX_PI * 2.0f;
	//	}

	//	cameraWk.pos.x = cameraWk.at.x - sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.pos.z = cameraWk.at.z - cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_Y))
	//{// 視点移動「上」
	//	cameraWk.pos.y += VALUE_MOVE_CAMERA;
	//}
	//if (GetKeyboardPress(DIK_N))
	//{// 視点移動「下」
	//	cameraWk.pos.y -= VALUE_MOVE_CAMERA;
	//}

	//if (GetKeyboardPress(DIK_Q))
	//{// 注視点旋回「左」
	//	cameraWk.rot.y -= VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y < -D3DX_PI)
	//	{
	//		cameraWk.rot.y += D3DX_PI * 2.0f;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_E))
	//{// 注視点旋回「右」
	//	cameraWk.rot.y += VALUE_ROTATE_CAMERA;
	//	if (cameraWk.rot.y > D3DX_PI)
	//	{
	//		cameraWk.rot.y -= D3DX_PI * 2.0f;
	//	}

	//	cameraWk.at.x = cameraWk.pos.x + sinf(cameraWk.rot.y) * cameraWk.distance;
	//	cameraWk.at.z = cameraWk.pos.z + cosf(cameraWk.rot.y) * cameraWk.distance;
	//}
	//if (GetKeyboardPress(DIK_T))
	//{// 注視点移動「上」
	//	cameraWk.at.y += VALUE_MOVE_CAMERA;
	//}
	//if (GetKeyboardPress(DIK_B))
	//{// 注視点移動「下」
	//	cameraWk.at.y -= VALUE_MOVE_CAMERA;
	//}

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