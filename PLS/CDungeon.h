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
	void TeleportIn(ICharacter IPlayer);
	bool CheckIfOk(ICharacter IPlayer);
	//void GiveAwayRewards();
	void TeleportAway(bool successful);
	bool DeleteMob(int offset);
	void LeaveInstance(void* offset);
	void BlobAllMobs();
	void WriteToParty(const char* str);


	struct Point
	{
		Point(int x, int y);
		int x, y;
	};

	struct DungSummon
	{
		DungSummon(int dungeon_id, int wave_id, bool is_boss_wave, int mini_boss_id, unsigned int mini_boss_spawn_chance, Point xy, int monster_id, int monster_amount);
		int dungeon_id;
		int wave_id;
		bool is_boss_wave;
		int mini_boss_id;
		unsigned int mini_boss_spawn_chance;
		int monster_amount;
		int monster_id;
		Point xy;

	};

	int dungeon_id;
	int min_players;
	int max_players;

	int min_level;
	int max_level;
	int startX, startY;
	int quest_id;
	int end_instance_time;

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

