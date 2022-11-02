//
//Gimmick.h
//
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "objectx.h"

class CGimmick : public CObjectX
{
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:
	
};

#endif