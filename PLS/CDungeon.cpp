#include "CDungeon.h"
#include "Summon.h"
#include <random>


int CDungeon::enter_buff_id = 188;
int CDungeon::cd_buff_id = 189;
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
	startY(0),
	end_instance_time(0)
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
	startY(startY),
	end_instance_time(0)
{
}

void CDungeon::SummonMonsters()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000);

	current_wave++;
	if (current_wave == waves_amount +1)
		TeleportAway(true);

	auto it = waves_map.find(current_wave);
	if (it != waves_map.end())
	{
		for (auto ite = it->second.wave_vec.begin(); ite != it->second.wave_vec.end(); ++it)
		{
			for (int i = 0; i < ite->monster_amount; i++)
				mobs_alive.push_back(MonsterSummon(0, CDungeon::map_id, ite->x, ite->y, ite->monster_id, 1, 0, 0));
		}
		//for (int i = 0; i < it->second.monster_amount; i++)
		//	mobs_alive.push_back(MonsterSummon(0, CDungeon::map_id, it->second.xy.x, it->second.xy.y, it->second.monster_id.front(), 1, 0, 0));
			
		if (dist(dev) <it->second.mini_boss_spawn_chance)
		{
			if (it->second.is_boss_wave)
				WriteToParty("Boss Spawned");
			else
				WriteToParty("Mini-Boss Spawned");

			//mobs_alive.push_back(MonsterSummon(0, CDungeon::map_id, it->second.xy.x, it->second.xy.y, it->second.mini_boss_id, 1, 0, 0));
		}
	}

}

void CDungeon::TeleportIn(ICharacter IPlayer)
{
	if (IPlayer.IsParty())
	{
		if (!CParty::IsHead(CParty::FindParty(IPlayer.GetPartyID()), (int)IPlayer.GetOffset()))
		{
			IPlayer.SystemMessage("You need to be leader to start Instance!", IConfig::TEXTCOLOR_RED);
			return;
		}
		if (is_running)
		{
			IPlayer.SystemMessage("Instance already running, please try again later!", IConfig::TEXTCOLOR_RED);
			return;
		}

		if (CheckIfOk(IPlayer))
		{
			void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());
			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					ICharacter IMembers((void*)*(DWORD*)((void*)i));
					IMembers.Teleport(CDungeon::map_id, startX, startY);
					IMembers.ScreenTime(instance_time);
					IMembers.SystemMessage("Instance started, Good Luck and Have Fun!", IConfig::TEXTCOLOR_BLUE);
					IMembers.Buff(CDungeon::enter_buff_id, instance_time, dungeon_id);
					player_party.insert(IMembers.GetOffset());

				}

				CIOObject::Release(Party);
			}
			end_instance_time = GetTickCount() + static_cast<long long>(instance_time) * 1000;
			is_running = true;
			SummonMonsters();
		}


	}
	else
	{
		IPlayer.SystemMessage("You are not in party!", IConfig::TEXTCOLOR_RED);
		return;
	}
}

bool CDungeon::CheckIfOk(ICharacter IPlayer)
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
			if ((IMembers.GetLevel() >= min_level && IMembers.GetLevel() <= max_level))
				counter++;
			else
			{
				std::string str = "Player " + IMembers.GetName();
				str += " is either too low or too high lvl to join the Instance!";
				IPlayer.SystemMessage(str, IConfig::TEXTCOLOR_RED);
			}

			if (!IMembers.IsBuff(CDungeon::cd_buff_id))
				counter++;
			else
			{
				int time = IMembers.GetBuffRemain(CDungeon::cd_buff_id) / 60;
				std::string str = "Player " + IMembers.GetName();
				if (time > 0)
					str += " has a " + std::to_string(time) + " minutes cooldown on Instance!";
				else
					str += " has less than a minute cooldown for instance!";

				IPlayer.SystemMessage(str, IConfig::TEXTCOLOR_RED);
			}

		}

		CIOObject::Release(Party);
	}
	else
		return false;

	return counter == 2*check;
}

void CDungeon::TeleportAway(bool successful)
{
	for (auto it = player_party.begin(); it != player_party.end();)
	{
		ICharacter IMember(*it);

		if (IMember.IsOnline())
		{
			IMember.Teleport(0, 257362, 259147);
			IMember.CancelBuff(CDungeon::enter_buff_id);
			IMember.Buff(CDungeon::cd_buff_id, instance_cooldown, 0);

			if(successful)
				IMember.SystemMessage("Instance finished!", IConfig::TEXTCOLOR_GREEN);
			else
				IMember.SystemMessage("Instance failed!", IConfig::TEXTCOLOR_RED);
			IMember.CloseScreenTime();

		}
		player_party.erase(it++);
	}
	if (!successful)
		BlobAllMobs();

	is_running = false;
	current_wave = 0;

}

bool CDungeon::DeleteMob(int offset)
{
	bool ret = false;
	for (auto it = mobs_alive.begin();it!= mobs_alive.end();++it)
		if (*it == offset)
		{
			mobs_alive.erase(it);
			ret = true;
			break;
		}

	if (ret && mobs_alive.empty())
		SummonMonsters();

	return ret;
}

void CDungeon::LeaveInstance(void* offset)
{
	
	if ((int)player_party.size() - 1 < min_players)
	{
		int playerID = 0;
		for (auto it = player_party.begin(); it != player_party.end();)
		{
			ICharacter IMember(*it);
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
		BlobAllMobs();
		is_running = false;
		current_wave = 0;
	}
	else
	{
		ICharacter IPlayer(offset);
		if (IPlayer.IsOnline())
		{
			IPlayer.Teleport(0, 257362, 259147);
			IPlayer.CancelBuff(CDungeon::enter_buff_id);
			IPlayer.Buff(CDungeon::cd_buff_id, instance_cooldown, 0);
			IPlayer.SystemMessage("You left instance party", IConfig::TEXTCOLOR_RED);
			IPlayer.CloseScreenTime();
		}
		player_party.erase(offset);
	}
}

void CDungeon::BlobAllMobs()
{
	if (mobs_alive.empty())
		return;

	for (auto it = mobs_alive.begin(); it != mobs_alive.end();)
	{
		ICharacter IMonster((void*)*it);
		if (IMonster.IsValid())
		{
			IMonster.Blob();
		}
		it = mobs_alive.erase(it);
	}
}

void CDungeon::WriteToParty(const char* str)
{
	if (player_party.empty())
		return;

	for (auto it = player_party.begin(); it != player_party.end();++it)
	{
		ICharacter IMember(*it);

		if (IMember.IsOnline())
			CPlayer::Write(IMember.GetOffset(), 0x3c, "ss", "InstanceSystem", str);
	}
}
