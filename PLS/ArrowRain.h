#ifndef ARROWRAIN_H
#define ARROWRAIN_H
#include "ServerFunctions.h"
#include "ResetContinueSkill.h"
void __fastcall ContinueArrowRain(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5565);
				return;
			}

			if (IsMoved(CheckContinueSkill.find(GetPID())->second.PlayerX, CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5565);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while(Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetAttack()*ARBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvE) + (nSkillGrade*ARPerGradeMultiPvE);

					if (Object.GetType() == 0)
						nDmg = (GetAttack()*ARBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvP) + (nSkillGrade*ARPerGradeMultiPvP);


					OktayDamageArea(Object,nDmg,47);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount64() + 900;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5565);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5565);
	return;
}

void __fastcall ArrowRain(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(47);

	if (IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(5565, 10, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(IPlayer,47);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(567,GetMap(),(int)GetSetXY,1,(int)GetOffset(),0,10000);
			delete[] GetSetXY;
			CheckContinueSkill[GetPID()].PlayerSkillID = 47;
			CheckContinueSkill[GetPID()].PlayerTarget = (void*)check;
			CheckContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueSkill[GetPID()].PlayerSkillCount = 10;
			CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			CheckContinueSkill[GetPID()].PlayerX = GetX();
			CheckContinueSkill[GetPID()].PlayerY = GetY();
		}
		ContinueArrowRain(IPlayer);
	}
}

//void __fastcall ArrowRain(ICharacter IPlayer, int pPacket, int pPos)
//{
//	int pSkill = GetSkillPointer(47);
//
//	if (IsValid() && pSkill)
//	{
//		int x = 0, y = 0;
//		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
//		ISkill xSkill((void*)pSkill);
//		int nSkillGrade = xSkill.GetGrade();
//
//		if (!nSkillGrade)
//			return;
//
//		int nMana = 20 + (GetLevel() * 4);
//
//		if (x <= 0 || y <= 0)
//			return;
//
//		if (nSkillGrade && IsValid())
//		{
//			if (GetCurMp() < nMana)
//				return;
//
//			DecreaseMana(nMana);
//			_ShowBattleAnimation(IPlayer,47);
//			int *GetSetXY = new int[1];
//			GetSetXY[0] = x;
//			GetSetXY[1] = y;
//			int check = CMonsterMagic::Create(567,GetMap(),(int)GetSetXY,1,(int)GetOffset(),0,10000);
//			delete[] GetSetXY;
//
//			int XX=GetX();
//			int YY=GetY();
//			CheckContinueSkill[GetPID()].PlayerX = GetX();
//			CheckContinueSkill[GetPID()].PlayerY = GetY();
//
//			int delay = GetTickCount();
//			int skillCount = 0;
//			ICharacter Target((void*)check);
//			while (skillCount < 10)
//			{
//
//				if (IsMoved(XX,YY))
//				{
//					break;
//				}
//
//				if (!IsValid() || !Target.IsValid())
//				{
//					break;
//				}
//
//				if (delay < static_cast<int>(GetTickCount()))
//				{
//					int Around = Target.GetObjectListAround(3);
//
//					while (Around)
//					{
//						ICharacter Object((void*)*(DWORD*)Around);
//
//						if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
//						{
//							int nDmg = (GetAttack()*ARBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvE) + (nSkillGrade*ARPerGradeMultiPvE);
//
//							if (Object.GetType() == 0)
//								nDmg = (GetAttack()*ARBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvP) + (nSkillGrade*ARPerGradeMultiPvE);
//
//
//							OktayDamageArea(Object, nDmg, 47);
//						}
//						Around = CBaseList::Pop((void*)Around);
//					}
//					delay = GetTickCount() + 900;
//					skillCount++;
//				}
//			}
//		}
//		//ContinueArrowRain(IPlayer);
//	}
//	CouldntExecuteSkill();
//}
#endif