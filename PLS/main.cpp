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


std::map<int, Teleport>ZenTP;
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


int HealBasePercentage;
int HealPerGradePercentage;
int HealBase;
int HealWisdom;

int SacrificeBaseHeal;
int SacrificeBasePercentageHeal;
int SacrificeHealPerGradePercentage;

int SacrificeBaseLoss;
int SacrificeBasePercentageLoss;
int SacrificeLossPerGradePercentage;

int CureBase;
int CureBasePercentage;
int CurePerGradePercentage;
int CureWisdom;

int CureBase2;
int CureBasePercentage2;
int CurePerGradePercentage2;
int Cure2Wisdom;

int CureBase3;
int CureBasePercentage3;
int CurePerGradePercentage3;
int Cure3Wisdom;

int CallofHealBase;
int CallofHealBasePercentage;
int CallofHealPerGradePercentage;

int AmensiaBaseDmgMulti;
int AmnesiaWisMulti;
int AmnesiaDmgPercentIncreaseBless;

int BlowUpBaseDmgMultiPvE;
int BlowUpAgiMultiPvE;
int BlowUpStrMultiPvE;
int BlowUpPerGradeMultiPvE;

int BlowUpBaseDmgMultiPvP;
int BlowUpAgiMultiPvP;
int BlowUpStrMultiPvP;
int BlowUpPerGradeMultiPvP;
int BlowUpPvEMaxHits;

int PassiveAttackBaseFreezeTime;
int PassiveAttackPerGradeFreezeTime;




int FABaseDamageMultiPvE;
int FAAGiMultiPvE;
int FAStrMultiPvE;
int FAPerGradeMultiPvE;
int FADoTBasePvE;
int FADoTPerGradePvE;

int FABaseDamageMultiPvP;
int FAAGiMultiPvP;
int FAStrMultiPvP;
int FAPerGradeMultiPvP;
int FADoTBasePvP;
int FADoTPerGradePvP;

int FADurationBase;
int FADurationPerGrade;


int MABaseDmgMultiPvE;
int MAAgiMultiPvE;
int MAStrMultiPvE;
int MAPerGradeMultiPvE;
int MADoTPerGradePvE;

int MABaseDmgMultiPvP;
int MAAgiMultiPvP;
int MAStrMultiPvP;
int MAPerGradeMultiPvP;
int MADoTPerGradePvP;

int MADoTDuration;










int ShieldAttackBaseStunTime = 5;
int ShieldAttackDamageMulti = 1;









int LSBaseDmgMultiPvE;
int LSAgiMultiPvE;
int LSStrMultiPvE;
int LSPerGradeMultiPvE;

int LSBaseDmgMultiPvP;
int LSAgiMultiPvP;
int LSStrMultiPvP;
int LSPerGradeMultiPvP;
int LSPvEMaxHits;


int TBBaseDmgMultiPvE;
int TBAgiMultiPvE;
int TBStrMultiPvE;
int TBPerGradeMultiPvE;

int TBBaseDmgMultiPvP;
int TBAgiMultiPvP;
int TBStrMultiPvP;
int TBPerGradeMultiPvP;
int TBPvEMaxHits;

int SWBaseDmgMultiPvE;
int SWWisMultiPvE;
int SWIntMultiPvE;
int SWPerGradeMultiPvE;

int SWBaseDmgMultiPvP;
int SWWisMultiPvP;
int SWIntMultiPvP;
int SWPerGradeMultiPvP;
int SWPvEMaxHits;



//Third job skills (my way)
int ARBaseDmgMultiPvE;
int ARAgiMultiPvE;
int ARStrMultiPvE;
int ARPerGradeMultiPvE;

int ARBaseDmgMultiPvP;
int ARAgiMultiPvP;
int ARStrMultiPvP;
int ARPerGradeMultiPvP;

int CSBaseDmgMultiPvE;
int CSAgiMultiPvE;
int CSStrMultiPvE;
int CSPerGradeMultiPvE;

int CSBaseDmgMultiPvP;
int CSAgiMultiPvP;
int CSStrMultiPvP;
int CSPerGradeMultiPvP;

int AEBaseDmgMultiPvE;
int AEAgiMultiPvE;
int AEStrMultiPvE;
int AEPerGradeMultiPvE;

