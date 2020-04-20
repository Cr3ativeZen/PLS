#ifndef _D4INSTANCE_H
#define _D4INSTANCE_H
void __fastcall DFourInstance(ICharacter IPlayer)
{

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 1)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);

		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 2)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 3)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 4)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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

	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] + D4Instance::F6TP[2] && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 5)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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


	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::F2TP[2] + D4Instance::F3TP[2] + D4Instance::F4TP[2] + D4Instance::F5TP[2] + D4Instance::F6TP[2] + D4Instance::LastRoomTP[2]-1 && IsOnline() && IsBuff(666) && GetMap() == D4Instance::MapNumber&&D4Instance::FloorNumber == 6)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Floor finished, move to the next one", 1);
		//void *Partyia = (void*)CParty::FindParty(GetPartyID());
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

	if (D4Instance::IsUp == false && GetMap() == D4Instance::MapNumber)
	{

		if (CChar::IsGState((int)GetOffset(), 2))
			Revive();

		Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		CloseScreenTime();
		CancelBuff(666);
		Buff(240, D4Instance::Cooldown, 0);
	}


	if (D4Instance::IsUp == true && !IsBuff(666)&&IsParty() && GetMap() == D4Instance::MapNumber)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Time ended.instance failed", 1);
		D4Instance::IsUp = false;
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		Buff(240, D4Instance::Cooldown, 0);
		InstaConfig();
		//Need to be fixed,when some1 uses exit command it stops instance
		//i think its fixed with  this GetMap()==D4Instance::MapNumber
	}



	if (D4Instance::IsUp == true && D4Instance::MapNumber != GetMap() && IsBuff(666))
	{
		Teleport(D4Instance::MapNumber, 35453, 34400);
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


	if (D4Instance::IsUp == true && D4Instance::StageNumber == D4Instance::LastStage &&GetMap()==D4Instance::MapNumber)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "You have successfully finished instance", 1);

		D4Instance::IsUp = false;
		CloseScreenTime();
		CancelBuff(666);
		Buff(240, D4Instance::Cooldown, 0);
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		InstaConfig();
	}



	if (D4Instance::IsUp == true && D4Instance::MapNumber != GetMap() && IsBuff(666))
	{
			if (D4Instance::FloorNumber == 1)
			{
				Teleport(D4Instance::MapNumber, 35453, 34400);
			}
			if (D4Instance::FloorNumber == 2)
			{
				Teleport(D4Instance::MapNumber, D4Instance::F2TP[0], D4Instance::F2TP[1]);
			}
			if (D4Instance::FloorNumber == 3)
			{
				Teleport(D4Instance::MapNumber, D4Instance::F3TP[0], D4Instance::F3TP[1]);
			}
			if (D4Instance::FloorNumber == 4)
			{
				Teleport(D4Instance::MapNumber, D4Instance::F4TP[0], D4Instance::F4TP[1]);
			}
			if (D4Instance::FloorNumber == 5)
			{
				Teleport(D4Instance::MapNumber, D4Instance::F5TP[0], D4Instance::F5TP[1]);
			}
			if (D4Instance::FloorNumber == 6)
			{
				Teleport(D4Instance::MapNumber, D4Instance::F6TP[0], D4Instance::F6TP[1]);
			}
		
	}

	if (!IsBuff(666) && IsOnline() && GetMap() == D4Instance::MapNumber)
	{
		CloseScreenTime();
		Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		if(IsParty())
			CPlayer::LeaveParty((int)GetOffset());

		Announcement("You left the instance", TEXTCOLOR_RED);
		Buff(240, D4Instance::Cooldown, 0);
		return;
	}

	if (!D4Instance::Party && D4Instance::IsUp==true)
	{
		CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Party destroyed,instance failed", 1);
		D4Instance::IsUp = false;
		CloseScreenTime();
		CancelBuff(666);
		Buff(240, D4Instance::Cooldown, 0);
		D4Instance::StageNumber = 0;
		D4Instance::MobsKilled = 0;
		InstaConfig();

	}

	if (!IsParty() && IsOnline() && GetMap() == D4Instance::MapNumber&&D4Instance::IsUp == true)
	{
		CancelBuff(666);
		CloseScreenTime();
		Teleport(0, D4Instance::ReturnX, D4Instance::ReturnY);
		Announcement("You left the instance", TEXTCOLOR_RED);
		Buff(240, D4Instance::Cooldown, 0);
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