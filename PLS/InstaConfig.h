#ifndef _INSTACONFIG_H
#define _INSTACONFIG_H
#include "Resources.h"
void InstaConfig()
{

	

	std::ifstream oD4Instance;
	oD4Instance.open("./Systems/D4Instance.txt", std::ios_base::in);
	int i = 0;
	char h;
	std::string stri;
	if (oD4Instance)
	{

		h = oD4Instance.get();
		while (h == '#')
		{
			std::getline(oD4Instance, stri);
			h = oD4Instance.get();
		}
		oD4Instance.unget();

		oD4Instance >> D4Instance::QuestID;
		oD4Instance >> D4Instance::MinLevel;
		oD4Instance >> D4Instance::PartySize;
		oD4Instance >> D4Instance::FloorNumber;
		oD4Instance >> D4Instance::MapNumber;
		oD4Instance >> D4Instance::LastStage;
		oD4Instance >> D4Instance::Time;
		oD4Instance >> D4Instance::Cooldown;
		oD4Instance >> D4Instance::MinPartyMembers;
		oD4Instance >> D4Instance::SpawnX;
		oD4Instance >> D4Instance::SpawnY;
		oD4Instance >> D4Instance::ReturnX;
		oD4Instance >> D4Instance::ReturnY;
		oD4Instance >> D4Instance::F2TP[0] >> D4Instance::F2TP[1] >> D4Instance::F2TP[2];
		oD4Instance >> D4Instance::F3TP[0] >> D4Instance::F3TP[1] >> D4Instance::F3TP[2];
		oD4Instance >> D4Instance::F4TP[0] >> D4Instance::F4TP[1] >> D4Instance::F4TP[2];
		oD4Instance >> D4Instance::F5TP[0] >> D4Instance::F5TP[1] >> D4Instance::F5TP[2];
		oD4Instance >> D4Instance::F6TP[0] >> D4Instance::F6TP[1] >> D4Instance::F6TP[2];
		oD4Instance >> D4Instance::LastRoomTP[0] >> D4Instance::LastRoomTP[1] >> D4Instance::LastRoomTP[2];
		while (!oD4Instance.eof())
		{
			oD4Instance >> D4Instance::CoordX[i];
			oD4Instance >> D4Instance::CoordY[i];
			oD4Instance >> D4Instance::MobID[i];
			oD4Instance >> D4Instance::MobsCount[i];
			i++;
		}
	}
	oD4Instance.close();
	D4Instance::PartyMembers.clear();

}

