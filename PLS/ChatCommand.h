#ifndef CHATCOMMAND_H_
#define CHATCOMMAND_H_
#include "InstaConfig.h"
void __fastcall ChatCommand(int Player, void *edx, const char *command)
{
	if (!strlen(command))
		return;

	std::string cmd = (std::string)command;
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && cmd.substr(0, 5) == "/exit" && D4InstanceON==true)
	{
		if (IPlayer.IsBuff(666))
		{
			IPlayer.CancelBuff(666);
			IPlayer.CloseScreenTime();
			IPlayer.Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
			CPlayer::LeaveParty((int)IPlayer.GetOffset());
			IPlayer.Announcement("You left the instance", TEXTCOLOR_RED);
			IPlayer.Buff(240, D4Instance::Cooldown, 0);
			return;
		}
		else
		{
			IPlayer.SystemMessage("You are not at instance atm", TEXTCOLOR_RED);
			return;
		}
	}
	if (IPlayer.IsOnline() && cmd.substr(0, 9) == "/instaoff" && IPlayer.GetAdmin() >= 8 && D4InstanceON == true)
	{
		D4Instance::IsUp = false;
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		D4Instance::PartySize = 0;
		InstaConfig();
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 12) == "/instaconfig" && IPlayer.GetAdmin() >= 8 && D4InstanceON == true)
	{
		if (D4Instance::IsUp == false)
		{
			IPlayer.SystemMessage("Insta config reloaded", TEXTCOLOR_GREEN);
			InstaConfig();
		}
		else
		{
			IPlayer.SystemMessage("You cannot reload Instance config when Instance is running", TEXTCOLOR_RED);
			return;
		}
	}




	if (IPlayer.IsOnline() && cmd.substr(0, 10) == "/zenconfig" && IPlayer.GetAdmin() >= 8)
	{
		IPlayer.SystemMessage("Zen skill config reloaded successfully", TEXTCOLOR_GREEN);
		ZenConfig();
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/riftconfig" && IPlayer.GetAdmin() >= 8)
	{

			IPlayer.SystemMessage("Rift skill config reloaded successfully", TEXTCOLOR_GREEN);
			RiftConfig();
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 12) == "/currentbuff" && IPlayer.GetAdmin() >= 8)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (IPlayer.IsBuff(i))
			{
				std::string kapi = "Buff: " + Int2String(i);
				IPlayer.SystemMessage(kapi.c_str(), TEXTCOLOR_BLUE);
			}
		}

	}

	if (IPlayer.IsOnline() && cmd.substr(0, 6) == "/point")
	{
		if (!IPlayer.IsBuff(LawlessZone::BuffID))
		{
			IPlayer.SystemMessage("You are not at LawlessZone right now", TEXTCOLOR_RED);
			return;
		}

			std::string points = "Current points: ";
			points += Int2String(LawlessZone::PointCounter.find(IPlayer.GetPID())->second);
			IPlayer.SystemMessage(points, TEXTCOLOR_PINK);

	}

	if (IPlayer.IsOnline() && cmd.substr(0, 5) == "/aoff" && IPlayer.GetAdmin() >= 8)
	{
		IPlayer.CancelBuff(LawlessZone::BuffID);
		for (int i = 0; i < 10; i++)
		{
			IPlayer.CancelBuff(LawlessZone::ExpBuffID[i]);
			IPlayer.RemoveBuffIcon(0, 0, 0, 1500+i);
		}
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/mautconfig"&& IPlayer.GetAdmin() >= 8)
	{
		if (Mautareta::IsUp == false)
		{
			MautaretaConfig();
			IPlayer.SystemMessage("Mautareta config reloaded successfully", TEXTCOLOR_GREEN);
			Mautareta::PartyLimit = 0;
			IPlayer.Teleport(0, Mautareta::SpawnMautX, Mautareta::SpawnMautX);
		}
		else
			IPlayer.SystemMessage("Mautareta is not running right now", TEXTCOLOR_RED);
		return;
	}


	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/mautreload" && IPlayer.GetAdmin() >= 8)
	{
		if (Mautareta::IsUp == true)
		{
			Mautareta::IsUp = false;
			IPlayer.SystemMessage("Mautareta stopped", TEXTCOLOR_GREEN);
			Mautareta::PartyLimit = 0;
		}
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 5) == "/buff" && IPlayer.GetAdmin() >= 8)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (IPlayer.IsBuff(i))
			{
				IPlayer.SystemMessage(Int2String(i), TEXTCOLOR_PINK);
			}
		}
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 5)=="/test" && IPlayer.GetAdmin() >= 8)
	{
	//	int BossID = 603;
	//	IPlayer.SystemMessage(Int2String(BossDropsMap[BossID].MinDamage), TEXTCOLOR_RED);
	//	IPlayer.SystemMessage(Int2String(BossDropsMap[BossID].MinDamagePercent), TEXTCOLOR_RED);
	//	IPlayer.SystemMessage(Int2String(BossDropsMap[BossID].drop[0].ItemID), TEXTCOLOR_RED);
	//	IPlayer.SystemMessage(Int2String(BossDropsMap[BossID].drop[0].ItemAmount), TEXTCOLOR_RED);
	//	IPlayer.SystemMessage(Int2String(BossDropsMap[BossID].HighTierLootID), TEXTCOLOR_RED);

		IPlayer.SystemMessage(Int2String(IPlayer.GetMoveSpeed()), TEXTCOLOR_RED);
	}
	CPlayer::ChatCommand(Player, command);
}
#endif