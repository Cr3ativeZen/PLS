#include "IConfig.h"

CDungeon::CDungeon():
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

CDungeon::CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id, int startX, int startY, int startZ):
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

void CDungeon::SummonMonsters()
{
}

void CDungeon::CheckEnterLimitsForParty()
{
}



void CDungeon::TeleportAway()
{
}