void ZenConfig()
{
	FILE *filez = fopen("./Configs/Cooldown.txt", "r");
	if (filez != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filez) != NULL)
		{
			int GetClass = 0, GetSkillID = 0, GetDelay = 0, GetCooldown = 0, GetSkillIDx = 0, GetDelayx = 0, GetCooldownx = 0;
			if (sscanf(line, "(eggskill (action %d)(delay %d)(cooldown %d))", &GetSkillIDx, &GetDelayx, &GetCooldownx) == 3)
			{
				CheckEggCooldownConfig[GetSkillIDx].EggCooldownConfig = GetCooldownx;
				CheckEggCooldownConfig[GetSkillIDx].EggDelayConfig = GetDelayx;
			}

			if (sscanf(line, "(skill (class %d)(action %d)(delay %d)(cooldown %d))", &GetClass, &GetSkillID, &GetDelay, &GetCooldown) == 4)
			{
				CheckCooldownConfig[GetSkillID + (GetClass * 100)].CooldownConfig = GetCooldown;
				CheckCooldownConfig[GetSkillID + (GetClass * 100)].DelayConfig = GetDelay;
			}
		}
		fclose(filez);
	}
	FILE *filex = fopen("./Configs/Teleport.txt", "r");
	if (filex != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filez) != NULL)
		{
			int Index = 0, TeleportX = 0, TeleportY = 0, TeleportMap = 0, LevelLimit = 0;
			if (sscanf(line, "(teleport (index %d)(X %d)(Y %d)(Map %d)(LvlLimit %d))", &Index, &TeleportX, &TeleportY, &TeleportMap, &LevelLimit) == 5)
			{
				ZenTP[Index].TeleportX = TeleportX;
				ZenTP[Index].TeleportY = TeleportY;
				ZenTP[Index].Map = TeleportMap;
				ZenTP[Index].LevelLimit = LevelLimit;
			}
		}
		fclose(filex);
	}

	std::ifstream ZenRNG;
	ZenRNG.open("./Systems/ZenRNG.txt", std::ios_base::in);
	char r;
	std::string strin;
	if (ZenRNG)
	{
		BossDropsMap.clear();
		int counter = 0;
		r = ZenRNG.get();
		while (r == '#')
		{
			std::getline(ZenRNG, strin);
			r = ZenRNG.get();
		}
		ZenRNG.unget();

		ZenRNG >> ZenRNGesus::TotalBossCount;

		while (counter < ZenRNGesus::TotalBossCount && !ZenRNG.eof())
		{
			int BossID = 0;
			ZenRNG >> BossID;
			ZenRNG >> BossDropsMap[BossID].MinDamage;
			ZenRNG >> BossDropsMap[BossID].MinDamagePercent;
			ZenRNG >> BossDropsMap[BossID].MaxPlayers;
			ZenRNG >> BossDropsMap[BossID].MaxDropPerPlayer;
			ZenRNG >> BossDropsMap[BossID].AmountOfDifferentItems;
			for (int i = 0; i < BossDropsMap[BossID].AmountOfDifferentItems; i++)
			{
				ZenRNG >> BossDropsMap[BossID].TempDropStruct.ItemID;
				ZenRNG >> BossDropsMap[BossID].TempDropStruct.ItemAmount;
				ZenRNG >> BossDropsMap[BossID].TempDropStruct.DropChance;
				BossDropsMap[BossID].Dropy.push_back(BossDropsMap[BossID].TempDropStruct);
				BossDropsMap[BossID].ItemsToDraw += BossDropsMap[BossID].Dropy[i].ItemAmount;
			}


			counter++;

		}
		ZenRNG.close();
	}


	Kn8WhiteListSkills.push_back(10);
	Kn8WhiteListSkills.push_back(3);
	Kn8WhiteListSkills.push_back(4);
	Kn8WhiteListSkills.push_back(7);
	Kn8WhiteListSkills.push_back(8);
	Kn8WhiteListSkills.push_back(13);
	Kn8WhiteListSkills.push_back(41);

	Kn8WhiteListSkills.push_back(14);
	Kn8WhiteListSkills.push_back(15);
	Kn8WhiteListSkills.push_back(16);
	Kn8WhiteListSkills.push_back(17);
	Kn8WhiteListSkills.push_back(18);
	Kn8WhiteListSkills.push_back(19);
	Kn8WhiteListSkills.push_back(22);
	Kn8WhiteListSkills.push_back(23);
	Kn8WhiteListSkills.push_back(24);
	Kn8WhiteListSkills.push_back(25);
	Kn8WhiteListSkills.push_back(26);
	Kn8WhiteListSkills.push_back(27);
	Kn8WhiteListSkills.push_back(28);
	Kn8WhiteListSkills.push_back(29);
	Kn8WhiteListSkills.push_back(30);
	Kn8WhiteListSkills.push_back(31);
	Kn8WhiteListSkills.push_back(32);
	Kn8WhiteListSkills.push_back(33);
	Kn8WhiteListSkills.push_back(34);
	Kn8WhiteListSkills.push_back(38);
	Kn8WhiteListSkills.push_back(44);
	Kn8WhiteListSkills.push_back(42);
	Kn8WhiteListSkills.push_back(43);
	Kn8WhiteListSkills.push_back(90);
	Kn8WhiteListSkills.push_back(91);
	Kn8WhiteListSkills.push_back(92);
	Kn8WhiteListSkills.push_back(93);
	Kn8WhiteListSkills.push_back(94);

	MageWhiteListSkills.push_back(8);
	MageWhiteListSkills.push_back(9);
	MageWhiteListSkills.push_back(15);
	MageWhiteListSkills.push_back(29);
	MageWhiteListSkills.push_back(55);
	MageWhiteListSkills.push_back(56);
	MageWhiteListSkills.push_back(58);
	MageWhiteListSkills.push_back(59);
	MageWhiteListSkills.push_back(60);
	MageWhiteListSkills.push_back(69);
	MageWhiteListSkills.push_back(64);
	MageWhiteListSkills.push_back(74);
	MageWhiteListSkills.push_back(76);
	MageWhiteListSkills.push_back(90);
	MageWhiteListSkills.push_back(91);
	MageWhiteListSkills.push_back(92);
	MageWhiteListSkills.push_back(93);
	MageWhiteListSkills.push_back(94);
	MageWhiteListSkills.push_back(99);


	ArcherWhiteListSkills.push_back(4);
	ArcherWhiteListSkills.push_back(7);
	ArcherWhiteListSkills.push_back(10);
	ArcherWhiteListSkills.push_back(16);
	ArcherWhiteListSkills.push_back(18);
	ArcherWhiteListSkills.push_back(21);
	ArcherWhiteListSkills.push_back(22);
	ArcherWhiteListSkills.push_back(24);
	ArcherWhiteListSkills.push_back(25);
	ArcherWhiteListSkills.push_back(26);
	ArcherWhiteListSkills.push_back(28);
	ArcherWhiteListSkills.push_back(29);
	ArcherWhiteListSkills.push_back(31);
	ArcherWhiteListSkills.push_back(33);
	ArcherWhiteListSkills.push_back(35);
	ArcherWhiteListSkills.push_back(36);
	ArcherWhiteListSkills.push_back(37);
	ArcherWhiteListSkills.push_back(38);
	ArcherWhiteListSkills.push_back(39);
	ArcherWhiteListSkills.push_back(40);
	ArcherWhiteListSkills.push_back(41);
	ArcherWhiteListSkills.push_back(43);
	ArcherWhiteListSkills.push_back(46);
	ArcherWhiteListSkills.push_back(47);
	ArcherWhiteListSkills.push_back(90);
	ArcherWhiteListSkills.push_back(91);
	ArcherWhiteListSkills.push_back(92);
	ArcherWhiteListSkills.push_back(93);
	ArcherWhiteListSkills.push_back(94);






	std::ifstream oD4Instance;
	oD4Instance.open("./Skills/ZenSkillConfig.txt", std::ios_base::in);



	TradeSystem::ItemID = GetPrivateProfileIntA("TradeSystem", "ItemID", 1, "./Systems/TradeSystem.txt");
	TradeSystem::MinLvl = GetPrivateProfileIntA("TradeSystem", "MinLvl", 1, "./Systems/TradeSystem.txt");
	TradeSystem::QuestRangeMin = GetPrivateProfileIntA("TradeSystem", "QuestRangeMin", 1, "./Systems/TradeSystem.txt");
	TradeSystem::QuestRangeMax = GetPrivateProfileIntA("TradeSystem", "QuestRangeMax", 1, "./Systems/TradeSystem.txt");
	TradeSystem::Cooldown = GetPrivateProfileIntA("TradeSystem", "Cooldown", 1, "./Systems/TradeSystem.txt");


	LawlessZone::TicketID = GetPrivateProfileIntA("LawlessZone", "TicketID", 1, "./Systems/LawlessZone.txt");
	LawlessZone::QuestID = GetPrivateProfileIntA("LawlessZone", "QuestID", 1, "./Systems/LawlessZone.txt");
	LawlessZone::QuitQuestID = GetPrivateProfileIntA("LawlessZone", "QuitQuestID", 1, "./Systems/LawlessZone.txt");
	LawlessZone::MinLvl = GetPrivateProfileIntA("LawlessZone", "MinLvl", 1, "./Systems/LawlessZone.txt");
	LawlessZone::MovingTrinketID = GetPrivateProfileIntA("LawlessZone", "MovingTrinketID", 1, "./Systems/LawlessZone.txt");
	LawlessZone::StartTeleportX = GetPrivateProfileIntA("LawlessZone", "StartTeleportX", 1, "./Systems/LawlessZone.txt");
	LawlessZone::StartTeleportY = GetPrivateProfileIntA("LawlessZone", "StartTeleportY", 1, "./Systems/LawlessZone.txt");
	LawlessZone::ReturnTeleportX = GetPrivateProfileIntA("LawlessZone", "ReturnTeleportX", 1, "./Systems/LawlessZone.txt");
	LawlessZone::ReturnTeleportY = GetPrivateProfileIntA("LawlessZone", "ReturnTeleportY", 1, "./Systems/LawlessZone.txt");
	LawlessZone::Map = GetPrivateProfileIntA("LawlessZone", "Map", 1, "./Systems/LawlessZone.txt");
	LawlessZone::Time = GetPrivateProfileIntA("LawlessZone", "Time", 1, "./Systems/LawlessZone.txt");
	LawlessZone::PKPoints = GetPrivateProfileIntA("LawlessZone", "PKPoints", 1, "./Systems/LawlessZone.txt");
	LawlessZone::MobPoints = GetPrivateProfileIntA("LawlessZone", "MobPoints", 1, "./Systems/LawlessZone.txt");



		TradeSystemON = GetPrivateProfileIntA("System", "TradeSystem", 0, "./Systems/SystemONOFF.txt");
		LawlessZoneON = GetPrivateProfileIntA("System", "LawlessZone", 0, "./Systems/SystemONOFF.txt");
		RiftON = GetPrivateProfileIntA("System", "Rift", 0, "./Systems/SystemONOFF.txt");
		D4InstanceON = GetPrivateProfileIntA("System", "D4Instance", 0, "./Systems/SystemONOFF.txt");
		MautaretaON = GetPrivateProfileIntA("System", "Mautareta", 0, "./Systems/SystemONOFF.txt");
		SpeedHackCheck = GetPrivateProfileIntA("System", "SpeedHackCheck", 0, "./Systems/SystemONOFF.txt");
		Logs = GetPrivateProfileIntA("System", "Logs", 0, "./Systems/SystemONOFF.txt");



		ScrollItemID = GetPrivateProfileIntA("ScrollItem", "ScrollItemID", 0, "./Systems/ZenSystem.txt");
		ScrollItemIconKey = GetPrivateProfileIntA("ScrollItem", "ScrollItemIconKey", 0, "./Systems/ZenSystem.txt");



		InstanceResetScrollID = GetPrivateProfileIntA("InstanceResetScroll", "ScrollID", 0, "./Systems/ZenSystem.txt");
		TradeSystemResetScrollID = GetPrivateProfileIntA("TradeSystemResetScroll", "ScrollID", 0, "./Systems/ZenSystem.txt");
		



	oD4Instance.close();

	std::ifstream LawlessZone;
	LawlessZone.open("./Systems/LawlessZone.txt", std::ios_base::in);
	char xd;
	int ok;
	std::string strie;
	if (LawlessZone)
	{

		xd = LawlessZone.get();
		while (xd == '#')
		{
			std::getline(LawlessZone, strie);
			xd = LawlessZone.get();
		}
		LawlessZone.unget();
	}
	while (LawlessZone >> ok)
	{
		if (ok == '[')
		{
			break;
		}

		LawlessZone::MobID.push_back(ok);
	}


	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int p = 0, k = 0;


	std::ifstream TradeSysteme;
	TradeSysteme.open("./Systems/TradeSystem.txt", std::ios_base::in);
	char h;
	std::string stri;
	if (TradeSysteme)
	{

		h = TradeSysteme.get();
		while (h == '#')
		{
			std::getline(TradeSysteme, stri);
			h = TradeSysteme.get();
		}
		TradeSysteme.unget();

		while (TradeSysteme >> a)
		{
			if (a == '[')
			{
				break;
			}
			if (a == 0)
			{
				break;
			}
			TradeSysteme >> b;
			TradeSysteme >> c;
			TradeSystem::Quest.insert(std::make_pair(std::make_pair(a, b), c));
		}


		while (TradeSysteme >> d)
		{
			if (d == '[')
			{
				break;
			}
			if (d == 0)
			{
				break;
			}
			TradeSysteme >> e;
			TradeSysteme >> f;
			TradeSystem::Reward.insert(std::make_pair(std::make_pair(d, e),f));
		}
		TradeSysteme.close();
	}

}
void RiftConfig()
{
	std::ifstream Rift;
	Rift.open("./Systems/Rift.txt", std::ios_base::in);
	char h;
	int mob_counter = 0;
	bool first = false;
	std::string stri;
	if (Rift)
	{

		h = Rift.get();
		while (h == '#')
		{

			std::getline(Rift, stri);
			h = Rift.get();
		}
		Rift.unget();
		if (first == false)
		{

			Rift >> RiftAmount;
			if (RiftAmount < 1)
			{
				return;
			}
			first = true;
		}
		for (int i = 0; i < RiftAmount; i++)
		{

			Rift >> RiftStruct[i].IsUp;
			Rift >> RiftStruct[i].WaveNumber;
			Rift >> RiftStruct[i].MaxWave;
			Rift >> RiftStruct[i].Map;
			Rift >> RiftStruct[i].FirstBoss;
			Rift >> RiftStruct[i].BossMobSpawnID;
			Rift >> RiftStruct[i].BossMobSpawnAmount;
			Rift >> RiftStruct[i].SpawnX;
			Rift >> RiftStruct[i].SpawnY;
			for (int j = 0; j < RiftStruct[i].MaxWave; j++)
			{
				Rift >> RiftStruct[i].MobID[j];
				Rift >> RiftStruct[i].MobAmount[j];
			}
			Rift.get();
			std::getline(Rift, stri);
		}

	}
	Rift.close();

}

