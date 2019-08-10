//=============================================================================
//
// �v���C���[���� [ResultRank.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _RESULTRANK_H_
#define _RESULTRANK_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULTRANK_TEXTURE	("data/TEXTURE/ResultPlayer.png")
#define RESULTRANK_DIVIDE_X	(1)
#define RESULTRANK_DIVIDE_Y	(4)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultRank :
	public _2dobj
{
private:
	static LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^
	int rank;	// ����
	int owner;	// �v���C���[�ԍ�
	HRESULT MakeVertex();

public:
	ResultRank(int rank, int owner);
	~ResultRank();

	void Update();
	void Draw();

};

#endif
