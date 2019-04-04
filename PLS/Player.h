#ifndef _PLAYER_H
#define _PLAYER_H
#include "D4Instance.h"
#include "WhirlwindFeather.h"
#include "EggThunderbolt.h"
#include "RevolveAttack.h"
#include "BloodSuction.h"
int __fastcall Tick(void *Player, void *edx)
{
	IChar IPlayer(Player);



	if (IPlayer.IsOnline() && CheckShiny.count((int)IPlayer.GetOffset()) && CheckShiny.find((int)IPlayer.GetOffset())->second.Target && IPlayer.IsBuff(307) && LightningArrowON == true)
	{
		IChar Caster(CheckShiny.find((int)IPlayer.GetOffset())->second.Target);

		if (!Caster.IsOnline())
		{
			IPlayer.CancelBuff(307);
			CheckShiny[(int)IPlayer.GetOffset()].Target = 0;
		}

		if (!IPlayer.IsValid())
		{
			IPlayer.CancelBuff(307);
			CheckShiny[(int)IPlayer.GetOffset()].Target = 0;
		}
	}

	if (IPlayer.IsOnline() && CChar::IsGState((int)IPlayer.GetOffset(), 2) && (GetTickCount() / 1000) % 5 == 0 && IPlayer.IsBuff(199))
	{
		IPlayer.Revive();
		IPlayer.SetBlue();
	}

	if (IPlayer.IsOnline() && CChar::IsGState((int)IPlayer.GetOffset(), 2) && (GetTickCount() / 1000) % 5 == 0 && IPlayer.IsBuff(198))
	{
		IPlayer.Revive();
		IPlayer.SetRed();
	}

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(70) && IPlayer.IsBuff(550))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

		IPlayer.RemoveEva(*(DWORD*)(Buff + 12));

		IPlayer.CancelBuff(70);
		IPlayer.CancelBuff(550);
	}

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(74) && IPlayer.IsBuff(560))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

		IPlayer.RemoveMinAttack(*(DWORD*)(Buff + 12));
		IPlayer.RemoveMaxAttack(*(DWORD*)(Buff + 12));

		IPlayer.CancelBuff(74);
		IPlayer.CancelBuff(560);
	}




	if (IPlayer.IsOnline() && !IPlayer.IsBuff(10) && IPlayer.IsBuff(500) && IPlayer.IsBuff(501))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 500);
		int Buff2 = CChar::FindBuff((int)IPlayer.GetOffset(), 501);

		IPlayer.RemoveMinPhysAttack(*(DWORD*)(Buff + 12));
		IPlayer.RemoveMaxPhysAttack(*(DWORD*)(Buff2 + 12));

		IPlayer.CancelBuff(10);
		IPlayer.CancelBuff(500);
		IPlayer.CancelBuff(501);
	}


	for (bufx = Buffs.begin(); bufx != Buffs.end(); ++bufx)
	{
		if (!IPlayer.IsBuff(bufx->second.BuffIndex) &&IPlayer.IsBuff(bufx->second.SecondBuffIndex))
		{
			int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), bufx->second.BuffIndex);
			int ItemID = bufx->first;

			if (Buffs[ItemID].PhysAttack)
			{
				IPlayer.RemoveMinPhysAttack(*(DWORD*)(Buff + 12));
				IPlayer.RemoveMaxPhysAttack(*(DWORD*)(Buff + 16));
			}
			else if (Buffs[ItemID].MagicAttack)
			{
				IPlayer.RemoveMinMagicAttack((*(DWORD*)(Buff + 12)));
				IPlayer.RemoveMaxMagicAttack((*(DWORD*)(Buff + 16)));
			}

			if (Buffs[ItemID].IconKey != 0)
			{
				IPlayer.RemoveBuffIcon(0, 0, 0, Buffs[ItemID].IconKey);
			}
			if (Buffs[ItemID].Strength)
			{
				IPlayer.RemoveStr(Buffs[ItemID].Strength);
			}
			if (Buffs[ItemID].Health)
			{
				IPlayer.RemoveHp(Buffs[ItemID].Health);
			}
			if (Buffs[ItemID].Int)
			{
				IPlayer.RemoveInt(Buffs[ItemID].Int);
			}
			if (Buffs[ItemID].Wisdom)
			{
				IPlayer.RemoveWis(Buffs[ItemID].Wisdom);
			}
			if (Buffs[ItemID].Agility)
			{
				IPlayer.RemoveAgi(Buffs[ItemID].Agility);
			}

			if (Buffs[ItemID].OTP)
			{
				IPlayer.RemoveOTP(Buffs[ItemID].OTP);
			}

			if (Buffs[ItemID].Evasion)
			{
				IPlayer.RemoveEva(Buffs[ItemID].Evasion);
			}

			if (Buffs[ItemID].DEF)
			{
				IPlayer.RemoveDef(Buffs[ItemID].DEF);
			}

			if (Buffs[ItemID].HP)
			{
				IPlayer.DecreaseMaxHp(Buffs[ItemID].HP);
			}

			if (Buffs[ItemID].MP)
			{
				IPlayer.DecreaseMaxMp(Buffs[ItemID].MP);
			}
			IPlayer.CancelBuff(bufx->second.SecondBuffIndex);
			IPlayer.CancelBuff(bufx->second.BuffIndex);
			IPlayer.SystemMessage("Buff cancelled", TEXTCOLOR_RED);
			break;
		}
	}


	//if (IPlayer.IsOnline() &&!IPlayer.IsBuff(505)&&IPlayer.IsBuff(506))
	//{
	//	int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 505);
	//	IPlayer.AddEva(*(DWORD*)(Buff + 12));
	//	IPlayer.NewAnnouncement("REEEEE");
	//}
	//if (IPlayer.GetMobIndex() == 667 && !IPlayer.IsBuff(781))
	//{
	//	IPlayer.Buff(781, 20, 0);
	//	int Around = IPlayer.GetObjectListAround(3);
	//	while (Around)
	//	{
	//		IPlayer.OktayDamageArea(IPlayer, 2000, 145);
	//		IPlayer._ShowBattleAnimation(IPlayer, 145);
	//		Around = CBaseList::Pop((void*)Around);
	//	}



	if (IPlayer.IsBuff(790))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 790);
		if (IPlayer.GetCurHp() > 1000 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
		{
			IPlayer.DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	if (IPlayer.IsBuff(791))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 791);
		if (IPlayer.GetCurHp() > 200 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
		{
			IPlayer.DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(4877) && IPlayer.IsBuff(4878))
	{
		IPlayer.CancelBuff(4878);
		IPlayer.RemoveBuffIcon(0, 0, 2427, 323);
	}

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(4848) && IPlayer.IsBuff(4849))
	{
		IPlayer.CancelBuff(4849);
		IPlayer.RemoveBuffIcon(0, 0, 2019, 217);
	}

	//i changed it here
	if (IPlayer.IsBuff(LawlessZone::BuffID) && LawlessZoneON == true)
	{
		if (IPlayer.IsOnline() && IPlayer.IsBuff(LawlessZone::BuffID))
		{
			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[0]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 0 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 1000)
			{
				IPlayer.Buff(LawlessZone::ExpBuffID[0], LawlessZone::Time + 1, 10);
				IPlayer.SetBuffIcon(-2, -1, 4500, 1500);

			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[1]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 1001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 2000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4500, 1500);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[0]);
				IPlayer.Buff(LawlessZone::ExpBuffID[1], LawlessZone::Time + 1, 20);
				IPlayer.SetBuffIcon(-2, -1, 4501, 1501);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[2]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 2001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 3000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4501, 1501);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[1]);
				IPlayer.Buff(LawlessZone::ExpBuffID[2], LawlessZone::Time + 1, 30);
				IPlayer.SetBuffIcon(-2, -1, 4502, 1502);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[3]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 3001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 4000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4502, 1502);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[2]);
				IPlayer.Buff(LawlessZone::ExpBuffID[3], LawlessZone::Time + 1, 40);
				IPlayer.SetBuffIcon(-2, -1, 4503, 1503);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[4]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 4001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 5000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4503, 1503);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[3]);
				IPlayer.Buff(LawlessZone::ExpBuffID[4], LawlessZone::Time + 1, 50);
				IPlayer.SetBuffIcon(-2, -1, 4504, 1504);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[5]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 5001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 6000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4504, 1504);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[4]);
				IPlayer.Buff(LawlessZone::ExpBuffID[5], LawlessZone::Time + 1, 60);
				IPlayer.SetBuffIcon(-2, -1, 4505, 1505);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[6]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 6001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 7000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4505, 1505);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[5]);
				IPlayer.Buff(LawlessZone::ExpBuffID[6], LawlessZone::Time + 1, 70);
				IPlayer.SetBuffIcon(-2, -1, 4506, 1506);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[7]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 7001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 8000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4506, 1506);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[6]);
				IPlayer.Buff(LawlessZone::ExpBuffID[7], LawlessZone::Time + 1, 80);
				IPlayer.SetBuffIcon(-2, -1, 4507, 1507);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[8]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 8001 && LawlessZone::PointCounter[IPlayer.GetPID()] <= 9000)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4507, 1507);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[7]);
				IPlayer.Buff(LawlessZone::ExpBuffID[8], LawlessZone::Time + 1, 90);
				IPlayer.SetBuffIcon(-2, -1, 4508, 1508);
			}

			if (!IPlayer.IsBuff(LawlessZone::ExpBuffID[9]) && LawlessZone::PointCounter[IPlayer.GetPID()] >= 9001)
			{
				IPlayer.RemoveBuffIcon(0, 0, 4508, 1508);
				IPlayer.CancelBuff(LawlessZone::ExpBuffID[8]);
				IPlayer.Buff(LawlessZone::ExpBuffID[9], LawlessZone::Time + 1, 100);
				IPlayer.SetBuffIcon(-2, -1, 4509, 1509);
			}
		}

		if (IPlayer.IsOnline() && IPlayer.IsBuff(LawlessZone::BuffID) && !IPlayer.IsBuff(104))
		{
			IPlayer.Buff(104, LawlessZone::Time, 0);
		}

		if (IPlayer.IsOnline() && IPlayer.IsBuff(LawlessZone::BuffID) && IPlayer.GetMap() != LawlessZone::Map)
		{
			IPlayer.Teleport(LawlessZone::Map, LawlessZone::StartTeleportX, LawlessZone::StartTeleportY);
		}

		if (IPlayer.IsOnline() && !IPlayer.IsBuff(LawlessZone::BuffID) && IPlayer.GetMap() == LawlessZone::Map)
		{
			IPlayer.Teleport(0, LawlessZone::ReturnTeleportX, LawlessZone::ReturnTeleportY);
			if (IPlayer.IsBuff(104))
			{
				IPlayer.CancelBuff(104);
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------
	//for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
	//{
	//	if (IPlayer.IsOnline() && !IPlayer.IsBuff(104) && CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->second.first, 1) && CChar::IsGState((int)IPlayer.GetOffset(), 2))
	//	{
	//		IPlayer.Buff(222, 3600, 0);
	//		IPlayer.CancelBuff(477);
	//		std::string rip = "The trader ";
	//		rip = rip + IPlayer.GetName();
	//		rip = rip + " is dead!";
	//		CPlayer::WriteAll(0xFF, "dsd", 247, rip, 2);
	//		//CPlayer::DropItem((int)IPlayer.GetOffset(), (char)9, TradeSystem::ItemID);
	//		//while (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->second.first,1))
	//		//{
	//		//	CPlayer::RemoveItem(IPlayer.GetOffset(), 9, TradeSystem::it->second.first, 1);
	//		//	Summon((int)IPlayer.GetOffset(), IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), TradeSystem::it->second.second, 1, 1, 0, 3600, 0);
	//		//}
	//	}
	//}

	if (TradeSystemON == true)
	{
		for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
		{
			if (IPlayer.IsOnline() && CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->second, 1) && !IPlayer.IsBuff(477))
			{
				std::string deli = "The player: ";
				std::string trader = IPlayer.GetName();
				deli = deli + trader;
				deli = deli + " is new trader! Kill him!";
				CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
				IPlayer.Buff(104, 3600, 0);
				IPlayer.Buff(477, 3610, 0);
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------------


	if (IPlayer.IsOnline() &&!IPlayer.IsBuff(4001) && IPlayer.IsBuff(4002))
	{
		IPlayer.CancelBuff(4002);
		ChatCommand((int)IPlayer.GetOffset(), 0, "/suicide");
		IPlayer.RemoveBuffIcon(0, 0, 0, 225);
	}


	//assasin off
	if (IPlayer.IsBuff(104) && IPlayer.IsBuff(254)&&IPlayer.GetMap()==Mautareta::Map&& MautaretaON == true)
	{
		IPlayer.CancelBuff(104);
	}

	//if player is on mautareta map w/o buff 254
	if (IPlayer.IsOnline() && IPlayer.GetMap() == Mautareta::Map && !IPlayer.IsBuff(254) && MautaretaON == true)
	{
		IPlayer.Teleport(0, Mautareta::ReturnTeleportX, Mautareta::ReturnTeleportY);
	}

	//if mautareta is done it cancels the buff and then ^ tps back to town
	if (IPlayer.IsOnline() && IPlayer.IsBuff(254) && IPlayer.GetMap() == Mautareta::Map &&Mautareta::IsUp==false && MautaretaON == true)
	{
		IPlayer.CancelBuff(254);
		IPlayer.CloseScreenTime();
	}

	//if some1 tps out of mautareta  it teleports him back
	if (IPlayer.IsOnline() && IPlayer.IsBuff(254) && IPlayer.GetMap() != Mautareta::Map&& MautaretaON == true)
	{
		IPlayer.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
	}

	//if time runs out
	if (IPlayer.IsOnline() && !IPlayer.IsBuff(254) && Mautareta::IsUp == true &&IPlayer.GetMap()==Mautareta::Map&& MautaretaON == true)
	{
		CPlayer::WriteInMap(Mautareta::Map, 0xFF, "dsd", 247, "RAID FAILED!", 1);
		IPlayer.CancelBuff(254);
		Mautareta::IsUp = false;
	}

	if (IPlayer.IsBuff(4003) && MautaretaON == true)
	{
		if (IPlayer.GetBuffRemain(4003)<0)
		{
			IPlayer.RemoveBuffIcon(0, 0, 0, 224);
		}
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 4003);
		if (IPlayer.GetCurHp() > 1000 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
		{
			IPlayer.DecreaseHp(*(DWORD*)(Buff + 12));
		}
	}

	if (IPlayer.IsOnline()&&IPlayer.IsBuff(790)&&IPlayer.IsBuff(254))
	{
		IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 4096);
	}

	if (IPlayer.IsOnline()&&IPlayer.IsBuff(4001))
	{
		IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 16384);
	}


	
	if (IPlayer.IsOnline()&&IPlayer.IsBuff(5556) && IPlayer.GetClass() == 1 && IcicleON==true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueIcicle(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5557)&& IPlayer.GetClass() == 1 &&FlameInjectionON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFlameInjection(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5558) && IPlayer.GetClass() == 1 && ThunderStormON == true)
	{
		if (CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueThunderStorm(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5559) && IPlayer.GetClass() == 1 && IceStormON == true)
	{
		if (CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueIceStorm(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5560) && IPlayer.GetClass() == 1 &&FireStormON == true)
	{
		if (CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFireStorm(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5565) && IPlayer.GetClass() == 2 &&ArrowRainON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueArrowRain(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5566) && IPlayer.GetClass() == 2 && ArrowExplosionON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueArrowExplosion(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5575) && IPlayer.GetClass() == 3 &&SpinBladeON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueSpinBlade(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5576) && IPlayer.GetClass() == 3 &&FatalWoundON == true)
	{
		if (CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueFatalWound(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5577) && IPlayer.GetClass() == 3 && RuptureON == true)
	{
		if (CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueRupture(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5578) && IPlayer.GetClass() == 3 && TwinBladeStrikeON == true)
	{
		if (CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueTwinBladeStrike(IPlayer);
		}
	}


	if (IPlayer.IsOnline() && IPlayer.IsBuff(5579) && IPlayer.GetClass() == 3 &&LightningSlashThiefON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueLightningSlash(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5585) && IPlayer.GetClass() == 0 &&SwordDanceON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueSwordDance(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5595) && WhirlwindFeatherON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueWhirlwindFeather(IPlayer);
		}
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(5596) && EggThunderboltON == true)
	{
		if (CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay < GetTickCount())
		{
			ContinueEggThunderbolt(IPlayer);
		}
	}

	//if (IPlayer.IsOnline() && IPlayer.IsBuff(295))
	//{
	//	for (int i = 0; i < 6; i++)
	//	{
	//		IPlayer.CancelBuff(290 + i);
	//	}
	//}



//evasion off
	if (IPlayer.IsOnline() && IPlayer.IsParty()&&IPlayer.IsBuff(550)&&IPlayer.IsBuff(70))
	{
		void* CasterOffset = CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
		IChar Caster(CasterOffset);
		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
		{
			int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

			IPlayer.RemoveEva(*(DWORD*)(Buff + 12));

			IPlayer.CancelBuff(70);
			IPlayer.CancelBuff(550);
		}
		

	}
//evasion on
	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(550)&&CallOfEvasionOTP[IPlayer.GetPID()].SkillID == 27)
	{
		void* CasterOffset = CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
		IChar Caster(CasterOffset);

		if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
		{
			if (IPlayer.IsInRange(Caster, CallRANGE))
			{
				ISkill ISkill((void*)Caster.GetSkillPointer(27));
				IPlayer.Buff(70, 0, 0);
				IPlayer.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
				IPlayer.AddEva((ISkill.GetGrade() - 1) * 5 + 10);
			}
		}
	}

//Copa off
if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(560) &&IPlayer.IsBuff(74))
{
	void* CasterOffset = CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

		IPlayer.RemoveMinAttack(*(DWORD*)(Buff + 12));
		IPlayer.RemoveMaxAttack(*(DWORD*)(Buff + 12));

		IPlayer.CancelBuff(74);
		IPlayer.CancelBuff(560);

	}
}

//Copa on
if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(560))
{
	void* CasterOffset = CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
	{
		if (IPlayer.IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(32));

			IPlayer.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
			IPlayer.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

			IPlayer.Buff(74, 0, 0);
			IPlayer.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
		}
	}
}
//otp off
if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(73))
{

	void* CasterOffset = CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
	{
		IPlayer.CancelBuff(73);

	}
}

