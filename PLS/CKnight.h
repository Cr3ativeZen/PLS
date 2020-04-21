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

	//void __fastcall BrutalAttack(int pSkill, int pPacket, int pPos);
	//void __fastcall Calls(int pSkill, int pPacket, int pPos);
	//void __fastcall HalfSwing(int pSkill, int pPacket, int pPos);
	//void __fastcall LightningSlash(int pSkill, int pPacket, int pPos);
	void __fastcall PowerfulUpwardSlash(int pSkill, int pPacket, int pPos);
	//void __fastcall PowerfulWideningWound(int pSkill, int pPacket, int pPos);
	//void __fastcall ProvocationOfBlow(int pSkill, int pPacket, int pPos);
	//void __fastcall Sacrifice(int pSkill, int pPacket, int pPos);
	//void __fastcall ShieldAttack(int pSkill, int pPacket, int pPos);
	//void __fastcall ShoutOfDefense(int pSkill, int pPacket, int pPos);
	//void __fastcall ShoutOfFightingSpirit(int pSkill, int pPacket, int pPos);
	void __fastcall SpinSlash(int pSkill, int pPacket, int pPos);
	//void __fastcall SwordDance(int pSkill, int pPacket, int pPos);
	//void __fastcall TheWaveOfEarth(int pSkill, int pPacket, int pPos);
	//void __fastcall TheBoomOfEarth(int pSkill, int pPacket, int pPos);
	//void __fastcall TranscendentalBlow(int pSkill, int pPacket, int pPos);

};

#endif