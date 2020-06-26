#ifndef _CKNIGHT_H_
#define _CKNIGHT_H_
#include "ICharacter.h"

class CKnight : public ICharacter
{
public:

	CKnight(void* offset) :ICharacter(offset)
	{

	}

	virtual ~CKnight()
	{

	}

	//1st job skills
	void __fastcall LightningSlash(int pPacket, int pPos);
	void __fastcall TranscendentalBlow(int pPacket, int pPos);
	void __fastcall CoalescenceOfRuin(int pPacket,int pPos);


	//2nd job skills vagabond
	void __fastcall BrutalAttack(int pPacket, int pPos);
	void __fastcall HalfSwing(int pPacket, int pPos);
	void __fastcall PowerfulUpwardSlash(int pPacket, int pPos);

	//2nd job skills commander
	void __fastcall Sacrifice(int pPacket, int pPos);
	void __fastcall Calls(int pPacket, int pPos,int SkillID);

	//3rd job skills God of Sword

	void __fastcall SpinSlash();


	//4th job for General
	//void __fastcall TheBoomOfEarth();



};

#endif