//otp on
if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(73)&& CallOfEvasionOTP[IPlayer.GetPID()].SkillID == 31)
{

	void* CasterOffset = CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
	{
		if (IPlayer.IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(31));
			IPlayer.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
		}
	}
}


//cor off
if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(38))
{
	void* CasterOffset = CallOfRecovery[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
	{
		IPlayer.CancelBuff(38);

	}
}

//cor on
if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(38))
{
	void* CasterOffset = CallOfRecovery[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
	{
		if (IPlayer.IsInRange(Caster, CallRANGE))
		{
			ISkill ISkill((void*)Caster.GetSkillPointer(23));
			if (IPlayer.GetSpecialty() == 23 && IPlayer.GetClass() == 1)
			{
				IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
			}
			else
			{
				IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
			}
		}
	}
}

//codoff
if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(28))
{
	void* CasterOffset = CallOfDefense[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);

	if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
	{
		IPlayer.CancelBuff(28);
	}
}

//cod on
if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(28))
{
	void* CasterOffset = CallOfDefense[IPlayer.GetPID()].CasterOffset;
	IChar Caster(CasterOffset);
	int Check = 0;
	void* pSkill=(void*)Caster.GetSkillPointer(19);

	if (IPlayer.GetPartyID() == Caster.GetPartyID()&&IPlayer.GetOffset()!=Caster.GetOffset())
	{
		if (IPlayer.IsInRange(Caster, CallRANGE))
		{
			Check = (*(int(__thiscall **)(void *, int))(*(DWORD*)pSkill + 80))(pSkill, (int)Caster.GetOffset());
			int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
			(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)IPlayer.GetOffset() + 180))((DWORD)IPlayer.GetOffset(), Buff);
		}
	}
}


	if (D4InstanceON == true)
	{
		DFourInstance(IPlayer);
	}



	return CPlayer::Tick(Player);
}
#endif