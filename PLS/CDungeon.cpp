#include "CDungeon.h"
#include "Summon.h"
#include <random>


int CDungeon::enter_buff_id = 200;
int CDungeon::cd_buff_id = 201;
int CDungeon::map_id = 7;

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
	startY(0)
{
}

CDungeon::CDungeon(int dungeon_id, int min_players, int max_players, int min_level, int max_level, int waves_amount, int instance_cooldown, int instance_time, int quest_id, int startX, int startY):
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
	startY(startY)
{
}

void CDungeon::SummonMonsters()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000);

	current_wave++;
	if (current_wave == waves_amount +1)
		TeleportAway();

	auto it = waves_map.find(current_wave);
	if (it != waves_map.end())
	{
		for (int i = 0; i < it->second.monster_amount; i++)
			mobs_alive.push_back(MonsterSummon(0, CDungeon::map_id, it->second.xy.x, it->second.xy.y, it->second.mob_id_vec.front(), 1, 0, 0));

		if (dist(dev) <it->second.mini_boss_spawn_chance)
		{
			if(it->second.is_boss_wave)
				CPlayer::WriteInMap(CDungeon::map_id, 0xFF, "dsd", 247, "Boss Spawned!", 1);
			else
				CPlayer::WriteInMap(CDungeon::map_id, 0xFF, "dsd", 247, "Mini-boss spawned!", 1);

			mobs_alive.push_back(MonsterSummon(0, CDungeon::map_id, it->second.xy.x, it->second.xy.y, it->second.mini_boss_id, 1, 0, 0));
		}
	}

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
		if (is_running)
		{
			IPlayer.SystemMessage("Instance already running, please try again later!", IConfig::TEXTCOLOR_RED);
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
					IMembers.Teleport(CDungeon::map_id, it->second.startX, it->second.startY);
					IMembers.ScreenTime(it->second.instance_time);
					IMembers.SystemMessage("Instance started, Good Luck and Have Fun!", IConfig::TEXTCOLOR_BLUE);
					IMembers.Buff(CDungeon::enter_buff_id, it->second.instance_time, dungeon_id);
					player_party.insert(IMembers.GetID());

				}

				CIOObject::Release(Party);
			}
			is_running = true;
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

	if (waves_amount != waves_map.size() || waves_amount == 0)
		return false;

	

	int counter = 0, check = 0;
	void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

	if (Party)
	{
		for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
		{
			ICharacter IMembers((void*)*(DWORD*)((void*)i));
			check++;
			if ((IMembers.GetLevel() >= it->second.min_level && IMembers.GetLevel() <= it->second.max_level) /*&& !IMembers.IsBuff(CDungeon::cd_buff_id)*/)
				counter++;


		}

		CIOObject::Release(Party);
	}

	return counter == check;
}





void CDungeon::TeleportAway()
{
	for (auto it = player_party.begin(); it != player_party.end();)
	{
		ICharacter IMember(CPlayer::FindPlayer(*it));

		if (IMember.IsOnline())
		{
			IMember.Teleport(0, 257362, 259147);
			IMember.CancelBuff(CDungeon::enter_buff_id);
			IMember.Buff(CDungeon::cd_buff_id, instance_cooldown, 0);
			IMember.SystemMessage("Instance finished!", IConfig::TEXTCOLOR_GREEN);
			IMember.CloseScreenTime();

		}
		player_party.erase(it++);
	}
	is_running = false;
	current_wave = 0;
}

void CDungeon::DeleteMob(int offset)
{
	for (auto it = mobs_alive.begin();it!= mobs_alive.end();++it)
		if (*it == offset)
		{
			mobs_alive.erase(it);
			break;
		}

	if(mobs_alive.empty())
		SummonMonsters();
}

void CDungeon::LeaveInstance(int id)
{
	
	if ((int)player_party.size() - 1 < min_players)
	{
		int playerID = 0;
		for (auto it = player_party.begin(); it != player_party.end();)
		{
			ICharacter IMember(CPlayer::FindPlayer(*it));
			if (IMember.IsOnline())
			{
				IMember.Teleport(0, 257362, 259147);
				IMember.CancelBuff(CDungeon::enter_buff_id);
				IMember.Buff(CDungeon::cd_buff_id, instance_cooldown, 0);
				IMember.SystemMessage("Your party was either destroyed or had too low amount of players to continue", IConfig::TEXTCOLOR_RED);
				IMember.CloseScreenTime();
			}
			player_party.erase(it++);
		}

		//Blob mobs, set instance is_running to false ( add new function)
	}
	else
	{
		ICharacter IPlayer(CPlayer::FindPlayer(id));
		if (IPlayer.IsOnline())
		{
			IPlayer.Teleport(0, 257362, 259147);
			IPlayer.CancelBuff(CDungeon::enter_buff_id);
			IPlayer.Buff(CDungeon::cd_buff_id, instance_cooldown, 0);
			IPlayer.SystemMessage("Your left instance party", IConfig::TEXTCOLOR_RED);
			IPlayer.CloseScreenTime();
		}
		player_party.erase(id);
	}
}
