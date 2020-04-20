#ifndef CHATCOMMAND_H_
#define CHATCOMMAND_H_
#include "InstaConfig.h"
#include <sql.h>
void __fastcall ChatCommand(int Player, void *edx, const char *command)
{
	if (!strlen(command))
		return;

	std::string cmd = (std::string)command;
	ICharacter IPlayer((void*)Player);

	if (IsOnline() && cmd.substr(0, 5) == "/exit" && D4InstanceON==true)
	{
		if (IsBuff(666))
		{
			D4Instance::PartyMembers.erase(GetPID());
			D4Instance::PartySize--;
			CancelBuff(666);
			CloseScreenTime();
			Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
			CPlayer::LeaveParty((int)GetOffset());
			Announcement("You left the instance", TEXTCOLOR_RED);
			Buff(240, D4Instance::Cooldown, 0);
			if (D4Instance::PartySize <= 1)
			{
				CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Party destroyed, instance failed", 1);
				D4Instance::IsUp = false;
				D4Instance::StageNumber = 0;
				D4Instance::MobsKilled = 0;
				InstaConfig();
			}
			return;
		}
		else
		{
			SystemMessage("You are not at instance atm", TEXTCOLOR_RED);
			return;
		}
	}
	if (IsOnline() && cmd.substr(0, 9) == "/instaoff" && GetAdmin() >= 8 && D4InstanceON == true)
	{
		D4Instance::IsUp = false;
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		D4Instance::PartySize = 0;
		InstaConfig();
		return;
	}

	if (IsOnline() && cmd.substr(0, 12) == "/instaconfig" && GetAdmin() >= 8 && D4InstanceON == true)
	{
		if (D4Instance::IsUp == false)
		{
			SystemMessage("Insta config reloaded", TEXTCOLOR_GREEN);
			InstaConfig();
		}
		else
		{
			SystemMessage("You cannot reload Instance config when Instance is running", TEXTCOLOR_RED);
			return;
		}
	}




	if (IsOnline() && cmd.substr(0, 10) == "/zenconfig" && GetAdmin() >= 8)
	{
		SystemMessage("Zen skill config reloaded successfully", TEXTCOLOR_GREEN);
		ZenConfig();
	}

	if (IsOnline() && cmd.substr(0, 11) == "/riftconfig" && GetAdmin() >= 8)
	{

			SystemMessage("Rift skill config reloaded successfully", TEXTCOLOR_GREEN);
			RiftConfig();
	}

	if (IsOnline() && cmd.substr(0, 12) == "/currentbuff" && GetAdmin() >= 8)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (IsBuff(i))
			{
				std::string kapi = "Buff: " + Int2String(i);
				SystemMessage(kapi.c_str(), TEXTCOLOR_BLUE);
			}
		}

	}

	if (IsOnline() && cmd.substr(0, 6) == "/point")
	{
		if (!IsBuff(LawlessZone::BuffID))
		{
			SystemMessage("You are not at Lawless Zone right now", TEXTCOLOR_RED);
			return;
		}

			std::string points = "Current points: ";
			points += Int2String(LawlessZone::PointCounter.find(GetPID())->second);
			SystemMessage(points, TEXTCOLOR_PINK);

	}

	if (IsOnline() && cmd.substr(0, 11) == "/lawlessoff" && IsBuff(LawlessZone::BuffID))
	{
			CancelBuff(LawlessZone::BuffID);
			for (int i = 0; i < 10; i++)
			{
				CancelBuff(LawlessZone::ExpBuffID[i]);
				RemoveBuffIcon(0, 0, 0, 1500 + i);
			}
			CancelBuff(104);
			Teleport(0, LawlessZone::ReturnTeleportX, LawlessZone::ReturnTeleportY);
			LawlessZone::PointCounter[GetPID()] = 0;
	}

	if (IsOnline() && cmd.substr(0, 11) == "/mautconfig"&& GetAdmin() >= 8)
	{
		if (Mautareta::IsUp == false)
		{
			MautaretaConfig();
			SystemMessage("Mautareta config reloaded successfully", TEXTCOLOR_GREEN);
			Mautareta::PartyLimit = 0;
			Teleport(0, Mautareta::SpawnMautX, Mautareta::SpawnMautX);
		}
		else
			SystemMessage("Mautareta is not running right now", TEXTCOLOR_RED);
		return;
	}


	if (IsOnline() && cmd.substr(0, 11) == "/mautreload" && GetAdmin() >= 8)
	{
		if (Mautareta::IsUp == true)
		{
			Mautareta::IsUp = false;
			SystemMessage("Mautareta stopped", TEXTCOLOR_GREEN);
			Mautareta::PartyLimit = 0;
		}
		return;
	}

	//if (IsOnline() && cmd.substr(0, 5) == "/test"&&GetAdmin() >= 11)
	//{
	//	CPlayer::Write(GetOffset(), 68, "bbb", 43, 13, 0);
	//	SystemMessage(Int2String(Undefined::sub_446FF0((int)GetOffset())),TEXTCOLOR_YELLOW);
	//}


	if (IsOnline())
	{

	}

	if (IsOnline() && cmd.substr(0, 5) == "/puff" && GetAdmin() >= 8)
	{
		AddDef(10000);
		AddMaxAttack(10000);
		AddMinAttack(10000);
		AddEva(10000);
		AddOTP(10000);
		AddHp(10000);
	}

	CPlayer::ChatCommand(Player, command);
}
#endif