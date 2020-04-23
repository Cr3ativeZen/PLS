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
	void __fastcall FlamyArrow(int pPacket, int pPos);
	void __fastcall MuscleSolidation();
	void __fastcall PassiveAttack(int pPacket, int pPos);

	//2nd job skills imperial commander
	void __fastcall BuffRemover(int pPacket, int pPos);
	void __fastcall LifeAbsorption(int pPacket, int pPos);
	//2nd job skills expert archer
	void __fastcall FocusShot(int pPacket, int pPos);
	void __fastcall MysteriousArrow(int pPacket, int pPos);


	//3rd job skills imperial general
	void __fastcall ArrowExplosion(int pPacket, int pPos);
	void __fastcall ContinueArrowExplosion();
	void __fastcall VirulentArrow(int pPacket, int pPos);


	//3rd job skills god of bow
	void __fastcall CombativeSpirit(int pPacket, int pPos);
	void __fastcall ContinueArrowRain();
	void __fastcall ArrowRain(int pPacket, int pPos);


};

#endif