int AEBaseDmgMultiPvP;
int AEAgiMultiPvP;
int AEStrMultiPvP;
int AEPerGradeMultiPvP;

int VAPerGradeDoTPvE;
int VABaseDoTPvE;

int VAPerGradeDoTPvP;
int VABaseDoTPvP;

int VABaseDmgMultiPvE;
int VAAgiMultiPvE;
int VAStrMultiPvE;
int VAPerGradeMultiPvE;

int VABaseDmgMultiPvP;
int VAAgiMultiPvP;
int VAStrMultiPvP;
int VAPerGradeMultiPvP;

int VADuration;

int SHSBaseDmgMultiPvE;
int SHSAgiMultiPvE;
int SHSStrMultiPvE;
int SHSPerGradeMultiPvE;

int SHSBaseDmgMultiPvP;
int SHSAgiMultiPvP;
int SHSStrMultiPvP;
int SHSPerGradeMultiPvP;
int SHSStunDuration;
int SHSStunDurationPerGrade;

int LSTBaseDmgMultiPvE;
int LSTAgiMultiPvE;
int LSTStrMultiPvE;
int LSTPerGradeMultiPvE;

int LSTBaseDmgMultiPvP;
int LSTAgiMultiPvP;
int LSTStrMultiPvP;
int LSTPerGradeMultiPvP;

int SBBaseDmgMultiPvE;
int SBAgiMultiPvE;
int SBStrMultiPvE;
int SBPerGradeMultiPvE;

int SBBaseDmgMultiPvP;
int SBAgiMultiPvP;
int SBStrMultiPvP;
int SBPerGradeMultiPvP;

int WOHBaseDmgMultiPvE;
int WOHAgiMultiPvE;
int WOHStrMultiPvE;
int WOHPerGradeMultiPvE;

int WOHBaseDmgMultiPvP;
int WOHAgiMultiPvP;
int WOHStrMultiPvP;
int WOHPerGradeMultiPvP;

int SSBaseDmgMultiPvE;
int SSAgiMultiPvE;
int SSStrMultiPvE;
int SSPerGradeMultiPvE;

int SSBaseDmgMultiPvP;
int SSAgiMultiPvP;
int SSStrMultiPvP;
int SSPerGradeMultiPvP;

int SSMultiWhenZerk;

int SDBaseDmgMultiPvE;
int SDAgiMultiPvE;
int SDStrMultiPvE;
int SDPerGradeMultiPvE;

int SDBaseDmgMultiPvP;
int SDAgiMultiPvP;
int SDStrMultiPvP;
int SDPerGradeMultiPvP;


int PoBBaseDmgMultiPvE;
int PoBAgiMultiPvE;
int PoBStrMultiPvE;
int PoBPerGradeMultiPvE;
int PoBDmgPercentIncreasePDPvE;

int PoBBaseDmgMultiPvP;
int PoBAgiMultiPvP;
int PoBStrMultiPvP;
int PoBPerGradeMultiPvP;
int PoBHostilityMultiplier;


int TTBaseHeal;
int TTPerGradeHeal;
int TTWisdom;
int TTDuration;

int ICIBaseDmgMultiPvE;
int ICIIntMultiPvE;
int ICIPerGradeMultiPvE;

int ICIBaseDmgMultiPvP;
int ICIIntMultiPvP;
int ICIPerGradeMultiPvP;
int ICIColdBindDuration;


int FIBaseDmgMultiPvE;
int FIIntMultiPvE;
int FIPerGradeMultiPvE;

int FIBaseDmgMultiPvP;
int FIIntMultiPvP;
int FIPerGradeMultiPvP;

int TBoltMBaseDmgMultiPvE;
int TBoltMIntMultiPvE;
int TBoltMPerGradeMultiPvE;

int TBoltMBaseDmgMultiPvP;
int TBoltMIntMultiPvP;
int TBoltMPerGradeMultiPvP;

int IAMBaseDmgMultiPvE;
int IAMIntMultiPvE;
int IAMPerGradeMultiPvE;

int IAMBaseDmgMultiPvP;
int IAMIntMultiPvP;
int IAMPerGradeMultiPvP;

int FBBaseDmgMultiPvE;
int FBIntMultiPvE;
int FBPerGradeMultiPvE;

int FBBaseDmgMultiPvP;
int FBIntMultiPvP;
int FBPerGradeMultiPvP;

