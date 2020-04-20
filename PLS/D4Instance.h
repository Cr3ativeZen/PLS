#ifndef _D4INSTANCE_H
#define _D4INSTANCE_H
void __fastcall DFourInstance(ICharacter IPlayer)
{

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 1)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);

		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::F2TP[0], D4Instance::F2TP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 2)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::F3TP[0], D4Instance::F3TP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 3)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::F4TP[0], D4Instance::F4TP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 4)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::F5TP[0], D4Instance::F5TP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] + D4Instance::F6TP[2] && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 5)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::F6TP[0], D4Instance::F6TP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}


	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] + D4Instance::F6TP[2] + D4Instance::LastRoomTP[2]-1 && IPlayer.IsOnline() && IPlayer.IsBuff(666) && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 6)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());
		//if (Partyia)
		//{
		//	for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
		//	{
		//		int Members = *(DWORD*)((void*)i);
		//		ICharacter IMembers((void*)*(DWORD*)((void*)i));
		//		IMembers.Teleport(D4Instance::MapNumber, D4Instance::LastRoomTP[0], D4Instance::LastRoomTP[1]);

		//	}
		//}
		D4Instance::FloorNumber++;
	}


	if (D4Instance::IsUp == true && D4Instance::MobsCount[D4Instance::StageNumber] > 0)
	{
		for (int i = 0; i < D4Instance::MobsCount[D4Instance::StageNumber]; i++)
		{
			Summon(0, D4Instance::MapNumber, D4Instance::CoordX[D4Instance::StageNumber] + CTools::Rate(1, 20), D4Instance::CoordY[D4Instance::StageNumber] + CTools::Rate(1, 20), D4Instance::MobID[D4Instance::StageNumber], 1, 1, 0, 0, 0);
		}
		D4Instance::MobsToKill = D4Instance::MobsCount[D4Instance::StageNumber];
		D4Instance::MobsCount[D4Instance::StageNumber] = 0;
	}

	if (D4Instance::IsUp == true && D4Instance::MobsKilled == D4Instance::MobsToKill)
	{
		D4Instance::MobsKilled = 0;
		D4Instance::MobsToKill = 1;

		D4Instance::StageNumber++;
	}

	if (D4Instance::IsUp == false && IPlayer.GetMap() == D4Instance::MapNumber)
	{

		if (CChar::IsGState((int)IPlayer.GetOffset(), 2))
			IPlayer.Revive();

		IPlayer.Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		IPlayer.CloseScreenTime();
		IPlayer.CancelBuff(666);
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
	}


	if (D4Instance::IsUp == true && !IPlayer.IsBuff(666)&&IPlayer.IsParty() && IPlayer.GetMap() == D4Instance::MapNumber)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Time ended.instance failed", 1);
		D4Instance::IsUp = false;
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
		InstaConfig();
		//Need to be fixed,when some1 uses exit command it stops instance
		//i think its fixed with  this IPlayer.GetMap()==D4Instance::MapNumber
	}



	if (D4Instance::IsUp == true && D4Instance::MapNumber != IPlayer.GetMap() && IPlayer.IsBuff(666))
	{
		IPlayer.Teleport(D4Instance::MapNumber, 35453, 34400);
		//change coords if u add teleport to next floors. if(stage<....)
	}

	

	if (D4Instance::IsUp == true && D4Instance::MobsCount[D4Instance::StageNumber] > 0)
	{

		for (int i = 0; i < D4Instance::MobsCount[D4Instance::StageNumber]; i++)
		{
			Summon(0, D4Instance::MapNumber, D4Instance::CoordX[D4Instance::StageNumber] + CTools::Rate(1, 20), D4Instance::CoordY[D4Instance::StageNumber] + CTools::Rate(1, 20), D4Instance::MobID[D4Instance::StageNumber], 1, 1, 0, 0, 0);
		}
		if (D4Instance::MobsCount[D4Instance::StageNumber] == 1)
		{
			CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Boss spawnned !", 1);
		}
		else
		{
			CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "New mobs spawnned find and kill them!", 1);
		}

		D4Instance::MobsToKill = D4Instance::MobsCount[D4Instance::StageNumber];
		D4Instance::MobsCount[D4Instance::StageNumber] = 0;
	}

	if (D4Instance::IsUp == true && D4Instance::MobsKilled == D4Instance::MobsToKill)
	{
		D4Instance::MobsKilled = 0;
		D4Instance::MobsToKill = 1;

		D4Instance::StageNumber++;
	}


	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::LastStage &&IPlayer.GetMap()==D4Instance::MapNumber)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "You have successfully finished instance", 1);

		D4Instance::IsUp = false;
		IPlayer.CloseScreenTime();
		IPlayer.CancelBuff(666);
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		InstaConfig();
	}



	if (D4Instance::IsUp == true && D4Instance::MapNumber != IPlayer.GetMap() && IPlayer.IsBuff(666))
	{
			if (D4Instance::FloorNumber == 1)
			{
				IPlayer.Teleport(D4Instance::MapNumber, 35453, 34400);
			}
			if (D4Instance::FloorNumber == 2)
			{
				IPlayer.Teleport(D4Instance::MapNumber, D4Instance::F2TP[0], D4Instance::F2TP[1]);
			}
			if (D4Instance::FloorNumber == 3)
			{
				IPlayer.Teleport(D4Instance::MapNumber, D4Instance::F3TP[0], D4Instance::F3TP[1]);
			}
			if (D4Instance::FloorNumber == 4)
			{
				IPlayer.Teleport(D4Instance::MapNumber, D4Instance::F4TP[0], D4Instance::F4TP[1]);
			}
			if (D4Instance::FloorNumber == 5)
			{
				IPlayer.Teleport(D4Instance::MapNumber, D4Instance::F5TP[0], D4Instance::F5TP[1]);
			}
			if (D4Instance::FloorNumber == 6)
			{
				IPlayer.Teleport(D4Instance::MapNumber, D4Instance::F6TP[0], D4Instance::F6TP[1]);
			}
		
	}

	if (!IPlayer.IsBuff(666) && IPlayer.IsOnline() && IPlayer.GetMap() == D4Instance::MapNumber)
	{
		IPlayer.CloseScreenTime();
		IPlayer.Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		if(IPlayer.IsParty())
			CPlayer::LeaveParty((int)IPlayer.GetOffset());

		IPlayer.Announcement("You left the instance", TEXTCOLOR_RED);
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
		return;
	}

	if (!D4Instance::Party && D4Instance::IsUp==true)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Party destroyed,instance failed", 1);
		D4Instance::IsUp = false;
		IPlayer.CloseScreenTime();
		IPlayer.CancelBuff(666);
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		InstaConfig();

	}

	if (!IPlayer.IsParty() && IPlayer.IsOnline() && IPlayer.GetMap() == D4Instance::MapNumber&&D4Instance::IsUp == true)
	{
		IPlayer.CancelBuff(666);
		IPlayer.CloseScreenTime();
		IPlayer.Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		IPlayer.Announcement("You left the instance", TEXTCOLOR_RED);
		IPlayer.Buff(240, D4Instance::Cooldown, 0);
		return;

	}

	if (D4Instance::IsUp == true && D4Instance::Countdown + (D4Instance::Time * 1000) < static_cast<int>(GetTickCount()))
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Time ended.instance failed", 1);
		D4Instance::IsUp = false;
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		InstaConfig();
	}

}
#endif