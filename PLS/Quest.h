//#include "IQuest.h"
//#include "Summon.h"
//void __fastcall Quest(void *QuestOffset, void *edx, int PlayerOffset)
//{
//
//	IQuest Quest(QuestOffset);
//	IChar IPlayer((void*)PlayerOffset);
//
//
//
//	if (IPlayer.IsOnline() && ID == D4Instance::QuestID)
//	{
//		if (IPlayer.IsBuff(240))
//		{
//			int Time = IPlayer.GetBuffRemain(240) / 60;
//			std::string msg = "You need to wait ";
//
//			if (Time > 0)
//			{
//				msg = msg + Int2String(Time);
//				msg = msg + " minutes to re-join Instance";
//			}
//			else {
//				msg = msg + " less then a minute to re-join Instance";
//			}
//
//			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
//			return;
//		}
//
//		if (D4Instance::IsUp == true)
//		{
//			IPlayer.SystemMessage("Instance already started try again later", TEXTCOLOR_RED);
//			return;
//		}
//		void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());
//
//		if (IPlayer.GetLevel() < D4Instance::MinLevel)
//		{
//			IPlayer.SystemMessage("Your level is too low to start instance", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (!Party)
//		{
//			IPlayer.SystemMessage("You need to be in party to start Instance", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (!CParty::IsHead((int)Party, (int)IPlayer.Offset))
//		{
//			IPlayer.SystemMessage("You are not the party leader so you cannot start Instance", TEXTCOLOR_RED);
//			return;
//		}
//
//
//		int PartySize = 0;
//
//		if (Party)
//		{
//			for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
//			{
//				int Members = *(DWORD*)((void*)i);
//				IChar IMembers((void*)*(DWORD*)((void*)i));
//				if (IMembers.GetLevel() < D4Instance::MinLevel)
//				{
//					IPlayer.SystemMessage("Some of your partymates level is too low to start instance", TEXTCOLOR_RED);
//					return;
//				}
//				if (IMembers.IsBuff(240))
//				{
//					IPlayer.SystemMessage("Some of your partymates still have Instance Cooldown.", TEXTCOLOR_RED);
//					return;
//				}
//			}
//
//			void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());
//
//
//			for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
//			{
//				int Members = *(DWORD*)((void*)i);
//				IChar IMembers((void*)*(DWORD*)((void*)i));
//
//				IMembers.Buff(666, D4Instance::Time, 0);
//				IMembers.Teleport(D4Instance::MapNumber, D4Instance::SpawnX, D4Instance::SpawnY);
//				IMembers.ScreenTime(D4Instance::Time);
//				IMembers.SystemMessage("Instance started! GL&HF", TEXTCOLOR_GREEN);
//				PartySize++;
//			}
//
//			D4Instance::PartySize = PartySize;
//		}
//
//
//
//		D4Instance::IsUp = true;
//		return;
//	}
//
//	//if (IPlayer.IsOnline() && ID == TradeSystem::StartQuestID)
//	//{
//	//	if (IPlayer.GetLevel() < TradeSystem::MinLvl)
//	//	{
//	//		IPlayer.SystemMessage("Your level is too low to start delivery", TEXTCOLOR_RED);
//	//		return;
//	//	}
//	//	if (IPlayer.IsBuff(104) && IPlayer.IsBuff(477))
//	//	{
//	//		IPlayer.SystemMessage("You cannot take more than 1 package", TEXTCOLOR_RED);
//	//		return;
//	//	}
//
//
//
//	//	if (IPlayer.IsBuff(222))
//	//	{
//	//		IPlayer.SystemMessage("Cooldown", TEXTCOLOR_RED);
//	//		return;
//	//	}
//
//	//	std::string deli = "Trading delivery started ! TRY TO KILL: ";
//	//	std::string trader = IPlayer.GetName();
//	//	deli = deli + trader;
//	//	deli = deli + " and try to steal his trade package!";
//	//	CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
//	//	IPlayer.Buff(104, 3600, 0);
//	//	IPlayer.Buff(477, 3610, 0);
//	//	CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::ItemID, 0, 1, 0);
//
//	//}
//
//	//	if (IPlayer.IsOnline() && ID == TradeSystem::EndQuestID)
//	//	{
//	//		if (!IPlayer.IsBuff(104) && !IPlayer.IsBuff(477))
//	//		{
//	//			IPlayer.SystemMessage("You are not in delivery mode right now.", TEXTCOLOR_RED);
//	//			return;
//	//		}
//	//		if (!CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::ItemID, 1))
//	//		{
//	//			IPlayer.SystemMessage("You have no delivery item in inventory", TEXTCOLOR_RED);
//	//			return;
//	//		}
//
//	//		CPlayer::RemoveItem(IPlayer.GetOffset(), 9, TradeSystem::ItemID, 1);
//	//		std::string deli = "Successful deliver by: ";
//	//		std::string trader = IPlayer.GetName();
//	//		deli = deli + trader;
//	//		CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
//	//		IPlayer.CancelBuff(104);
//	//		IPlayer.CancelBuff(477);
//	//		IPlayer.Buff(222, 3600, 0);
//	//		CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::RewardItemID, 0, TradeSystem::RewardItemAmount, 0);
//	//	}
//
//	//Start quest
//	if (IPlayer.IsOnline()&& ID > TradeSystem::QuestRangeMin && ID < TradeSystem::QuestRangeMax)
//	{
//		for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
//		{
//			if (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->first.second, 1) && ID == TradeSystem::it->first.first)
//			{
//				if (IPlayer.GetLevel() < TradeSystem::MinLvl)
//				{
//					IPlayer.SystemMessage("Your level is too low to start delivery", TEXTCOLOR_RED);
//					return;
//				}
//				if (IPlayer.IsBuff(104) && IPlayer.IsBuff(477))
//				{
//					IPlayer.SystemMessage("You cannot take more than 1 package", TEXTCOLOR_RED);
//					return;
//				}
//
//
//
//				if (IPlayer.IsBuff(222))
//				{
//					IPlayer.SystemMessage("Cooldown", TEXTCOLOR_RED);
//					return;
//				}
//				IPlayer.SystemMessage("Item found!", TEXTCOLOR_RED);
//				CPlayer::RemoveItem(IPlayer.GetOffset(), 9, (TradeSystem::it->first.second), 1);
//				CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::it->second, 256, 1, 0);
//
//				std::string deli = "Trading delivery started ! TRY TO KILL ";
//				std::string trader = IPlayer.GetName();
//				deli = deli + trader;
//				deli = deli + " and try to steal his trade package!";
//				CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
//				IPlayer.Buff(104, 3600, 0);
//				IPlayer.Buff(477, 3610, 0);
//				return;
//			
//			}
//		}
//	}
//
//
//	////End quest
//	if (IPlayer.IsOnline()&&ID > TradeSystem::QuestRangeMin && ID < TradeSystem::QuestRangeMax)
//	{
//
//		bool message = false;
//		for (TradeSystem::iterat = TradeSystem::Reward.begin(); TradeSystem::iterat != TradeSystem::Reward.end(); TradeSystem::iterat++)
//		{
//			if (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::iterat->first.second, 1) && ID == TradeSystem::iterat->first.first)
//			{
//				while (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::iterat->first.second, 1))
//				{
//					CPlayer::RemoveItem(IPlayer.GetOffset(), 9, (TradeSystem::iterat->first.second), 1);
//					CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::ItemID, 0, TradeSystem::iterat->second, 0);
//				}
//				IPlayer.SystemMessage("Item found!", TEXTCOLOR_RED);
//				message = true;
//
//			}
//			
//		}
//		if (message == true)
//		{
//			std::string deli = "Successful deliver by: ";
//			std::string trader = IPlayer.GetName();
//			deli = deli + trader;
//			CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
//			IPlayer.CancelBuff(104);
//			IPlayer.CancelBuff(477);
//			IPlayer.Buff(222, 3600, 0);
//			IPlayer.SystemMessage("Successful delivery", TEXTCOLOR_BLUE);
//			return;
//		}
//		return;
//	}
//
//
//	if (IPlayer.IsOnline() && ID == LawlessZone::QuestID)
//	{
//		if (IPlayer.GetLevel() < LawlessZone::MinLvl)
//		{
//			IPlayer.SystemMessage("Your level is too low to join Lawless Zone", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (!CPlayer::FindItem(IPlayer.GetOffset(), LawlessZone::MovingTrinketID, 1))
//		{
//			IPlayer.SystemMessage("You dont have Moving Trinket", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (!CPlayer::FindItem(IPlayer.GetOffset(), LawlessZone::TicketID, 1))
//		{
//			IPlayer.SystemMessage("You dont have the ticket to join Lawless Zone", TEXTCOLOR_RED);
//			return;
//		}
//		else
//		{
//			CPlayer::RemoveItem(IPlayer.GetOffset(), 0, LawlessZone::TicketID, 1);
//		}
//
//		IPlayer.Teleport(LawlessZone::Map, LawlessZone::StartTeleportX, LawlessZone::StartTeleportY);
//
//		IPlayer.SystemMessage("WELCOME TO LAWLESS ZONE!", TEXTCOLOR_PINK);
//		IPlayer.SystemMessage("GOOD LUCK HAVE FUN!", TEXTCOLOR_PINK);
//
//		IPlayer.SetBuffIcon(LawlessZone::Time, 1, 4510, 430);
//
//		IPlayer.Buff(LawlessZone::BuffID, LawlessZone::Time, 0);
//		IPlayer.Buff(104, LawlessZone::Time, 0);
//
//		LawlessZone::PointCounter[IPlayer.GetPID()] = 0;
//		return;
//	}
//
//	if (IPlayer.IsOnline() && ID == LawlessZone::QuitQuestID)
//	{
//		IPlayer.CancelBuff(LawlessZone::BuffID);
//		for (int i = 0; i < 10; i++)
//		{
//			if (IPlayer.IsBuff(LawlessZone::ExpBuffID[i]))
//			{
//				IPlayer.CancelBuff(LawlessZone::ExpBuffID[i]);
//				IPlayer.RemoveBuffIcon(0, 0, 4500 + i, 1500 + i);
//			}
//		}
//		IPlayer.Teleport(0, LawlessZone::ReturnTeleportX, LawlessZone::ReturnTeleportY);
//		LawlessZone::PointCounter[IPlayer.GetPID()] = 0;
//
//		IPlayer.SystemMessage("You left the Lawless Zone", TEXTCOLOR_PINK);
//		return;
//	}
//
//	if (IPlayer.IsOnline()&& ID == Mautareta::QuestID/*&&CPlayer::FindItem(IPlayer.GetOffset(),Mautareta::QuestItemID,1)&&Mautareta::IsUp==false &&Mautareta::PartyLimit<2*/)
//	{
//		void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
//
//		if (Mautareta::IsUp == true&&Mautareta::PartyLimit==2)
//		{
//			IPlayer.SystemMessage("Mautareta already started please try again later...", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (!Partyia)
//		{
//			IPlayer.SystemMessage("You need to be in party to start Mautareta", TEXTCOLOR_RED);
//			return;
//		}
//		
//		if (!CParty::IsHead((int)Partyia, (int)IPlayer.Offset))
//		{
//			IPlayer.SystemMessage("You are not the party leader so you cannot start Mautareta", TEXTCOLOR_RED);
//			return;
//		}
//
//		if (Mautareta::PartyLimit > 1)
//		{
//			IPlayer.SystemMessage("There are already 2 parties in.", TEXTCOLOR_RED);
//			return;
//		}
//		IPlayer.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
//
//		int sizecheck = 0;
//
//		if (Partyia)
//		{
//			for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
//			{
//				sizecheck++;
//			}
//			if (sizecheck <1)
//			{
//				IPlayer.SystemMessage("Your party need to be full(2 members for test) to start Mautareta raid!", TEXTCOLOR_RED);
//				return;
//			}
//
//			for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
//			{
//				IPlayer.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
//				int Members = *(DWORD*)((void*)i);
//				IChar IMembers((void*)*(DWORD*)((void*)i));
//				IMembers.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
//				IMembers.Buff(254, 1800, 0);
//				IMembers.ScreenTime(1800);
//			}
//			Mautareta::PartyLimit++;
//		}
//		Mautareta::IsUp = true;
//		if (Mautareta::PartyLimit == 2)
//		{
//			
//			CPlayer::WriteInMap(0, 0xFF, "dsd", 247, "Mautareta spawned!", 1);
//			Summon(0, Mautareta::Map, Mautareta::SpawnMautX, Mautareta::SpawnMautY, Mautareta::BossID, 1, 1, 0, 1800, 0);
//		}
//	}
//
//
//
//
//	CQuest::Run(QuestOffset, PlayerOffset);
//}