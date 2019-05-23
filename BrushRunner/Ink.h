//=============================================================================
//
// �C���N�Q�[�W�\������ [Ink.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _INK_H_
#define _INK_H_

#include "_2dobj.h"
#include "Player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INK_SIZE	D3DXVECTOR2(135.0f, 30.0f)	// �\���T�C�Y

#define INKLINEBLUE_POS     D3DXVECTOR3(60.0f, 25.0f, 0.0f)
#define INKLINERED_POS      D3DXVECTOR3(378.0f, 25.0f, 0.0f)
#define INKLINEYELLOW_POS   D3DXVECTOR3(696.0f, 25.0f, 0.0f)
#define INKLINEGREEN_POS    D3DXVECTOR3(1014.0f, 25.0f, 0.0f)

#define INKLINEBLACK_POS01  D3DXVECTOR3(60.0f, 35.0f, 0.0f)
#define INKLINEBLACK_POS02  D3DXVECTOR3(378.0f, 35.0f, 0.0f)
#define INKLINEBLACK_POS03  D3DXVECTOR3(696.0f, 35.0f, 0.0f)
#define INKLINEBLACK_POS04  D3DXVECTOR3(1014.0f, 35.0f, 0.0f)

#define DISPLACE	(20.0f)		// �΂߂ɂ��炷�p�x

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class INK :
	public _2dobj
{
private:
	PLAYER * pPlayer;	// �Q�Ƃ���L�����N�^�N���X�̃|�C���^
	int inktype;		// �g�p����C���N�̎��(0=color,1=black)
public:
	INK(PLAYER *pP, D3DXVECTOR3 _pos, const char *texno, int _inktype);
	~INK();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex();

};

#endif