void MautaretaConfig()
{
	std::ifstream Mautaretaa;
	Mautaretaa.open("./Systems/Mautareta.txt", std::ios_base::in);

	Mautareta::StartTeleportX = GetPrivateProfileIntA("Mautareta", "StartTeleportX", 1, "./Systems/Mautareta.txt");
	Mautareta::StartTeleportY = GetPrivateProfileIntA("Mautareta", "StartTeleportY", 1, "./Systems/Mautareta.txt");

	Mautareta::ReturnTeleportX = GetPrivateProfileIntA("Mautareta", "ReturnTeleportX", 1, "./Systems/Mautareta.txt");
	Mautareta::ReturnTeleportY = GetPrivateProfileIntA("Mautareta", "ReturnTeleportY", 1, "./Systems/Mautareta.txt");

	Mautareta::Map = GetPrivateProfileIntA("Mautareta", "Map", 1, "./Systems/Mautareta.txt");

	Mautareta::QuestID = GetPrivateProfileIntA("Mautareta", "QuestID", 1, "./Systems/Mautareta.txt");
	Mautareta::QuestItemID = GetPrivateProfileIntA("Mautareta", "QuestItemID", 1, "./Systems/Mautareta.txt");

	Mautareta::BossID = GetPrivateProfileIntA("Mautareta", "BossID", 1, "./Systems/Mautareta.txt");
	Mautareta::WandererID = GetPrivateProfileIntA("Mautareta", "WandererID", 1, "./Systems/Mautareta.txt");

	Mautareta::SpawnMautX = GetPrivateProfileIntA("Mautareta", "SpawnMautX", 1, "./Systems/Mautareta.txt");
	Mautareta::SpawnMautY = GetPrivateProfileIntA("Mautareta", "SpawnMautY", 1, "./Systems/Mautareta.txt");


	Mautaretaa.close();

}

#endif