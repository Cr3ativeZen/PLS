void BossDropDraw(ICharacter IMonster);

int __fastcall SummonDie(int Monster, void* edx, int Arg, int Arg1, int Arg2, int Arg3)
{
	ICharacter IMonster((void*)Monster);

	//if (IConfig::BossRewards.count(IMonster.GetMobIndex()))
	//{
	//	BossDropDraw(IMonster);
	//}











	return CMonsterMaguniMaster::Die(Monster, Arg, Arg1, Arg2, Arg3);
}



//
//void BossDropDraw(ICharacter IMonster)
//{
//	std::random_device dev;
//	std::mt19937 rng(dev());
//	std::uniform_int_distribution<std::mt19937::result_type> dist(1,1000);
//
//	uint32_t total_players = IConfig::BossRNG[IMonster.GetOffset()].size();
//
//	if (total_players == 0)
//		return;
//
//	std::map<int, std::vector<IConfig::Rewards>>::iterator rewardit;
//	std::map<void*, int>::iterator playerit;
//
//	void* PlayerOffset = IConfig::BossRNG[IMonster.GetOffset()].begin()->first;
//	ICharacter IPlayer(PlayerOffset);
//
//	std::vector<IConfig::Rewards> rewardvec;
//	std::map<void*, int > playersmap;
//
//	rewardit = IConfig::BossRewards.find(IMonster.GetMobIndex());
//	playerit = IConfig::BossRNG[IMonster.GetOffset()].find(IMonster.GetMobIndex)->first;
//
//	if (rewardit != IConfig::BossRewards.end())
//	{
//		for (auto rewards : rewardit->second)
//		{
//			rewardvec.push_back(rewards);
//			IPlayer.SystemMessage(Int2String(rewards.item_id), TEXTCOLOR_RED);
//		}
//	}
//
//	if (playerit != IConfig::BossRNG[IMonster.GetOffset()].end())
//	{
//
//	}
//
//	else
//		return;
//
//
//
//
//
//}