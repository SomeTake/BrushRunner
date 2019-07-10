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
#define CHIP_SIZE		(20.0f)								// �}�b�v�`�b�v�ꖇ�̃T�C�Y


enum eChipType
{
	eMapChip,
	eObjectChip,
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Chip
{
private:
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 D3DTexture;		// �e�N�X�`���ւ̃|�C���^
	bool use;
	int ChipType;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	Chip(int x, int y, int texnum, int ChipType);
	~Chip();

	void Update();
	void Draw();
	static void ReleaseTexture(void) { SAFE_RELEASE(Chip::D3DTexture); };

	D3DXVECTOR3 GetPos() { return pos; };
	bool GetUse() { return use; };
};

#endif
