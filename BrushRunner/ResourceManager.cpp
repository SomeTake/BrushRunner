//=============================================================================
//
// リソースマネージャ [ResouceManager.cpp]
// Author : HAL東京 GP11B341 17 染谷武志
//
//=============================================================================
#include "Main.h"
#include "ResourceManager.h"

//*****************************************************************************
// 名前空間の確保
//*****************************************************************************
using namespace std;

////=============================================================================
//// メッシュの読み込み
////=============================================================================
//void ResouceManager::LoadMesh(const char* tag, const char* path)
//{
//	string tagStr = string(tag);
//
//	// タグの重複確認
//
//	// メッシュコンテナを生成してロード
//}
//
////=============================================================================
//// メッシュの開放
////=============================================================================
//void ResouceManager::ReleaseMesh(const char* tag)
//{
//	string tagStr = string(tag);
//
//	// タグの登録確認
//
//	// メッシュコンテナを削除
//}
//
////=============================================================================
//// メッシュの取得
////=============================================================================
//bool ResouceManager::GetMesh(const char* tag)
//{
//	string tagStr = string(tag);
//
//	// 登録確認
//
//	// メッシュへの参照を格納
//}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void ResourceManager::LoadTexture(const char* tag, const char* path)
{
	string tagStr = string(tag);

	// 重複確認
	if (texturePool.count(tagStr) != 0)
		SAFE_RELEASE(texturePool[tagStr]);

	// 読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

//=============================================================================
// テクスチャの開放
//=============================================================================
void ResourceManager::ReleaseTexture(const char* tag)
{
	string tagStr = string(tag);

	// 登録確認
	if (texturePool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(texturePool[tagStr]);
}

//=============================================================================
// テクスチャの取得
//=============================================================================
bool ResourceManager::GetTexture(const char* tag, LPDIRECT3DTEXTURE9 *pOut)
{
	string tagStr = string(tag);

	// 登録確認
	if (texturePool.count(tagStr) == 0)
		return false;

	*pOut = texturePool[tagStr];
	return true;
}

//=============================================================================
// リソースの全削除
//=============================================================================
void ResourceManager::AllRelease()
{
	for (auto &pool : texturePool)
	{
		SAFE_RELEASE(pool.second)
	}
	texturePool.clear();
}