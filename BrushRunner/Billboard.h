//=============================================================================
//
// �r���{�[�h�p�N���X [Billboard.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BILLBOARD
{
protected:
	LPDIRECT3DTEXTURE9		D3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3				pos;			// �ʒu
	D3DXVECTOR3				rot;			// ��]
	D3DXVECTOR3				scl;			// �X�P�[��
	D3DXCOLOR				col;			// �F
	D3DXVECTOR3				move;			// �ړ���
	float					width;			// ��
	float					height;			// ����

public:
	BILLBOARD();
	~BILLBOARD();

	// ���z�֐�
	virtual void Update() {};
	virtual void Draw() {};
	virtual int Set() { return 0; };
};

#endif
