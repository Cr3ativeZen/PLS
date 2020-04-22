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

	HealBasePercentage = GetPrivateProfileIntA("Heal", "HealBasePercentage", 1, "./Skills/ZenSkillConfig.txt");
	HealPerGradePercentage = GetPrivateProfileIntA("Heal", "HealPerGradePercentage", 1, "./Skills/ZenSkillConfig.txt");
	HealBase = GetPrivateProfileIntA("Heal", "HealBase", 1, "./Skills/ZenSkillConfig.txt");
	HealWisdom = GetPrivateProfileIntA("Heal", "HealWisdom", 1, "./Skills/ZenSkillConfig.txt");
	
	SacrificeBaseHeal = GetPrivateProfileIntA("Sacrifice", "SacrificeBaseHeal", 1, "./Skills/ZenSkillConfig.txt");
	SacrificeBasePercentageHeal = GetPrivateProfileIntA("Sacrifice", "SacrificeBasePercentageHeal", 1, "./Skills/ZenSkillConfig.txt");
	SacrificeHealPerGradePercentage = GetPrivateProfileIntA("Sacrifice", "SacrificeHealPerGradePercentage", 1, "./Skills/ZenSkillConfig.txt");
	SacrificeBaseLoss = GetPrivateProfileIntA("Sacrifice", "SacrificeBaseLoss", 1, "./Skills/ZenSkillConfig.txt");
	SacrificeBasePercentageLoss = GetPrivateProfileIntA("Sacrifice", "SacrificeBasePercentageLoss", 1, "./Skills/ZenSkillConfig.txt");
	SacrificeLossPerGradePercentage = GetPrivateProfileIntA("Sacrifice", "SacrificeLossPerGradePercentage", 1, "./Skills/ZenSkillConfig.txt");
	
	CureBase = GetPrivateProfileIntA("Cure", "CureBase", 1, "./Skills/ZenSkillConfig.txt");
	CureBasePercentage = GetPrivateProfileIntA("Cure", "CureBasePercentage", 1, "./Skills/ZenSkillConfig.txt");
	CurePerGradePercentage = GetPrivateProfileIntA("Cure", "CurePerGradePercentage", 1, "./Skills/ZenSkillConfig.txt");
	CureWisdom = GetPrivateProfileIntA("Cure", "CureWisdom", 1, "./Skills/ZenSkillConfig.txt");
	
	CureBase2 = GetPrivateProfileIntA("Cure2", "CureBase2", 1, "./Skills/ZenSkillConfig.txt");
	CureBasePercentage2 = GetPrivateProfileIntA("Cure2", "CureBasePercentage2", 1, "./Skills/ZenSkillConfig.txt");
	CurePerGradePercentage2 = GetPrivateProfileIntA("Cure2", "CurePerGradePercentage2", 1, "./Skills/ZenSkillConfig.txt");
	Cure2Wisdom = GetPrivateProfileIntA("Cure2", "Cure2Wisdom", 1, "./Skills/ZenSkillConfig.txt");
	
	CureBase3 = GetPrivateProfileIntA("Cure3", "CureBase3", 1, "./Skills/ZenSkillConfig.txt");
	CureBasePercentage3 = GetPrivateProfileIntA("Cure3", "CureBasePercentage3", 1, "./Skills/ZenSkillConfig.txt");
	CurePerGradePercentage3 = GetPrivateProfileIntA("Cure3", "CurePerGradePercentage3", 1, "./Skills/ZenSkillConfig.txt");
	Cure3Wisdom = GetPrivateProfileIntA("Cure3", "Cure3Wisdom", 1, "./Skills/ZenSkillConfig.txt");
	
	CallRANGE = GetPrivateProfileIntA("Calls", "CallRANGE", 1, "./Skills/ZenSkillConfig.txt");

	CallofHealBase = GetPrivateProfileIntA("CallOfHeal", "CallofHealBase", 1, "./Skills/ZenSkillConfig.txt");
	CallofHealBasePercentage = GetPrivateProfileIntA("CallOfHeal", "CallofHealBasePercentage", 1, "./Skills/ZenSkillConfig.txt");
	CallofHealPerGradePercentage = GetPrivateProfileIntA("CallOfHeal", "CallofHealPerGradePercentage", 1, "./Skills/ZenSkillConfig.txt");
	
	AmensiaBaseDmgMulti = GetPrivateProfileIntA("Amnesia", "AmensiaBaseDmgMulti", 1, "./Skills/ZenSkillConfig.txt");
	AmnesiaWisMulti = GetPrivateProfileIntA("Amnesia", "AmnesiaWisMulti", 1, "./Skills/ZenSkillConfig.txt");
	AmnesiaDmgPercentIncreaseBless = GetPrivateProfileIntA("Amnesia", "AmnesiaDmgPercentIncreaseBless", 1, "./Skills/ZenSkillConfig.txt");

	SoulDestructionBaseDmgMultiPvE = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	SoulDestructionWisMultiPvE = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionWisMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	SoulDestructionPerGradeMultiPvE = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	SoulDestructionBaseDmgMultiPvP = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SoulDestructionWisMultiPvP = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionWisMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SoulDestructionPerGradeMultiPvP = GetPrivateProfileIntA("SoulDestruction", "SoulDestructionPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");

	PWWBaseDmgMultiPvE = GetPrivateProfileIntA("PowerfulWideningWound", "PWWBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PWWAgiMultiPvE = GetPrivateProfileIntA("PowerfulWideningWound", "PWWAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PWWStrMultiPvE = GetPrivateProfileIntA("PowerfulWideningWound", "PWWStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PWWPerGradeMultiPvE = GetPrivateProfileIntA("PowerfulWideningWound", "PWWPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PWWHostilityMultiplier = GetPrivateProfileIntA("PowerfulWideningWound", "PWWHostilityMultiplier", 1, "./Skills/ZenSkillConfig.txt");

	PWWBaseDmgMultiPvP = GetPrivateProfileIntA("PowerfulWideningWound", "PWWBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PWWAgiMultiPvP = GetPrivateProfileIntA("PowerfulWideningWound", "PWWAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PWWStrMultiPvP = GetPrivateProfileIntA("PowerfulWideningWound", "PWWStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PWWPerGradeMultiPvP = GetPrivateProfileIntA("PowerfulWideningWound", "PWWPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");




	BlowUpBaseDmgMultiPvE = GetPrivateProfileIntA("BlowUpArrow", "BlowUpBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpAgiMultiPvE = GetPrivateProfileIntA("BlowUpArrow", "BlowUpAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpStrMultiPvE = GetPrivateProfileIntA("BlowUpArrow", "BlowUpStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpPerGradeMultiPvE = GetPrivateProfileIntA("BlowUpArrow", "BlowUpPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpPvEMaxHits = GetPrivateProfileIntA("BlowUpArrow", "BlowUpPvEMaxHits", 1, "./Skills/ZenSkillConfig.txt");

	BlowUpBaseDmgMultiPvP = GetPrivateProfileIntA("BlowUpArrow", "BlowUpBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpAgiMultiPvP = GetPrivateProfileIntA("BlowUpArrow", "BlowUpAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpStrMultiPvP = GetPrivateProfileIntA("BlowUpArrow", "BlowUpStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BlowUpPerGradeMultiPvP = GetPrivateProfileIntA("BlowUpArrow", "BlowUpPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	
	PassiveAttackBaseFreezeTime = GetPrivateProfileIntA("Passive Attack", "PassiveAttackBaseFreezeTime", 1, "./Skills/ZenSkillConfig.txt");
	PassiveAttackPerGradeFreezeTime = GetPrivateProfileIntA("Passive Attack", "PassiveAttackPerGradeFreezeTime", 1, "./Skills/ZenSkillConfig.txt");
	
	MABaseDmgMultiPvE = GetPrivateProfileIntA("MysteriousArrow", "MABaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	MAAgiMultiPvE = GetPrivateProfileIntA("MysteriousArrow", "MAAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	MAStrMultiPvE = GetPrivateProfileIntA("MysteriousArrow", "MAStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	MAPerGradeMultiPvE = GetPrivateProfileIntA("MysteriousArrow", "MAPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	MADoTPerGradePvE = GetPrivateProfileIntA("MysteriousArrow", "MADoTPerGradePvE", 1, "./Skills/ZenSkillConfig.txt");

	MABaseDmgMultiPvP = GetPrivateProfileIntA("MysteriousArrow", "MABaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	MAAgiMultiPvP = GetPrivateProfileIntA("MysteriousArrow", "MAAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	MAStrMultiPvP = GetPrivateProfileIntA("MysteriousArrow", "MAStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	MAPerGradeMultiPvP = GetPrivateProfileIntA("MysteriousArrow", "MAPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	MADoTPerGradePvP = GetPrivateProfileIntA("MysteriousArrow", "MADoTPerGradePvP", 1, "./Skills/ZenSkillConfig.txt");

	MADoTDuration = GetPrivateProfileIntA("MysteriousArrow", "MADoTDuration", 1, "./Skills/ZenSkillConfig.txt");




	FABaseDamageMultiPvE = GetPrivateProfileIntA("FlamyArrow", "FABaseDamageMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FAAGiMultiPvE = GetPrivateProfileIntA("FlamyArrow", "FAAGiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FAStrMultiPvE = GetPrivateProfileIntA("FlamyArrow", "FAStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FAPerGradeMultiPvE = GetPrivateProfileIntA("FlamyArrow", "FAPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FADoTBasePvE = GetPrivateProfileIntA("FlamyArrow", "FADoTBasePvE", 1, "./Skills/ZenSkillConfig.txt");
	FADoTPerGradePvE = GetPrivateProfileIntA("FlamyArrow", "FADoTPerGradePvE", 1, "./Skills/ZenSkillConfig.txt");

	FABaseDamageMultiPvP = GetPrivateProfileIntA("FlamyArrow", "FABaseDamageMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FAAGiMultiPvP = GetPrivateProfileIntA("FlamyArrow", "FAAGiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FAStrMultiPvP = GetPrivateProfileIntA("FlamyArrow", "FAStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FAPerGradeMultiPvP = GetPrivateProfileIntA("FlamyArrow", "FAPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FADoTBasePvP = GetPrivateProfileIntA("FlamyArrow", "FADoTBasePvP", 1, "./Skills/ZenSkillConfig.txt");
	FADoTPerGradePvP = GetPrivateProfileIntA("FlamyArrow", "FADoTPerGradePvP", 1, "./Skills/ZenSkillConfig.txt");

	FADurationBase = GetPrivateProfileIntA("FlamyArrow", "FADurationBase", 1, "./Skills/ZenSkillConfig.txt");
	FADurationPerGrade = GetPrivateProfileIntA("FlamyArrow", "FADurationPerGrade", 1, "./Skills/ZenSkillConfig.txt");
	
	
	ShieldAttackBaseStunTime = GetPrivateProfileIntA("ShieldAttack", "ShieldAttackBaseStunTime", 1, "./Skills/ZenSkillConfig.txt");
	ShieldAttackDamageMulti = GetPrivateProfileIntA("ShieldAttack", "ShieldAttackDamageMulti", 1, "./Skills/ZenSkillConfig.txt");
	
	LSBaseDmgMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LSAgiMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LSStrMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LSPerGradeMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	LSBaseDmgMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LSAgiMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LSStrMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LSPerGradeMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LSPvEMaxHits = GetPrivateProfileIntA("LightningSlash", "LSPvEMaxHits", 1, "./Skills/ZenSkillConfig.txt");
	
	TBBaseDmgMultiPvE = GetPrivateProfileIntA("TranscendentalBlow", "TBBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	TBAgiMultiPvE = GetPrivateProfileIntA("TranscendentalBlow", "TBAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	TBStrMultiPvE = GetPrivateProfileIntA("TranscendentalBlow", "TBStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	TBPerGradeMultiPvE = GetPrivateProfileIntA("TranscendentalBlow", "TBPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	TBBaseDmgMultiPvP = GetPrivateProfileIntA("TranscendentalBlow", "TBBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	TBAgiMultiPvP = GetPrivateProfileIntA("TranscendentalBlow", "TBAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	TBStrMultiPvP = GetPrivateProfileIntA("TranscendentalBlow", "TBStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	TBPerGradeMultiPvP = GetPrivateProfileIntA("TranscendentalBlow", "TBPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	TBPvEMaxHits = GetPrivateProfileIntA("TranscendentalBlow", "TBPvEMaxHits", 1, "./Skills/ZenSkillConfig.txt");
	
	SWBaseDmgMultiPvE = GetPrivateProfileIntA("ShockWave", "SWBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	SWWisMultiPvE = GetPrivateProfileIntA("ShockWave", "SWWisMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	SWIntMultiPvE = GetPrivateProfileIntA("ShockWave", "SWIntMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	SWPerGradeMultiPvE = GetPrivateProfileIntA("ShockWave", "SWPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	SWBaseDmgMultiPvP = GetPrivateProfileIntA("ShockWave", "SWBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SWWisMultiPvP = GetPrivateProfileIntA("ShockWave", "SWWisMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SWIntMultiPvP = GetPrivateProfileIntA("ShockWave", "SWIntMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SWPerGradeMultiPvP = GetPrivateProfileIntA("ShockWave", "SWPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	SWPvEMaxHits = GetPrivateProfileIntA("ShockWave", "SWPvEMaxHits", 1, "./Skills/ZenSkillConfig.txt");



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

	//Third Job Skills

	ARBaseDmgMultiPvE = GetPrivateProfileIntA("ArrowRain", "ARBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ARStrMultiPvE = GetPrivateProfileIntA("ArrowRain", "ARStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ARAgiMultiPvE = GetPrivateProfileIntA("ArrowRain", "ARAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ARPerGradeMultiPvE = GetPrivateProfileIntA("ArrowRain", "ARPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ARDamagePercentageReducePvE = GetPrivateProfileIntA("ArrowRain", "ARDamagePercentageReducePvE", 1, "./Skills/ThirdJobSkills.txt");

	ARBaseDmgMultiPvP = GetPrivateProfileIntA("ArrowRain", "ARBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ARStrMultiPvP = GetPrivateProfileIntA("ArrowRain", "ARStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ARAgiMultiPvP = GetPrivateProfileIntA("ArrowRain", "ARAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ARPerGradeMultiPvP = GetPrivateProfileIntA("ArrowRain", "ARPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	CSBaseDmgMultiPvE = GetPrivateProfileIntA("CombativeSpirit", "CSBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	CSAgiMultiPvE = GetPrivateProfileIntA("CombativeSpirit", "CSAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	CSStrMultiPvE = GetPrivateProfileIntA("CombativeSpirit", "CSStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	CSPerGradeMultiPvE = GetPrivateProfileIntA("CombativeSpirit", "CSPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	CSBaseDmgMultiPvP = GetPrivateProfileIntA("CombativeSpirit", "CSBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	CSAgiMultiPvP = GetPrivateProfileIntA("CombativeSpirit", "CSAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	CSStrMultiPvP = GetPrivateProfileIntA("CombativeSpirit", "CSStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	CSPerGradeMultiPvP = GetPrivateProfileIntA("CombativeSpirit", "CSPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	AEBaseDmgMultiPvE = GetPrivateProfileIntA("ArrowExplosion", "AEBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	AEStrMultiPvE = GetPrivateProfileIntA("ArrowExplosion", "AEStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	AEAgiMultiPvE = GetPrivateProfileIntA("ArrowExplosion", "AEAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	AEPerGradeMultiPvE = GetPrivateProfileIntA("ArrowExplosion", "AEPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	AEBaseDmgMultiPvP = GetPrivateProfileIntA("ArrowExplosion", "AEBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	AEStrMultiPvP = GetPrivateProfileIntA("ArrowExplosion", "AEStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	AEAgiMultiPvP = GetPrivateProfileIntA("ArrowExplosion", "AEAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	AEPerGradeMultiPvP = GetPrivateProfileIntA("ArrowExplosion", "AEPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");


	VAPerGradeDoTPvE = GetPrivateProfileIntA("VirulentArrow", "VAPerGradeDoTPvE", 1, "./Skills/ThirdJobSkills.txt");
	VABaseDoTPvE = GetPrivateProfileIntA("VirulentArrow", "VABaseDoTPvE", 1, "./Skills/ThirdJobSkills.txt");

	VAPerGradeDoTPvP = GetPrivateProfileIntA("VirulentArrow", "VAPerGradeDoTPvP", 1, "./Skills/ThirdJobSkills.txt");
	VABaseDoTPvP = GetPrivateProfileIntA("VirulentArrow", "VABaseDoTPvP", 1, "./Skills/ThirdJobSkills.txt");

	VABaseDmgMultiPvE = GetPrivateProfileIntA("VirulentArrow", "VABaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	VAAgiMultiPvE = GetPrivateProfileIntA("VirulentArrow", "VAAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	VAStrMultiPvE = GetPrivateProfileIntA("VirulentArrow", "VAStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	VAPerGradeMultiPvE = GetPrivateProfileIntA("VirulentArrow", "VAPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	VABaseDmgMultiPvP = GetPrivateProfileIntA("VirulentArrow", "VABaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	VAAgiMultiPvP = GetPrivateProfileIntA("VirulentArrow", "VAAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	VAStrMultiPvP = GetPrivateProfileIntA("VirulentArrow", "VAStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	VAPerGradeMultiPvP = GetPrivateProfileIntA("VirulentArrow", "VAPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	VADuration = GetPrivateProfileIntA("VirulentArrow", "VADuration", 1, "./Skills/ThirdJobSkills.txt");

	SHSBaseDmgMultiPvE = GetPrivateProfileIntA("ShadowSlash", "SHSBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SHSAgiMultiPvE = GetPrivateProfileIntA("ShadowSlash", "SHSAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SHSStrMultiPvE = GetPrivateProfileIntA("ShadowSlash", "SHSStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SHSPerGradeMultiPvE = GetPrivateProfileIntA("ShadowSlash", "SHSPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	SHSBaseDmgMultiPvP = GetPrivateProfileIntA("ShadowSlash", "SHSBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SHSAgiMultiPvP = GetPrivateProfileIntA("ShadowSlash", "SHSAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SHSStrMultiPvP = GetPrivateProfileIntA("ShadowSlash", "SHSStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SHSPerGradeMultiPvP = GetPrivateProfileIntA("ShadowSlash", "SHSPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	SHSStunDuration = GetPrivateProfileIntA("ShadowSlash", "SHSStunDuration", 1, "./Skills/ThirdJobSkills.txt");
	SHSStunDurationPerGrade = GetPrivateProfileIntA("ShadowSlash", "SHSStunDurationPerGrade", 1, "./Skills/ThirdJobSkills.txt");

	LSTBaseDmgMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSTBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LSTAgiMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSTAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LSTStrMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSTStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LSTPerGradeMultiPvE = GetPrivateProfileIntA("LightningSlash", "LSTPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	LSTBaseDmgMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSTBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LSTAgiMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSTAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LSTStrMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSTStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LSTPerGradeMultiPvP = GetPrivateProfileIntA("LightningSlash", "LSTPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	SBBaseDmgMultiPvE = GetPrivateProfileIntA("SpinBlade", "SBBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SBAgiMultiPvE = GetPrivateProfileIntA("SpinBlade", "SBAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SBStrMultiPvE = GetPrivateProfileIntA("SpinBlade", "SBStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SBPerGradeMultiPvE = GetPrivateProfileIntA("SpinBlade", "SBPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	SBBaseDmgMultiPvP = GetPrivateProfileIntA("SpinBlade", "SBBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SBAgiMultiPvP = GetPrivateProfileIntA("SpinBlade", "SBAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SBStrMultiPvP = GetPrivateProfileIntA("SpinBlade", "SBStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SBPerGradeMultiPvP = GetPrivateProfileIntA("SpinBlade", "SBPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	
	WOHBaseDmgMultiPvE = GetPrivateProfileIntA("WrathOfHeaven", "WOHBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	WOHAgiMultiPvE = GetPrivateProfileIntA("WrathOfHeaven", "WOHAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	WOHStrMultiPvE = GetPrivateProfileIntA("WrathOfHeaven", "WOHStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	WOHPerGradeMultiPvE = GetPrivateProfileIntA("WrathOfHeaven", "WOHPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	WOHBaseDmgMultiPvP = GetPrivateProfileIntA("WrathOfHeaven", "WOHBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	WOHAgiMultiPvP = GetPrivateProfileIntA("WrathOfHeaven", "WOHAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	WOHStrMultiPvP = GetPrivateProfileIntA("WrathOfHeaven", "WOHStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	WOHPerGradeMultiPvP = GetPrivateProfileIntA("WrathOfHeaven", "WOHPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	SSBaseDmgMultiPvE = GetPrivateProfileIntA("SpinSlash", "SSBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SSAgiMultiPvE = GetPrivateProfileIntA("SpinSlash", "SSAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SSStrMultiPvE = GetPrivateProfileIntA("SpinSlash", "SSStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SSPerGradeMultiPvE = GetPrivateProfileIntA("SpinSlash", "SSPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SSAdditonalDMG = GetPrivateProfileIntA("SpinSlash", "SSAdditonalDMG", 1, "./Skills/ThirdJobSkills.txt");

	SSBaseDmgMultiPvP = GetPrivateProfileIntA("SpinSlash", "SSBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SSAgiMultiPvP = GetPrivateProfileIntA("SpinSlash", "SSAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SSStrMultiPvP = GetPrivateProfileIntA("SpinSlash", "SSStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SSPerGradeMultiPvP = GetPrivateProfileIntA("SpinSlash", "SSPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	SDBaseDmgMultiPvE = GetPrivateProfileIntA("SwordDance", "SDBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SDAgiMultiPvE = GetPrivateProfileIntA("SwordDance", "SDAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SDStrMultiPvE = GetPrivateProfileIntA("SwordDance", "SDStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	SDPerGradeMultiPvE = GetPrivateProfileIntA("SwordDance", "SDPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	SDBaseDmgMultiPvP = GetPrivateProfileIntA("SwordDance", "SDBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SDAgiMultiPvP = GetPrivateProfileIntA("SwordDance", "SDAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SDStrMultiPvP = GetPrivateProfileIntA("SwordDance", "SDStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	SDPerGradeMultiPvP = GetPrivateProfileIntA("SwordDance", "SDPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");


	PoBBaseDmgMultiPvE = GetPrivateProfileIntA("ProvocationOfBlow", "PoBBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	PoBAgiMultiPvE = GetPrivateProfileIntA("ProvocationOfBlow", "PoBAgiMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	PoBStrMultiPvE = GetPrivateProfileIntA("ProvocationOfBlow", "PoBStrMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	PoBPerGradeMultiPvE = GetPrivateProfileIntA("ProvocationOfBlow", "PoBPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	PoBHostilityMultiplier = GetPrivateProfileIntA("ProvocationOfBlow", "PoBHostilityMultiplier", 1, "./Skills/ThirdJobSkills.txt");
	PoBDmgPercentIncreasePDPvE = GetPrivateProfileIntA("ProvocationOfBlow", "PoBDmgPercentIncreasePDPvE", 1, "./Skills/ThirdJobSkills.txt");

	PoBBaseDmgMultiPvP = GetPrivateProfileIntA("ProvocationOfBlow", "PoBBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	PoBAgiMultiPvP = GetPrivateProfileIntA("ProvocationOfBlow", "PoBAgiMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	PoBStrMultiPvP = GetPrivateProfileIntA("ProvocationOfBlow", "PoBStrMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	PoBPerGradeMultiPvP = GetPrivateProfileIntA("ProvocationOfBlow", "PoBPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	TTBaseHeal = GetPrivateProfileIntA("TherapeuticTouch", "TTBaseHeal", 1, "./Skills/ThirdJobSkills.txt");
	TTPerGradeHeal = GetPrivateProfileIntA("TherapeuticTouch", "TTPerGradeHeal", 1, "./Skills/ThirdJobSkills.txt");
	TTWisdom = GetPrivateProfileIntA("TherapeuticTouch", "TTWisdom", 1, "./Skills/ThirdJobSkills.txt");
	TTDuration = GetPrivateProfileIntA("TherapeuticTouch", "TTDuration", 1, "./Skills/ThirdJobSkills.txt");

	ICIBaseDmgMultiPvE = GetPrivateProfileIntA("Icicle", "ICIBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ICIIntMultiPvE = GetPrivateProfileIntA("Icicle", "ICIIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	ICIPerGradeMultiPvE = GetPrivateProfileIntA("Icicle", "ICIPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	ICIBaseDmgMultiPvP = GetPrivateProfileIntA("Icicle", "ICIBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ICIIntMultiPvP = GetPrivateProfileIntA("Icicle", "ICIIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ICIPerGradeMultiPvP = GetPrivateProfileIntA("Icicle", "ICIPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	ICIColdBindDuration = GetPrivateProfileIntA("Icicle", "ICIColdBindDuration", 1, "./Skills/ThirdJobSkills.txt");


	FIBaseDmgMultiPvE = GetPrivateProfileIntA("FlameInjection", "FIBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	FIIntMultiPvE = GetPrivateProfileIntA("FlameInjection", "FIIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	FIPerGradeMultiPvE = GetPrivateProfileIntA("FlameInjection", "FIPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	FIBaseDmgMultiPvP = GetPrivateProfileIntA("FlameInjection", "FIBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	FIIntMultiPvP = GetPrivateProfileIntA("FlameInjection", "FIIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	FIPerGradeMultiPvP = GetPrivateProfileIntA("FlameInjection", "FIPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	TBoltMBaseDmgMultiPvE = GetPrivateProfileIntA("Thunderbolt", "TBoltMBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	TBoltMIntMultiPvE = GetPrivateProfileIntA("Thunderbolt", "TBoltMIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	TBoltMPerGradeMultiPvE = GetPrivateProfileIntA("Thunderbolt", "TBoltMPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	TBoltMBaseDmgMultiPvP = GetPrivateProfileIntA("Thunderbolt", "TBoltMBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	TBoltMIntMultiPvP = GetPrivateProfileIntA("Thunderbolt", "TBoltMIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	TBoltMPerGradeMultiPvP = GetPrivateProfileIntA("Thunderbolt", "TBoltMPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	IAMBaseDmgMultiPvE = GetPrivateProfileIntA("IceArrow", "IAMBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	IAMIntMultiPvE = GetPrivateProfileIntA("IceArrow", "IAMIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	IAMPerGradeMultiPvE = GetPrivateProfileIntA("IceArrow", "IAMPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	IAMBaseDmgMultiPvP = GetPrivateProfileIntA("IceArrow", "IAMBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	IAMIntMultiPvP = GetPrivateProfileIntA("IceArrow", "IAMIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	IAMPerGradeMultiPvP = GetPrivateProfileIntA("IceArrow", "IAMPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	FBBaseDmgMultiPvE = GetPrivateProfileIntA("Fireball", "FBBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	FBIntMultiPvE = GetPrivateProfileIntA("Fireball", "FBIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	FBPerGradeMultiPvE = GetPrivateProfileIntA("Fireball", "FBPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	FBBaseDmgMultiPvP = GetPrivateProfileIntA("Fireball", "FBBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	FBIntMultiPvP = GetPrivateProfileIntA("Fireball", "FBIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	FBPerGradeMultiPvP = GetPrivateProfileIntA("Fireball", "FBPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");


	LABaseDmgMultiPvE = GetPrivateProfileIntA("LightningArrow", "LABaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LAIntMultiPvE = GetPrivateProfileIntA("LightningArrow", "LAIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LAPerGradeMultiPvE = GetPrivateProfileIntA("LightningArrow", "LAPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	LABaseDmgMultiPvP = GetPrivateProfileIntA("LightningArrow", "LABaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LAIntMultiPvP = GetPrivateProfileIntA("LightningArrow", "LAIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LAPerGradeMultiPvP = GetPrivateProfileIntA("LightningArrow", "LAPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	LAActivationBaseDmgMultiPvE = GetPrivateProfileIntA("LightningArrow", "LAActivationBaseDmgMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LAActivationIntMultiPvE = GetPrivateProfileIntA("LightningArrow", "LAActivationIntMultiPvE", 1, "./Skills/ThirdJobSkills.txt");
	LAActivationPerGradeMultiPvE = GetPrivateProfileIntA("LightningArrow", "LAActivationPerGradeMultiPvE", 1, "./Skills/ThirdJobSkills.txt");

	LAActivationBaseDmgMultiPvP = GetPrivateProfileIntA("LightningArrow", "LAActivationBaseDmgMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LAActivationIntMultiPvP = GetPrivateProfileIntA("LightningArrow", "LAActivationIntMultiPvP", 1, "./Skills/ThirdJobSkills.txt");
	LAActivationPerGradeMultiPvP = GetPrivateProfileIntA("LightningArrow", "LAActivationPerGradeMultiPvP", 1, "./Skills/ThirdJobSkills.txt");

	LADuration = GetPrivateProfileIntA("LightningArrow", "LADuration", 1, "./Skills/ThirdJobSkills.txt");


	COChanceToPopBase = GetPrivateProfileIntA("CounterOffensive", "COChanceToPopBase", 1, "./Skills/ThiefSecondJob.txt");
	COChanceToPopPerGrade = GetPrivateProfileIntA("CounterOffensive", "COChanceToPopPerGrade", 1, "./Skills/ThiefSecondJob.txt");

	CODamageMultiPvE = GetPrivateProfileIntA("CounterOffensive", "CODamageMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	CODamageMultiPvP = GetPrivateProfileIntA("CounterOffensive", "CODamageMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	
	COBaseDamagePvE = GetPrivateProfileIntA("CounterOffensive", "COBaseDamagePvE", 1, "./Skills/ThiefSecondJob.txt");
	COBaseDamagePvP = GetPrivateProfileIntA("CounterOffensive", "COBaseDamagePvP", 1, "./Skills/ThiefSecondJob.txt");

	COBoostPercentage3rdJob = GetPrivateProfileIntA("CounterOffensive", "COBoostPercentage3rdJob", 1, "./Skills/ThiefSecondJob.txt");

	CAChanceToPopBase = GetPrivateProfileIntA("CounterAttack", "CAChanceToPopBase", 1, "./Skills/ThiefSecondJob.txt");
	CAChanceToPopPerGrade = GetPrivateProfileIntA("CounterAttack", "CAChanceToPopPerGrade", 1, "./Skills/ThiefSecondJob.txt");

	CADamageMultiPvE = GetPrivateProfileIntA("CounterAttack", "CADamageMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	CADamageMultiPvP = GetPrivateProfileIntA("CounterAttack", "CADamageMultiPvP", 1, "./Skills/ThiefSecondJob.txt");

	CABaseDamagePvE = GetPrivateProfileIntA("CounterAttack", "CABaseDamagePvE", 1, "./Skills/ThiefSecondJob.txt");
	CABaseDamagePvP = GetPrivateProfileIntA("CounterAttack", "CABaseDamagePvP", 1, "./Skills/ThiefSecondJob.txt");

	//DoKDamageMultiPvE = GetPrivateProfileIntA("DanceOfKilling", "DoKDamageMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	//DoKDamageMultiPvP = GetPrivateProfileIntA("DanceOfKilling", "DoKDamageMultiPvP", 1, "./Skills/ThiefSecondJob.txt");

	SABaseDmgMultiPvE = GetPrivateProfileIntA("SpinAttack", "SABaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	SAAgiMultiPvE = GetPrivateProfileIntA("SpinAttack", "SAAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	SAStrMultiPvE = GetPrivateProfileIntA("SpinAttack", "SAStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	SAPerGradeMultiPvE = GetPrivateProfileIntA("SpinAttack", "SAPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");

	SABaseDmgMultiPvP = GetPrivateProfileIntA("SpinAttack", "SABaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	SAAgiMultiPvP = GetPrivateProfileIntA("SpinAttack", "SAAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	SAStrMultiPvP = GetPrivateProfileIntA("SpinAttack", "SAStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	SAPerGradeMultiPvP = GetPrivateProfileIntA("SpinAttack", "SAPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");


	ABreakerAdditionalDamage = GetPrivateProfileIntA("ArmorBreaker", "ABreakerAdditionalDamage", 1, "./Skills/ThiefSecondJob.txt");
	ABreakerAdditionalDamagePerGrade = GetPrivateProfileIntA("ArmorBreaker", "ABreakerAdditionalDamagePerGrade", 1, "./Skills/ThiefSecondJob.txt");

	ABreakerDuration = GetPrivateProfileIntA("ArmorBreaker", "ABreakerDuration", 1, "./Skills/ThiefSecondJob.txt");
	ABreakerDurationPerGrade = GetPrivateProfileIntA("ArmorBreaker", "ABreakerDurationPerGrade", 1, "./Skills/ThiefSecondJob.txt");

	TBSBaseDmgMultiPvE = GetPrivateProfileIntA("TwinBladeStrike", "TBSaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	TBSAgiMultiPvE = GetPrivateProfileIntA("TwinBladeStrike", "TBSAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	TBSStrMultiPvE = GetPrivateProfileIntA("TwinBladeStrike", "TBSStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");

	TBSBaseDmgMultiPvP = GetPrivateProfileIntA("TwinBladeStrike", "TBSBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	TBSAgiMultiPvP = GetPrivateProfileIntA("TwinBladeStrike", "TBSAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	TBSStrMultiPvP = GetPrivateProfileIntA("TwinBladeStrike", "TBSStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");


	FWBaseDmgMultiPvE = GetPrivateProfileIntA("FatalWound", "FWBaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FWAgiMultiPvE = GetPrivateProfileIntA("FatalWound", "FWAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FWStrMultiPvE = GetPrivateProfileIntA("FatalWound", "FWStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FWPerGradeMultiPvE = GetPrivateProfileIntA("FatalWound", "FWPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");

	FWBaseDmgMultiPvP = GetPrivateProfileIntA("FatalWound", "FWBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FWAgiMultiPvP = GetPrivateProfileIntA("FatalWound", "FWAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FWStrMultiPvP = GetPrivateProfileIntA("FatalWound", "FWStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FWPerGradeMultiPvP = GetPrivateProfileIntA("FatalWound", "FWPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	
	FinalBBaseDmgMultiPvE = GetPrivateProfileIntA("FinalBlow", "FinalBBaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FinalBAgiMultiPvE = GetPrivateProfileIntA("FinalBlow", "FinalBAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FinalBStrMultiPvE = GetPrivateProfileIntA("FinalBlow", "FinalBStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FinalBPerGradeMultiPvE = GetPrivateProfileIntA("FinalBlow", "FinalBPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	FinalBMultiWhenBelowPvE = GetPrivateProfileIntA("FinalBlow", "FinalBMultiWhenBelowPvE", 1, "./Skills/ThiefSecondJob.txt");

	FinalBBaseDmgMultiPvP = GetPrivateProfileIntA("FinalBlow", "FinalBBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FinalBAgiMultiPvP = GetPrivateProfileIntA("FinalBlow", "FinalBAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FinalBStrMultiPvP = GetPrivateProfileIntA("FinalBlow", "FinalBStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FinalBPerGradeMultiPvP = GetPrivateProfileIntA("FinalBlow", "FinalBPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	FinalBMultiWhenBelowPvP = GetPrivateProfileIntA("FinalBlow", "FinalBMultiWhenBelowPvP", 1, "./Skills/ThiefSecondJob.txt");
	
	TSBDamagePerHPPvE = GetPrivateProfileIntA("SuicidalBlow", "TSBDamagePerHPPvE", 1, "./Skills/ThiefSecondJob.txt");
	TSBBaseDmgMultiPvE = GetPrivateProfileIntA("SuicidalBlow", "TSBBaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	TSBAgiMultiPvE = GetPrivateProfileIntA("SuicidalBlow", "TSBAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	TSBStrMultiPvE = GetPrivateProfileIntA("SuicidalBlow", "TSBStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	TSBPerGradeMultiPvE = GetPrivateProfileIntA("SuicidalBlow", "TSBPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");

	TSBDamagePerHPPvP = GetPrivateProfileIntA("SuicidalBlow", "TSBDamagePerHPPvP", 1, "./Skills/ThiefSecondJob.txt");
	TSBBaseDmgMultiPvP = GetPrivateProfileIntA("SuicidalBlow", "TSBBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	TSBAgiMultiPvP = GetPrivateProfileIntA("SuicidalBlow", "TSBAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	TSBStrMultiPvP = GetPrivateProfileIntA("SuicidalBlow", "TSBStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	TSBPerGradeMultiPvP= GetPrivateProfileIntA("SuicidalBlow", "TSBPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");

	TSBHPPercent = GetPrivateProfileIntA("SuicidalBlow", "TSBHPPercent", 1, "./Skills/ThiefSecondJob.txt");

	VSBaseDmgMultiPvE = GetPrivateProfileIntA("VitalStrike", "VSBaseDmgMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	VSAgiMultiPvE = GetPrivateProfileIntA("VitalStrike", "VSAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	VSStrMultiPvE = GetPrivateProfileIntA("VitalStrike", "VSStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	VSPerGradeMultiPvE = GetPrivateProfileIntA("VitalStrike", "VSPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	VSDmgMultiWhenBelowPvE = GetPrivateProfileIntA("VitalStrike", "VSDmgMultiWhenBelowPvE", 1, "./Skills/ThiefSecondJob.txt");

	VSBaseDmgMultiPvP = GetPrivateProfileIntA("VitalStrike", "VSBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	VSAgiMultiPvP = GetPrivateProfileIntA("VitalStrike", "VSAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	VSStrMultiPvP = GetPrivateProfileIntA("VitalStrike", "VSStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	VSPerGradeMultiPvP = GetPrivateProfileIntA("VitalStrike", "VSPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	VSDmgMultiWhenBelowPvP = GetPrivateProfileIntA("VitalStrike", "VSDmgMultiWhenBelowPvP", 1, "./Skills/ThiefSecondJob.txt");

	RupBaseDmgMultiPvE = GetPrivateProfileIntA("Rupture", "VSDmgMultiWhenBelowPvP", 1, "./Skills/ThiefSecondJob.txt");
	RupAgiMultiPvE = GetPrivateProfileIntA("Rupture", "RupAgiMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	RupStrMultiPvE = GetPrivateProfileIntA("Rupture", "RupStrMultiPvE", 1, "./Skills/ThiefSecondJob.txt");
	RupPerGradeMultiPvE = GetPrivateProfileIntA("Rupture", "RupPerGradeMultiPvE", 1, "./Skills/ThiefSecondJob.txt");

	RupBaseDmgMultiPvP = GetPrivateProfileIntA("Rupture", "RupBaseDmgMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	RupAgiMultiPvP = GetPrivateProfileIntA("Rupture", "RupAgiMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	RupStrMultiPvP = GetPrivateProfileIntA("Rupture", "RupStrMultiPvP", 1, "./Skills/ThiefSecondJob.txt");
	RupPerGradeMultiPvP = GetPrivateProfileIntA("Rupture", "RupPerGradeMultiPvP", 1, "./Skills/ThiefSecondJob.txt");

	
	PUSBaseDmgMultiPvE = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PUSAgiMultiPvE = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PUSStrMultiPvE = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	PUSPerGradeMultiPvE = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	PUSBaseDmgMultiPvP = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PUSAgiMultiPvP = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PUSStrMultiPvP = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	PUSPerGradeMultiPvP = GetPrivateProfileIntA("PowerfulUpwardSlash", "PUSPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");

	BRUTBaseDmgMultiPvE = GetPrivateProfileIntA("BrutalAttack", "BRUTBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BRUTAgiMultiPvE = GetPrivateProfileIntA("BrutalAttack", "BRUTAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BRUTStrMultiPvE = GetPrivateProfileIntA("BrutalAttack", "BRUTStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	BRUTPerGradeMultiPvE = GetPrivateProfileIntA("BrutalAttack", "BRUTPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	BRUTBaseDmgMultiPvP = GetPrivateProfileIntA("BrutalAttack", "BRUTBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BRUTAgiMultiPvP = GetPrivateProfileIntA("BrutalAttack", "BRUTAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BRUTStrMultiPvP = GetPrivateProfileIntA("BrutalAttack", "BRUTStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	BRUTPerGradeMultiPvP = GetPrivateProfileIntA("BrutalAttack", "BRUTPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");

	
	HSBaseDmgMultiPvE = GetPrivateProfileIntA("HalfSwing", "HSBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	HSAgiMultiPvE = GetPrivateProfileIntA("HalfSwing", "HSAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	HSStrMultiPvE = GetPrivateProfileIntA("HalfSwing", "HSStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	HSPerGradeMultiPvE = GetPrivateProfileIntA("HalfSwing", "HSPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	HSBaseDmgMultiPvP = GetPrivateProfileIntA("HalfSwing", "HSBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	HSAgiMultiPvP = GetPrivateProfileIntA("HalfSwing", "HSAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	HSStrMultiPvP = GetPrivateProfileIntA("HalfSwing", "HSStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	HSPerGradeMultiPvP = GetPrivateProfileIntA("HalfSwing", "HSPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	
	LAbsBaseDmgMultiPvE = GetPrivateProfileIntA("LifeAbsorption", "LAbsBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LAbsAgiMultiPvE = GetPrivateProfileIntA("LifeAbsorption", "LAbsAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LAbsStrMultiPvE = GetPrivateProfileIntA("LifeAbsorption", "LAbsStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	LAbsPerGradeMultiPvE = GetPrivateProfileIntA("LifeAbsorption", "LAbsPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	LAbsBaseDmgMultiPvP = GetPrivateProfileIntA("LifeAbsorption", "LAbsBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LAbsAgiMultiPvP = GetPrivateProfileIntA("LifeAbsorption", "LAbsAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LAbsStrMultiPvP = GetPrivateProfileIntA("LifeAbsorption", "LAbsStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	LAbsPerGradeMultiPvP = GetPrivateProfileIntA("LifeAbsorption", "LAbsPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	
	//LAbsHealBase = GetPrivateProfileIntA("LifeAbsorption", "LAbsHealBase", 1, "./Skills/ZenSkillConfig.txt");
	LAbsHealPerGrade = GetPrivateProfileIntA("LifeAbsorption", "LAbsHealPerGrade", 1, "./Skills/ZenSkillConfig.txt");

	FSBaseDmgMultiPvE = GetPrivateProfileIntA("FocusShot", "FSBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FSAgiMultiPvE = GetPrivateProfileIntA("FocusShot", "FSAgiMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FSStrMultiPvE = GetPrivateProfileIntA("FocusShot", "FSStrMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FSPerGradeMultiPvE = GetPrivateProfileIntA("FocusShot", "FSPerGradeMultiPvE", 1, "./Skills/ZenSkillConfig.txt");

	FSBaseDmgMultiPvP = GetPrivateProfileIntA("FocusShot", "FSBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FSAgiMultiPvP = GetPrivateProfileIntA("FocusShot", "FSAgiMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FSStrMultiPvP = GetPrivateProfileIntA("FocusShot", "FSStrMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FSPerGradeMultiPvP = GetPrivateProfileIntA("FocusShot", "FSPerGradeMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	

	CLBaseDmgMultiPvE = GetPrivateProfileIntA("ChainLightning", "CLBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	CLIntMultiPvE = GetPrivateProfileIntA("ChainLightning", "CLIntMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	CLBaseDmgMultiPvP = GetPrivateProfileIntA("ChainLightning", "CLBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	CLIntMultiPvP = GetPrivateProfileIntA("ChainLightning", "CLIntMultiPvP", 1, "./Skills/ZenSkillConfig.txt");


	IStormBaseDmgMultiPvE = GetPrivateProfileIntA("IceStorm", "IStormBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	IStormIntMultiPvE = GetPrivateProfileIntA("IceStorm", "IStormIntMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	IStormBaseDmgMultiPvP = GetPrivateProfileIntA("IceStorm", "IStormBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	IStormIntMultiPvP = GetPrivateProfileIntA("IceStorm", "IStormIntMultiPvP", 1, "./Skills/ZenSkillConfig.txt");

	TStormBaseDmgMultiPvE = GetPrivateProfileIntA("ThunderStorm", "TStormBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	TStormIntMultiPvE = GetPrivateProfileIntA("ThunderStorm", "TStormIntMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	TStormBaseDmgMultiPvP = GetPrivateProfileIntA("ThunderStorm", "TStormBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	TStormIntMultiPvP = GetPrivateProfileIntA("ThunderStorm", "TStormIntMultiPvP", 1, "./Skills/ZenSkillConfig.txt");


	FStormBaseDmgMultiPvE = GetPrivateProfileIntA("FireStorm", "FStormBaseDmgMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FStormIntMultiPvE = GetPrivateProfileIntA("FireStorm", "FStormIntMultiPvE", 1, "./Skills/ZenSkillConfig.txt");
	FStormBaseDmgMultiPvP = GetPrivateProfileIntA("FireStorm", "FStormBaseDmgMultiPvP", 1, "./Skills/ZenSkillConfig.txt");
	FStormIntMultiPvP = GetPrivateProfileIntA("FireStorm", "FStormIntMultiPvP", 1, "./Skills/ZenSkillConfig.txt");


	BSBaseDmgMultiPvE = GetPrivateProfileIntA("BloodSuction", "BSBaseDmgMultiPvE", 1, "./Skills/AnimalSkills.txt");
	BSBaseDmgMultiPvP = GetPrivateProfileIntA("BloodSuction", "BSBaseDmgMultiPvE", 1, "./Skills/AnimalSkills.txt");

	EggTBBaseDmgMultiPvE = GetPrivateProfileIntA("EggThunderbolt", "EggTBBaseDmgMultiPvE", 1, "./Skills/AnimalSkills.txt");
	EggTBBaseDmgMultiPvP = GetPrivateProfileIntA("EggThunderbolt", "EggTBBaseDmgMultiPvP", 1, "./Skills/AnimalSkills.txt");

	WFBaseDmgMultiPvE = GetPrivateProfileIntA("WhirlwindFeather", "WFBaseDmgMultiPvE", 1, "./Skills/AnimalSkills.txt");
	WFBaseDmgMultiPvP = GetPrivateProfileIntA("WhirlwindFeather", "WFBaseDmgMultiPvP", 1, "./Skills/AnimalSkills.txt");

	RABaseDmgMultiPvE = GetPrivateProfileIntA("RevolveAttack", "RABaseDmgMultiPvE", 1, "./Skills/AnimalSkills.txt");
	RABaseDmgMultiPvP = GetPrivateProfileIntA("RevolveAttack", "RABaseDmgMultiPvP", 1, "./Skills/AnimalSkills.txt");

	AnkleAPercentDamageIncreasePvE = GetPrivateProfileIntA("AnkleAmputate", "AnkleAPercentDamageIncreasePvE", 1, "./Skills/ThiefSecondJob.txt");
	AnkleAPercentDamageIncreasePvP = GetPrivateProfileIntA("AnkleAmputate", "AnkleAPercentDamageIncreasePvP", 1, "./Skills/ThiefSecondJob.txt");

	AOTMBaseDmgMultiPvE = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMBaseDmgMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	AOTMAgiMultiPvE = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMAgiMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	AOTMStrMultiPvE = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMStrMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	AOTMPerGradeMultiPvE = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMPerGradeMultiPvE", 1, "./Skills/ForthJobSkills.txt");

	AOTMBaseDmgMultiPvP = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMBaseDmgMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	AOTMAgiMultiPvP = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMAgiMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	AOTMStrMultiPvP = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMStrMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	AOTMPerGradeMultiPvP = GetPrivateProfileIntA("ArrowsoftheMaster", "AOTMPerGradeMultiPvP", 1, "./Skills/ForthJobSkills.txt");

	OHSBaseDmgMultiPvE = GetPrivateProfileIntA("OneHitStrike", "OHSBaseDmgMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	OHSAgiMultiPvE = GetPrivateProfileIntA("OneHitStrike", "OHSAgiMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	OHSStrMultiPvE = GetPrivateProfileIntA("OneHitStrike", "OHSStrMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	OHSPerGradeMultiPvE = GetPrivateProfileIntA("OneHitStrike", "OHSPerGradeMultiPvE", 1, "./Skills/ForthJobSkills.txt");

	OHSBaseDmgMultiPvP = GetPrivateProfileIntA("OneHitStrike", "OHSBaseDmgMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	OHSAgiMultiPvP = GetPrivateProfileIntA("OneHitStrike", "OHSAgiMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	OHSStrMultiPvP = GetPrivateProfileIntA("OneHitStrike", "OHSStrMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	OHSPerGradeMultiPvP = GetPrivateProfileIntA("OneHitStrike", "OHSPerGradeMultiPvP", 1, "./Skills/ForthJobSkills.txt");



	MFBaseDmgMultiPvE = GetPrivateProfileIntA("MassiveFire", "MFBaseDmgMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	MFAgiMultiPvE = GetPrivateProfileIntA("MassiveFire", "MFAgiMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	MFStrMultiPvE = GetPrivateProfileIntA("MassiveFire", "MFStrMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	MFPerGradeMultiPvE = GetPrivateProfileIntA("MassiveFire", "MFPerGradeMultiPvE", 1, "./Skills/ForthJobSkills.txt");

	MFBaseDmgMultiPvP = GetPrivateProfileIntA("MassiveFire", "MFBaseDmgMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	MFAgiMultiPvP = GetPrivateProfileIntA("MassiveFire", "MFAgiMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	MFStrMultiPvP = GetPrivateProfileIntA("MassiveFire", "MFStrMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	MFPerGradeMultiPvP = GetPrivateProfileIntA("MassiveFire", "MFPerGradeMultiPvP", 1, "./Skills/ForthJobSkills.txt");



	SOTABaseDmgMultiPvE = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTABaseDmgMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	SOTAAgiMultiPvE = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAAgiMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	SOTAStrMultiPvE = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAStrMultiPvE", 1, "./Skills/ForthJobSkills.txt");
	SOTAPerGradeMultiPvE = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAPerGradeMultiPvE", 1, "./Skills/ForthJobSkills.txt");

	SOTABaseDmgMultiPvP = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTABaseDmgMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	SOTAAgiMultiPvP = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAAgiMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	SOTAStrMultiPvP = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAStrMultiPvP", 1, "./Skills/ForthJobSkills.txt");
	SOTAPerGradeMultiPvP = GetPrivateProfileIntA("SpiritOfTheArrows", "SOTAPerGradeMultiPvP", 1, "./Skills/ForthJobSkills.txt");




		BloodSuctionON = GetPrivateProfileIntA("AnimalSkill", "BloodSuction", 0, "./Skills/SkillONOFF.txt");
		EggThunderboltON = GetPrivateProfileIntA("AnimalSkill", "EggThunderbolt", 0, "./Skills/SkillONOFF.txt");
		RevolveAttackON = GetPrivateProfileIntA("AnimalSkill", "RevolveAttack", 0, "./Skills/SkillONOFF.txt");
		WhirlwindFeatherON = GetPrivateProfileIntA("AnimalSkill", "WhirlwindFeather", 0, "./Skills/SkillONOFF.txt");


		BlowUpArrowON = GetPrivateProfileIntA("FirstJobSkill", "BlowUpArrow", 0, "./Skills/SkillONOFF.txt");
		FlamyArrowON = GetPrivateProfileIntA("FirstJobSkill", "FlamyArrow", 0, "./Skills/SkillONOFF.txt");
		HealON = GetPrivateProfileIntA("FirstJobSkill", "Heal", 0, "./Skills/SkillONOFF.txt");
		LightningSlashON = GetPrivateProfileIntA("FirstJobSkill", "LightningSlash", 0, "./Skills/SkillONOFF.txt");
		MuscleSolidationON = GetPrivateProfileIntA("FirstJobSkill", "MuscleSolidation", 0, "./Skills/SkillONOFF.txt");
		PassiveAttackON = GetPrivateProfileIntA("FirstJobSkill", "PassiveAttack", 0, "./Skills/SkillONOFF.txt");
		ShieldAttackON = GetPrivateProfileIntA("FirstJobSkill", "ShieldAttack", 0, "./Skills/SkillONOFF.txt");
		ShockWaveON = GetPrivateProfileIntA("FirstJobSkill", "ShockWave", 0, "./Skills/SkillONOFF.txt");
		TranscendentalBlowON = GetPrivateProfileIntA("FirstJobSkill", "TranscendentalBlow", 0, "./Skills/SkillONOFF.txt");
		CureON = GetPrivateProfileIntA("FirstJobSkill", "Cure", 0, "./Skills/SkillONOFF.txt");


		AmnesiaON = GetPrivateProfileIntA("SecondJobSkill", "Amnesia", 0, "./Skills/SkillONOFF.txt");
		AnkleAmputateON = GetPrivateProfileIntA("SecondJobSkill", "AnkleAmputate", 0, "./Skills/SkillONOFF.txt");
		ArmorBreakerON = GetPrivateProfileIntA("SecondJobSkill", "ArmorBreaker", 0, "./Skills/SkillONOFF.txt");
		BuffRemoverON = GetPrivateProfileIntA("SecondJobSkill", "BuffRemover", 0, "./Skills/SkillONOFF.txt");
		BrutalAttackON = GetPrivateProfileIntA("SecondJobSkill", "BrutalAttack", 0, "./Skills/SkillONOFF.txt");
		CallsON = GetPrivateProfileIntA("SecondJobSkill", "Calls", 0, "./Skills/SkillONOFF.txt");
		ChainLightningON = GetPrivateProfileIntA("SecondJobSkill", "ChainLightning", 0, "./Skills/SkillONOFF.txt");
		FatalWoundON = GetPrivateProfileIntA("SecondJobSkill", "FatalWound", 0, "./Skills/SkillONOFF.txt");
		FinalBlowON = GetPrivateProfileIntA("SecondJobSkill", "FinalBlow", 0, "./Skills/SkillONOFF.txt");
		FireStormON = GetPrivateProfileIntA("SecondJobSkill", "FireStorm", 0, "./Skills/SkillONOFF.txt");
		IceStormON = GetPrivateProfileIntA("SecondJobSkill", "IceStorm", 0, "./Skills/SkillONOFF.txt");
		ThunderStormON = GetPrivateProfileIntA("SecondJobSkill", "ThunderStorm", 0, "./Skills/SkillONOFF.txt");
		FocusShotON = GetPrivateProfileIntA("SecondJobSkill", "FocusShot", 0, "./Skills/SkillONOFF.txt");
		HalfSwingON = GetPrivateProfileIntA("SecondJobSkill", "HalfSwing", 0, "./Skills/SkillONOFF.txt");
		LifeAbsorptionON = GetPrivateProfileIntA("SecondJobSkill", "LifeAbsorption",0, "./Skills/SkillONOFF.txt");
		MysteriousArrowON = GetPrivateProfileIntA("SecondJobSkill", "MysteriousArrow", 0, "./Skills/SkillONOFF.txt");
		PowerfulUpwardSlashON = GetPrivateProfileIntA("SecondJobSkill", "PowerfulUpwardSlash", 0, "./Skills/SkillONOFF.txt");
		PurificationON = GetPrivateProfileIntA("SecondJobSkill", "Purification", 0, "./Skills/SkillONOFF.txt");
		RuptureON = GetPrivateProfileIntA("SecondJobSkill", "Rupture", 0, "./Skills/SkillONOFF.txt");
		SacrificeON = GetPrivateProfileIntA("SecondJobSkill", "Sacrifice", 0, "./Skills/SkillONOFF.txt");
		SpinAttackON = GetPrivateProfileIntA("SecondJobSkill", "SpinAttack", 0, "./Skills/SkillONOFF.txt");
		SuicidalBlowON = GetPrivateProfileIntA("SecondJobSkill", "SuicidalBlow", 0, "./Skills/SkillONOFF.txt");
		SummonsON = GetPrivateProfileIntA("SecondJobSkill", "Summons", 0, "./Skills/SkillONOFF.txt");
		TwinBladeStrikeON = GetPrivateProfileIntA("SecondJobSkill", "TwinBladeStrike", 0, "./Skills/SkillONOFF.txt");
		VitalStrikeON = GetPrivateProfileIntA("SecondJobSkill", "VitalStrike", 0, "./Skills/SkillONOFF.txt");
		//DanceOfKillingON = GetPrivateProfileIntA("SecondJobSkill", "DanceOfKilling", 0, "./Skills/SkillONOFF.txt");
		CounterOffensiveON = GetPrivateProfileIntA("SecondJobSkill", "CounterOffensive", 0, "./Skills/SkillONOFF.txt");
		CounterAttackON = GetPrivateProfileIntA("SecondJobSkill", "CounterAttack", 0, "./Skills/SkillONOFF.txt");
		SoulDestructionON = GetPrivateProfileIntA("SecondJobSkill", "SoulDestruction", 0, "./Skills/SkillONOFF.txt");
		PowerfulWideningWoundON = GetPrivateProfileIntA("SecondJobSkill", "PowerfulWideningWound", 0, "./Skills/SkillONOFF.txt");
		
		ArrowExplosionON = GetPrivateProfileIntA("ThirdJobSkill", "ArrowExplosion", 0, "./Skills/SkillONOFF.txt");
		ArrowRainON = GetPrivateProfileIntA("ThirdJobSkill", "ArrowRain", 0, "./Skills/SkillONOFF.txt");
		CombativeSpiritON = GetPrivateProfileIntA("ThirdJobSkill", "CombativeSpirit", 0, "./Skills/SkillONOFF.txt");
		FireballON = GetPrivateProfileIntA("ThirdJobSkill", "Fireball", 0, "./Skills/SkillONOFF.txt");
		FlameInjectionON = GetPrivateProfileIntA("ThirdJobSkill", "FlameInjection", 0, "./Skills/SkillONOFF.txt");
		IceArrowON = GetPrivateProfileIntA("ThirdJobSkill", "IceArrow", 0, "./Skills/SkillONOFF.txt");
		LightningArrowON = GetPrivateProfileIntA("ThirdJobSkill", "LightningArrow", 0, "./Skills/SkillONOFF.txt");
		LightningSlashThiefON = GetPrivateProfileIntA("ThirdJobSkill", "LightningSlashThief", 0, "./Skills/SkillONOFF.txt");
		ProvocationOfBlowON = GetPrivateProfileIntA("ThirdJobSkill", "ProvocationOfBlow", 0, "./Skills/SkillONOFF.txt");
		ShadowSlashON = GetPrivateProfileIntA("ThirdJobSkill", "ShadowSlash", 0, "./Skills/SkillONOFF.txt");
		SpinBladeON = GetPrivateProfileIntA("ThirdJobSkill", "SpinBlade", 0, "./Skills/SkillONOFF.txt");
		SpinSlashON = GetPrivateProfileIntA("ThirdJobSkill", "SpinSlash", 0, "./Skills/SkillONOFF.txt");
		SwordDanceON = GetPrivateProfileIntA("ThirdJobSkill", "SwordDance", 0, "./Skills/SkillONOFF.txt");
		TherapeuticTouchON = GetPrivateProfileIntA("ThirdJobSkill", "TherapeuticTouch", 0, "./Skills/SkillONOFF.txt");
		ThunderboltON = GetPrivateProfileIntA("ThirdJobSkill", "Thunderbolt", 0, "./Skills/SkillONOFF.txt");
		VirulentArrowON = GetPrivateProfileIntA("ThirdJobSkill", "VirulentArrow", 0, "./Skills/SkillONOFF.txt");
		WrathOfHeavenON = GetPrivateProfileIntA("ThirdJobSkill", "WrathOfHeaven", 0, "./Skills/SkillONOFF.txt");
		IcicleON = GetPrivateProfileIntA("ThirdJobSkill", "Icicle", 0, "./Skills/SkillONOFF.txt");


		OneHitStrikeON = GetPrivateProfileIntA("ForthJobSkill", "OneHitStrike", 0, "./Skills/SkillONOFF.txt");
		ArrowsoftheMasterON = GetPrivateProfileIntA("ForthJobSkill", "ArrowsoftheMaster", 0, "./Skills/SkillONOFF.txt");

		SpiritOfTheArrowsON = GetPrivateProfileIntA("ForthJobSkill", "SpiritOfTheArrows", 0, "./Skills/SkillONOFF.txt");
		MassiveFireON = GetPrivateProfileIntA("ForthJobSkill", "MassiveFire", 0, "./Skills/SkillONOFF.txt");

		TheBoomofEarthON = GetPrivateProfileIntA("ForthJobSkill", "TheBoomofEarth", 0, "./Skills/SkillONOFF.txt");
		ThewaveofEarthON = GetPrivateProfileIntA("ForthJobSkill", "ThewaveofEarth", 0, "./Skills/SkillONOFF.txt");

		ShoutOfFightingSpiritON = GetPrivateProfileIntA("ForthJobSkill", "ShoutOfFightingSpirit", 0, "./Skills/SkillONOFF.txt");
		ShoutOfDefenseON = GetPrivateProfileIntA("ForthJobSkill", "ShoutOfDefense", 0, "./Skills/SkillONOFF.txt");

		PunishmentON = GetPrivateProfileIntA("ForthJobSkill", "Punishment", 0, "./Skills/SkillONOFF.txt");
		ReleasingTheEnergyON = GetPrivateProfileIntA("ForthJobSkill", "ReleasingTheEnergy", 0, "./Skills/SkillONOFF.txt");

		IncapacitationON = GetPrivateProfileIntA("ForthJobSkill", "Incapacitation", 0, "./Skills/SkillONOFF.txt");
		BombingON = GetPrivateProfileIntA("ForthJobSkill", "Bombing", 0, "./Skills/SkillONOFF.txt");

		CriticalDiffusionON = GetPrivateProfileIntA("ForthJobSkill", "CriticalDiffusion", 0, "./Skills/SkillONOFF.txt");
		CriticalStrikeON = GetPrivateProfileIntA("ForthJobSkill", "CriticalStrike", 0, "./Skills/SkillONOFF.txt");

		DestroyingArmorON = GetPrivateProfileIntA("ForthJobSkill", "DestroyingArmor", 0, "./Skills/SkillONOFF.txt");
		StrikeOfGodON = GetPrivateProfileIntA("ForthJobSkill", "StrikeOfGod", 0, "./Skills/SkillONOFF.txt");



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