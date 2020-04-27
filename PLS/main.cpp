#pragma comment(lib, "detours.lib")

#undef UNICODE
#include <cstdio>
#include <windows.h>
#include "detours.h"
#include <process.h>
#include <fstream>
#include <map>
#include <vector>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <random>
#include <algorithm>
#include <math.h>
#include <direct.h>
#include <set>


std::string Int2String(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}

int String2Int(std::string String)
{
	int Integer;
	std::istringstream iss(String);
	iss >> Integer;
	return Integer;
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

struct Coordinates
{
	int x, y;
	int average_speed;
	int current_check;
	bool flag = false;
	bool check = false;
	int temp;
};

struct PlayerContinueSkill
{
	int PlayerX;
	int PlayerY;
	void *PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
};


struct PlayerFarContinueSkill
{
	void *PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
	int PlayerDamage;
	void* CasterOffset;
};

struct RuptureContinueSkill
{
	void *PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
	int PlayerDamage;
	void* CasterOffset;
};


struct CheckConfigCooldown
{
	int CooldownConfig;
	int DelayConfig;
};

struct CheckConfigEggCooldown
{
	int EggCooldownConfig;
	int EggDelayConfig;
};

struct Teleport
{
	int TeleportX;
	int TeleportY;
	int Map;
	int LevelLimit;
};


struct BuffItem
{
	int	BuffIndex = 0;
	int SecondBuffIndex = 0;
	int	Duration = 0;
	int	IconKey = 0;
	int Strength = 0;
	int Health = 0; 
	int Int = 0;
	int Wisdom = 0;
	int Agility = 0;
	int	PhysAttack = 0;
	int	MagicAttack = 0;
	int	OTP = 0;
	int	Evasion = 0;
	int	DEF = 0;
	int	HP = 0;
	int	MP = 0;
};

namespace ZenRNGesus
{
	int TotalBossCount = 0;
}
	struct Drop
	{
		int ItemID = 0;
		int ItemAmount = 0;
		int DropChance = 0;

		bool operator < (const Drop& d) const
		{
			return (this->DropChance < d.DropChance);
		}
	};

struct BossDrops
{
	int MinDamage = 0;
	int MinDamagePercent = 0;
	int MaxPlayers = 0;
	int MaxDropPerPlayer = 0;
	int AmountOfDifferentItems = 0;


	std::vector<Drop> Dropy;
	Drop TempDropStruct;
	int ItemsToDraw = 0;

};

enum ToFile
{
	SpeedHack = 1,
	SkillLogs = 2,
	Mails = 3,
	WoodenBox = 4,
	SkillHacks = 5
};

struct SkillCheck
{
	bool animation_check = false;
	int SkillID = 0;
	int time_used = 0;

};

std::map<int, SkillCheck> CastProtection;

std::map<int, Coordinates> PlayerCoords;

std::map<std::pair<void*, void*>, int> ::iterator boss;
std::map<int, BossDrops> ::iterator sIt;
std::map<int, BossDrops>BossDropsMap;
std::map<std::pair<void*, void*>, int>BossRNG;
std::map<int, BuffItem>::iterator bufx;
std::map<int, BuffItem>Buffs;
std::map<int, int> PlayerBlockCheck;
std::map<int, Teleport>ZenTP;
std::map<int, DWORD> MonsterDisappear;


std::map<int, CheckConfigCooldown> CheckCooldownConfig;
std::map<int, CheckConfigEggCooldown> CheckEggCooldownConfig;

std::map<int, int> CooldownTable;
std::map<int, int> EggCooldownTable;

std::map<int, DWORD> CODelay;
//std::map<int, int>CheckFocus;


bool TradeSystemON = 0;
bool LawlessZoneON = 0;
bool RiftON = 0;
bool D4InstanceON = 0;
bool MautaretaON = 0;

bool SpeedHackCheck = 0;

int ScrollItemID = 0;
int ScrollItemIconKey = 0;

int InstanceResetScrollID = 0;
int TradeSystemResetScrollID = 0;

bool Logs = 0;

std::ofstream SpeedHackLog;
std::ofstream SkillLog;
std::ofstream SkillHaxLog;
std::string SkillLogFile = "./ZenLogs/SkillUseLog";
std::string SpeedHackLogn = "./ZenLogs/SpeedHackLog";
std::string SkillHaxFile = "./ZenLogs/SkillHaxLog";
time_t now = time(0);

std::vector<int> Kn8WhiteListSkills;
std::vector<int> ::iterator itt;
std::vector<int> ArcherWhiteListSkills;
std::vector<int> MageWhiteListSkills;



enum TextColor
{
	TEXTCOLOR_GENERAL = RGB(255, 255, 255),
	TEXTCOLOR_INFOMSG = RGB(70, 227, 232),
	TEXTCOLOR_SHUTDOWN = RGB(240, 116, 15),
	TEXTCOLOR_ORANGE = RGB(255, 128, 64),
	TEXTCOLOR_BLUE = RGB(0, 128, 255),
	TEXTCOLOR_YELLOW = RGB(255, 255, 128),
	TEXTCOLOR_RED = RGB(255, 0, 0),
	TEXTCOLOR_PARTY = RGB(210, 64, 0),
	TEXTCOLOR_GUILD = RGB(10, 255, 229),
	TEXTCOLOR_ALLIANCE = RGB(128, 128, 192),
	TEXTCOLOR_GREEN = RGB(0, 255, 0),
	TEXTCOLOR_DARKGREEN = RGB(0, 170, 0),
	TEXTCOLOR_FAILED = RGB(250, 210, 0),
	TEXTCOLOR_CLASSMATE = RGB(0, 128, 0),
	TEXTCOLOR_PUPIL = RGB(255, 128, 64),
	TEXTCOLOR_PINK = RGB(255, 155, 255),
};

namespace D4Instance
{
	void* Party = 0;
	std::set<int> PartyMembers;
	int PartySize = 0;
	int MapNumber = 0;
	bool IsUp = false;
	int MobsCount[200] = { 0 };
	int CoordX[200] = { 0 };
	int CoordY[200] = { 0 };
	int MobID[200] = { 0 };
	int StageNumber = 0;
	int MobsKilled = 0;
	int MobsToKill = 0;
	int LastStage = 0;
	int Time = 0;
	int ReturnX = 0;
	int ReturnY = 0;
	int F2TP[3] = { 0 };
	int F3TP[3] = { 0 };
	int F4TP[3] = { 0 };
	int F5TP[3] = { 0 };
	int F6TP[3] = { 0 };
	int LastRoomTP[3] = { 0 };
	int FloorNumber = 0;
	int MinLevel = 0;
	int QuestID = 0;
	int SpawnX = 0;
	int SpawnY = 0;
	int Cooldown = 0;
	int Countdown = 0;
	int MinPartyMembers = 0;
}

int RiftAmount = 0;
struct Rifts
{
	bool IsUp = false;
	int SpawnX = 0;
	int SpawnY = 0;

	int MobID[200];
	int MobAmount[300];
	int MaxWave;

	int WaveNumber = 0;
	int MobDeadCount = 0;
	int Map = 0;
	int FirstBoss = 0;
	int BossMobSpawnID = 0;
	int BossMobSpawnAmount = 0;
	int Timer = 0;
};
Rifts RiftStruct[50] = { 0 };

namespace TradeSystem
{
	std::map<std::pair<int, int>,int>Quest;
	std::map<std::pair<int, int>, int> Reward;
	std::map<std::pair<int, int>,int> ::iterator it;
	std::map<std::pair<int, int>, int> ::iterator iterat;
	int ItemID = 0;
	int MinLvl = 60;
	int QuestRangeMin = 0;
	int QuestRangeMax = 0;
	int Cooldown = 0;
}

namespace LawlessZone
{
	std::vector<int>MobID;
	std::map<int, int>PointCounter;
	int TicketID = 0;
	int QuestID = 0;
	int QuitQuestID = 0;
	int BuffID=241;
	int MinLvl = 0;
	int MovingTrinketID = 0;
	int StartTeleportX = 0;
	int StartTeleportY = 0;
	int ReturnTeleportX = 0;
	int ReturnTeleportY = 0;
	int Map = 0;

	int Time = 0;
	int PKPoints = 0;
	int MobPoints = 0;

	int ExpBuffID[10] = { 1001,1002,1003,1004,1005,1006,1007,1008,1009,1010 };
}

namespace Mautareta
{
	bool IsUp = false;
	bool MautIsDead = false;
	int StartTeleportX = 0;
	int StartTeleportY = 0;
	int ReturnTeleportX = 0;
	int ReturnTeleportY = 0;
	int Map = 0;
	int BuffID = 254;                                                                         // buff when entering
	int BoostID[3];                                                                           // hp mana attack
	int BossID = 0;
	int WandererID = 0;
	int QuestItemID = 0;
	int QuestID = 0;
	int PartyLimit = 0;
	bool MobSummonCheck[19];
	double SpawnAtHP[19] = {0.95,0.90,0.85,0.80,0.75,0.70,0.65,0.60,0.55,0.50,0.45,0.40,0.35,0.30,0.25,0.20,0.15,0.10,0.05};
	int SpawnMautX = 0;
	int SpawnMautY = 0;
}




#pragma pack(1)
#include <string>
#include "ServerFunctions.h"
#include "ICharacter.h"
#include "IQuest.h"
#include "IItem.h"
#include "ExecuteSkill.h"
#include "ChatCommand.h"
#include "Summon.h"
#include "InstaConfig.h"
#include "Player.h"
#include "D4Instance.h"
#include "MonsterTick.h"
#include "PKKill.h"
#include "UpdateProperty.h"
#include "FinalDamage.h"
#include "CanAttack.h"
#include "Packet.h"
#include "SendMail.h"
#include "Resources.h"
#include "IConfig.h"




void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	CIOServer::Start(Start, hostshort);
	InstaConfig();
	ZenConfig();
	RiftConfig();
	MautaretaConfig();

	CONFIG.LoadSkillFormulas();
	ConsoleWriteBlue("CreativeZen's DLL loaded successfully");
	Sleep(500);

}


