//=============================================================================
//
// Xファイル読み込み用クラス[FromXFile.cpp]
// Author : HAL東京 GP12B332-19 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "FromXFile.h"

//=============================================================================
// コンストラクタ
//=============================================================================
FromXFile::FromXFile()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
FromXFile::~FromXFile()
{
	SAFE_RELEASE(this->AnimController);

	D3DXFrameDestroy(this->FrameRoot, this->AllocateHier);

	this->AllocateHier->DestroyFrame(this->FrameRoot);

	SAFE_DELETE(this->AllocateHier);

}

//=============================================================================
// Xファイル読み込み
//=============================================================================
HRESULT FromXFile::Load(const char* tag, const char* path)
{
	char Message[64];
	LPDIRECT3DDEVICE9 Device = GetDevice();
	this->AllocateHier = new AllocateHierarchy();

	// Xfileの読み込み
	if (FAILED(D3DXLoadMeshHierarchyFromX(path,
		D3DXMESH_MANAGED,
		Device,
		this->AllocateHier,
		NULL,
		&this->FrameRoot,
		&this->AnimController)))
	{
		sprintf_s(Message, "Load %s Model Failed！", tag);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	return S_OK;
}