int __cdecl UpdateProperty(int Player, int Type, int InOut, signed __int64 Exp)
{
	IChar IPlayer((void*)Player);


	if (Type == 25 && IPlayer.IsOnline() && InOut &&IPlayer.IsBuff(LawlessZone::BuffID) && LawlessZoneON == true)
	{
		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[0]))
		{
			Exp += static_cast<int>(Exp *0.10);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[1]))
		{
			Exp += static_cast<int>(Exp *0.20);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[2]))
		{
			Exp += static_cast<int>(Exp *0.30);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[3]))
		{
			Exp += static_cast<int>(Exp*0.40);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[4]))
		{
			Exp += static_cast<int>(Exp*0.50);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[5]))
		{
			Exp += static_cast<int>(Exp * 0.60);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[6]))
		{
			Exp += static_cast<int>(Exp * 0.70);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[7]))
		{
			Exp += static_cast<int>(Exp * 0.80);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[8]))
		{
			Exp += static_cast<int>(Exp * 0.90);
		}

		if (IPlayer.IsBuff(LawlessZone::ExpBuffID[9]))
		{
			Exp += Exp;
		}
	}







	return CPlayer::UpdateProperty(Player, Type, InOut, Exp);
}