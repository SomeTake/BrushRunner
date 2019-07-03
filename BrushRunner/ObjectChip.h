//=============================================================================
//
// �t�B�[���h�I�u�W�F�N�g�`�b�v���� [ObjectChip.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _OBJECTCHIP_H_
#define _OBJECTCHIP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJECTCHIP_TEXTURE	("data/MAP/tilea5.png")
#define OBJECTCHIP_DIVIDE_X	(8)
#define OBJECTCHIP_DIVIDE_Y	(16)

// �t�B�[���h�I�u�W�F�N�g�̎��
#define OBJ_NUM_SPDUP		(0)	// ������
#define OBJ_NUM_SPDDOWN		(1)	// ������
#define OBJ_NUM_NUMA		(2)	// ���n�i�����j
#define OBJ_NUM_JUMP		(3)	// �W�����v��
#define OBJ_NUM_DRAIN		(4)	// �h���C���t���A
#define OBJ_NUM_HEAL		(5)	// �񕜔�
#define OBJ_NUM_ITEM		(6)	// �A�C�e��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ObjectChip
{
private:
	D3DXVECTOR3	pos;
	D3DXVECTOR3	rot;
	D3DXVECTOR3	scl;
	static LPDIRECT3DTEXTURE9 D3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	bool use;

	HRESULT MakeVertex(int texnum);
	void CheckOnCamera();

public:
	ObjectChip(int x, int y, int texnum);
	~ObjectChip();

	void Update();
	void Draw();

	D3DXVECTOR3 GetPos() { return pos; };

};

#endif
