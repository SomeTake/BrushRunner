#ifndef _RESULTPLAYER_H_
#define _RESULTPLAYER_H_

#include "VirtualModel.h"
class ResultPlayer :
	public VirtualModel
{
public:
	ResultPlayer(int rank, int owner);
	~ResultPlayer();

	void Update()override;
	void Draw()override;
};

#endif
