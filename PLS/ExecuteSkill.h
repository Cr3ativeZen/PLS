//#include "BlowUpArrow.h"
//#include "Calls.h"
//#include "MuscleSolidation.h"
//#include "Sacrifice.h"
//#include "Amnesia.h"
//#include "ShockWave.h"
//#include "FocusShot.h"
//#include "MysteriousArrow.h"
//#include "PassiveAttack.h"
//#include "FlamyArrow.h"
//#include "Summons.h"
//#include "ShieldAttack.h"
//#include "LightningSlash.h"
//#include "TranscendentalBlow.h"
//#include "Purification.h"
//#include "BuffRemover.h"
//#include "ShadowSlash.h"
//#include "ArrowRain.h"
//#include "CombativeSpirit.h"
//#include "ArrowExplosion.h"
//#include "VirulentArrow.h"
//#include "LightningSlashThief.h"
//#include "SpinBlade.h"
//#include "WrathOfHeaven.h"
//#include "SpinSlash.h"
//#include "SwordDance.h"
//#include "ProvocationOfBlow.h"
//#include "TherapeuticTouch.h"
//#include "Icicle.h"
//#include "FlameInjection.h"
//#include "Thunderbolt.h"
//#include "IceArrow.h"
//#include "Fireball.h"
//#include "LightningArrow.h"
//#include "SpinAttack.h"
//#include "ArmorBreaker.h"
//#include "TwinBladeStrike.h"
//#include "AnkleAmputate.h"
//#include "FatalWound.h"
//#include "FinalBlow.h"
//#include "SuicidalBlow.h"
//#include "Rupture.h"
//#include "VitalStrike.h"
//#include "PowerfulUpwardSlash.h"
//#include "BrutalAttack.h"
//#include "HalfSwing.h"
//#include "LifeAbsorption.h"
//#include "ChainLightning.h"
//#include "ThunderStorm.h"
//#include "IceStorm.h"
//#include "FireStorm.h"
//#include "ArrowsoftheMaster.h"
//#include "OneHitStrike.h"
//#include "MassiveFire.h"
//#include "SpiritOfTheArrows.h"
//#include "TheBoomofEarth.h"
//#include "ThewaveofEarth.h"
//#include "ShoutOfDefense.h"
//#include "ShoutOfFightingSpirit.h"
//#include "ReleasingTheEnergy.h"
//#include "Punishment.h"
//#include "Bombing.h"
//#include "Incapacitation.h"
//#include "CriticalDiffusion.h"
//#include "CriticalStrike.h"
//#include "StrikeOfGod.h"
//#include "DestroyingArmor.h"
//#include "SoulDestruction.h"
//#include "PowerfulWideningWound.h"
#include "Resources.h"
#include "CKnight.h"
#include "CMage.h"
#include "CArcher.h"
#include "CThief.h"





