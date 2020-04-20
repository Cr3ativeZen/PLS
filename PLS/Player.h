#ifndef _PLAYER_H
#define _PLAYER_H
#include "D4Instance.h"
#include "WhirlwindFeather.h"
#include "EggThunderbolt.h"
#include "RevolveAttack.h"
#include "BloodSuction.h"
#include "Packet.h"
int __fastcall Tick(void *Player, void *edx)
{
	ICharacter IPlayer(Player);



	//if (IsOnline() && GetClass() == 0 && GetSpecialty() == 23)
	//{
	//	SpinSlash(IPlayer);
	//	IncreaseMana(700);
	//	IncreaseHp(30000);
	//}





	if (IsOnline() && CheckShiny.count((int)GetOffset()) && CheckShiny.find((int)GetOffset())->second.Target && IsBuff(307) && LightningArrowON == true)
	{
		ICharacter Caster(CheckShiny.find((int)GetOffset())->second.Target);

		if (!Caster.IsOnline())
		{
			CancelBuff(307);
			CheckShiny[(int)GetOffset()].Target = 0;
		}

		if (!IsValid())
		{
			CancelBuff(307);
			CheckShiny[(int)GetOffset()].Target = 0;
		}
	}



	//if (IsOnline() && CChar::IsGState((int)GetOffset(), 2) && (GetTickCount() / 1000) % 5 == 0 && IsBuff(199))
	//{
	//	Revive();
	//	SetBlue();
	//}

	//if (IsOnline() && CChar::IsGState((int)GetOffset(), 2) && (GetTickCount() / 1000) % 5 == 0 && IsBuff(198))
	//{
	//	Revive();
	//	SetRed();
	//}

	if (IsOnline() && !IsBuff(70) && IsBuff(550))
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 550);

		RemoveEva(*(DWORD*)(Buff + 12));

		CancelBuff(70);
		CancelBuff(550);
	}

	if (IsOnline() && !IsBuff(74) && IsBuff(560))
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 560);

		RemoveMinAttack(*(DWORD*)(Buff + 12));
		RemoveMaxAttack(*(DWORD*)(Buff + 12));

		CancelBuff(74);
		CancelBuff(560);
	}




	if (IsOnline() && !IsBuff(10) && IsBuff(500) && IsBuff(501))
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 500);
		int Buff2 = CChar::FindBuff((int)GetOffset(), 501);

		RemoveMinPhysAttack(*(DWORD*)(Buff + 12));
		RemoveMaxPhysAttack(*(DWORD*)(Buff2 + 12));

		CancelBuff(10);
		CancelBuff(500);
		CancelBuff(501);
	}


	//for (bufx = Buffs.begin(); bufx != Buffs.end(); ++bufx)
	//{
	//	if (!IsBuff(bufx->second.BuffIndex) &&IsBuff(bufx->second.SecondBuffIndex))
	//	{
	//		int Buff = CChar::FindBuff((int)GetOffset(), bufx->second.BuffIndex);
	//		int ItemID = bufx->first;

	//		if (Buffs[ItemID].PhysAttack)
	//		{
	//			RemoveMinPhysAttack(*(DWORD*)(Buff + 12));
	//			RemoveMaxPhysAttack(*(DWORD*)(Buff + 16));
	//		}
	//		else if (Buffs[ItemID].MagicAttack)
	//		{
	//			RemoveMinMagicAttack((*(DWORD*)(Buff + 12)));
	//			RemoveMaxMagicAttack((*(DWORD*)(Buff + 16)));
	//		}

	//		if (Buffs[ItemID].IconKey != 0)
	//		{
	//			RemoveBuffIcon(0, 0, 0, Buffs[ItemID].IconKey);
	//		}
	//		if (Buffs[ItemID].Strength)
	//		{
	//			RemoveStr(Buffs[ItemID].Strength);
	//		}
	//		if (Buffs[ItemID].Health)
	//		{
	//			RemoveHp(Buffs[ItemID].Health);
	//		}
	//		if (Buffs[ItemID].Int)
	//		{
	//			RemoveInt(Buffs[ItemID].Int);
	//		}
	//		if (Buffs[ItemID].Wisdom)
	//		{
	//			RemoveWis(Buffs[ItemID].Wisdom);
	//		}
	//		if (Buffs[ItemID].Agility)
	//		{
	//			RemoveAgi(Buffs[ItemID].Agility);
	//		}

	//		if (Buffs[ItemID].OTP)
	//		{
	//			RemoveOTP(Buffs[ItemID].OTP);
	//		}

	//		if (Buffs[ItemID].Evasion)
	//		{
	//			RemoveEva(Buffs[ItemID].Evasion);
	//		}

	//		if (Buffs[ItemID].DEF)
	//		{
	//			RemoveDef(Buffs[ItemID].DEF);
	//		}

	//		if (Buffs[ItemID].HP)
	//		{
	//			DecreaseMaxHp(Buffs[ItemID].HP);
	//		}

	//		if (Buffs[ItemID].MP)
	//		{
	//			DecreaseMaxMp(Buffs[ItemID].MP);
	//		}
	//		CancelBuff(bufx->second.SecondBuffIndex);
	//		CancelBuff(bufx->second.BuffIndex);
	//		SystemMessage("Buff cancelled", TEXTCOLOR_RED);
	//		break;
	//	}
	//}


	//if (IsOnline() &&!IsBuff(505)&&IsBuff(506))
	//{
	//	int Buff = CChar::FindBuff((int)GetOffset(), 505);
	//	AddEva(*(DWORD*)(Buff + 12));
	//	NewAnnouncement("REEEEE");
	//}
	//if (GetMobIndex() == 667 && !IsBuff(781))
	//{
	//	Buff(781, 20, 0);
	//	int Around = GetObjectListAround(3);
	//	while (Around)
	//	{
	//		OktayDamageArea(IPlayer, 2000, 145);
	//		_ShowBattleAnimation(IPlayer, 145);
	//		Around = CBaseList::Pop((void*)Around);
	//	}



	if (IsBuff(790))
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 790);
		if (GetCurHp() > 1000 && !(CChar::IsGState((int)GetOffset(), 2)))
		{
			DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	if (IsBuff(791))
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 791);
		if (GetCurHp() > 200 && !(CChar::IsGState((int)GetOffset(), 2)))
		{
			DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	if (IsOnline() && !IsBuff(4877) && IsBuff(4878))
	{
		CancelBuff(4878);
		RemoveBuffIcon(0, 0, 2427, 323);
	}

	if (IsOnline() && !IsBuff(4848) && IsBuff(4849))
	{
		CancelBuff(4849);
		RemoveBuffIcon(0, 0, 2019, 217);
	}

	//i changed it here
	if (IsBuff(LawlessZone::BuffID) && LawlessZoneON == true)
	{
		if (IsOnline() && IsBuff(LawlessZone::BuffID))
		{
			if (!IsBuff(LawlessZone::ExpBuffID[0]) && LawlessZone::PointCounter[GetPID()] >= 0 && LawlessZone::PointCounter[GetPID()] <= 1000)
			{
				Buff(LawlessZone::ExpBuffID[0], LawlessZone::Time + 1, 10);
				SetBuffIcon(-2, -1, 4500, 1500);

			}

			if (!IsBuff(LawlessZone::ExpBuffID[1]) && LawlessZone::PointCounter[GetPID()] >= 1001 && LawlessZone::PointCounter[GetPID()] <= 2000)
			{
				RemoveBuffIcon(0, 0, 4500, 1500);
				CancelBuff(LawlessZone::ExpBuffID[0]);
				Buff(LawlessZone::ExpBuffID[1], LawlessZone::Time + 1, 20);
				SetBuffIcon(-2, -1, 4501, 1501);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[2]) && LawlessZone::PointCounter[GetPID()] >= 2001 && LawlessZone::PointCounter[GetPID()] <= 3000)
			{
				RemoveBuffIcon(0, 0, 4501, 1501);
				CancelBuff(LawlessZone::ExpBuffID[1]);
				Buff(LawlessZone::ExpBuffID[2], LawlessZone::Time + 1, 30);
				SetBuffIcon(-2, -1, 4502, 1502);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[3]) && LawlessZone::PointCounter[GetPID()] >= 3001 && LawlessZone::PointCounter[GetPID()] <= 4000)
			{
				RemoveBuffIcon(0, 0, 4502, 1502);
				CancelBuff(LawlessZone::ExpBuffID[2]);
				Buff(LawlessZone::ExpBuffID[3], LawlessZone::Time + 1, 40);
				SetBuffIcon(-2, -1, 4503, 1503);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[4]) && LawlessZone::PointCounter[GetPID()] >= 4001 && LawlessZone::PointCounter[GetPID()] <= 5000)
			{
				RemoveBuffIcon(0, 0, 4503, 1503);
				CancelBuff(LawlessZone::ExpBuffID[3]);
				Buff(LawlessZone::ExpBuffID[4], LawlessZone::Time + 1, 50);
				SetBuffIcon(-2, -1, 4504, 1504);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[5]) && LawlessZone::PointCounter[GetPID()] >= 5001 && LawlessZone::PointCounter[GetPID()] <= 6000)
			{
				RemoveBuffIcon(0, 0, 4504, 1504);
				CancelBuff(LawlessZone::ExpBuffID[4]);
				Buff(LawlessZone::ExpBuffID[5], LawlessZone::Time + 1, 60);
				SetBuffIcon(-2, -1, 4505, 1505);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[6]) && LawlessZone::PointCounter[GetPID()] >= 6001 && LawlessZone::PointCounter[GetPID()] <= 7000)
			{
				RemoveBuffIcon(0, 0, 4505, 1505);
				CancelBuff(LawlessZone::ExpBuffID[5]);
				Buff(LawlessZone::ExpBuffID[6], LawlessZone::Time + 1, 70);
				SetBuffIcon(-2, -1, 4506, 1506);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[7]) && LawlessZone::PointCounter[GetPID()] >= 7001 && LawlessZone::PointCounter[GetPID()] <= 8000)
			{
				RemoveBuffIcon(0, 0, 4506, 1506);
				CancelBuff(LawlessZone::ExpBuffID[6]);
				Buff(LawlessZone::ExpBuffID[7], LawlessZone::Time + 1, 80);
				SetBuffIcon(-2, -1, 4507, 1507);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[8]) && LawlessZone::PointCounter[GetPID()] >= 8001 && LawlessZone::PointCounter[GetPID()] <= 9000)
			{
				RemoveBuffIcon(0, 0, 4507, 1507);
				CancelBuff(LawlessZone::ExpBuffID[7]);
				Buff(LawlessZone::ExpBuffID[8], LawlessZone::Time + 1, 90);
				SetBuffIcon(-2, -1, 4508, 1508);
			}

			if (!IsBuff(LawlessZone::ExpBuffID[9]) && LawlessZone::PointCounter[GetPID()] >= 9001)
			{
				RemoveBuffIcon(0, 0, 4508, 1508);
				CancelBuff(LawlessZone::ExpBuffID[8]);
				Buff(LawlessZone::ExpBuffID[9], LawlessZone::Time + 1, 100);
				SetBuffIcon(-2, -1, 4509, 1509);
			}
		}

		if (IsOnline() && IsBuff(LawlessZone::BuffID) && !IsBuff(104))
		{
			Buff(104, LawlessZone::Time, 0);
		}

		if (IsOnline() && IsBuff(LawlessZone::BuffID) && GetMap() != LawlessZone::Map)
		{
			Teleport(LawlessZone::Map, LawlessZone::StartTeleportX, LawlessZone::StartTeleportY);
		}

		
	}

	if (LawlessZoneON == true && IsOnline() && !IsBuff(LawlessZone::BuffID) && GetMap() == LawlessZone::Map)
	{
		Teleport(0, LawlessZone::ReturnTeleportX, LawlessZone::ReturnTeleportY);
		if (IsBuff(104))
		{
			CancelBuff(104);
		}

		for (int i = 0; i < 10; i++)
		{
			if (IsBuff(LawlessZone::ExpBuffID[i]))
			{
				CancelBuff(LawlessZone::ExpBuffID[i]);
				RemoveBuffIcon(0, 0, 4500 + i, 1500 + i);
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------
	//for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
	//{
	//	if (IsOnline() && !IsBuff(104) && CPlayer::FindItem(GetOffset(), TradeSystem::it->second.first, 1) && CChar::IsGState((int)GetOffset(), 2))
	//	{
	//		Buff(222, 3600, 0);
	//		CancelBuff(477);
	//		std::string rip = "The trader ";
	//		rip = rip + GetName();
	//		rip = rip + " is dead!";
	//		CPlayer::WriteAll(0xFF, "dsd", 247, rip, 2);
	//		//CPlayer::DropItem((int)GetOffset(), (char)9, TradeSystem::ItemID);
	//		//while (CPlayer::FindItem(GetOffset(), TradeSystem::it->second.first,1))
	//		//{
	//		//	CPlayer::RemoveItem(GetOffset(), 9, TradeSystem::it->second.first, 1);
	//		//	Summon((int)GetOffset(), GetMap(), GetX(), GetY(), TradeSystem::it->second.second, 1, 1, 0, 3600, 0);
	//		//}
	//	}
	//}

	if (TradeSystemON == true)
	{
		for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
		{
			if (IsOnline() && CPlayer::FindItem(GetOffset(), TradeSystem::it->second, 1) && !IsBuff(477))
			{
				std::string deli = "The player: ";
				std::string trader = GetName();
				deli = deli + trader;
				deli = deli + " is new trader! Kill him!";
				CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
				Buff(104, 3600, 0);
				Buff(477, 3610, 0);
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------------


	if (IsOnline() &&!IsBuff(4001) && IsBuff(4002))
	{
		CancelBuff(4002);
		ChatCommand((int)GetOffset(), 0, "/suicide");
		RemoveBuffIcon(0, 0, 0, 225);
	}


	//assasin off
	if (IsBuff(104) && IsBuff(254)&&GetMap()==Mautareta::Map&& MautaretaON == true)
	{
		CancelBuff(104);
	}

	//if player is on mautareta map w/o buff 254
	if (IsOnline() && GetMap() == Mautareta::Map && !IsBuff(254) && MautaretaON == true)
	{
		Teleport(0, Mautareta::ReturnTeleportX, Mautareta::ReturnTeleportY);
	}

	//if mautareta is done it cancels the buff and then ^ tps back to town
	if (IsOnline() && IsBuff(254) && GetMap() == Mautareta::Map &&Mautareta::IsUp==false && MautaretaON == true)
	{
		CancelBuff(254);
		CloseScreenTime();
	}

	//if some1 tps out of mautareta  it teleports him back
	if (IsOnline() && IsBuff(254) && GetMap() != Mautareta::Map&& MautaretaON == true)
	{
		Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
	}

	//if time runs out
	if (IsOnline() && !IsBuff(254) && Mautareta::IsUp == true &&GetMap()==Mautareta::Map&& MautaretaON == true)
	{
		CPlayer::WriteInMap(Mautareta::Map, 0xFF, "dsd", 247, "RAID FAILED!", 1);
		CancelBuff(254);
		Mautareta::IsUp = false;
	}

	if (IsBuff(4003) && MautaretaON == true)
	{
		if (GetBuffRemain(4003)<0)
		{
			RemoveBuffIcon(0, 0, 0, 224);
		}
		int Buff = CChar::FindBuff((int)GetOffset(), 4003);
		if (GetCurHp() > 1000 && !(CChar::IsGState((int)GetOffset(), 2)))
		{
			DecreaseHp(*(DWORD*)(Buff + 12));
		}
	}

	if (IsOnline()&&IsBuff(790)&&IsBuff(254))
	{
		SendGStateEx(GetGStateEx() + 4096);
	}

	if (IsOnline()&&IsBuff(4001))
	{
		SendGStateEx(GetGStateEx() + 16384);
	}


	
	if (IsOnline()&&IsBuff(5556) && GetClass() == 1 && IcicleON==true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueIcicle(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5557)&& GetClass() == 1 &&FlameInjectionON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFlameInjection(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5558) && GetClass() == 1 && ThunderStormON == true)
	{
		if (CheckContinueThunderStorm[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueThunderStorm(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5559) && GetClass() == 1 && IceStormON == true)
	{
		if (CheckContinueIceStorm[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueIceStorm(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5560) && GetClass() == 1 &&FireStormON == true)
	{
		if (CheckContinueFireStorm[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFireStorm(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5565) && GetClass() == 2 &&ArrowRainON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueArrowRain(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5566) && GetClass() == 2 && ArrowExplosionON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueArrowExplosion(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5575) && GetClass() == 3 &&SpinBladeON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueSpinBlade(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5576) && GetClass() == 3 &&FatalWoundON == true)
	{
		if (CheckFarContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFatalWound(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5577) && GetClass() == 3 && RuptureON == true)
	{
		if (CheckRuptureContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueRupture(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5578) && GetClass() == 3 && TwinBladeStrikeON == true)
	{
		if (CheckFarContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueTwinBladeStrike(IPlayer);
		}
	}


	if (IsOnline() && IsBuff(5579) && GetClass() == 3 &&LightningSlashThiefON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueLightningSlash(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5585) && GetClass() == 0 &&SwordDanceON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueSwordDance(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5595) && WhirlwindFeatherON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueWhirlwindFeather(IPlayer);
		}
	}

	if (IsOnline() && IsBuff(5596) && EggThunderboltON == true)
	{
		if (CheckContinueSkill[GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueEggThunderbolt(IPlayer);
		}
	}

	//if (IsOnline() && IsBuff(295))
	//{
	//	for (int i = 0; i < 6; i++)
	//	{
	//		CancelBuff(290 + i);
	//	}
	//}



//evasion off
	if (IsOnline() && IsParty()&&IsBuff(550)&&IsBuff(70))
	{
		void* CasterOffset = CallOfEvasionOTP[GetPID()].CasterOffset;
		ICharacter Caster(CasterOffset);
		if (GetPartyID() != Caster.GetPartyID() || !IsInRange(Caster, CallRANGE) && GetOffset() != Caster.GetOffset())
		{
			int Buff = CChar::FindBuff((int)GetOffset(), 550);

			RemoveEva(*(DWORD*)(Buff + 12));

			CancelBuff(70);
			CancelBuff(550);
		}
		

	}
//evasion on
	if (IsOnline() && IsParty() && !IsBuff(550)&&CallOfEvasionOTP[GetPID()].SkillID == 27)
	{
		void* CasterOffset = CallOfEvasionOTP[GetPID()].CasterOffset;
		ICharacter Caster(CasterOffset);

		if (GetPartyID() == Caster.GetPartyID() && GetOffset() != Caster.GetOffset())
		{
			if (IsInRange(Caster, CallRANGE))
			{
				ISkill ISkill((void*)Caster.GetSkillPointer(27));
				Buff(70, 0, 0);
				Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
				AddEva((ISkill.GetGrade() - 1) * 5 + 10);
			}
		}
	}

//Copa off
if (IsOnline() && IsParty() && IsBuff(560) &&IsBuff(74))
{
	void* CasterOffset = CallOfPhysicalAttack[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() != Caster.GetPartyID() || !IsInRange(Caster, CallRANGE) && GetOffset() != Caster.GetOffset())
	{
		int Buff = CChar::FindBuff((int)GetOffset(), 560);

		RemoveMinAttack(*(DWORD*)(Buff + 12));
		RemoveMaxAttack(*(DWORD*)(Buff + 12));

		CancelBuff(74);
		CancelBuff(560);

	}
}

//Copa on
if (IsOnline() && IsParty() && !IsBuff(560))
{
	void* CasterOffset = CallOfPhysicalAttack[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() == Caster.GetPartyID() && GetOffset() != Caster.GetOffset())
	{
		if (IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(32));

			AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
			AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

			Buff(74, 0, 0);
			Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
		}
	}
}
//otp off
if (IsOnline() && IsParty() && IsBuff(73))
{

	void* CasterOffset = CallOfEvasionOTP[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() != Caster.GetPartyID() || !IsInRange(Caster, CallRANGE) && GetOffset() != Caster.GetOffset())
	{
		CancelBuff(73);

	}
}

//otp on
if (IsOnline() && IsParty() && !IsBuff(73)&& CallOfEvasionOTP[GetPID()].SkillID == 31)
{

	void* CasterOffset = CallOfEvasionOTP[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() == Caster.GetPartyID() && GetOffset() != Caster.GetOffset())
	{
		if (IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(31));
			Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
		}
	}
}


//cor off
if (IsOnline() && IsParty() && IsBuff(38))
{
	void* CasterOffset = CallOfRecovery[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() != Caster.GetPartyID() || !IsInRange(Caster, CallRANGE) && GetOffset() != Caster.GetOffset())
	{
		CancelBuff(38);

	}
}

//cor on
if (IsOnline() && IsParty() && !IsBuff(38))
{
	void* CasterOffset = CallOfRecovery[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() == Caster.GetPartyID() && GetOffset() != Caster.GetOffset())
	{
		if (IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(23));
			if (GetSpecialty() == 23 && GetClass() == 1)
			{
				Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
			}
			else
			{
				Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
			}
		}
	}
}

//codoff
if (IsOnline() && IsParty() && IsBuff(28))
{
	void* CasterOffset = CallOfDefense[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);

	if (GetPartyID() != Caster.GetPartyID() || !IsInRange(Caster, CallRANGE) && GetOffset() != Caster.GetOffset())
	{
		CancelBuff(28);
	}
}

//cod on
if (IsOnline() && IsParty() && !IsBuff(28))
{
	void* CasterOffset = CallOfDefense[GetPID()].CasterOffset;
	ICharacter Caster(CasterOffset);
	int Check = 0;
	void* pSkill=(void*)Caster.GetSkillPointer(19);

	if (GetPartyID() == Caster.GetPartyID()&&GetOffset()!=Caster.GetOffset())
	{
		if (IsInRange(Caster, CallRANGE))
		{
			Check = (*(int(__thiscall **)(void *, int))(*(DWORD*)pSkill + 80))(pSkill, (int)Caster.GetOffset());
			int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
			(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)GetOffset() + 180))((DWORD)GetOffset(), Buff);
		}
	}
}


	if (D4InstanceON == true)
	{
		DFourInstance(IPlayer);
	}



	if (Logs == true)
	{
		if (IsOnline() && SpeedHackCheck == true && !IsBuff(347) && !IsBuff(349) && !IsBuff(40) && !IsBuff(82) && ((GetMoveSpeed() <= 110 && CChar::IsGState((int)GetOffset(), 512)) || (!CChar::IsGState((int)GetOffset(), 512) && GetMoveSpeed() <= 75)))
		{

			PlayerCoords[GetPID()].average_speed = static_cast<int>(sqrt(pow((PlayerCoords[GetPID()].x - GetX()), 2) + pow((PlayerCoords[GetPID()].y - GetY()), 2)) * 100);

			PlayerCoords[GetPID()].x = GetX();
			PlayerCoords[GetPID()].y = GetY();

			//SystemMessage(Int2String(PlayerCoords[GetPID()].average_speed), TEXTCOLOR_RED);




			if (PlayerCoords[GetPID()].average_speed >= 11000)
			{
				PlayerCoords[GetPID()].current_check++;

				if (PlayerCoords[GetPID()].current_check > 12)
				{
					time_t now = time(0);
					//char* dt = ctime(&now);
					char dt;
					ctime_s(&dt, 1, &now);

					std::string to_file = "------|Name: ";
					to_file += GetName();
					to_file += "------|PID: ";
					to_file += Int2String(GetPID());
					to_file += +"-------";
					to_file += dt;
					WritePacketToFile(IPlayer, SpeedHack, to_file);

					PlayerCoords[GetPID()].current_check = 0;
				}

			}
			else
			{
				PlayerCoords[GetPID()].current_check = 0;
			}
		}


		if (SpeedHackCheck == true && IsBuff(347) && IsBuff(349) && !IsBuff(40) && !IsBuff(82))
		{
			PlayerCoords[GetPID()].average_speed = static_cast<int>(sqrt(pow((PlayerCoords[GetPID()].x - GetX()), 2) + pow((PlayerCoords[GetPID()].y - GetY()), 2)) * 100);

			PlayerCoords[GetPID()].x = GetX();
			PlayerCoords[GetPID()].y = GetY();

			//SystemMessage(Int2String(PlayerCoords[GetPID()].average_speed), TEXTCOLOR_RED);



			if (PlayerCoords[GetPID()].average_speed >= 18300)
			{
				PlayerCoords[GetPID()].current_check++;
				if (PlayerCoords[GetPID()].current_check > 12)
				{
					time_t now = time(0);
					//char* dt = ctime(&now);
					char dt;
					ctime_s(&dt, 1, &now);

					std::string to_file = "ON MOUNT!------|Name: ";
					to_file += GetName();
					to_file += "------|PID: ";
					to_file += Int2String(GetPID());
					to_file += +" -------";
					to_file += dt;
					WritePacketToFile(IPlayer, SpeedHack, to_file);

					PlayerCoords[GetPID()].current_check = 0;
				}

			}
			else
			{
				PlayerCoords[GetPID()].current_check = 0;
			}
		}
	}

	return CPlayer::Tick(Player);
}
#endif