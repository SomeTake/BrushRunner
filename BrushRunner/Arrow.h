//=============================================================================
//
// –îˆó [Arrow.h]
// Author : HAL“Œ‹ GP12B332-19 80277 õ’J•u
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "_2dobj.h"
//*****************************************************************************
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************
class Arrow :
	public _2dobj
{
private:
	bool reverse;
	bool draw;

	void MakeVertex();

public:
	Arrow(bool reverse);
	~Arrow();

	void Update()override;
	void Draw()override;
};

#endif
