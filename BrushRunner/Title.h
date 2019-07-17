//=============================================================================
//
// �^�C�g���\������ [Title.h]
// Author : HAL���� GP11B341 17 ���J���u
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "_2dobj.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TITLE01 _T("data/texture/Runner.png")										// �^�C�g���̃e�N�X�`��
#define TITLE_SIZE01			D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)				// �e�N�X�`���T�C�Y
#define TITLE_POS01				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y,0.0f)			// �e�N�X�`�����W

#define TEXTURE_TITLE02 _T("data/texture/Logo.png")											// �^�C�g���̃e�N�X�`��
#define TITLE_SIZE02			D3DXVECTOR3(SCREEN_CENTER_X*1.5,SCREEN_CENTER_Y*1.5,0.0f)	// �e�N�X�`���T�C�Y
#define TITLE_POS02				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y*0.75,0.0f)		// �e�N�X�`�����W

#define TEXTURE_TITLE03 _T("data/texture/TitleLogo.png")									// �^�C�g���̃e�N�X�`��
#define TITLE_SIZE03			D3DXVECTOR3(SCREEN_CENTER_X/2,SCREEN_CENTER_Y/2,0.0f)		// �e�N�X�`���T�C�Y
#define TITLE_POS03				D3DXVECTOR3(SCREEN_CENTER_X,SCREEN_CENTER_Y*1.6,0.0f)		// �e�N�X�`�����W

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TITLE :
	public _2dobj
{
public:
	TITLE(D3DXVECTOR3 _pos,D3DXVECTOR3 _size,const char *texno);
	~TITLE();

	// �I�[�o�[���C�h�֐�
	void Update();
	void Draw();
	HRESULT MakeVertex();
	void SetTexture(int cntPattern);
	void SetVertex(void);
	void SetVertexMove(D3DXVECTOR3 pos);
};

#endif
