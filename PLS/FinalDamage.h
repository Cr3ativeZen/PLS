
#include "Resources.h"
int __fastcall FinalDamage(void* Target, void* edx, int Player, int Damage, int Argument)
{
	ICharacter IPlayer((void*)Player);
	ICharacter ITarget(Target);
	int CheckDamage = CChar::GetFinalDamage(Target, Player, Damage, Argument);



	if (IPlayer.IsValid() && IPlayer.IsOnline() && IPlayer.GetType() == TYPE_PLAYER && ITarget.GetType() == TYPE_MONSTER && CheckDamage > 0)
	{
		IConfig::BossRNG[ITarget.GetOffset()][IPlayer.GetOffset()] += CheckDamage;
	}


	return CheckDamage;
}