//=============================================================================
//
// その他関数まとめ [MyLibrary.h]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

//=============================================================================
// プロトタイプ宣言
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, 
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);	// スクリーン座標をワールド座標へ変換

int CmpDescendf(const void *p, const void *q);		// floatの比較（降順）
int CmpAscendf(const void *p, const void *q);		// floatの比較（昇順）
int CmpDescend(const void *p, const void *q);		// intの比較（降順）
int CmpAscend(const void *p, const void *q);		// intの比較（昇順）

template<typename T> T clamp(T x, T low, T high)	// 上限、下限のチェック
{
	return min(max(x, low), high);
}

void ReadCsv(const char *data, int **table);		// CSVファイルの読み込み

#endif

