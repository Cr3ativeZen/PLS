#include <fstream>
#include "IConfig.h"



void IConfig::LoadConfigs()
{
	IConfig::SkillCalc.clear();
	IConfig::DebuffCalc.clear();
	IConfig::HealCalc.clear();
	IConfig::SkillEnabled.clear();
	IConfig::SkillCastCheck.clear();
	IConfig::Setup.clear();
	IConfig::BossRewards.clear();
	IConfig::dungeon_map.clear();

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

	FILE* file = fopen("./Configs/Cooldown.txt", "r");
	if (file != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, file) != NULL)
		{
			int character = 0, skill_id = 0, casttime = 0, cooldown = 0;

			if (sscanf(line, "(skill (class %d)(action %d)(delay %d)(cooldown %d))", &character, &skill_id, &casttime, &cooldown) == 4)
			{
				IConfig::SkillCastCheck[{character, skill_id}].cooldown = cooldown;
				IConfig::SkillCastCheck[{character, skill_id}].casttime = casttime;
			}
		}
		fclose(file);
	}


	FILE* filep = fopen("./Skills/SkillList.txt", "r");
	if (filep != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filep) != NULL)
		{
			int character = 0, skill_id = 0,animation = 0, enabled = 0;
			if (sscanf(line, "(skill (class %d)(index %d)(has_animation %d)(enabled %d))", &character, &skill_id, &animation, &enabled) == 4)
			{
				IConfig::SkillCastCheck[{character, skill_id}].animation = animation;
				IConfig::SkillCastCheck[{character, skill_id}].enabled = enabled;
			}
		}
		fclose(filep);
	}

	FILE* filer = fopen("./Systems/ZenRewards.txt", "r");
	if (filer != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filer) != NULL)
		{
			int boss_id = 0, item_id = 0, item_amount = 0, prefix = 0, rolls = 0, chance = 0, min_damage = 0, min_percent_damage = 0, max_drops = 0, max_drop_per_player = 0, max_players = 0;
			if (sscanf(line, "(reward (boss_id %d)(item_id %d)(item_amount %d)(chance %d)(rolls %d)(prefix %d))", &boss_id, &item_id, &item_amount, &chance, &rolls, &prefix) == 6)
			{
				IConfig::Rewards rew = IConfig::Rewards();

				rew.item_id = item_id;
				rew.item_amount = item_amount;
				rew.prefix = prefix;
				rew.rolls = rolls;
				rew.chance = chance;


				IConfig::BossRewards[boss_id].push_back(rew);
			}
			if (sscanf(line, "(setup (boss_id %d)(min_damage %d)(min_percent_damage %d)(max_drops %d)(max_drop_per_player %d)(max_players %d))", &boss_id, &min_damage, &min_percent_damage, &max_drops, &max_drop_per_player, &max_players) == 6)
			{
				IConfig::BossSetup setup = IConfig::BossSetup();

				setup.min_damage = min_damage;
				setup.min_percent_damage = min_percent_damage;
				setup.max_drops = max_drops;
				setup.max_per_player = max_drop_per_player;
				setup.max_players = max_players;

				IConfig::Setup.insert({ boss_id,setup });
			}
		}
		fclose(filer);
	}

	//IConfig::CallEnabled = true;
}

bool IConfig::LoadInstanceConfig()
{
	//instance_mod_on = static_cast<bool>(GetPrivateProfileIntA("ZenInstance", "OnOFF", 1, "./Systems/ZenSystem.txt"));
	IConfig::dungeon_map.clear();

	auto it = std::find_if(IConfig::dungeon_map.begin(), IConfig::dungeon_map.end(), [](const auto& d) {return d.second.is_running; });

	if (it == IConfig::dungeon_map.end())
	{
		FILE* fileinstance = fopen("./Systems/ZenInstance.txt", "r");
		if (fileinstance != NULL)
		{

			std::vector<CDungeon> temp;
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileinstance) != NULL)
			{
				int id = 0, min_players = 0, max_players = 0, min_level = 0, max_level = 0, cooldown = 0, time = 0, waves_amount = 0, quest_id = 0, startX = 0, startY = 0;
				int instance_id = 0, wave_id = 0, is_boss_wave = 0, mini_boss_id = 0, mini_boss_spawn_chance = 0, monster_id = 0, x = 0, y = 0, monster_amount = 0;
				if (sscanf(line, "(instance (id %d)(min_players %d)(max_players %d)(min_level %d)(max_level %d)(waves_amount %d)(cooldown %d)(time %d)(quest_id %d)(startX %d)(startY %d))", &id, &min_players, &max_players, &min_level, &max_level, &waves_amount, &cooldown, &time, &quest_id, &startX, &startY) == 11)
				{
					CDungeon kekw(id, min_players, max_players, min_level, max_level, waves_amount, cooldown, time, quest_id, startX, startY);
					IConfig::dungeon_map[id] = kekw;
				}




				if (sscanf(line, "(wave (instance_id %d)(wave_id %d)(is_boss_wave %d)(mini_boss_id %d)(mini_boss_spawn_chance %d)(x %d)(y %d)(monster_id %d)(monster_amount %d))", &instance_id, &wave_id, &is_boss_wave, &mini_boss_id, &mini_boss_spawn_chance, &x, &y, &monster_id, &monster_amount) == 9)
				{
					CDungeon::DungSummon summon(instance_id, wave_id, is_boss_wave, mini_boss_id, mini_boss_spawn_chance, CDungeon::Point(x, y), monster_id, monster_amount);
					auto p = std::find_if(dungeon_map.begin(), dungeon_map.end(), [id = instance_id](const auto& d) {return d.second.dungeon_id == id; });
					if (p != dungeon_map.end())
					{
						p->second.waves_map.insert({ wave_id,summon });
					}
				}
			}
			fclose(fileinstance);
		}
		return true;
	}
	return false;
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


std::map<int, IConfig::SkillCheck> IConfig::CastProtection;
std::map<std::pair<int, int>, DWORD> IConfig::CooldownProtection;

std::map<std::pair<int, int>, IConfig::MySkills> IConfig::SkillCastCheck;
std::map<std::pair<int, int>,bool> IConfig::SkillEnabled;
std::map<void*, std::map<void*, int>>IConfig::BossRNG;
std::map<int, std::vector<IConfig::Rewards>> IConfig::BossRewards;
std::map<int,IConfig::BossSetup> IConfig::Setup;
std::map<int, CDungeon> IConfig::dungeon_map;

extern IConfig CONFIG = IConfig::GetInstance();