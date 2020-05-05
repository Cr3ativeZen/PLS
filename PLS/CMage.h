#ifndef _CMAGE_H_
#define _CMAGE_H_

#include "ICharacter.h"

class CMage : public ICharacter
{
public:

	CMage(void* offset) :ICharacter(offset)
	{

	}

	virtual ~CMage()
	{

	}
	//1st job skills

	void __fastcall Cure(int pPacket, int pPos,int skill_id);
	void __fastcall Heal();
	void __fastcall ShockWave(int pPacket, int pPos);


	//2nd job CJB skills
	void __fastcall Amnesia(int pPacket, int pPos);
	void __fastcall Purification(int pPacket, int pPos);
	void __fastcall Summons(int pPacket, int pPos);



};

#endif