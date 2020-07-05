#ifndef LOGOUT_H_
#define LOGOUT_H_

void __fastcall GameRestart(void* Player)
{

	ICharacter IPlayer(Player);

	if (IPlayer.IsOnline() && IPlayer.IsBuff(CDungeon::enter_buff_id))
	{
		int instance_id = 0;
		if (IPlayer.IsBuff(CDungeon::enter_buff_id))
			instance_id = IPlayer.GetBuffValue(CDungeon::enter_buff_id);

		IPlayer.CancelBuff(CDungeon::enter_buff_id);

		auto it = IConfig::dungeon_map.find(instance_id);
		if (it != IConfig::dungeon_map.end())
		{
			IPlayer.Buff(CDungeon::cd_buff_id, it->second.instance_cooldown, 0);
			it->second.LeaveInstance(IPlayer.GetOffset());
		}
	}

	CPlayer::GameRestart(Player);
}





#endif