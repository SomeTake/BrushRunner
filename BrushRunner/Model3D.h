//=============================================================================
//
// 3D���f���ǂݍ��ݗp���ۃN���X [Model3D.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MODEL3D_H_
#define _MODEL3D_H_

#include "D3DXAnimation.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Model3D :
	public D3DXANIMATION
{
private:
	float animSpd;		// �A�j���[�V�����̍Đ��X�s�[�h

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData)override;
	void CreateAnimSet()override;

public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scl;
	D3DXVECTOR3 rot;

	Model3D(const char* tag, const char* path);
	~Model3D();

	void Update();
	void Draw();

	float GetAnimSpd() { return this->animSpd; };
	void SetAnimSpd(float animSpd) { this->animSpd = animSpd; };
};

#endif
