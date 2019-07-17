//=============================================================================
//
// �~�j�v���C���[���� [MiniPlayer.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MINIPLAYER_H_
#define _MINIPLAYER_H_

#include "_2dobj.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MiniPlayer : public _2dobj
{
private:
	static LPDIRECT3DTEXTURE9		D3DTexture;		// �e�N�X�`���ւ̃|�C���^

	HRESULT MakeVertex(int PlayerNo);	// ���_���̍쐬
	void SetTexture(int PlayerNo);		// �e�N�X�`�����W�̐ݒ�
	void SetVertex(void);				// ���_���W�̐ݒ�

public:
	MiniPlayer(int PlayerNo);
	~MiniPlayer();
	static void ReleaseTexture(void) { SAFE_RELEASE(MiniPlayer::D3DTexture); };

	void Update(D3DXVECTOR3 PlayerPos);
	void Draw();
};

#endif

