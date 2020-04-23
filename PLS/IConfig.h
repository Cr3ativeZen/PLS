#ifndef _ICONFIG_H_
#define _ICONFIG_H_

#include <windows.h>
#include <map>

class IConfig
{
	IConfig();
	~IConfig();
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

	static std::map<int, PlayerContinueSkill> CheckContinueSkill;
	static std::map<int, CallCheck>CallOfEvasionOTP;
	static std::map<int, CallCheck>CallOfDefense;

	static std::map<int, CallCheck>CallOfPhysicalAttack;
	static std::map<int, CallCheck>CallOfRecovery;
	static std::map<int, PlayerFarContinueSkill> CheckFarContinueSkill;
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

