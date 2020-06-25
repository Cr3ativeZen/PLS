//#ifndef CDUNGEON_H_
//#define CDUNGEON_H_
//
//#include "IConfig.h"
//
//class CDungeon
//{
//public:
//
//	CDungeon():
//		dungeon_id(0),
//		min_players(0),
//		max_players(0),
//		min_level(0),
//		max_level(0),
//		waves_amount(0),
//		instance_cooldown(0),
//		instance_time(0),
//		is_running(0),
//		current_wave(0)
//	{
//
//	}
//
//	CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount,int instance_cooldown,int instance_time):
//		dungeon_id(dungeon_id),
//		min_players(min_players),
//		max_players(max_players),
//		min_level(min_level),
//		max_level(max_level),
//		waves_amount(waves_amount),
//		instance_cooldown(instance_cooldown),
//		instance_time(instance_time),
//		is_running(false),
//		current_wave(0)
//	{
//	}
//
//
//	void SummonMonsters();
//
//
//	struct Point
//	{
//		Point(int x, int y, int z) :
//			x(x),
//			y(y),
//			z(z)
//		{
//		}
//		int x, y, z;
//	};
//
//	struct DungSummon
//	{
//		DungSummon(int dungeon_id, int wave_id, bool is_boss_wave, int mini_boss_id, int mini_boss_spawn_chance, Point xyz, int monster_id) :
//			dungeon_id(dungeon_id),
//			wave_id(wave_id),
//			is_boss_wave(is_boss_wave),
//			mini_boss_id(mini_boss_id),
//			mini_boss_spawn_chance(mini_boss_spawn_chance),
//			xyz(xyz)
//		{
//			//mob_id_vec.push_back(vec.begin(), vec.end());
//			mob_id_vec.push_back(monster_id);
//		}
//		int dungeon_id;
//		int wave_id;
//		bool is_boss_wave;
//		int mini_boss_id;
//		int mini_boss_spawn_chance;
//		std::vector<int> mob_id_vec;
//		Point xyz;
//
//	};
//
//	const int dungeon_id;
//	const int min_players;
//	const int max_players;
//
//	const int min_level;
//	const int max_level;
//
//	const int waves_amount;
//	int current_wave;
//
//	int instance_cooldown;
//	int instance_time;         //check timer function(hook it)
//	bool is_running;
//
//	std::map<int, DungSummon> waves_map;
//
//};
//#endif