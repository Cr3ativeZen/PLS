#ifndef CDUNGEON_H_
#define CDUNGEON_H_
#include "Resources.h"
#include "ICharacter.h"

class ICharacter;
class CDungeon
{
public:

	CDungeon();

	CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id, int startX, int startY);


	void SummonMonsters();
	void TeleportIn(ICharacter IPlayer,std::map<int,CDungeon>::iterator it);
	bool CheckIfOk(ICharacter IPlayer, std::map<int, CDungeon>::iterator it);
	//void GiveAwayRewards();
	void TeleportAway();
	void DeleteMob(int offset);
	void LeaveInstance(void* Offset);


	struct Point
	{
		Point(int x, int y) :
			x(x),
			y(y)
		{
		}
		int x, y;
	};

	struct DungSummon
	{
		DungSummon(int dungeon_id, int wave_id, bool is_boss_wave, int mini_boss_id, unsigned int mini_boss_spawn_chance, Point xy, int monster_id,int monster_amount) :
			dungeon_id(dungeon_id),
			wave_id(wave_id),
			is_boss_wave(is_boss_wave),
			mini_boss_id(mini_boss_id),
			mini_boss_spawn_chance(mini_boss_spawn_chance),
			xy(xy),
			monster_amount(monster_amount)
		{
			//mob_id_vec.push_back(vec.begin(), vec.end());
			mob_id_vec.push_back(monster_id);
		}
		int dungeon_id;
		int wave_id;
		bool is_boss_wave;
		int mini_boss_id;
		unsigned int mini_boss_spawn_chance;
		int monster_amount;
		std::vector<int> mob_id_vec;
		Point xy;

	};

	int dungeon_id;
	int min_players;
	int max_players;

	int min_level;
	int max_level;
	int startX, startY;
	int quest_id;

	int waves_amount;
	int current_wave;

	int instance_cooldown;
	int instance_time;         //check timer function(hook it)
	bool is_running;
	
	std::map<int, DungSummon> waves_map;
	std::vector<int> mobs_alive;
	std::set<void*> player_party;
	static int enter_buff_id;
	static int cd_buff_id;
	static int map_id;
};

#endif

