#include "IConfig.h"

void IConfig::LoadConfigs()
{
}

void IConfig::LoadSkillFormulas()
{
	FILE* filez = fopen("./Skills/SkillFormulas.txt", "r");
	if (filez != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filez) != NULL)
		{
			int character = 0, skill_id = 0, str = 0, agi = 0, wis = 0, inte = 0, base_damage = 0, damage_per_grade = 0, enabled = 0, pvp_reduction = 0, damageC = 0, per_deathblow = 0;

			if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %d)(wis %d)(inte %d)(damage_per_grade %d)(pvp_reduction %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &wis, &inte, &damage_per_grade, &pvp_reduction, &enabled) == 9)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].wis = wis;
				IConfig::SkillCalc[{character, skill_id}].inte = inte;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillCalc[{character, skill_id}].enabled = enabled;
			}
			else if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %d)(str %d)(agi %d)(damage_per_grade %d)(pvp_reduction %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &str, &agi, &damage_per_grade, &pvp_reduction, &enabled) == 9)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].str = str;
				IConfig::SkillCalc[{character, skill_id}].agi = agi;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillCalc[{character, skill_id}].enabled = enabled;
			}
			//Brutal Attack or Spin Slash(DeathBlow based)
			else if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %d)(str %d)(agi %d)(damage_per_grade %d)(pvp_reduction %d)(per_deathblow %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &str, &agi, &damage_per_grade, &pvp_reduction,&per_deathblow, &enabled) == 10)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].str = str;
				IConfig::SkillCalc[{character, skill_id}].agi = agi;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillCalc[{character, skill_id}].enabled = enabled;
				IConfig::SkillCalc[{character, skill_id}].per_deathblow = per_deathblow;
			}
		}
		fclose(filez);
	}
}



int IConfig::CallRANGE = 20;

int IConfig::AEBaseDmgMultiPvE = 0;
int IConfig::AEAgiMultiPvE = 0;
int IConfig::AEStrMultiPvE = 0;
int IConfig::AEPerGradeMultiPvE = 0;

int IConfig::AEBaseDmgMultiPvP = 0;
int IConfig::AEAgiMultiPvP = 0;
int IConfig::AEStrMultiPvP = 0;
int IConfig::AEPerGradeMultiPvP = 0;
bool IConfig::ArrowExplosionON = true;
bool IConfig::ArrowRainON = true;


std::map<std::pair<int, int>, IConfig::SkillFormulas> IConfig::SkillCalc;

std::map<int, IConfig::ConfigIceArrow> IConfig::CheckIceArrow;
std::map<int, IConfig::ConfigShiny> IConfig::CheckShiny;
std::map<int, int> IConfig::MageMICheck;

std::map<int, IConfig::PlayerContinueSkill> IConfig::CheckContinueSkill;
std::map<int, IConfig::PlayerFarContinueSkill> IConfig::CheckFarContinueSkill;

std::map<int, IConfig::CallCheck>IConfig::CallOfEvasionOTP;
std::map<int, IConfig::CallCheck>IConfig::CallOfDefense;
std::map<int, IConfig::CallCheck>IConfig::CallOfPhysicalAttack;
std::map<int, IConfig::CallCheck>IConfig::CallOfRecovery;


std::map<int, IConfig::PlayerContinueIceStorm>IConfig::CheckContinueIceStorm;
std::map<int, IConfig::PlayerContinueFireStorm>IConfig::CheckContinueFireStorm;
std::map<int, IConfig::PlayerContinueThunderStorm>IConfig::CheckContinueThunderStorm;

