#ifndef _RESULTPLAYER_H_
#define _RESULTPLAYER_H_

#include "Model3D.h"
class ResultPlayer :
	public Model3D
{
public:
	ResultPlayer(int rank, int owner, const char* tag);
	~ResultPlayer();

	void Update()override;
	//void Draw()override;
};

#endif