int LABaseDmgMultiPvE;
int LAIntMultiPvE;
int LAPerGradeMultiPvE;

int LABaseDmgMultiPvP;
int LAIntMultiPvP;
int LAPerGradeMultiPvP;

int LAActivationBaseDmgMultiPvE;
int LAActivationIntMultiPvE;
int LAActivationPerGradeMultiPvE;

int LAActivationBaseDmgMultiPvP;
int LAActivationIntMultiPvP;
int LAActivationPerGradeMultiPvP;

int LADuration;


int COChanceToPopBase;
int COChanceToPopPerGrade;

int CODamageMultiPvE;
int CODamageMultiPvP;
int COBaseDamagePvE;
int COBaseDamagePvP;

int CAChanceToPopBase;
int CAChanceToPopPerGrade;

int CADamageMultiPvE;
int CADamageMultiPvP;
int CABaseDamagePvE;
int CABaseDamagePvP;

//int DoKDamageMultiPvE;
//int DoKDamageMultiPvP;

int SABaseDmgMultiPvE;
int SAAgiMultiPvE;
int SAStrMultiPvE;
int SAPerGradeMultiPvE;

int SABaseDmgMultiPvP;
int SAAgiMultiPvP;
int SAStrMultiPvP;
int SAPerGradeMultiPvP;

int ABreakerAdditionalDamage;
int ABreakerDuration;
int ABreakerDurationPerGrade;
int ABreakerAdditionalDamagePerGrade;

int TBSBaseDmgMultiPvE;
int TBSAgiMultiPvE;
int TBSStrMultiPvE;

int TBSBaseDmgMultiPvP;
int TBSAgiMultiPvP;
int TBSStrMultiPvP;

int FWBaseDmgMultiPvE;
int FWAgiMultiPvE;
int FWStrMultiPvE;
int FWPerGradeMultiPvE;

int FWBaseDmgMultiPvP;
int FWAgiMultiPvP;
int FWStrMultiPvP;
int FWPerGradeMultiPvP;

int FinalBBaseDmgMultiPvE;
int FinalBAgiMultiPvE;
int FinalBStrMultiPvE;
int FinalBPerGradeMultiPvE;
int FinalBMultiWhenBelowPvE;

int FinalBBaseDmgMultiPvP;
int FinalBAgiMultiPvP;
int FinalBStrMultiPvP;
int FinalBPerGradeMultiPvP;
int FinalBMultiWhenBelowPvP;

int TSBDamagePerHPPvE;
int TSBBaseDmgMultiPvE;
int TSBAgiMultiPvE;
int TSBStrMultiPvE;
int TSBPerGradeMultiPvE;

int TSBDamagePerHPPvP;
int TSBBaseDmgMultiPvP;
int TSBAgiMultiPvP;
int TSBStrMultiPvP;
int TSBPerGradeMultiPvP;

int TSBHPPercent;


int VSBaseDmgMultiPvE;
int VSAgiMultiPvE;
int VSStrMultiPvE;
int VSPerGradeMultiPvE;
int VSDmgMultiWhenBelowPvE;

int VSBaseDmgMultiPvP;
int VSAgiMultiPvP;
int VSStrMultiPvP;
int VSPerGradeMultiPvP;
int VSDmgMultiWhenBelowPvP;

int RupBaseDmgMultiPvE;
int RupAgiMultiPvE;
int RupStrMultiPvE;
int RupPerGradeMultiPvE;

int RupBaseDmgMultiPvP;
int RupAgiMultiPvP;
int RupStrMultiPvP;
int RupPerGradeMultiPvP;

int PUSBaseDmgMultiPvE;
int PUSAgiMultiPvE;
int PUSStrMultiPvE;
int PUSPerGradeMultiPvE;

int PUSBaseDmgMultiPvP;
int PUSAgiMultiPvP;
int PUSStrMultiPvP;
int PUSPerGradeMultiPvP;



int BRUTBaseDmgMultiPvE;
int BRUTAgiMultiPvE;
int BRUTStrMultiPvE;
int BRUTPerGradeMultiPvE;

int BRUTBaseDmgMultiPvP;
int BRUTAgiMultiPvP;
int BRUTStrMultiPvP;
int BRUTPerGradeMultiPvP;


