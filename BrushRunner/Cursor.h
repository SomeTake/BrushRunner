//=============================================================================
//
// カーソル表示 [Cursor.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "_2dobj.h"
#include "CharacterAI.h"


//*****************************************************************************
// クラス定義
//*****************************************************************************
class Cursor : public _2dobj
{
private:
	int		ctrlNum;			// 操作するコントローラ番号
	float	vec = 0.0f;			// ジョイスティックのベクトルを1/1000にして保存(1.0f-0.0f)
	float	moveX = 0.0f;		// ジョイスティックのX値を1/1000にして保存(1.0f-0.0f)
	float	moveY = 0.0f;		// ジョイスティックのY値を1/1000にして保存(1.0f-0.0f)

	// AI用
	CharacterAI		*AIptr = nullptr;
	bool			AIUse = false;
	D3DXVECTOR3		WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	void PaintPath(void);					// インクで通れる道を作る
	void DeletePath(void);					// 他のプレイヤーのペイントを削除
	void PaintObjChip(void);				// オブジェクトチップをペイントする

	HRESULT MakeVertex();				// 頂点の作成
	void SetTexture();					// テクスチャ座標の設定
	void SetVertex();					// 頂点座標の設定
	void KeyMove();						// キーボード操作
	void PadMove();						// コントローラ操作
	void Move();						// 操作
	void CalWorldPos();

public:
	Cursor(int PlayerNo, bool AIUse, CharacterAI *AIptr);
	~Cursor();

	// 更新
	void Update();
	// 描画
	void Draw();	
	// インクを切り替え
	void ChangeInk();						

	// カーソルの座標を取得
	D3DXVECTOR3 GetPos(void) { return this->pos; };
	D3DXVECTOR3 GetWorldPos(void) { return this->WorldPos; };
};

#endif
