//=============================================================================
//
// �}�b�v���� [Map.cpp]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <string>
#include <fstream>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_TEXTURE0	("data/TEXTURE/map0.jpg")
#define MAP_TEXTURE1	("data/TEXTURE/map1.jpg")
#define MAP_TEXTURE2	("data/TEXTURE/map2.jpg")
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// �\���ꏊ
#define MAP_FILE		("data/MAP/data.csv")			// �ǂݍ��ރ}�b�v�f�[�^
#define MAP_SIZE_X		(3)							// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(3)								// �}�b�v�̏c�̖���
#define CHIP_SIZE		(40.0f)							// �}�b�v�`�b�v�ꖇ�̃T�C�Y

// �}�b�v�`�b�v�̎��
enum {
	MapField,
	MapTrap,
	MapItem,

	// �}�b�v�`�b�v�̎�ސ�
	MapChipMax
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MAP
{
private:
	string					line;								// ��������ꎞ�I�ɕۑ�
	int						maptbl[MAP_SIZE_Y][MAP_SIZE_X];		// �}�b�v�p�̔z��
	const string			delim = ",";						// �f�[�^��؂�p�̕���
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	LPDIRECT3DTEXTURE9		D3DTexture[MapChipMax] = { NULL };	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;					// ���_�o�b�t�@�ւ̃|�C���^


public:
	MAP();
	~MAP();

	void Update();
	void Draw();

	void ReadCsv(const char *data);		// CSV�t�@�C���̓ǂݍ���
	HRESULT MakeVertex();				// ���_���̍쐬
};

#endif
