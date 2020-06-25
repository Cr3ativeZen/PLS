#ifndef _ICONFIG_H_
#define _ICONFIG_H_

#include <windows.h>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include "CDungeon.h"


//Here temporarlly till i figure it out -.-

class CDungeon
{
public:

	CDungeon() :
		dungeon_id(0),
		min_players(0),
		max_players(0),
		min_level(0),
		max_level(0),
		waves_amount(0),
		instance_cooldown(0),
		instance_time(0),
		is_running(0),
		current_wave(0),
		quest_id(0),
		startX(0),
		startY(0),
		startZ(0)
	{

	}

	CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id,int startX,int startY,int startZ) :
		dungeon_id(dungeon_id),
		min_players(min_players),
		max_players(max_players),
		min_level(min_level),
		max_level(max_level),
		waves_amount(waves_amount),
		instance_cooldown(instance_cooldown),
		instance_time(instance_time),
		is_running(false),
		current_wave(0),
		quest_id(quest_id),
		startX(startX),
		startY(startY),
		startZ(startZ)
	{
	}


	void SummonMonsters();
	void CheckEnterLimitsForParty();
	void TeleportIn();
	//void GiveAwayRewards();
	void TeleportAway();


	struct Point
	{
		Point(int x, int y, int z) :
			x(x),
			y(y),
			z(z)
		{
		}
		int x, y, z;
	};

	struct DungSummon
	{
		DungSummon(int dungeon_id, int wave_id, bool is_boss_wave, int mini_boss_id, int mini_boss_spawn_chance, Point xyz, int monster_id) :
			dungeon_id(dungeon_id),
			wave_id(wave_id),
			is_boss_wave(is_boss_wave),
			mini_boss_id(mini_boss_id),
			mini_boss_spawn_chance(mini_boss_spawn_chance),
			xyz(xyz)
		{
			//mob_id_vec.push_back(vec.begin(), vec.end());
			mob_id_vec.push_back(monster_id);
		}
		int dungeon_id;
		int wave_id;
		bool is_boss_wave;
		int mini_boss_id;
		int mini_boss_spawn_chance;
		std::vector<int> mob_id_vec;
		Point xyz;

	};

	const int dungeon_id;
	const int min_players;
	const int max_players;

	const int min_level;
	const int max_level;
	const int startX, startY, startZ;
	const int quest_id;

	const int waves_amount;
	int current_wave;

	int instance_cooldown;
	int instance_time;         //check timer function(hook it)
	bool is_running;

	std::map<int, DungSummon> waves_map;

};



//IConfig is a Singleton used for loading necessary variables from config files.

class IConfig
{
	IConfig()
	{

	}
public:
	static IConfig& GetInstance()
	{
		static IConfig config;
		return config;
	}

	void LoadConfigs();

	void LoadSkillFormulas();


	struct SkillFormulas
	{
		int character;
		int skill_id;
		double damageC;
		int str;
		int agi;
		int wis;
		int inte;
		int base_damage;
		int damage_per_grade;
		int pvp_reduction;
		bool enabled;
		int per_deathblow;

	};

	struct Debuff
	{
		double damageC;
		int character;
		int skill_id;
		int buff_id;
		int str;
		int agi;
		int wis;
		int inte;
		int base_damage;
		int damage_per_grade;
		int pvp_reduction;
		int duration;
		int duration_per_grade;
		bool enabled;
	};

	struct Heals
	{
		int character;
		int skill_id;
		int wis;
		int cast_max_hp_percent;
		int target_max_hp_percent;
		int base_heal;
		int cast_heal_per_grade_percent;
		int target_heal_per_grade_percent;
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

	struct SkillCheck
	{
		bool animation_check;
		int skillID;
		DWORD time_used;

	};

	struct MySkills
	{
		int animation;
		int enabled;
		int cooldown;
		int casttime;
	};

	struct Rewards
	{
		int item_id;
		int item_amount;
		int rolls;
		int chance;
		int prefix;
	};

	struct BossSetup
	{
		int min_damage;
		int min_percent_damage;
		int max_drops;
		int max_per_player;
		int max_players;
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



	static int CallRANGE;
	static bool CallEnabled;

	static std::map<int, CallCheck>CallOfEvasionOTP;
	static std::map<int, CallCheck>CallOfDefense;
	static std::map<int, CallCheck>CallOfPhysicalAttack;
	static std::map<int, CallCheck>CallOfRecovery;

	static std::map<std::pair<int, int>, SkillFormulas> SkillCalc;
	static std::map<std::pair<int, int>, Debuff> DebuffCalc;
	static std::map<std::pair<int, int>, Heals> HealCalc;
	static std::map<int, int>CheckFocus;
	static std::map<int, PlayerFarContinueSkill> CheckFarContinueSkill;

	static std::map<std::pair<int, int>,bool> SkillEnabled;

	static std::map<int, SkillCheck> CastProtection;
	//PID,SkillID,Cooldown
	static std::map<std::pair<int,int>, DWORD> CooldownProtection;
	static std::map<std::pair<int, int>, MySkills> SkillCastCheck;
	static std::map<void*, std::map<void*,int>>BossRNG;
	static std::map<int, std::vector<Rewards>> BossRewards;
	static std::map<int,BossSetup> Setup;


	static std::vector<CDungeon> dungeon_vector;
};

extern IConfig CONFIG;





#endif


