//=============================================================================
//
// �|�b�v�A�b�v�\������ [Pop.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _POP_H_
#define _POP_H_

#include "Billboard.h"
//#include "Player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Pop : public Billboard
{
private:
	//Player * pPlayer;
	int PlayerNo;

	static LPDIRECT3DTEXTURE9 D3DTexture;		// �e�N�X�`���ւ̃|�C���^

	HRESULT MakeVertex();

public:
	//Pop(Player *pP);
	Pop(int PlayerNo);
	~Pop();

	void Update() {};
	void Update(D3DXVECTOR3 PlayerPos);
	void Draw();
};

#endif
