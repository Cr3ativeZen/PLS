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

	void __fastcall Cure(int pSkill, void* edx, int pPacket, int pPos);
	void __fastcall Cure2(int pSkill, void* edx, int pPacket, int pPos);
	void __fastcall Cure3(int pSkill, void* edx, int pPacket, int pPos);




};

#endif