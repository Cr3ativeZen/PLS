#ifndef _CARCHER_H_
#define _CARCHER_H_

#include "ICharacter.h"

class CArcher: public ICharacter
{
public:


	CArcher(void* offset) :ICharacter(offset)
	{

	}

	virtual ~CArcher()
	{

	}
	

	//1st job skills
	void __fastcall BlowUpArrow(int pPacket, int pPos);
	void __fastcall FlamyArrow(int pPacket, int pPos);
	void __fastcall MuscleSolidation();
	void __fastcall PassiveAttack(int pPacket, int pPos);

	//2nd job skills imperial commander
	void __fastcall BuffRemover(int pPacket, int pPos);
	//2nd job skills expert archer
	void __fastcall FocusShot(int pPacket, int pPos);
	void __fastcall MysteriousArrow(int pPacket, int pPos);
};

#endif