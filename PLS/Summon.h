#ifndef _SUMMON_H
#define _SUMMON_H
#include "InstaConfig.h"
#include "ChatCommand.h"


void BossDropDraw(IChar IMonster)
{
	int BossID = IMonster.GetMobIndex();
	int MaxDropPerChar = BossDropsMap[BossID].MaxDropPerPlayer;
	int itemgivencounter = 0;
	bool temp_bool = false;
	std::map<void*, int>PlayerMap;
	std::map<void*, int>::iterator PlayerMapIt;
	std::vector<Drop> temp_drop;
	temp_drop = BossDropsMap[BossID].Dropy;
	//std::sort(temp_drop.end(), temp_drop.begin());
	std::random_device device;
	std::random_device device2;
	std::mt19937 generator(device());
	std::mt19937 generator2(device2());
	int dropsgiven = BossDropsMap[BossID].ItemsToDraw;

	int i = 0;
	for (boss = BossRNG.begin(); boss != BossRNG.end(); ++boss)
	{
		if (boss->first.first == IMonster.GetOffset())
		{
			PlayerMap[boss->first.second] = boss->second;
			BossRNG.erase(boss);
		}
	}

	for (PlayerMapIt=PlayerMap.begin(); PlayerMapIt!=PlayerMap.end();++PlayerMapIt)
	{
		if ((BossDropsMap[BossID].MinDamage < PlayerMapIt->second&&BossDropsMap[BossID].MinDamage != 0) || (PlayerMapIt->second > (IMonster.GetMaxHp() / 100)*BossDropsMap[BossID].MinDamagePercent&&BossDropsMap[BossID].MinDamagePercent != 0))
		{
			PlayerMapIt->second = 0;
		}
		else
		{
			PlayerMap.erase(PlayerMapIt);
		}
	}
	while (dropsgiven > 0&&PlayerMap.size()!=0)
	{

		std::uniform_int_distribution<int> distribution(0,PlayerMap.size() - 1);
		PlayerMapIt = PlayerMap.begin();
		std::advance(PlayerMapIt, distribution(generator));
		IChar IPlayer(PlayerMapIt->first);
		std::uniform_int_distribution<int> distribution2(0, 999);
		if (distribution2(generator2) < temp_drop[i].DropChance * 10)
		{
			temp_bool = true;
		}
		temp_drop[i].ItemAmount--;
		if (CPlayer::GetInvenSize(PlayerMapIt->first) + 2 < IPlayer.MaxInventorySize())
		{
			PlayerMap.erase(PlayerMapIt);
		}
		if (temp_bool==true&&IPlayer.IsOnline())
		{
			dropsgiven--;
			if(IPlayer.IsOnline())
				CItem::InsertItem((int)PlayerMapIt->first, 0, temp_drop[i].ItemID, 0, 1, 0);

			PlayerMapIt->second++;

			temp_bool = false;

		}
		if (temp_drop[i].ItemAmount == 0)
		{
			i++;
		}
		
		if(PlayerMapIt->second>=MaxDropPerChar)
		{
			PlayerMap.erase(PlayerMapIt);
		}

		if (PlayerMap.size() == 0)
		{
			break;
		}
	}



}
int __cdecl Summon(int Player, int Map, int X, int Y, int Index, int Amount, int SafeZoneCheck, int Delay, int Disappear, int Pet)
{
	void *GetMonster = 0; int Value = 0, Monster = 0, Argument = 0;
	int GetMap = Undefined::MapCheck(Map);

	if (GetMap)
	{
		void *MonsterValueCheck = (void*)Undefined::GetMonsterValue(0x2B0u);

		if (MonsterValueCheck)
			GetMonster = Undefined::MonsterCreate(MonsterValueCheck);
		else
			GetMonster = 0;

		Monster = (int)GetMonster;
		IChar IMonster((void*)Monster);
		CIOCriticalSection::Enter((void*)0x4E182C);
		Undefined::CreateMonsterValue((void*)0x4E1820, (int)&Argument, (int)&Index);
		int GetCheck = Undefined::Check((int)0x4E1820, (int)&Value);

		if (*(DWORD*)(void*)&Argument == *(DWORD*)GetCheck)
		{
			CIOCriticalSection::Leave((void*)0x4E182C);
		}
		else {
			int Check = *(DWORD *)(Undefined::GetValue(&Argument) + 4);

			if (*(DWORD *)(Check + 304))
			{
				int *GetSetXY = new int[1];
				GetSetXY[0] = X;
				GetSetXY[1] = Y;
				*(DWORD *)(Monster + 316) = Map;
				*(DWORD *)(Monster + 320) = GetMap;
				*(DWORD *)(Monster + 512) = Index;
				*(DWORD *)(Monster + 476) = 1;

				if (Disappear)
					MonsterDisappear[(int)IMonster.GetOffset()] = GetTickCount() + Disappear;

				CChar::SetXY(Monster, (int)GetSetXY);
				delete[] GetSetXY;
				(*(void(__thiscall **)(int, int))(*(DWORD *)Monster + 192))(Monster, Check);

				if (Delay)
				{
					IMonster.Buff(159, (Delay + 2000) / 1000, 0);
					IMonster.Delay(Delay);
					IMonster.UnAttack(Delay);
				}

				CIOCriticalSection::Leave((void*)0x4E182C);
				CChar::Lock((void*)Monster);
				int *CellMapCoordinate = new int[1];
				CellMapCoordinate[0] = X >> 5;
				CellMapCoordinate[1] = Y >> 5;
				IMonster.MonsterSummonWrite(SafeZoneCheck, Monster, (int)CellMapCoordinate);
				delete[] CellMapCoordinate;
			}
			else {
				CIOCriticalSection::Leave((void*)0x4E182C);
			}
		}
	}



	return Monster;
}


