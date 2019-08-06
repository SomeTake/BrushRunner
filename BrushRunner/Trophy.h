//=============================================================================
//
// �g���t�B�[[Trophy.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _TROPHY_H_
#define _TROPHY_H_

#include "D3DXAnimation.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Trophy :
	public D3DXANIMATION
{
private:
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet();

public:
	Trophy();
	~Trophy();

	void Update()override;
	void Draw()override;
};

#endif
