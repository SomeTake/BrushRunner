//=============================================================================
//
// 2D�p�I�u�W�F�N�g���� [_2dobj.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _2DOBJ_H_
#define _2DOBJ_H_

#include "Struct.h"

//*****************************************************************************
// 2D�p�I�u�W�F�N�g���N���X��`
//*****************************************************************************
class _2dobj //�N���X��
{
	//   private:�@    �s�G�@�p���s��
	//   protected:    �s�G�@�p����
	//   public:       �G�@�@�p����
protected:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9	D3DTexture;					// �e�N�X�`���̃|�C���^
	Vertex2D			vertexWk[NUM_VERTEX];		// ���_���i�[�\����
	D3DXVECTOR3			pos;						// ���W
	int					PatternAnim;				// �A�j���[�V�����p�^�[��
	bool				use;						// �g�p�t���O

public:
	// �����o�֐�
	_2dobj();
	~_2dobj();

	// ���z�֐�
	virtual void Update() {};						// �X�V
	virtual void Draw() {};							// �`��
	virtual HRESULT MakeVertex() { return S_OK; };	// ���_�̍쐬
	virtual void SetTexture(int cntPattern) {};		// �e�N�X�`�����W�̐ݒ�
	virtual void SetVertex() {};					// ���_���W�̐ݒ�

};

#endif