int __fastcall SummonTick(void *Monster, void *edx)
{
	IChar IMonster(Monster);

	if (D4InstanceON == true)
	{
		for (int i = 0; i < D4Instance::LastStage; i++)
		{
			if (IMonster.GetMobIndex() == D4Instance::MobID[i] && D4Instance::IsUp == false)
			{
				IMonster.Blob();
			}
		}
	}
	//if (IMonster.GetMobIndex() == 697)
	//{
	//	if (!IMonster.IsBuff(697)&&IMonster.IsMobHaveTarget())
	//	{
	//		IMonster.Buff(697, 20, 0);
	//		IMonster.AddFxToTarget("davi_M564_71", 1, 0, 0);
	//		IChar IPlayer((void*)IMonster.GetMobTanker());
	//		int Around = IPlayer.GetObjectListAround(2);
	//		IMonster.OktayDamageSingle(IPlayer, 3000, 14);
	//		while (Around)
	//		{
	//			IChar Object((void*)*(DWORD*)Around);
	//			if (Object.GetType() == 0)
	//			{
	//				IMonster.OktayDamageSingle(Object, 3000, 14);
	//			}
	//			Around = CBaseList::Pop((void*)Around);
	//		}
	//	}
	//}


	//Change to Mautareta namespace...
	//if (IMonster.GetMobIndex() == Mautareta::BossID && !IMonster.IsBuff(777) && IMonster.IsMobHaveTarget())
	//{
	//	IMonster.Buff(777, 25, 0);
	//	Summon(0, 0, 266646, 242064, Mautareta::WandererID, 1, 1, 0, 1800, 0);
	//}
	if (MautaretaON == true)
	{
		if (IMonster.GetMobIndex() == Mautareta::BossID)
		{
			for (int i = 0; i < 19; i++)
			{
				if (IMonster.GetCurHp() < IMonster.GetMaxHp()*Mautareta::SpawnAtHP[i] && Mautareta::MobSummonCheck[i] == false)
				{
					if (i == 4 || i == 9 || i == 14 || i == 18)
					{
						for (int i = 0; i < 3; i++)
						{
							Summon(0, Mautareta::Map, IMonster.GetX(), IMonster.GetY(), Mautareta::WandererID, 1, 1, 0, 1800, 0);
						}
						Mautareta::MobSummonCheck[i] = true;
						break;
					}
					Summon(0, Mautareta::Map, IMonster.GetX(), IMonster.GetY(), Mautareta::WandererID, 1, 1, 0, 1800, 0);
					Mautareta::MobSummonCheck[i] = true;
					break;
				}
			}

			if (IMonster.GetMaxHp() == IMonster.GetCurHp())
			{
				for (int i = 0; i < 19; i++)
				{
					Mautareta::MobSummonCheck[i] = false;
				}
			}



		}


		if (!IMonster.IsBuff(777) && IMonster.IsMobHaveTarget() && IMonster.GetMobIndex() == Mautareta::BossID)
		{
			IMonster.Buff(777, 20, 0);
			IMonster._ShowBattleAnimation(IMonster, 223);

			int i = 0;
			IChar Tanky((void*)IMonster.GetMobTanker());
			Tanky.Buff(790, 10, 1000);
			Tanky.SetBuffIcon(1, 1, 2038, 224);
			int Around = Tanky.GetObjectListAround(5);

			while (Around && i <(int)CTools::Rate(3, 6))
			{

				IChar Object((void*)*(DWORD*)Around);
				if (Object.IsValid() && !CChar::IsGState((int)Object.GetOffset(), 2) && IMonster.GetOffset() != Object.GetOffset())
				{
					Object.Buff(790, 10, 1000);
					Object.SetBuffIcon(10000, 0, 2038, 224);

					i++;
				}
				Around = CBaseList::Pop((void*)Around);
			}
		}

		if (IMonster.GetMobIndex() == Mautareta::WandererID && !IMonster.IsBuff(777) && IMonster.IsMobHaveTarget())
		{
			IMonster.Buff(777, 15, 0);
			IMonster._ShowBattleAnimation(IMonster, 213);

			IChar Tanky((void*)IMonster.GetMobTanker());
			int Around = Tanky.GetObjectListAround(5);
			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);
				if (Object.IsValid() && !CChar::IsGState((int)Object.GetOffset(), 2) && IMonster.GetOffset() != Object.GetOffset())
				{
					IMonster.OktayDamageArea(Object, 5000, 214);
				}
				Around = CBaseList::Pop((void*)Around);
			}
		}

		if (IMonster.GetMobIndex() == Mautareta::WandererID && !IMonster.IsBuff(778) && IMonster.IsMobHaveTarget())
		{
			IMonster.Buff(778, 15, 0);
			int Around = IMonster.GetObjectListAround(5);
			IChar Tanker((void*)IMonster.GetMobTanker());
			if (!Tanker.IsBuff(4001) && !Tanker.IsBuff(4002))
			{
				Tanker.Buff(4001, 10, 0);
				Tanker.Buff(4002, 15, 0);
				Tanker.SetBuffIcon(10000, 0, 2040, 225);
			}
		}

		if (IMonster.GetMobIndex() == Mautareta::WandererID && !IMonster.IsBuff(779) && IMonster.IsMobHaveTarget())
		{
			IMonster.Buff(779, 25, 0);
			int j = 0;
			IChar Tanky((void*)IMonster.GetMobTanker());
			Tanky.Buff(7, 2, 0);
			int Around = Tanky.GetObjectListAround(5);

			while (Around && j < (int)CTools::Rate(3, 6))
			{

				IChar Object((void*)*(DWORD*)Around);
				if (Object.IsValid() && !CChar::IsGState((int)Object.GetOffset(), 2) && IMonster.GetOffset() != Object.GetOffset() && Object.GetType() == 0)
				{
					Object.Buff(7, 2, 0);
					j++;
				}
				Around = CBaseList::Pop((void*)Around);
			}
		}
	}

	for (int i = 0; i < RiftAmount; i++)
	{
		if (IMonster.GetMobIndex() == RiftStruct[i].FirstBoss && !IMonster.IsBuff(777) && IMonster.IsMobHaveTarget() && RiftON == true)
		{
			IMonster.Buff(777, 25, 0);
			IMonster._ShowBattleAnimation(IMonster, 146);

			for (int j = 0; j < RiftStruct[i].BossMobSpawnAmount; j++)
				Summon(IMonster.GetMap(), 0, IMonster.GetX(), IMonster.GetY(), RiftStruct[i].BossMobSpawnID, 1, 0, 0, 3600, 0);
		}
	}

	//if (IMonster.IsBuff(777))
	//{
	//	IMonster.IncreaseHp(IMonster.GetMaxHp() - IMonster.GetCurHp());
	//}




	return CMonsterMaguniMaster::Tick(Monster);
}


