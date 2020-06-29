#ifndef SUMMONDIE_H_
#define SUMMONDIE_H_
#include "Resources.h"


void BossDropDraw(ICharacter IMonster);
bool Roll(unsigned int chance);
int RollPlayer(unsigned int player_amount);

int __fastcall SummonDie(int Monster, void* edx, int Arg, int Arg1, int Arg2, int Arg3)
{
	ICharacter IMonster((void*)Monster);

	if (IConfig::BossRewards.count(IMonster.GetMobIndex()))
		BossDropDraw(IMonster);

	return CMonsterMaguniMaster::Die(Monster, Arg, Arg1, Arg2, Arg3);
}





void BossDropDraw(ICharacter IMonster)
{

	uint32_t total_players = IConfig::BossRNG[IMonster.GetOffset()].size();

	if (total_players == 0)
		return;


	std::vector<IConfig::Rewards> rewardvec = IConfig::BossRewards[IMonster.GetMobIndex()];
	std::map<void*, int > playersmap = IConfig::BossRNG[IMonster.GetOffset()];
	std::map<void*, int > top_players;

	IConfig::BossSetup setup = IConfig::Setup[IMonster.GetMobIndex()];

	if (rewardvec.empty() || playersmap.empty() || setup.max_drops == 0 || setup.max_per_player == 0)
		return;

	int min_damage = setup.min_damage > (IMonster.GetMaxHp() / 100) * setup.min_percent_damage ? setup.min_damage : (IMonster.GetMaxHp() / 100) * setup.min_percent_damage;

	for (auto it = playersmap.begin(); it != playersmap.end();++it)
		if (it->second > min_damage)
			top_players[it->first] = it->second;

	if (top_players.empty())
		return;


	std::vector<std::pair<void*, int>> playervec;

	for (auto& i : top_players)
		playervec.push_back({ i.first,i.second });

	if (playervec.size() > static_cast<unsigned>(setup.max_players))
	{
		std::sort(playervec.begin(), playervec.end(), [](std::pair<void*, int> p1, std::pair<void*, int> p2) { return p1.second > p2.second; });
		playervec.resize(setup.max_players);
	}

	int dropsgiven = 0;
	int playervec_id = 0;
	std::map<void*, int> drop_amount;

	for (auto& i : rewardvec)
	{
		if (dropsgiven >= setup.max_drops || playervec.empty())
			break;

		for (int j = 0; j < i.rolls; j++)
		{
			if (dropsgiven >= setup.max_drops || playervec.empty())
				break;

			if (Roll(i.chance))
			{
				playervec_id = RollPlayer(playervec.size());
				ICharacter IPlayer(playervec[playervec_id].first);
				
				if (IPlayer.IsValid() && IPlayer.IsOnline())
				{
					IPlayer.InsertItem(i.item_id, i.prefix, i.item_amount, 0);

					if(!IPlayer.IsInventoryFull())
						CPlayer::Write(IPlayer.GetOffset(), 0x3c, "ss", "RNGSystem", "Congratulations! You got a drop");

					drop_amount[IPlayer.GetOffset()]++;

					if (drop_amount[IPlayer.GetOffset()] >= setup.max_per_player)
						playervec.erase(playervec.begin()+playervec_id);
				}
			}
			dropsgiven++;
		}
	}

	IConfig::BossRNG.erase(IMonster.GetOffset());
}



bool Roll(unsigned int chance)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1000);
	return dist(dev) < chance;
}

int RollPlayer(unsigned int player_amount)
{

	if (player_amount == 1)
		return 0;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, player_amount-1);

	return dist(dev);
}

#endif