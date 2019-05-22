//=============================================================================
//
// �}�b�v���� [Map.h]
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
#define MAP_TEXTURE0	("data/MAP/map0.jpg")
#define MAP_TEXTURE1	("data/MAP/map1.jpg")
#define MAP_TEXTURE2	("data/MAP/map2.jpg")
#define MAP_POS			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// �\���ꏊ
#define MAP_ROT			D3DXVECTOR3(D3DXToRadian(-90), 0.0f, 0.0f)	// ��]
#define MAP_FILE		("data/MAP/data.csv")				// �ǂݍ��ރ}�b�v�f�[�^
#define MAP_SIZE_X		(100)									// �}�b�v�̉��̖���
#define MAP_SIZE_Y		(10)									// �}�b�v�̏c�̖���
#define CHIP_SIZE		(20.0f)								// �}�b�v�`�b�v�ꖇ�̃T�C�Y

// �}�b�v�`�b�v�̎��
enum MapStateNum{
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

	int GetMapTbl(int _MapX, int _MapY) { return maptbl[_MapX][_MapY]; };
};

#endif
