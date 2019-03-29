#pragma comment(lib, "detours.lib")

#undef UNICODE
#include <cstdio>
#include <windows.h>
#include "detours.h"
#include <process.h>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <thread>
#include <random>
#include <algorithm>

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

//std::map<int, BossDrops>BossDropsMap;
//std::map<std::pair<void*, void*>, int>BossRNG;
//std::map<std::pair<void*, void*>, int> ::iterator boss;
//std::map<int, BossDrops> ::iterator sIt;


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

struct PlayerContinueThunderStorm
{

	void *PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
};

struct PlayerContinueIceStorm
{
	void *PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
};

struct PlayerContinueFireStorm
{
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

struct ConfigIceArrow
{
	DWORD Cooldown;
	DWORD Delay;
};

struct ConfigShiny
{
	void *Target;
	DWORD Delay;
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

struct CallCheck
{
	void* CasterOffset;
	void* ReciverOffset;
	int SkillID;

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

std::map<std::pair<void*, void*>, int> ::iterator boss;
std::map<int, BossDrops> ::iterator sIt;
std::map<int, BossDrops>BossDropsMap;
std::map<std::pair<void*, void*>, int>BossRNG;
std::map<int, BuffItem>::iterator bufx;
std::map<int, BuffItem>Buffs;
std::map<int, CallCheck>Call;
std::map<int, Teleport>ZenTP;
std::map<int, DWORD> MonsterDisappear;
std::map<int, PlayerFarContinueSkill> CheckFarContinueSkill;
std::map<int, PlayerContinueSkill> CheckContinueSkill;
std::map<int, RuptureContinueSkill> CheckRuptureContinueSkill;

std::map<int, PlayerContinueIceStorm> CheckContinueIceStorm;
std::map<int, PlayerContinueFireStorm> CheckContinueFireStorm;
std::map<int, PlayerContinueThunderStorm> CheckContinueThunderStorm;

std::map<int, CheckConfigCooldown> CheckCooldownConfig;
std::map<int, CheckConfigEggCooldown> CheckEggCooldownConfig;

std::map<int, int> CooldownTable;
std::map<int, int> EggCooldownTable;

std::map<int, ConfigIceArrow> CheckIceArrow;
std::map<int, ConfigShiny> CheckShiny;
std::map<int, int> MageMICheck;
std::map<int, DWORD> CODelay;
std::map<int, int>CheckFocus;







int HealBasePercentage = 0;
int HealPerGradePercentage = 0;
int HealBase = 0;
int HealWisdom = 0;

int SacrificeBaseHeal = 0;
int SacrificeBasePercentageHeal = 0;
int SacrificeHealPerGradePercentage = 0;

int SacrificeBaseLoss = 0;
int SacrificeBasePercentageLoss = 0;
int SacrificeLossPerGradePercentage = 0;

int CureBase = 0;
int CureBasePercentage = 0;
int CurePerGradePercentage = 0;
int CureWisdom = 0;

int CureBase2 = 0;
int CureBasePercentage2 = 0;
int CurePerGradePercentage2 = 0;
int Cure2Wisdom = 0;

int CureBase3 = 0;
int CureBasePercentage3 = 0;
int CurePerGradePercentage3 = 0;
int Cure3Wisdom = 0;

int CallofHealBase = 0;
int CallofHealBasePercentage = 0;
int CallofHealPerGradePercentage = 0;

int AmensiaBaseDmgMulti = 0;
int AmnesiaWisMulti = 0;
int AmnesiaDmgPercentIncreaseBless = 0;



int SoulDestructionBaseDmgMultiPvE = 0;
int SoulDestructionWisMultiPvE = 0;
int SoulDestructionPerGradeMultiPvE = 0;

int SoulDestructionBaseDmgMultiPvP = 0;
int SoulDestructionWisMultiPvP = 0;
int SoulDestructionPerGradeMultiPvP = 0;


int PWWBaseDmgMultiPvE = 0;
int PWWAgiMultiPvE = 0;
int PWWStrMultiPvE = 0;
int PWWPerGradeMultiPvE = 0;

int PWWBaseDmgMultiPvP = 0;
int PWWAgiMultiPvP = 0;
int PWWStrMultiPvP = 0;
int PWWPerGradeMultiPvP = 0;
int PWWHostilityMultiplier = 0;


int BlowUpBaseDmgMultiPvE = 0;
int BlowUpAgiMultiPvE = 0;
int BlowUpStrMultiPvE = 0;
int BlowUpPerGradeMultiPvE = 0;

int BlowUpBaseDmgMultiPvP = 0;
int BlowUpAgiMultiPvP = 0;
int BlowUpStrMultiPvP = 0;
int BlowUpPerGradeMultiPvP = 0;
int BlowUpPvEMaxHits = 0;

int PassiveAttackBaseFreezeTime = 0;
int PassiveAttackPerGradeFreezeTime = 0;




int FABaseDamageMultiPvE = 0;
int FAAGiMultiPvE = 0;
int FAStrMultiPvE = 0;
int FAPerGradeMultiPvE = 0;
int FADoTBasePvE = 0;
int FADoTPerGradePvE = 0;

int FABaseDamageMultiPvP = 0;
int FAAGiMultiPvP = 0;
int FAStrMultiPvP = 0;
int FAPerGradeMultiPvP = 0;
int FADoTBasePvP = 0;
int FADoTPerGradePvP = 0;

int FADurationBase = 0;
int FADurationPerGrade = 0;


int MABaseDmgMultiPvE = 0;
int MAAgiMultiPvE = 0;
int MAStrMultiPvE = 0;
int MAPerGradeMultiPvE = 0;
int MADoTPerGradePvE = 0;

int MABaseDmgMultiPvP = 0;
int MAAgiMultiPvP = 0;
int MAStrMultiPvP = 0;
int MAPerGradeMultiPvP = 0;
int MADoTPerGradePvP = 0;
int MADoTDuration = 0;


int ShieldAttackBaseStunTime = 5;
int ShieldAttackDamageMulti = 1;


int LSBaseDmgMultiPvE = 0;
int LSAgiMultiPvE = 0;
int LSStrMultiPvE = 0;
int LSPerGradeMultiPvE = 0;

int LSBaseDmgMultiPvP = 0;
int LSAgiMultiPvP = 0;
int LSStrMultiPvP = 0;
int LSPerGradeMultiPvP = 0;
int LSPvEMaxHits = 0;


int TBBaseDmgMultiPvE = 0;
int TBAgiMultiPvE = 0;
int TBStrMultiPvE = 0;
int TBPerGradeMultiPvE = 0;

int TBBaseDmgMultiPvP = 0;
int TBAgiMultiPvP = 0;
int TBStrMultiPvP = 0;
int TBPerGradeMultiPvP = 0;
int TBPvEMaxHits = 0;

int SWBaseDmgMultiPvE = 0;
int SWWisMultiPvE = 0;
int SWIntMultiPvE = 0;
int SWPerGradeMultiPvE = 0;

int SWBaseDmgMultiPvP = 0;
int SWWisMultiPvP = 0;
int SWIntMultiPvP = 0;
int SWPerGradeMultiPvP = 0;
int SWPvEMaxHits = 0;



//Third job skills (my way)
int ARBaseDmgMultiPvE = 0;
int ARAgiMultiPvE = 0;
int ARStrMultiPvE = 0;
int ARPerGradeMultiPvE = 0;
int ARDamagePercentageReducePvE = 0;

int ARBaseDmgMultiPvP = 0;
int ARAgiMultiPvP = 0;
int ARStrMultiPvP = 0;
int ARPerGradeMultiPvP = 0;


int CSBaseDmgMultiPvE = 0;
int CSAgiMultiPvE = 0;
int CSStrMultiPvE = 0;
int CSPerGradeMultiPvE = 0;

int CSBaseDmgMultiPvP = 0;
int CSAgiMultiPvP = 0;
int CSStrMultiPvP = 0;
int CSPerGradeMultiPvP = 0;

int AEBaseDmgMultiPvE = 0;
int AEAgiMultiPvE = 0;
int AEStrMultiPvE = 0;
int AEPerGradeMultiPvE = 0;

int AEBaseDmgMultiPvP = 0;
int AEAgiMultiPvP = 0;
int AEStrMultiPvP = 0;
int AEPerGradeMultiPvP = 0;

int VAPerGradeDoTPvE = 0;
int VABaseDoTPvE = 0;

int VAPerGradeDoTPvP = 0;
int VABaseDoTPvP = 0;

int VABaseDmgMultiPvE = 0;
int VAAgiMultiPvE = 0;
int VAStrMultiPvE = 0;
int VAPerGradeMultiPvE = 0;

int VABaseDmgMultiPvP = 0;
int VAAgiMultiPvP = 0;
int VAStrMultiPvP = 0;
int VAPerGradeMultiPvP = 0;

int VADuration = 0;

int SHSBaseDmgMultiPvE = 0;
int SHSAgiMultiPvE = 0;
int SHSStrMultiPvE = 0;
int SHSPerGradeMultiPvE = 0;

int SHSBaseDmgMultiPvP = 0;
int SHSAgiMultiPvP = 0;
int SHSStrMultiPvP = 0;
int SHSPerGradeMultiPvP = 0;
int SHSStunDuration = 0;
int SHSStunDurationPerGrade = 0;

int LSTBaseDmgMultiPvE = 0;
int LSTAgiMultiPvE = 0;
int LSTStrMultiPvE = 0;
int LSTPerGradeMultiPvE = 0;

int LSTBaseDmgMultiPvP = 0;
int LSTAgiMultiPvP = 0;
int LSTStrMultiPvP = 0;
int LSTPerGradeMultiPvP = 0;

int SBBaseDmgMultiPvE = 0;
int SBAgiMultiPvE = 0;
int SBStrMultiPvE = 0;
int SBPerGradeMultiPvE = 0;

int SBBaseDmgMultiPvP = 0;
int SBAgiMultiPvP = 0;
int SBStrMultiPvP = 0;
int SBPerGradeMultiPvP = 0;

int WOHBaseDmgMultiPvE = 0;
int WOHAgiMultiPvE = 0;
int WOHStrMultiPvE = 0;
int WOHPerGradeMultiPvE = 0;

int WOHBaseDmgMultiPvP = 0;
int WOHAgiMultiPvP = 0;
int WOHStrMultiPvP = 0;
int WOHPerGradeMultiPvP = 0;

int SSBaseDmgMultiPvE = 0;
int SSAgiMultiPvE = 0;
int SSStrMultiPvE = 0;
int SSPerGradeMultiPvE = 0;

int SSBaseDmgMultiPvP = 0;
int SSAgiMultiPvP = 0;
int SSStrMultiPvP = 0;
int SSPerGradeMultiPvP = 0;

int SSMultiWhenZerk = 0;

int SDBaseDmgMultiPvE = 0;
int SDAgiMultiPvE = 0;
int SDStrMultiPvE = 0;
int SDPerGradeMultiPvE = 0;

int SDBaseDmgMultiPvP = 0;
int SDAgiMultiPvP = 0;
int SDStrMultiPvP = 0;
int SDPerGradeMultiPvP = 0;


int PoBBaseDmgMultiPvE = 0;
int PoBAgiMultiPvE = 0;
int PoBStrMultiPvE = 0;
int PoBPerGradeMultiPvE = 0;
int PoBDmgPercentIncreasePDPvE = 0;

int PoBBaseDmgMultiPvP = 0;
int PoBAgiMultiPvP = 0;
int PoBStrMultiPvP = 0;
int PoBPerGradeMultiPvP = 0;
int PoBHostilityMultiplier = 0;


int TTBaseHeal = 0;
int TTPerGradeHeal = 0;
int TTWisdom = 0;
int TTDuration = 0;

int ICIBaseDmgMultiPvE = 0;
int ICIIntMultiPvE = 0;
int ICIPerGradeMultiPvE = 0;

int ICIBaseDmgMultiPvP = 0;
int ICIIntMultiPvP = 0;
int ICIPerGradeMultiPvP = 0;
int ICIColdBindDuration = 0;


int FIBaseDmgMultiPvE = 0;
int FIIntMultiPvE = 0;
int FIPerGradeMultiPvE = 0;

int FIBaseDmgMultiPvP = 0;
int FIIntMultiPvP = 0;
int FIPerGradeMultiPvP = 0;

int TBoltMBaseDmgMultiPvE = 0;
int TBoltMIntMultiPvE = 0;
int TBoltMPerGradeMultiPvE = 0;

int TBoltMBaseDmgMultiPvP = 0;
int TBoltMIntMultiPvP = 0;
int TBoltMPerGradeMultiPvP = 0;

int IAMBaseDmgMultiPvE = 0;
int IAMIntMultiPvE = 0;
int IAMPerGradeMultiPvE = 0;

int IAMBaseDmgMultiPvP = 0;
int IAMIntMultiPvP = 0;
int IAMPerGradeMultiPvP = 0;

int FBBaseDmgMultiPvE = 0;
int FBIntMultiPvE = 0;
int FBPerGradeMultiPvE = 0;

int FBBaseDmgMultiPvP = 0;
int FBIntMultiPvP = 0;
int FBPerGradeMultiPvP = 0;

int LABaseDmgMultiPvE = 0;
int LAIntMultiPvE = 0;
int LAPerGradeMultiPvE = 0;

int LABaseDmgMultiPvP = 0;
int LAIntMultiPvP = 0;
int LAPerGradeMultiPvP = 0;

int LAActivationBaseDmgMultiPvE = 0;
int LAActivationIntMultiPvE = 0;
int LAActivationPerGradeMultiPvE = 0;

int LAActivationBaseDmgMultiPvP = 0;
int LAActivationIntMultiPvP = 0;
int LAActivationPerGradeMultiPvP = 0;

int LADuration = 0;


int COChanceToPopBase = 0;
int COChanceToPopPerGrade = 0;

int CODamageMultiPvE = 0;
int CODamageMultiPvP = 0;
int COBaseDamagePvE = 0;
int COBaseDamagePvP = 0;
int COBoostPercentage3rdJob = 0;

int CAChanceToPopBase = 0;
int CAChanceToPopPerGrade = 0;

int CADamageMultiPvE = 0;
int CADamageMultiPvP = 0;
int CABaseDamagePvE = 0;
int CABaseDamagePvP = 0;

//int DoKDamageMultiPvE = 0;
//int DoKDamageMultiPvP = 0;

int SABaseDmgMultiPvE = 0;
int SAAgiMultiPvE = 0;
int SAStrMultiPvE = 0;
int SAPerGradeMultiPvE = 0;

int SABaseDmgMultiPvP = 0;
int SAAgiMultiPvP = 0;
int SAStrMultiPvP = 0;
int SAPerGradeMultiPvP = 0;

int ABreakerAdditionalDamage = 0;
int ABreakerDuration = 0;
int ABreakerDurationPerGrade = 0;
int ABreakerAdditionalDamagePerGrade = 0;

int TBSBaseDmgMultiPvE = 0;
int TBSAgiMultiPvE = 0;
int TBSStrMultiPvE = 0;

int TBSBaseDmgMultiPvP = 0;
int TBSAgiMultiPvP = 0;
int TBSStrMultiPvP = 0;

int FWBaseDmgMultiPvE = 0;
int FWAgiMultiPvE = 0;
int FWStrMultiPvE = 0;
int FWPerGradeMultiPvE = 0;

int FWBaseDmgMultiPvP = 0;
int FWAgiMultiPvP = 0;
int FWStrMultiPvP = 0;
int FWPerGradeMultiPvP = 0;

int FinalBBaseDmgMultiPvE = 0;
int FinalBAgiMultiPvE = 0;
int FinalBStrMultiPvE = 0;
int FinalBPerGradeMultiPvE = 0;
int FinalBMultiWhenBelowPvE = 0;

int FinalBBaseDmgMultiPvP = 0;
int FinalBAgiMultiPvP = 0;
int FinalBStrMultiPvP = 0;
int FinalBPerGradeMultiPvP = 0;
int FinalBMultiWhenBelowPvP = 0;

int TSBDamagePerHPPvE = 0;
int TSBBaseDmgMultiPvE = 0;
int TSBAgiMultiPvE = 0;
int TSBStrMultiPvE = 0;
int TSBPerGradeMultiPvE = 0;

int TSBDamagePerHPPvP = 0;
int TSBBaseDmgMultiPvP = 0;
int TSBAgiMultiPvP = 0;
int TSBStrMultiPvP = 0;
int TSBPerGradeMultiPvP = 0;

int TSBHPPercent = 0;


int VSBaseDmgMultiPvE = 0;
int VSAgiMultiPvE = 0;
int VSStrMultiPvE = 0;
int VSPerGradeMultiPvE = 0;
int VSDmgMultiWhenBelowPvE = 0;

int VSBaseDmgMultiPvP = 0;
int VSAgiMultiPvP = 0;
int VSStrMultiPvP = 0;
int VSPerGradeMultiPvP = 0;
int VSDmgMultiWhenBelowPvP = 0;

int RupBaseDmgMultiPvE = 0;
int RupAgiMultiPvE = 0;
int RupStrMultiPvE = 0;
int RupPerGradeMultiPvE = 0;

int RupBaseDmgMultiPvP = 0;
int RupAgiMultiPvP = 0;
int RupStrMultiPvP = 0;
int RupPerGradeMultiPvP = 0;

int PUSBaseDmgMultiPvE = 0;
int PUSAgiMultiPvE = 0;
int PUSStrMultiPvE = 0;
int PUSPerGradeMultiPvE = 0;

int PUSBaseDmgMultiPvP = 0;
int PUSAgiMultiPvP = 0;
int PUSStrMultiPvP = 0;
int PUSPerGradeMultiPvP = 0;



int BRUTBaseDmgMultiPvE = 0;
int BRUTAgiMultiPvE = 0;
int BRUTStrMultiPvE = 0;
int BRUTPerGradeMultiPvE = 0;

int BRUTBaseDmgMultiPvP = 0;
int BRUTAgiMultiPvP = 0;
int BRUTStrMultiPvP = 0;
int BRUTPerGradeMultiPvP = 0;


int HSBaseDmgMultiPvE = 0;
int HSAgiMultiPvE = 0;
int HSStrMultiPvE = 0;
int HSPerGradeMultiPvE = 0;

int HSBaseDmgMultiPvP = 0;
int HSAgiMultiPvP = 0;
int HSStrMultiPvP = 0;
int HSPerGradeMultiPvP = 0;

int LAbsBaseDmgMultiPvE = 0;
int LAbsAgiMultiPvE = 0;
int LAbsStrMultiPvE = 0;
int LAbsPerGradeMultiPvE = 0;

int LAbsBaseDmgMultiPvP = 0;
int LAbsAgiMultiPvP = 0;
int LAbsStrMultiPvP = 0;
int LAbsPerGradeMultiPvP = 0;

//int LAbsHealBase = 0;
int LAbsHealPerGrade = 0;

int FSBaseDmgMultiPvE = 0;
int FSAgiMultiPvE = 0;
int FSStrMultiPvE = 0;
int FSPerGradeMultiPvE = 0;

int FSBaseDmgMultiPvP = 0;
int FSAgiMultiPvP = 0;
int FSStrMultiPvP = 0;
int FSPerGradeMultiPvP = 0;


int CLBaseDmgMultiPvE = 0;
int CLIntMultiPvE = 0;
int CLBaseDmgMultiPvP = 0;
int CLIntMultiPvP = 0;


int IStormBaseDmgMultiPvE = 0;
int IStormIntMultiPvE = 0;
int IStormBaseDmgMultiPvP = 0;
int IStormIntMultiPvP = 0;

int TStormBaseDmgMultiPvE = 0;
int TStormIntMultiPvE = 0;
int TStormBaseDmgMultiPvP = 0;
int TStormIntMultiPvP = 0;

int FStormBaseDmgMultiPvE = 0;
int FStormIntMultiPvE = 0;
int FStormBaseDmgMultiPvP = 0;
int FStormIntMultiPvP = 0;


int BSBaseDmgMultiPvE = 0;
int BSBaseDmgMultiPvP = 0;

int EggTBBaseDmgMultiPvE = 0;
int EggTBBaseDmgMultiPvP = 0;

int WFBaseDmgMultiPvE = 0;
int WFBaseDmgMultiPvP = 0;

int RABaseDmgMultiPvE = 0;
int RABaseDmgMultiPvP = 0;

int AnkleAPercentDamageIncreasePvE = 0;
int AnkleAPercentDamageIncreasePvP = 0;


int AOTMBaseDmgMultiPvE = 0;
int AOTMAgiMultiPvE = 0;
int AOTMStrMultiPvE = 0;
int AOTMPerGradeMultiPvE = 0;

int AOTMBaseDmgMultiPvP = 0;
int AOTMAgiMultiPvP = 0;
int AOTMStrMultiPvP = 0;
int AOTMPerGradeMultiPvP = 0;

int OHSBaseDmgMultiPvE = 0;
int OHSAgiMultiPvE = 0;
int OHSStrMultiPvE = 0;
int OHSPerGradeMultiPvE = 0;

int OHSBaseDmgMultiPvP = 0;
int OHSAgiMultiPvP = 0;
int OHSStrMultiPvP = 0;
int OHSPerGradeMultiPvP = 0;

int MFBaseDmgMultiPvE = 0;
int MFAgiMultiPvE = 0;
int MFStrMultiPvE = 0;
int MFPerGradeMultiPvE = 0;

int MFBaseDmgMultiPvP = 0;
int MFAgiMultiPvP = 0;
int MFStrMultiPvP = 0;
int MFPerGradeMultiPvP = 0;

int SOTABaseDmgMultiPvE = 0;
int SOTAAgiMultiPvE = 0;
int SOTAStrMultiPvE = 0;
int SOTAPerGradeMultiPvE = 0;

int SOTABaseDmgMultiPvP = 0;
int SOTAAgiMultiPvP = 0;
int SOTAStrMultiPvP = 0;
int SOTAPerGradeMultiPvP = 0;




bool BloodSuctionON = 0;
bool EggThunderboltON = 0;
bool RevolveAttackON = 0;
bool WhirlwindFeatherON = 0;

bool BlowUpArrowON = 0;
bool FlamyArrowON = 0;
bool HealON = 0;
bool LightningSlashON = 0;
bool MuscleSolidationON = 0;
bool PassiveAttackON = 0;
bool ShieldAttackON = 0;
bool ShockWaveON = 0;
bool TranscendentalBlowON = 0;
bool CureON = 0;

bool AmnesiaON = 0;
bool AnkleAmputateON = 0;
bool ArmorBreakerON = 0;
bool BuffRemoverON = 0;
bool BrutalAttackON = 0;
bool CallsON = 0;
bool ChainLightningON = 0;
bool FatalWoundON = 0;
bool FinalBlowON = 0;
bool FireStormON = 0;
bool IceStormON = 0;
bool ThunderStormON = 0;
bool FocusShotON = 0;
bool HalfSwingON = 0;
bool LifeAbsorptionON = 0;
bool MysteriousArrowON = 0;
bool PowerfulUpwardSlashON = 0;
bool PurificationON = 0;
bool RuptureON = 0;
bool SacrificeON = 0;
bool SpinAttackON = 0;
bool SuicidalBlowON = 0;
bool SummonsON = 0;
bool TwinBladeStrikeON = 0;
bool VitalStrikeON = 0;
bool DanceOfKillingON = 0;
bool CounterOffensiveON = 0;
bool CounterAttackON = 0;

bool ArrowExplosionON = 0;
bool ArrowRainON = 0;
bool CombativeSpiritON = 0;
bool FireballON = 0;
bool FlameInjectionON = 0;
bool IceArrowON = 0;
bool LightningArrowON = 0;
bool LightningSlashThiefON = 0;
bool ProvocationOfBlowON = 0;
bool ShadowSlashON = 0;
bool SpinBladeON = 0;
bool SpinSlashON = 0;
bool SwordDanceON = 0;
bool TherapeuticTouchON = 0;
bool ThunderboltON = 0;
bool VirulentArrowON = 0;
bool WrathOfHeavenON = 0;
bool IcicleON = 0;
bool SoulDestructionON = 0;
bool PowerfulWideningWoundON = 0;

bool OneHitStrikeON = 0;
bool ArrowsoftheMasterON = 0;

bool SpiritOfTheArrowsON = 0;
bool MassiveFireON = 0;

bool TheBoomofEarthON = 0;
bool ThewaveofEarthON = 0;

bool ShoutOfFightingSpiritON = 0;
bool ShoutOfDefenseON = 0;

bool PunishmentON = 0;
bool ReleasingTheEnergyON = 0;

bool IncapacitationON = 0;
bool BombingON = 0;

bool CriticalDiffusionON = 0;
bool CriticalStrikeON = 0;

bool DestroyingArmorON = 0;
bool StrikeOfGodON = 0;


bool TradeSystemON = 0;
bool LawlessZoneON = 0;
bool RiftON = 0;
bool D4InstanceON = 0;
bool MautaretaON = 0;

int ScrollItemID = 0;


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
#include "IChar.h"
#include "IQuest.h"
#include "IItem.h"
#include "Heal.h"
#include "Cure.h"
#include "ExecuteSkill.h"
#include "ChatCommand.h"
#include "Summon.h"
#include "InstaConfig.h"
#include "Player.h"
#include "D4Instance.h"
#include "BlowUpArrow.h"
#include "Calls.h"
#include "MuscleSolidation.h"
#include "Sacrifice.h"
#include "Amnesia.h"
#include "FocusShot.h"
#include "MysteriousArrow.h"
#include "PassiveAttack.h"
#include "FlamyArrow.h"
#include "Summons.h"
#include "Player.h"
#include "ShieldAttack.h"
#include "LightningSlash.h"
#include "TranscendentalBlow.h"
#include "Purification.h"
#include "BuffRemover.h"
#include "MonsterTick.h"
#include "PKKill.h"
#include "UpdateProperty.h"
#include "FinalDamage.h"
#include "ShadowSlash.h"
#include "ArrowRain.h"
#include "ResetContinueSkill.h"
#include "CombativeSpirit.h"
#include "ArrowExplosion.h"
#include "VirulentArrow.h"
#include "LightningSlashThief.h"
#include "SpinBlade.h"
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
#include "CanAttack.h"
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
#include "Packet.h"
#include "ChainLightning.h"
#include "ThunderStorm.h"
#include "IceStorm.h"
#include "FireStorm.h"
#include "WhirlwindFeather.h"
#include "RevolveAttack.h"
#include "EggThunderbolt.h"
#include "BloodSuction.h"
#include "OneHitStrike.h"
#include "ArrowsoftheMaster.h"
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
#include "SoulDestruction.h"
#include "PowerfulWideningWound.h"
#include "InfoDie.h"

void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	CIOServer::Start(Start, hostshort);
	InstaConfig();
	ZenConfig();
	RiftConfig();
	MautaretaConfig();
	ConsoleWriteBlue("CreativeZen's DLL loaded successfully");
	Sleep(500);
}


int __fastcall Hooked_MainServer_Stop(int stop)
{
	return MainServer::Stop(stop);
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
		DetourAttach(&(PVOID&)CPlayer::InfoDie, InfoDie);
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
		DetourDetach(&(PVOID&)CPlayer::InfoDie, InfoDie);
		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}