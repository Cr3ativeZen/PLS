#include "ServerFunctions.h"
int __fastcall NormalHit(void *Player, void *edx, int bType, int nTargetID)
{
	IChar IPlayer(Player);
	IPlayer.Buff(313, 3, 0);



	if (IPlayer.IsOnline())
		return CPlayer::Attack(Player, bType, nTargetID);
	else
		return 0;
}