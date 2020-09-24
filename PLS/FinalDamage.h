
#include "Resources.h"
int __fastcall FinalDamage(void* Target, void* edx, int Player, int Damage, int Argument)
{
	ICharacter IPlayer((void*)Player);
	ICharacter ITarget(Target);
	int check_damage = CChar::GetFinalDamage(Target, Player, Damage, Argument);



	if (IPlayer.IsValid() && IPlayer.IsOnline()&& ITarget.IsValid() && ITarget.GetType() == TYPE_MONSTER && IPlayer.GetType() == TYPE_PLAYER && IConfig::BossRewards.count(ITarget.GetMobIndex())  && check_damage > 0)
 	{
		IConfig::BossRNG[ITarget.GetOffset()][IPlayer.GetOffset()] += check_damage;
	}


	return check_damage;
}