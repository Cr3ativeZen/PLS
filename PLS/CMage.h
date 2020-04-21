#ifndef _CMAGE_H_
#define _CMAGE_H_

#include "ICharacter.h"

class CMage : public ICharacter
{
public:
	CMage() : ICharacter()
	{

	}

	CMage(void* offset) :ICharacter(offset)
	{

	}

	~CMage()
	{

	}





};

#endif