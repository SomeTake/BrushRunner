//=============================================================================
//
// �y�C���g [Paint.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _PAINT_H_
#define _PAINT_H_

#include "Billboard.h"
#include "Player.h"
#include "Cursor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PAINT		"data/TEXTURE/paint.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PAINT_WIDTH			(30.0f)						// ��
#define	PAINT_HEIGHT		(30.0f)						// ����
#define PAINT_DIVIDE_X		(5)
#define PAINT_DIVIDE_Y		(1)
#define PAINT_DIVIDE		(PAINT_DIVIDE_X * PAINT_DIVIDE_Y)
#define PAINT_MAX			(INK_MAX * 2)				// �J���[�C���N�����C���N
#define DRAW_FRAME_COLOR	(300)						// �\�����Ă����t���[����
#define DRAW_FRAME_BLACK	(60)						// �\�����Ă����t���[����

enum InkColor
{
	RedInkColor,
	BlueInkColor,
	YellowInkColor,
	GreenInkColor,
	BlackInkColor
};

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
	static LPDIRECT3DTEXTURE9		D3DTexture;		// �e�N�X�`���ւ̃|�C���^

public:
	PAINT();
	~PAINT();

	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetVertex();
	void SetColor();
	void SetTexture();

	// �Q�b�^�[
	bool GetUse() { return use; };
	int GetTime() { return time; };
	D3DXVECTOR3 GetPos() { return pos; };
	int GetPatternAnim() { return patternAnim; };

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 _pos) { pos = _pos; };
	void SetRot(D3DXVECTOR3 _rot) { rot = _rot; };
	void SetScl(D3DXVECTOR3 _scl) { scl = _scl; };
	void SetCol(D3DXCOLOR _col) { col = _col; };
	void SetMove(D3DXVECTOR3 _move) { move = _move; };
	void SetWidth(float _width) { width = _width; };
	void SetHeight(float _height) { height = _height; };
	void SetUse(bool _use) { use = _use; };
	void SetDecAlpha(float _DecAlpha) { DecAlpha = _DecAlpha; };
	void SetTime(int _time) { time = _time; };
	void SetPatternAnim(int num) { patternAnim = num; };
};

#endif
