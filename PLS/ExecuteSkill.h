#include "BlowUpArrow.h"
#include "Calls.h"
#include "MuscleSolidation.h"
#include "Sacrifice.h"
#include "Amnesia.h"
#include "ShockWave.h"
#include "FocusShot.h"
#include "MysteriousArrow.h"
#include "PassiveAttack.h"
#include "FlamyArrow.h"
#include "Summons.h"
#include "ShieldAttack.h"
#include "LightningSlash.h"
#include "TranscendentalBlow.h"
#include "Purification.h"
#include "BuffRemover.h"
#include "ShadowSlash.h"
#include "ArrowRain.h"
#include "CombativeSpirit.h"
#include "ArrowExplosion.h"
#include "VirulentArrow.h"
#include "LightningSlashThief.h"
#include "SpinBlade.h"
#include "WrathOfHeaven.h"
#include "SpinSlash.h"
#include "SwordDance.h"
#include "ProvocationOfBlow.h"
#include "TherapeuticTouch.h"
#include "Icicle.h"
#include "FlameInjection.h"
#include "Thunderbolt.h"
#include "IceArrow.h"
#include "Fireball.h"
#include "LightningArrow.h"
#include "SpinAttack.h"
#include "ArmorBreaker.h"
#include "TwinBladeStrike.h"
#include "AnkleAmputate.h"
#include "FatalWound.h"
#include "FinalBlow.h"
#include "SuicidalBlow.h"
#include "Rupture.h"
#include "VitalStrike.h"
#include "PowerfulUpwardSlash.h"
#include "BrutalAttack.h"
#include "HalfSwing.h"
#include "LifeAbsorption.h"
#include "ChainLightning.h"
#include "ThunderStorm.h"
#include "IceStorm.h"
#include "FireStorm.h"
#include "ArrowsoftheMaster.h"
#include "OneHitStrike.h"
#include "MassiveFire.h"
#include "SpiritOfTheArrows.h"
#include "TheBoomofEarth.h"
#include "ThewaveofEarth.h"
#include "ShoutOfDefense.h"
#include "ShoutOfFightingSpirit.h"
#include "ReleasingTheEnergy.h"
#include "Punishment.h"
#include "Bombing.h"
#include "Incapacitation.h"
#include "CriticalDiffusion.h"
#include "CriticalStrike.h"
#include "StrikeOfGod.h"
#include "DestroyingArmor.h"

