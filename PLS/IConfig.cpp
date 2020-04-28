#include "IConfig.h"
#include "ServerFunctions.h"

void IConfig::LoadConfigs()
{
}

void IConfig::LoadSkillFormulas()
{
	IConfig::SkillCalc.clear();
	IConfig::DebuffCalc.clear();
	IConfig::HealCalc.clear();
	IConfig::SkillEnabled.clear();
	FILE* filez = fopen("./Skills/SkillFormulas.txt", "r");
	if (filez != NULL)
	{

		char line[BUFSIZ];
		while (fgets(line, sizeof line, filez) != NULL)
		{
			float damageC = 0;
			int character = 0, skill_id = 0, str = 0, agi = 0, wis = 0, inte = 0, base_damage = 0, damage_per_grade = 0, enabled = 0, pvp_reduction = 0, per_deathblow = 0, buff_id = 0, duration_per_grade = 0, duration = 0;
			int cast_max_hp_percent = 0,target_max_hp_percent = 0,base_heal = 0;
			int cast_heal_per_grade_percent = 0;
			int target_heal_per_grade_percent = 0;
			


			if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %f)(wis %d)(inte %d)(damage_per_grade %d)(pvp_reduction %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &wis, &inte, &damage_per_grade, &pvp_reduction, &enabled) == 9)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].wis = wis;
				IConfig::SkillCalc[{character, skill_id}].inte = inte;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillEnabled[{character, skill_id }] = enabled;


			}
			else if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %f)(str %d)(agi %d)(damage_per_grade %d)(pvp_reduction %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &str, &agi, &damage_per_grade, &pvp_reduction, &enabled) == 9)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].str = str;
				IConfig::SkillCalc[{character, skill_id}].agi = agi;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillEnabled[{character, skill_id }] = enabled;
			}
			//Brutal Attack or Spin Slash(DeathBlow based)
			else if (sscanf(line, "(skill_damage (class %d)(skill_id %d)(base_damage %d)(damageC %f)(str %d)(agi %d)(damage_per_grade %d)(pvp_reduction %d)(per_deathblow %d)(enabled %d))", &character, &skill_id, &base_damage, &damageC, &str, &agi, &damage_per_grade, &pvp_reduction, &per_deathblow, &enabled) == 10)
			{
				IConfig::SkillCalc[{character, skill_id}].damageC = damageC;
				IConfig::SkillCalc[{character, skill_id}].str = str;
				IConfig::SkillCalc[{character, skill_id}].agi = agi;
				IConfig::SkillCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::SkillCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::SkillCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::SkillCalc[{character, skill_id}].per_deathblow = per_deathblow;
				IConfig::SkillEnabled[{character, skill_id }] = enabled;
			}
			//Debuffs like MA or Flamy Arrow DoT
			else if (sscanf(line, "(debuff (class %d)(skill_id %d)(buff_id %d)(base_damage %d)(damageC %f)(str %d)(agi %d)(damage_per_grade %d)(pvp_reduction %d)(duration %d)(duration_per_grade %d)(enabled %d))", &character, &skill_id, &buff_id, &base_damage, &damageC, &str, &agi, &damage_per_grade, &pvp_reduction, &duration, &duration_per_grade, &enabled) == 12)
			{
				IConfig::DebuffCalc[{character, skill_id}].damageC = damageC;
				IConfig::DebuffCalc[{character, skill_id}].buff_id = buff_id;
				IConfig::DebuffCalc[{character, skill_id}].str = str;
				IConfig::DebuffCalc[{character, skill_id}].agi = agi;
				IConfig::DebuffCalc[{character, skill_id}].base_damage = base_damage;
				IConfig::DebuffCalc[{character, skill_id}].damage_per_grade = damage_per_grade;
				IConfig::DebuffCalc[{character, skill_id}].pvp_reduction = pvp_reduction;
				IConfig::DebuffCalc[{character, skill_id}].duration = duration;
				IConfig::DebuffCalc[{character, skill_id}].duration_per_grade = duration_per_grade;
				IConfig::SkillEnabled[{character, skill_id }] = enabled;
			}
			//Heals
			else if (sscanf(line, "(heal (class %d)(skill_id %d)(base_heal %d)(wis %d)(cast_max_hp_percent %d)(cast_heal_per_grade_percent %d)(target_max_hp_percent %d)(target_heal_per_grade_percent %d)(enabled %d))",
				&character, &skill_id, &base_heal, &wis, &cast_max_hp_percent, &cast_heal_per_grade_percent, &target_max_hp_percent, &target_heal_per_grade_percent, &enabled) == 9)
			{
				IConfig::HealCalc[{character, skill_id}].character = character;
				IConfig::HealCalc[{character, skill_id}].skill_id = skill_id;
				IConfig::HealCalc[{character, skill_id}].base_heal = base_heal;
				IConfig::HealCalc[{character, skill_id}].wis = wis;
				IConfig::HealCalc[{character, skill_id}].cast_max_hp_percent = cast_max_hp_percent;
				IConfig::HealCalc[{character, skill_id}].target_max_hp_percent = target_max_hp_percent;
				IConfig::HealCalc[{character, skill_id}].cast_heal_per_grade_percent = cast_heal_per_grade_percent;
				IConfig::HealCalc[{character, skill_id}].target_heal_per_grade_percent = target_heal_per_grade_percent;
				IConfig::SkillEnabled[{character, skill_id }] = enabled;


			}
			else if (sscanf(line, "(enable (class %d)(skill_id %d)(enabled %d))", &character, &skill_id, &enabled) == 3)
			{
				IConfig::SkillEnabled[{character, skill_id }] = enabled;
			}
			else if (sscanf(line, "(calls (enabled %d))",&enabled) == 1)
			{

				IConfig::SkillEnabled[{0, 27 }] = enabled;
				IConfig::SkillEnabled[{0, 23 }] = enabled;
				IConfig::SkillEnabled[{0, 31 }] = enabled;
				IConfig::SkillEnabled[{0, 32 }] = enabled;
				IConfig::SkillEnabled[{0, 29 }] = enabled;
				IConfig::SkillEnabled[{0, 28 }] = enabled;
				IConfig::SkillEnabled[{0, 19 }] = enabled;
			}
			

		}


		fclose(filez);
	}


	//IConfig::CallEnabled = GetPrivateProfileIntA("Calls", "Enabled", 1, "./Skills/ZenSystem.txt");
	IConfig::CallEnabled = true;
}



int IConfig::CallRANGE = 20;
bool IConfig::CallEnabled = true;

std::map<int, IConfig::PlayerFarContinueSkill> IConfig::CheckFarContinueSkill;

std::map<std::pair<int, int>, IConfig::SkillFormulas> IConfig::SkillCalc;
std::map<std::pair<int, int>, IConfig::Debuff> IConfig::DebuffCalc;
std::map<std::pair<int, int>, IConfig::Heals> IConfig::HealCalc;

std::map<int, int>IConfig::CheckFocus;




std::map<int, IConfig::CallCheck>IConfig::CallOfEvasionOTP;
std::map<int, IConfig::CallCheck>IConfig::CallOfDefense;
std::map<int, IConfig::CallCheck>IConfig::CallOfPhysicalAttack;
std::map<int, IConfig::CallCheck>IConfig::CallOfRecovery;

std::map<std::pair<int, int>,bool> IConfig::SkillEnabled;


extern IConfig CONFIG = IConfig::GetInstance();
