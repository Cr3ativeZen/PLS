#ifndef _PKKILL_H
#define _PKKILL_H
int __fastcall PKKill(void *Player, void* edx, int a5)
{
	//Check for duels...
	IChar IKiller(Player);
	IChar IPlayer((void*)a5);
	bool trade = false;
	if (TradeSystemON == true)
	{
		for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
		{
			if (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->second, 1))
			{
				std::string rip = "The trader ";
				rip = rip + IPlayer.GetName();
				rip = rip + " is dead!";
				CPlayer::WriteAll(0xFF, "dsd", 247, rip, 2);
				for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
				{
					while (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->second, 1))
					{
						CPlayer::RemoveItem(IPlayer.GetOffset(), 9, TradeSystem::it->second, 1);
						CItem::InsertItem((int)IKiller.GetOffset(), 0, TradeSystem::it->second, 256, 1, 0);
						trade = true;
					}
				}
			}
		}
		if (trade == true)
		{
			std::string deli = "The player: ";
			std::string trader = IKiller.GetName();
			deli = deli + trader;
			deli = deli + " is new trader! Kill him!";
			CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
			IKiller.Buff(104, 3600, 0);
			IKiller.Buff(477, 3610, 0);
		}
	}



	if (IPlayer.IsBuff(LawlessZone::BuffID) && IKiller.IsBuff(LawlessZone::BuffID) && LawlessZoneON == true)
	{
		std::string kill = "You killed ";
		kill += IPlayer.GetName();
		kill += " You got extra ";
		kill += Int2String(LawlessZone::PKPoints);
		kill += " Points";
		IKiller.SystemMessage(kill, TEXTCOLOR_PINK);

		LawlessZone::PointCounter[IKiller.GetPID()] +=LawlessZone::PKPoints;
		
	}
	return CPlayer::PKKill(Player, a5);
}
#endif