int HSBaseDmgMultiPvE;
int HSAgiMultiPvE;
int HSStrMultiPvE;
int HSPerGradeMultiPvE;

int HSBaseDmgMultiPvP;
int HSAgiMultiPvP;
int HSStrMultiPvP;
int HSPerGradeMultiPvP;

int LAbsBaseDmgMultiPvE;
int LAbsAgiMultiPvE;
int LAbsStrMultiPvE;
int LAbsPerGradeMultiPvE;

int LAbsBaseDmgMultiPvP;
int LAbsAgiMultiPvP;
int LAbsStrMultiPvP;
int LAbsPerGradeMultiPvP;

//int LAbsHealBase;
int LAbsHealPerGrade;

int FSBaseDmgMultiPvE;
int FSAgiMultiPvE;
int FSStrMultiPvE;
int FSPerGradeMultiPvE;

int FSBaseDmgMultiPvP;
int FSAgiMultiPvP;
int FSStrMultiPvP;
int FSPerGradeMultiPvP;


int CLBaseDmgMultiPvE;
int CLIntMultiPvE;
int CLBaseDmgMultiPvP;
int CLIntMultiPvP;


int IStormBaseDmgMultiPvE;
int IStormIntMultiPvE;
int IStormBaseDmgMultiPvP;
int IStormIntMultiPvP;

int TStormBaseDmgMultiPvE;
int TStormIntMultiPvE;
int TStormBaseDmgMultiPvP;
int TStormIntMultiPvP;

int FStormBaseDmgMultiPvE;
int FStormIntMultiPvE;
int FStormBaseDmgMultiPvP;
int FStormIntMultiPvP;


int BSBaseDmgMultiPvE;
int BSBaseDmgMultiPvP;

int EggTBBaseDmgMultiPvE;
int EggTBBaseDmgMultiPvP;

int WFBaseDmgMultiPvE;
int WFBaseDmgMultiPvP;

int RABaseDmgMultiPvE;
int RABaseDmgMultiPvP;

int AnkleAPercentDamageIncreasePvE;
int AnkleAPercentDamageIncreasePvP;


int AOTMBaseDmgMultiPvE;
int AOTMAgiMultiPvE;
int AOTMStrMultiPvE;
int AOTMPerGradeMultiPvE;

int AOTMBaseDmgMultiPvP;
int AOTMAgiMultiPvP;
int AOTMStrMultiPvP;
int AOTMPerGradeMultiPvP;

int OHSBaseDmgMultiPvE;
int OHSAgiMultiPvE;
int OHSStrMultiPvE;
int OHSPerGradeMultiPvE;

int OHSBaseDmgMultiPvP;
int OHSAgiMultiPvP;
int OHSStrMultiPvP;
int OHSPerGradeMultiPvP;

int MFBaseDmgMultiPvE;
int MFAgiMultiPvE;
int MFStrMultiPvE;
int MFPerGradeMultiPvE;

int MFBaseDmgMultiPvP;
int MFAgiMultiPvP;
int MFStrMultiPvP;
int MFPerGradeMultiPvP;

int SOTABaseDmgMultiPvE;
int SOTAAgiMultiPvE;
int SOTAStrMultiPvE;
int SOTAPerGradeMultiPvE;

int SOTABaseDmgMultiPvP;
int SOTAAgiMultiPvP;
int SOTAStrMultiPvP;
int SOTAPerGradeMultiPvP;




bool BloodSuctionON;
bool EggThunderboltON;
bool RevolveAttackON;
bool WhirlwindFeatherON;

bool BlowUpArrowON;
bool FlamyArrowON;
bool HealON;
bool LightningSlashON;
bool MuscleSolidationON;
bool PassiveAttackON;
bool ShieldAttackON;
bool ShockWaveON;
bool TranscendentalBlowON;
bool CureON;

bool AmnesiaON;
bool AnkleAmputateON;
bool ArmorBreakerON;
bool BuffRemoverON;
bool BrutalAttackON;
bool CallsON;
bool ChainLightningON;
bool FatalWoundON;
bool FinalBlowON;
bool FireStormON;
bool IceStormON;
bool ThunderStormON;
bool FocusShotON;
bool HalfSwingON;
bool LifeAbsorptionON;
bool MysteriousArrowON;
bool PowerfulUpwardSlashON;
bool PurificationON;
bool RuptureON;
bool SacrificeON;
bool SpinAttackON;
bool SuicidalBlowON;
bool SummonsON;
bool TwinBladeStrikeON;
bool VitalStrikeON;
bool DanceOfKillingON;
bool CounterOffensiveON;
bool CounterAttackON;

