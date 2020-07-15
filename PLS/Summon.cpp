#include "Summon.h"

int __cdecl MonsterSummon(int Player, int Map, int X, int Y, int Index, int Amount, int SafeZoneCheck, int Delay)
{
	void* GetMonster = 0; int Value = 0, Monster = 0, Argument = 0;
	int GetMap = Undefined::MapCheck(Map);

	if (GetMap)
	{
		void* MonsterValueCheck = (void*)Undefined::GetMonsterValue(0x2B0u);

		if (MonsterValueCheck)
			GetMonster = Undefined::MonsterCreate(MonsterValueCheck);         //malloc here
		else
			GetMonster = 0;

		Monster = (int)GetMonster;
		ICharacter IMonster((void*)Monster);
		CIOCriticalSection::Enter((void*)0x4E182C);
		Undefined::CreateMonsterValue((void*)0x4E1820, (int)&Argument, (int)&Index);
		int GetCheck = Undefined::Check((int)0x4E1820, (int)&Value);

		if (*(DWORD*)(void*)&Argument == *(DWORD*)GetCheck)
		{
			CIOCriticalSection::Leave((void*)0x4E182C);
		}
		else 
		{
			int Check = *(DWORD*)(Undefined::GetValue(&Argument) + 4);

			if (*(DWORD*)(Check + 304))
			{
				int GetSetXY[2];
				GetSetXY[0] = X;
				GetSetXY[1] = Y;
				*(DWORD*)(Monster + 316) = Map;
				*(DWORD*)(Monster + 320) = GetMap;
				*(DWORD*)(Monster + 512) = Index;
				*(DWORD*)(Monster + 476) = 1;


				CChar::SetXY(Monster, (int)GetSetXY);
				(*(void(__thiscall**)(int, int))(*(DWORD*)IMonster.GetOffset() + 192))(Monster, Check);

				if (Delay)
				{
					IMonster.Buff(159, (Delay + 2000) / 1000, 0);
					IMonster.Delay(Delay);
					IMonster.UnAttack(Delay);
				}

				CIOCriticalSection::Leave((void*)0x4E182C);
				CChar::Lock((void*)Monster);
				int CellMapCoordinate[2];
				CellMapCoordinate[0] = X >> 5;
				CellMapCoordinate[1] = Y >> 5;
				IMonster.MonsterSummonWrite(SafeZoneCheck, Monster, (int)CellMapCoordinate);
			}
			else
				CIOCriticalSection::Leave((void*)0x4E182C);

		}
	}



	return Monster;
}