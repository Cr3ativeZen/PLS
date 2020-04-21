#ifndef _CKNIGHT_H_
#define _CKNIGHT_H_

#include "ICharacter.h"

class CKnight : public ICharacter
{
public:
	CKnight() : ICharacter()
	{

	}

	CKnight(void* offset) :ICharacter(offset)
	{

	}

	~CKnight()
	{

	}

	void __fastcall PowerfulUpwardSlash(int pSkill, int pPacket, int pPos);



};

#endif