#pragma once
#include "_2dobj.h"
#include "Player.h"

class INK :
	public _2dobj
{
private:
	PLAYER * pPlayer;	// �Q�Ƃ���L�����N�^�N���X�̃|�C���^
public:
	INK(PLAYER *pP, D3DXVECTOR3 _pos, const char *texno);
	~INK();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

