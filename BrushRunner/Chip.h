//=============================================================================
//
// �`�b�v���� [Chip.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _CHIP_H_
#define _CHIP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHIP_TEXTURE	("data/MAP/tilea5.png")
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// �\���ꏊ
#define MAP_ROT			D3DXVECTOR3(D3DXToRadian(-90), 0.0f, 0.0f)	// ��]
#define CHIP_SIZE		(20.0f)								// �}�b�v�`�b�v�ꖇ�̃T�C�Y
#define CHIP_DIVIDE_X	(8)
#define CHIP_DIVIDE_Y	(16)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Chip
{
private:
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	static LPDIRECT3DTEXTURE9 D3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	bool use;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	Chip(int x, int y, int texnum);
	~Chip();

	void Update();
	void Draw();

	D3DXVECTOR3 GetPos() { return pos; };
	bool GetUse() { return use; };

};

#endif
