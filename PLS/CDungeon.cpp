#include "CDungeon.h"
#include "Summon.h"

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
	map(0)
{
}

CDungeon::CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id, int startX, int startY, int map):
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
	map(map)
{
}

void CDungeon::SummonMonsters()
{
	ICharacter IMonster((void*)MonsterSummon(0, 0, 237682, 285268, 500, 1, 0,0));
	IMonster.Blob();
}

void CDungeon::CheckEnterLimitsForParty()
{
}

void CDungeon::TeleportIn(ICharacter IPlayer, std::map<int, CDungeon>::iterator it)
{


	if (IPlayer.IsParty())
	{
		if (!CParty::IsHead(CParty::FindParty(IPlayer.GetPartyID()), (int)IPlayer.GetOffset()))
		{
			IPlayer.SystemMessage("You are not a party leader!", IConfig::TEXTCOLOR_RED);
			return;
		}

		if (CheckIfOk(IPlayer, it))
		{
			void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());
			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					ICharacter IMembers((void*)*(DWORD*)((void*)i));
					IMembers.Teleport(it->second.map, it->second.startX, it->second.startY);
					IMembers.ScreenTime(it->second.instance_time);
					IMembers.SystemMessage("Instance started, Good Luck and Have Fun!", IConfig::TEXTCOLOR_ORANGE);


				}

				CIOObject::Release(Party);
			}
			SummonMonsters();
		}
		else
		{
			IPlayer.SystemMessage("SOMETHING IS WRONG", IConfig::TEXTCOLOR_RED);
		}


	}
	else
	{
		IPlayer.SystemMessage("You are not in party!", IConfig::TEXTCOLOR_RED);
		return;
	}
}

bool CDungeon::CheckIfOk(ICharacter IPlayer, std::map<int, CDungeon>::iterator it)
{
	int counter = 0, check = 0;
	void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

	if (Party)
	{
		for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
		{
			ICharacter IMembers((void*)*(DWORD*)((void*)i));
			check++;
			if ((IMembers.GetLevel() >= it->second.min_level && IMembers.GetLevel() <= it->second.max_level))
				counter++;


		}

		CIOObject::Release(Party);
	}

	return counter == check;
}





void CDungeon::TeleportAway()
{
}
