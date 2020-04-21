#ifndef _CARCHER_H_
#define _CARCHER_H_

#include "ICharacter.h"

class CArcher: public ICharacter
{
public:
	CArcher() : ICharacter()
	{

	}

	CArcher(void* offset) :ICharacter(offset)
	{

	}

	~CArcher()
	{

	}
	

	//1st job skills
	void __fastcall BlowUpArrow(int pPacket, int pPos);
	



};

#endif