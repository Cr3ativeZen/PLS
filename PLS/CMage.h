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
	//1st job skills

	void __fastcall Cure(int pPacket, int pPos);
	void __fastcall Heal();
	void __fastcall Cure2(int pPacket, int pPos);


	//2nd job CJB skills

	void __fastcall Cure3(int pPacket, int pPos);
	void __fastcall ShockWave(int pPacket, int pPos);
	void __fastcall Amnesia(int pPacket, int pPos);


	//2nd job Hermit skills

	void __fastcall ChainLightning(int pPacket, int pPos);
	void __fastcall SoulDestruction(int pPacket, int pPos);


};

#endif