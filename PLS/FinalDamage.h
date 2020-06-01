int __fastcall FinalDamage(void* Target, void* edx, int Player, int Damage, int Argument)
{
	ICharacter IPlayer((void*)Player);
	ICharacter ITarget(Target);
	int CheckDamage = CChar::GetFinalDamage(Target, Player, Damage, Argument);



	if (IPlayer.IsValid() && IPlayer.IsOnline() && IPlayer.GetType() == 0 && ITarget.GetType() == 1 && CheckDamage > 0)
	{
		IConfig::BossRNG[ITarget.GetOffset()][IPlayer.GetOffset()] += CheckDamage;
		IPlayer.SystemMessage(Int2String(IConfig::BossRNG[ITarget.GetOffset()].size()), TEXTCOLOR_RED);
		IPlayer.SystemMessage(Int2String(IConfig::BossRNG[ITarget.GetOffset()][IPlayer.GetOffset()]), TEXTCOLOR_RED);
	}















	return CheckDamage;
}