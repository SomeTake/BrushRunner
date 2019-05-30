//=============================================================================
//
// �y�C���g [Paint.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _PAINT_H_
#define _PAINT_H_

#include "Billboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PAINT		"data/TEXTURE/paint"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PAINT_WIDTH			(10.0f)						// ��
#define	PAINT_HEIGHT		(10.0f)						// ����
#define MAX_PAINT			(100)						// �����ɕ\���ł���ő吔
#define PAINT_DIVIDE_X		(5)
#define PAINT_DIVIDE_Y		(1)
#define PAINT_DIVIDE		(PAINT_DIVIDE_X * PAINT_DIVIDE_Y)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PAINT :
	public BILLBOARD
{
private:
	bool					use;			// �g�p���Ă��邩�ǂ���
	float					DecAlpha;		// �����l
	int						time;			// �\�����鎞��
	int						patternAnim;	// �e�N�X�`���p�^�[��
	int						ctrlNum;		// �R���g���[���ԍ�

public:
	PAINT(int _ctrlNum);
	~PAINT();

	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetVertex(int nIdxParticle, float _Width, float _Height);
	void SetColor(int nIdxParticle, D3DXCOLOR _col);
	void SetTexture();
};

#endif
