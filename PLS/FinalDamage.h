
int __fastcall FinalDamage(void *Target, void *edx, int Player, int Damage, int Argument)
{
	ICharacter IPlayer((void*)Player);
	ICharacter ITarget(Target);
	int CheckDamage = CChar::GetFinalDamage(Target, Player, Damage, Argument);

	if (IPlayer.IsValid() && IPlayer.GetType() == 0)
		IPlayer.Buff(313, 3, 0);

	if (ITarget.IsValid() && ITarget.GetType() == 0)
		ITarget.Buff(313, 3, 0);


	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 0 &&IPlayer.IsBuff(LawlessZone::BuffID)&& ITarget.IsBuff(LawlessZone::BuffID) &&IPlayer.GetPartyID()==ITarget.GetPartyID()&&IPlayer.IsParty()&&ITarget.IsParty())
	{
		IPlayer.SystemMessage("You cannot attack your party members at Lawless Zone!", TEXTCOLOR_RED);
		return 0;
	}

		if (IPlayer.IsValid() && IPlayer.IsOnline() && IPlayer.GetType() == 0 && ITarget.GetType() == 1 && BossDropsMap.count(ITarget.GetMobIndex()))
		{
			if (CheckDamage > 1)
			{
				BossRNG[{ITarget.GetOffset(), IPlayer.GetOffset()}] += CheckDamage;

			}
		}


	
	return CheckDamage;
}