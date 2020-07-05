#ifndef CTHIEF_H_
#define CTHIEF_H_

#include "ICharacter.h"

class CThief : public ICharacter
{
public:
	CThief(void* offset) : ICharacter(offset)
	{

	}
	virtual ~CThief()
	{


	}


	//3rd job Unearthly Ghost

	void __fastcall ShadowSlash(int pPacket, int pPos);
};


#endif