int __fastcall Hooked_MainServer_Stop(int stop)
{
	return MainServer::Stop(stop);
	SkillLog.close();
	SpeedHackLog.close();
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)CIOServer::Start, Start);
		DetourAttach(&(PVOID&)MainServer::Stop, Hooked_MainServer_Stop);
		DetourAttach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
		DetourAttach(&(PVOID&)CPlayer::Tick, Tick);
		DetourAttach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourAttach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
		DetourAttach(&(PVOID&)CMonsterReal::Die, MonsterDie);
		DetourAttach(&(PVOID&)CPlayer::PKKill, PKKill);
		DetourAttach(&(PVOID&)CPlayer::UpdateProperty, UpdateProperty);
		DetourAttach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourAttach(&(PVOID&)CPlayer::Process, Packet);
		DetourAttach(&(PVOID&)CPlayer::CanAttack, CanAttack);
		DetourAttach(&(PVOID&)CPlayer::SendMail, SendMail);
		DetourTransactionCommit();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)CIOServer::Start, Start);
		DetourDetach(&(PVOID&)MainServer::Stop, Hooked_MainServer_Stop);
		DetourDetach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
		DetourDetach(&(PVOID&)CPlayer::Tick, Tick);
		DetourDetach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourDetach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
		DetourDetach(&(PVOID&)CMonsterReal::Die, MonsterDie);
		DetourDetach(&(PVOID&)CPlayer::PKKill, PKKill);
		DetourDetach(&(PVOID&)CPlayer::UpdateProperty, UpdateProperty);
		DetourDetach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourDetach(&(PVOID&)CPlayer::Process, Packet);
		DetourDetach(&(PVOID&)CPlayer::CanAttack, CanAttack);
		DetourDetach(&(PVOID&)CPlayer::SendMail, SendMail);
		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}