#ifndef _RESULTPLAYER_H_
#define _RESULTPLAYER_H_

#include "D3DXAnimation.h"
class ResultPlayer :
	public D3DXANIMATION
{
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;

	HRESULT CALLBACK HandleCallback(THIS_ UINT Track, LPVOID pCallbackData);
	void CreateAnimSet()override;

public:
	ResultPlayer(int rank, int owner);
	~ResultPlayer();

	void Update()override;
	void Draw()override;
};

#endif
