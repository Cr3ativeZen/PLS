#ifndef LEAVEPARTY_H_
#define LEAVEPARTY_H_

void __fastcall LeaveParty(int Player)
{
	ICharacter IPlayer((void*)Player);

	if (IPlayer.IsOnline() && IPlayer.GetMap() == CDungeon::map_id && IPlayer.IsBuff(CDungeon::enter_buff_id))
	{
		int instance_id = 0;
		if(IPlayer.IsBuff(CDungeon::enter_buff_id))
			instance_id = IPlayer.GetBuffValue(CDungeon::enter_buff_id);
		//IPlayer.CancelBuff(CDungeon::enter_buff_id);

		auto it = IConfig::dungeon_map.find(instance_id);
		if(it != IConfig::dungeon_map.end())
			it->second.LeaveInstance(IPlayer.GetOffset());


		//if party.size < min_players
		//leave instance

	}




	CPlayer::LeaveParty(Player);
}

#endif