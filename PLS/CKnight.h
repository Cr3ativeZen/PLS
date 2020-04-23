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

	//1st job skills
	void __fastcall LightningSlash(int pPacket, int pPos);
	void __fastcall ShieldAttack(int pPacket, int pPos);
	void __fastcall TranscendentalBlow(int pPacket, int pPos);


	//2nd job skills vagabond
	void __fastcall BrutalAttack(int pPacket, int pPos);
	void __fastcall HalfSwing(int pPacket, int pPos);
	void __fastcall PowerfulUpwardSlash(int pPacket, int pPos);
	void __fastcall PowerfulWideningWound(int pPacket, int pPos);


	//2nd job skills commander
	void __fastcall Sacrifice(int pPacket, int pPos);
	void __fastcall Calls(int pPacket, int pPos,int SkillID);


	//3rd job god of sword
	void __fastcall SpinSlash();
	void __fastcall SwordDance(int pPacket, int pPos);
	void __fastcall ContinueSwordDance();

	//3rd job general
	void __fastcall ProvocationOfBlow(int pPacket, int pPos);


	//4th job god of sword
	void __fastcall ShoutOfDefense();
	void __fastcall ShoutOfFightingSpirit();
	
	//4th job general
	void __fastcall TheWaveOfEarth();
	void __fastcall TheBoomOfEarth();



};

#endif