//=============================================================================
//
// ���\�[�X�}�l�[�W�� [ResouceManager.cpp]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#include "Main.h"
#include "ResourceManager.h"

//*****************************************************************************
// ���O��Ԃ̊m��
//*****************************************************************************
using namespace std;

////=============================================================================
//// ���b�V���̓ǂݍ���
////=============================================================================
//void ResouceManager::LoadMesh(const char* tag, const char* path)
//{
//	string tagStr = string(tag);
//
//	// �^�O�̏d���m�F
//
//	// ���b�V���R���e�i�𐶐����ă��[�h
//}
//
////=============================================================================
//// ���b�V���̊J��
////=============================================================================
//void ResouceManager::ReleaseMesh(const char* tag)
//{
//	string tagStr = string(tag);
//
//	// �^�O�̓o�^�m�F
//
//	// ���b�V���R���e�i���폜
//}
//
////=============================================================================
//// ���b�V���̎擾
////=============================================================================
//bool ResouceManager::GetMesh(const char* tag)
//{
//	string tagStr = string(tag);
//
//	// �o�^�m�F
//
//	// ���b�V���ւ̎Q�Ƃ��i�[
//}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void ResourceManager::LoadTexture(const char* tag, const char* path)
{
	string tagStr = string(tag);

	// �d���m�F
	if (texturePool.count(tagStr) != 0)
		SAFE_RELEASE(texturePool[tagStr]);

	// �ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

//=============================================================================
// �e�N�X�`���̊J��
//=============================================================================
void ResourceManager::ReleaseTexture(const char* tag)
{
	string tagStr = string(tag);

	// �o�^�m�F
	if (texturePool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(texturePool[tagStr]);
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
bool ResourceManager::GetTexture(const char* tag, LPDIRECT3DTEXTURE9 *pOut)
{
	string tagStr = string(tag);

	// �o�^�m�F
	if (texturePool.count(tagStr) == 0)
		return false;

	*pOut = texturePool[tagStr];
	return true;
}

//=============================================================================
// ���\�[�X�̑S�폜
//=============================================================================
void ResourceManager::AllRelease()
{
	for (auto &pool : texturePool)
	{
		SAFE_RELEASE(pool.second)
	}
	texturePool.clear();
}