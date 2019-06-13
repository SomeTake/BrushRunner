//=============================================================================
//
// �|�b�v�A�b�v�\������ [Pop.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _POP_H_
#define _POP_H_

#include "Billboard.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_POP		"data/TEXTURE/pointer.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	POP_WIDTH		(64.0f)							// ���a����
#define	POP_HEIGHT		(32.0f)							// ���a��
#define POP_POS			D3DXVECTOR3(0.0f, 90.0f, 0.0f)	// �\���ꏊ
#define POP_DIVIDE_X	(4)
#define POP_DIVIDE_Y	(1)
#define POP_ANIM_DIVIDE	(POP_DIVIDE_X * POP_DIVIDE_Y)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class POP :
	public BILLBOARD
{
private:
	PLAYER * pPlayer;
	int patternAnim;

	static LPDIRECT3DTEXTURE9 D3DTexture;		// �e�N�X�`���ւ̃|�C���^

public:
	POP(PLAYER *pP);
	~POP();

	void Update();
	void Draw();
	HRESULT MakeVertex();

};

#endif
