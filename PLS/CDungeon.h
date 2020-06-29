#ifndef CDUNGEON_H_
#define CDUNGEON_H_
#include "Resources.h"
#include "ICharacter.h"


class ICharacter;

class CDungeon
{
public:

	CDungeon();

	CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id, int startX, int startY, int map);


	void SummonMonsters();
	void CheckEnterLimitsForParty();
	void TeleportIn(ICharacter IPlayer,std::map<int,CDungeon>::iterator it);
	bool CheckIfOk(ICharacter IPlayer, std::map<int, CDungeon>::iterator it);
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

	int dungeon_id;
	int min_players;
	int max_players;

	int min_level;
	int max_level;
	int startX, startY, map;
	int quest_id;

	int waves_amount;
	int current_wave;

	int instance_cooldown;
	int instance_time;         //check timer function(hook it)
	bool is_running;

	std::map<int, DungSummon> waves_map;

};
#endif