//void __fastcall ExecuteSkill(void* pSkill, void* edx, signed int SkillID, int PACKET, int pPos)
//{
//	if (SkillID > 100)
//		return;
//
//	if (SkillID == 88) SkillID = 95;
//	ISkill Skill(pSkill);
//	ICharacter IPlayer(Skill.GetPlayer());
//	int SkillPointerCheck = IPlayer.GetSkillPointer(SkillID);
//
//
//
//	switch (IPlayer.GetClass())
//	{
//	case CLASS_KNIGHT:
//	{
//		CKnight knight((void*)Skill.GetPlayer());
//		switch (SkillID)
//		{
//		case SKILL_KNIGHT_POWERFULUPWARDSLASH:
//		{
//			knight.PowerfulUpwardSlash(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_SPINSLASH:
//		{
//			knight.SpinSlash();
//			return;
//		}
//		case SKILL_KNIGHT_HALFSWING:
//		{
//			knight.HalfSwing(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_BRUTALATTACK:
//		{
//			knight.BrutalAttack(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_LIGHTNINGSLASH:
//		{
//			knight.LightningSlash(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_POWERFULWIDENINGWOUND:
//		{
//			knight.PowerfulWideningWound(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_PROVOCATIONOFBLOW:
//		{
//			knight.ProvocationOfBlow(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_SACRIFICE:
//		{
//			knight.Sacrifice(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_SHIELDATTACK:
//		{
//			knight.ShieldAttack(PACKET, pPos);
//			return;
//		}
//		case SKILL_KNIGHT_SHOUTOFDEFENSE:
//		{
//			knight.ShoutOfDefense();
//			return;
//		}
//		case SKILL_KNIGHT_SHOUTOFFIGHTINGSPIRIT:
//		{
//			knight.ShoutOfFightingSpirit();
//			return;
//		}
//		case SKILL_KNIGHT_THEWAVEOFEARTH:
//		{
//			knight.TheWaveOfEarth();
//			return;
//		}
//		case SKILL_KNIGHT_THEBOOMOFEARTH:
//		{
//			knight.TheBoomOfEarth();
//			return;
//		}
//		case SKILL_KNIGHT_TRANSCENDENTALBLOW:
//		{
//			knight.TranscendentalBlow(PACKET, pPos);
//			return;
//		}
//
//		}
//		break;
//	}
//
//	case CLASS_MAGE:
//	{
//		CMage mage((void*)Skill.GetPlayer());
//		switch (SkillID)
//		{
//		case SKILL_MAGE_CURE:
//		{
//			mage.Cure(PACKET, pPos);
//			return;
//		}
//		case SKILL_MAGE_CURE2:
//		{
//			mage.Cure2(PACKET, pPos);
//			return;
//		}
//		case SKILL_MAGE_CURE3:
//		{
//			mage.Cure3(PACKET, pPos);
//			return;
//		}
//		case SKILL_MAGE_HEAL:
//		{
//			mage.Heal();
//			return;
//		}
//		case SKILL_MAGE_CHAINLIGHTNING:
//		{
//			mage.ChainLightning(PACKET, pPos);
//			return;
//		}
//		case SKILL_MAGE_AMNESIA:
//		{
//			mage.Amnesia(PACKET, pPos);
//			return;
//		}
//		case SKILL_MAGE_SOULDESTRUCTION:
//		{
//			mage.SoulDestruction(PACKET, pPos);
//			return;
//		}
//		}
//		break;
//	}
//	case CLASS_ARCHER:
//	{
//		CArcher archer((void*)Skill.GetPlayer());
//		switch (SkillID)
//		{
//		case SKILL_ARCHER_BLOWUPARROW:
//		{
//			archer.BlowUpArrow(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_FLAMYARROW:
//		{
//			archer.FlamyArrow(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_MUSCLESOLIDATION:
//		{
//			archer.MuscleSolidation();
//			return;
//		}
//		case SKILL_ARCHER_PASSIVEATTACK:
//		{
//			archer.PassiveAttack(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_FOCUSSHOT:
//		{
//			archer.FocusShot(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_LIFEABSORPTION:
//		{
//			archer.LifeAbsorption(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_MYSTERIOUSARROW:
//		{
//			archer.MysteriousArrow(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_ARROWEXPLOSION:
//		{
//			archer.ArrowExplosion(PACKET, pPos);
//			return;
//		}
//
//		case SKILL_ARCHER_ARROWRAIN:
//		{
//			archer.ArrowRain(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_VIRULENTARROW:
//		{
//			archer.VirulentArrow(PACKET, pPos);
//			return;
//		}
//		case SKILL_ARCHER_COMBATIVESPIRIT:
//		{
//			archer.CombativeSpirit(PACKET, pPos);
//			return;
//		}
//		}
//
//		break;
//	}
//	case CLASS_THIEF:
//	{
//		break;
//	}
//	default:
//		break;
//	}
//
//}
