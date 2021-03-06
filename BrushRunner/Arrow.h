//=============================================================================
//
// ξσ [Arrow.h]
// Author : HAL GP12B332-19 80277 υJu
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "_2dobj.h"
//*****************************************************************************
// NXθ`
//*****************************************************************************
class Arrow :
	public _2dobj
{
private:
	bool reverse;
	bool draw;
	int cntFlash;
	bool flash;		// _Ε³ΉιtO(true = \¦)

	void MakeVertex();

public:
	Arrow(bool reverse);
	~Arrow();

	void Update()override;
	void Draw()override;
};

#endif
