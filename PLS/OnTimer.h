#ifndef ONTIMER_H_
#define ONTIMER_H_
#include "CDungeon.h"

void __fastcall OnTimer(void* Value, void* edx, int Argument)
{
	CCalendar::OnTimer(Value, Argument);
	ULONGLONG now= GetTickCount64();

	for (auto it = IConfig::dungeon_map.begin(); it != IConfig::dungeon_map.end(); ++it)
		if (it->second.is_running && now >= it->second.end_instance_time)
			it->second.TeleportAway(false);

}

#endif