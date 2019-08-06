//=============================================================================
//
// �\����[Podium.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PODIUM_H_
#define _PODIUM_H_

#include "D3DXAnimation.h"
class Podium :
	public D3DXANIMATION
{
private:
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet();

public:
	Podium();
	~Podium();

	void Update();
	void Draw();
};

#endif