void __fastcall ExecuteSkill(void *pSkill, void* edx, signed int SkillID, int pPacket, int pPos)
{
//
//
//
//
//	if (SkillID > 100)
//		return;
//
//	if (SkillID == 88) SkillID = 95;
//	ISkill Skill(pSkill);
//	IChar IPlayer(Skill.GetPlayer());
//	int SkillPointerCheck = IPlayer.GetSkillPointer(SkillID);
//
//
//	IPlayer.Buff(313, 3, 0);
//
//
//
//	//if (IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 && (SkillID == 4 || SkillID == 9 || SkillID == 23 || SkillID == 31 || SkillID == 41 || SkillID == 42 || SkillID == 75))
//	//	ActivateShiny(IPlayer, pPacket, pPos);
//
//
//	if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
//	{
//		if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
//			return;
//
//	}
//
//
//	if (IPlayer.GetClass() == 2 && SkillID == 47 && IPlayer.GetSpecialty() == 23)
//	{
//		ArrowRain(IPlayer, pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 51 && IPlayer.GetSpecialty() == 23)
//	{
//		CombativeSpirit(IPlayer, pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 49 && IPlayer.GetSpecialty() == 43)
//	{
//		ArrowExplosion(IPlayer, pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 50 && IPlayer.GetSpecialty() == 43)
//	{
//		VirulentArrow(IPlayer, pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 3 && SkillID == 33 && IPlayer.GetSpecialty() == 23)
//	{
//		WrathOfHeaven(IPlayer, pPacket, pPos);
//		return;
//	}
//
//if (IPlayer.GetClass() == 3 && SkillID == 36 && IPlayer.GetSpecialty() == 23)
//{
//	SpinBlade(IPlayer);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 32 && IPlayer.GetSpecialty() == 43)
//{
//	ShadowSlash(IPlayer,pPacket,pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 28 && IPlayer.GetSpecialty() == 43)
//{
//	LightningSlashThief(IPlayer,pPacket,pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 0 && SkillID == 38 && IPlayer.GetSpecialty() == 23)
//{
//	SpinSlash(IPlayer);
//	return;
//}
//
//if (IPlayer.GetClass() == 0 && SkillID == 43 && IPlayer.GetSpecialty() == 23)
//{
//	SwordDance(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 0 && SkillID == 42 && IPlayer.GetSpecialty() == 43)
//{
//	ProvocationOfBlow(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 72 && IPlayer.GetSpecialty() == 43)
//{
//	TherapeuticTouch(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 73 && IPlayer.GetSpecialty() == 23)
//{
//	Fireball(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 74 && IPlayer.GetSpecialty() == 23)
//{
//	IceArrow(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 75 && IPlayer.GetSpecialty() == 23)
//{
//	Thunderbolt(IPlayer, pPacket, pPos);
//	return;
//}
//
//
//		if (IPlayer.GetClass() == 1 && SkillID == 65 && IPlayer.GetSpecialty() == 23)
//		{
//			FlameInjection(IPlayer,pPacket,pPos);
//			return;
//		}
//
//		if (IPlayer.GetClass() == 1 && SkillID == 66 && IPlayer.GetSpecialty() == 23)
//		{
//			Icicle(IPlayer);
//			return;
//		}
//
//if (IPlayer.GetClass() == 1 && SkillID == 67 && IPlayer.GetSpecialty() == 23)
//{
//	LightningArrow(IPlayer,pPacket,pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 43)
//{
//	ThunderStorm(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 48)
//{
//	FireStorm(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 1 && SkillID == 45)
//{
//	IceStorm(IPlayer, pPacket, pPos);
//	return;
//}
//
///*if (IPlayer.GetClass() == 3 && SkillID == 13 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(333))
//{
//	int pSkill = IPlayer.GetSkillPointer(13);
//
//	if (pSkill)
//	{
//		ISkill xSkill((void*)pSkill);
//		int nSkillGrade = xSkill.GetGrade();
//		int nMana = nSkillGrade * 20 + 80;
//
//		if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
//		{
//			if (!IPlayer.IsBuff(333))
//				IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 1024);
//
//			IPlayer.Buff(333, nSkillGrade * 15, 0);
//			IPlayer.DecreaseMana(nMana);
//			IPlayer._ShowBattleAnimation(IPlayer, 13, nSkillGrade);
//		}
//	}
//
//	return;
//}*/
//
//if (IPlayer.GetClass() == 3 && SkillID == 19 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
//{
//	SpinAttack(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 22 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
//{
//	ArmorBreaker(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 23 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
//{
//	TwinBladeStrike(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 18 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	FinalBlow(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 21 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	SuicidalBlow(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 15 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	AnkleAmputate(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 16 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	VitalStrike(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 14 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	FatalWound(IPlayer, pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 3 && SkillID == 17 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
//{
//	Rupture(IPlayer, pPacket, pPos);
//	return;
//}
//
////if (IPlayer.GetClass() == 0 && SkillID == 16&& PowerfulUpwardSlashActive==true)
////{
////	PowerfulUpwardSlash((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
////	return;
////}
//
//if (IPlayer.GetClass() == 0 && SkillID == 17 && BrutalAttackActive == true)
//{
//	BrutalAttack((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 0 && SkillID == 25 && HalfSwingActive == true)
//{
//	HalfSwing((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//	return;
//}
//
//if (IPlayer.GetClass() == 2 && SkillID == 18)
//{
//	LifeAbsorption((void*)SkillPointerCheck,edx, IPlayer.GetOffset(), (char*)pPacket, (char*)pPos);
//	return;
//}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 16)
//	{
//
//		FocusShot((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//	
//
//
//
//
//	if (IPlayer.GetClass() == 2 && SkillID == 21 && MAActive ==true)
//	{
//		MysteriousArrow((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 6&&FAActive==true)
//	{
//		FlamyArrow((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 4 &&PassiveAttackActive==true)
//	{
//		PassiveAttack((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 14&&BlowUpActive==true)
//	{
//		BlowUpArrow((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 2 && SkillID == 10&&MuscleActive==true)
//	{
//		MuscleSolidation(SkillPointerCheck, pPacket, (int)IPlayer.GetOffset());
//		return;
//	}
//	if (IPlayer.GetClass() == 2&& SkillID == 45&&BuffRemoverActive==true)
//	{
//		BuffRemover(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 8&&HealActive==true)
//	{
//		Heal(SkillPointerCheck,pPacket, (int)IPlayer.GetOffset());
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 10&&CureActive==true)
//	{
//		Cure(SkillPointerCheck,edx,(int)IPlayer.GetOffset(),pPacket,pPos);
//		return;
//	}
//	
//	if (IPlayer.GetClass() == 1 && SkillID == 22&&Cure2Active==true)
//	{
//		Cure(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 35&&Cure3Active==true)
//	{
//		Cure(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 55)
//	{
//		Cure(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 29)
//	{
//		Cure(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 34&&SummonsActive==true)
//	{
//		Summons(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//
//	if (IPlayer.GetClass() == 1 && SkillID == 41)
//	{
//		ChainLightning((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 27 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//
//	if (IPlayer.GetClass() == 0 && SkillID == 31 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 23 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	//if (IPlayer.GetClass() == 0 && SkillID == 38 && CallsActive == true)
//	//{
//	//	Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//	//	return;
//	//}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 32 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 19 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 29 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 28 && CallsActive == true)
//	{
//		Calls((void*)SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 26&&SacrificeActive==true)
//	{
//		Sacrifice(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 15 && ShieldAttackActive == true)
//	{
//		ShieldAttack((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 3 && LightningSlashActive == true)
//	{
//		LightningSlash((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 0 && SkillID == 5 && TranscendentalBlowActive == true)
//	{
//		TranscendentalBlow((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//	if (IPlayer.GetClass() == 1 && SkillID == 9&& ShockWaveActive==true)
//	{
//		ShockWave((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 61 && AmnesiaActive == true)
//	{
//		Amnesia((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
//		return;
//	}
//
//	if (IPlayer.GetClass() == 1 && SkillID == 54 &&PurificationActive==true)
//	{
//		Purification(SkillPointerCheck, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
//	}
//
//
//	
//
//	CSkill::ExecuteSkill(pSkill, SkillID, pPacket, pPos);
}