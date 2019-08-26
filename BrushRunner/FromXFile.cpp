//=============================================================================
//
// X�t�@�C���ǂݍ��ݗp�N���X[FromXFile.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#include "Main.h"
#include "FromXFile.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
FromXFile::FromXFile()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
FromXFile::~FromXFile()
{
	SAFE_RELEASE(this->AnimController);

	D3DXFrameDestroy(this->FrameRoot, this->AllocateHier);

	this->AllocateHier->DestroyFrame(this->FrameRoot);

	SAFE_DELETE(this->AllocateHier);

}

//=============================================================================
// X�t�@�C���ǂݍ���
//=============================================================================
HRESULT FromXFile::Load(const char* tag, const char* path)
{
	char Message[64];
	LPDIRECT3DDEVICE9 Device = GetDevice();
	this->AllocateHier = new AllocateHierarchy();

	// Xfile�̓ǂݍ���
	if (FAILED(D3DXLoadMeshHierarchyFromX(path,
		D3DXMESH_MANAGED,
		Device,
		this->AllocateHier,
		NULL,
		&this->FrameRoot,
		&this->AnimController)))
	{
		sprintf_s(Message, "Load %s Model Failed�I", tag);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	return S_OK;
}