int __fastcall SummonDie(int Monster, void *edx, int Arg, int Arg1, int Arg2, int Arg3)
{
	IChar IMonster((void*)Monster);



	if (D4Instance::IsUp == true && IMonster.GetMobIndex() == D4Instance::MobID[D4Instance::StageNumber] && D4InstanceON == true)
	{
		D4Instance::MobsKilled++;
	}

	if (RiftON == true)
	{

		for (int i = 0; i < RiftAmount; i++)
		{
			if (IMonster.IsValid() && IMonster.GetMobIndex() == RiftStruct[i].MobID[RiftStruct[i].WaveNumber] && RiftStruct[i].IsUp == true)
			{
				RiftStruct[i].MobDeadCount++;
			}
		}

		for (int i = 0; i < RiftAmount; i++)
		{
			if (IMonster.IsValid() && IMonster.GetMobIndex() == RiftStruct[i].FirstBoss&& RiftStruct[i].IsUp == false)
			{
				RiftStruct[i].IsUp = true;
				CPlayer::WriteAll(0xFF, "dsd", 247, "RIFT STARTED!", 2);
				CPlayer::WriteAll(0xFF, "dsd", 247, "FIND AND KILL ALL MONSTERS!", 2);
				for (int j = 0; j < RiftStruct[i].MobAmount[RiftStruct[i].WaveNumber]; j++)
				{
					Summon(0, RiftStruct[i].Map, RiftStruct[i].SpawnX, RiftStruct[i].SpawnY, RiftStruct[i].MobID[RiftStruct[i].WaveNumber], 1, 0, 0, 3600, 0);
				}
			}
		}

		for (int i = 0; i < RiftAmount; i++)
		{
			if (RiftStruct[i].MobDeadCount == RiftStruct[i].MobAmount[RiftStruct[i].WaveNumber] && RiftStruct[i].WaveNumber != RiftStruct[i].MaxWave&&RiftStruct[i].IsUp == true)
			{
				RiftStruct[i].WaveNumber++;
				RiftStruct[i].MobDeadCount = 0;
				if (RiftStruct[i].MobAmount[RiftStruct[i].WaveNumber] == 1)
				{
					CPlayer::WriteAll(0xFF, "dsd", 247, "LAST STAGE, BOSS SPAWNED", 2);
				}
				else if (RiftStruct[i].WaveNumber != 0)
				{
					CPlayer::WriteAll(0xFF, "dsd", 247, "WAVE DONE PREPARE FOR NEXT ONE!", 2);
				}
				for (int j = 0; j < RiftStruct[i].MobAmount[RiftStruct[i].WaveNumber]; j++)
				{
					Summon(0, RiftStruct[i].Map, RiftStruct[i].SpawnX, RiftStruct[i].SpawnY, RiftStruct[i].MobID[RiftStruct[i].WaveNumber], 1, 0, 0, 3600, 0);
				}

			}
		}

		for (int i = 0; i < RiftAmount; i++)
		{
			if (RiftStruct[i].WaveNumber == RiftStruct[i].MaxWave)
			{
				RiftConfig();
				CPlayer::WriteAll(0xFF, "dsd", 247, "ALL MOBS DIED,YOU DID IT !", 2);
				RiftStruct[i].WaveNumber = 0;
				RiftStruct[i].IsUp = false;
			}
		}
	}



	if (Mautareta::IsUp == true && IMonster.GetMobIndex() == Mautareta::BossID && MautaretaON == true)
	{
		Mautareta::IsUp = false;
		Mautareta::PartyLimit = 0;
	}

	if (BossDropsMap.count(IMonster.GetMobIndex()))
	{
		BossDropDraw(IMonster);
	}


	return CMonsterMaguniMaster::Die(Monster, Arg, Arg1, Arg2, Arg3);
}

#endif