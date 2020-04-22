#include "ServerFunctions.h"

int __fastcall MonsterDie(int mob,void* edx,int tankerID, int a3, int a4, int a5)
{
	ICharacter IMonster((void*)mob);
	ICharacter IPlayer((void*)tankerID);


	if (LawlessZoneON==true&& IPlayer.IsBuff(LawlessZone::BuffID)&&std::find(LawlessZone::MobID.begin(), LawlessZone::MobID.end(), IMonster.GetMobIndex()) != LawlessZone::MobID.end() )
	{
		LawlessZone::PointCounter[IPlayer.GetPID()] += LawlessZone::MobPoints;
	}



	return CMonsterReal::Die(mob, tankerID, a3, a4, a5);
}