bool ArrowExplosionON;
bool ArrowRainON;
bool CombativeSpiritON;
bool FireballON;
bool FlameInjectionON;
bool IceArrowON;
bool LightningArrowON;
bool LightningSlashThiefON;
bool ProvocationOfBlowON;
bool ShadowSlashON;
bool SpinBladeON;
bool SpinSlashON;
bool SwordDanceON;
bool TherapeuticTouchON;
bool ThunderboltON;
bool VirulentArrowON;
bool WrathOfHeavenON;
bool IcicleON;

bool OneHitStrikeON;
bool ArrowsoftheMasterON;

bool SpiritOfTheArrowsON;
bool MassiveFireON;

bool TheBoomofEarthON;
bool ThewaveofEarthON;

bool ShoutOfFightingSpiritON;
bool ShoutOfDefenseON;

bool PunishmentON;
bool ReleasingTheEnergyON;

bool IncapacitationON;
bool BombingON;

bool CriticalDiffusionON;
bool CriticalStrikeON;

bool DestroyingArmorON;
bool StrikeOfGodON;


bool TradeSystemON;
bool LawlessZoneON;
bool RiftON;
bool D4InstanceON;
bool MautaretaON;



std::map<int, DWORD> MonsterDisappear;
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
	void* Party;
	int PartySize;
	int MapNumber;
	bool IsUp = false;
	int MobsCount[200];
	int CoordX[200];
	int CoordY[200];
	int MobID[200];
	int StageNumber;
	int MobsKilled;
	int MobsToKill;
	int LastStage;
	int Time;
	int ReturnX;
	int ReturnY;
	int F2TP[3];
	int F3TP[3];
	int F4TP[3];
	int F5TP[3];
	int F6TP[3];
	int LastRoomTP[3];
	int FloorNumber;
	int MinLevel;
	int QuestID;
	int SpawnX;
	int SpawnY;
	int Cooldown;
}

int RiftAmount;
struct Rifts
{
	bool IsUp = false;
	int SpawnX;
	int SpawnY;

	int MobID[200];
	int MobAmount[300];
	int MaxWave;

	int WaveNumber = 0;
	int MobDeadCount = 0;
	int Map;
	int FirstBoss;
	int BossMobSpawnID;
	int BossMobSpawnAmount;
};
Rifts RiftStruct[50];

namespace TradeSystem
{
	std::map<std::pair<int, int>,int>Quest;
	std::map<std::pair<int, int>, int> Reward;
	std::map<std::pair<int, int>,int> ::iterator it;
	std::map<std::pair<int, int>, int> ::iterator iterat;
	int ItemID;
	int MinLvl = 60;
	int QuestRangeMin;
	int QuestRangeMax;
}

namespace LawlessZone
{
	std::vector<int>MobID;
	std::map<int, int>PointCounter;
	int TicketID;
	int QuestID;
	int QuitQuestID;
	int BuffID=241;
	int MinLvl;
	int MovingTrinketID;
	int StartTeleportX;
	int StartTeleportY;
	int ReturnTeleportX;
	int ReturnTeleportY;
	int Map;

	int Time;
	int PKPoints;
	int MobPoints;

	int ExpBuffID[10] = { 1001,1002,1003,1004,1005,1006,1007,1008,1009,1010 };
}

namespace Mautareta
{
	bool IsUp = false;
	bool MautIsDead = false;
	int StartTeleportX;
	int StartTeleportY;
	int ReturnTeleportX;
	int ReturnTeleportY;
	int Map;
	int BuffID = 254;                                                                         // buff when entering
	int BoostID[3];                                                                           // hp mana attack
	int BossID;
	int WandererID;
	int QuestItemID;
	int QuestID;
	int PartyLimit;
	bool MobSummonCheck[19];
	double SpawnAtHP[19] = {0.95,0.90,0.85,0.80,0.75,0.70,0.65,0.60,0.55,0.50,0.45,0.40,0.35,0.30,0.25,0.20,0.15,0.10,0.05};
	int SpawnMautX;
	int SpawnMautY;
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

		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}