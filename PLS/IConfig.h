#ifndef _ICONFIG_H_
#define _ICONFIG_H_

#include <windows.h>
#include <map>

class IConfig
{
	IConfig()
	{

	}
	~IConfig()
	{

	}
public:
	static IConfig& GetInstance()
	{
		static IConfig config;
		return config;
	}

	void LoadConfigs();


	struct PlayerContinueSkill
	{
		int PlayerX;
		int PlayerY;
		void* PlayerTarget;
		int PlayerSkillGrade;
		int PlayerSkillID;
		DWORD PlayerSkillDelay;
		int PlayerSkillCount;
	};

	struct CallCheck
	{
		void* CasterOffset;
		void* ReciverOffset;
		int SkillID;

	};

	struct PlayerFarContinueSkill
	{
		void* PlayerTarget;
		int PlayerSkillGrade;
		int PlayerSkillID;
		DWORD PlayerSkillDelay;
		int PlayerSkillCount;
		int PlayerDamage;
		void* CasterOffset;
	};

	struct PlayerContinueThunderStorm
	{

		void* PlayerTarget;
		int PlayerSkillGrade;
		int PlayerSkillID;
		DWORD PlayerSkillDelay;
		int PlayerSkillCount;
	};

	struct PlayerContinueIceStorm
	{
		void* PlayerTarget;
		int PlayerSkillGrade;
		int PlayerSkillID;
		DWORD PlayerSkillDelay;
		int PlayerSkillCount;
	};

	struct PlayerContinueFireStorm
	{
		void* PlayerTarget;
		int PlayerSkillGrade;
		int PlayerSkillID;
		DWORD PlayerSkillDelay;
		int PlayerSkillCount;
	};

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

	struct ConfigIceArrow
	{
		DWORD Cooldown;
		DWORD Delay;
	};

	struct ConfigShiny
	{
		void* Target;
		DWORD Delay;
	};


	static std::map<int, ConfigIceArrow> CheckIceArrow;
	static std::map<int, ConfigShiny> CheckShiny;

	static std::map<int, PlayerContinueSkill> CheckContinueSkill;
	static std::map<int, PlayerFarContinueSkill> CheckFarContinueSkill;

	static std::map<int, CallCheck>CallOfEvasionOTP;
	static std::map<int, CallCheck>CallOfDefense;
	static std::map<int, CallCheck>CallOfPhysicalAttack;
	static std::map<int, CallCheck>CallOfRecovery;

	static std::map<int, PlayerContinueIceStorm> CheckContinueIceStorm;
	static std::map<int, PlayerContinueFireStorm> CheckContinueFireStorm;
	static std::map<int, PlayerContinueThunderStorm> CheckContinueThunderStorm;
	static std::map<int, int> MageMICheck;


	static int AEBaseDmgMultiPvE;
	static int AEAgiMultiPvE;
	static int AEStrMultiPvE;
	static int AEPerGradeMultiPvE;

	static int AEBaseDmgMultiPvP;
	static int AEAgiMultiPvP;
	static int AEStrMultiPvP;
	static int AEPerGradeMultiPvP;

	static bool ArrowExplosionON;
	static bool ArrowRainON;
	static int CallRANGE;

};

#endif

