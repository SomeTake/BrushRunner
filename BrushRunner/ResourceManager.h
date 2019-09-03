//=============================================================================
//
// リソースマネージャ [ResourceManager.h]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "BaseSingleton.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResourceManager :
	public BaseSingleton<ResourceManager>
{
	// BaseSingletonクラスのInctanceを呼び出せるように
	friend class BaseSingleton<ResourceManager>;

public:
	ResourceManager() {}
	~ResourceManager() {}

	// 読み込み、開放処理
	// メッシュコンテナ
	//void LoadMesh(const char* tag, const char* path);
	//void ReleaseMesh(const char* tag);

	// 2Dテクスチャ＆3Dポリゴン
	void LoadTexture(const char* tag, const char* path);
	void ReleaseTexture(const char* tag);

	// 参照処理
	//bool GetMesh(const char* tag);
	bool GetTexture(const char* tag, LPDIRECT3DTEXTURE9* pOut);

	// 全リソース開放処理
	void AllRelease();

private:
	std::map<std::string, LPDIRECT3DTEXTURE9> texturePool;	// テクスチャ情報を保存しておく場所
};

#endif
