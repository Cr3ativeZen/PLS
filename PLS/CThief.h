#ifndef _CTHIEF_H_
#define _CTHIEF_H_

#include "ICharacter.h"

class CThief : public ICharacter
{
public:
	CThief() : ICharacter()
	{

	}

	CThief(void* offset) :ICharacter(offset)
	{

	}

	~CThief()
	{

	}





};

#endif