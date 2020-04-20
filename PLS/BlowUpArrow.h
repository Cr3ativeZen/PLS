#ifndef _BLOWUPARROW_H
#define _BLOWUPARROW_H
#include "ServerFunctions.h"

void __fastcall BlowUpArrow(int pSkill, void *pPlayer, int pPacket, int pPos)
{

	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2 ||!pTarget||pTarget==GetOffset()||GetCurMp()<nMana)
		return;


	ICharacter Target(pTarget);

	if (!IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		return;
	}

	if (bType == 0)
	{
		
		if (IsValid() &&Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 14))
			{
				int nDmg = (GetAttack()*BlowUpBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*BlowUpAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*BlowUpStrMultiPvP) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvP);
				OktayDamageSingle(Target, nDmg, 14);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 14);
			}
			else
			{
				_ShowBattleMiss(Target, 14);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(3);
		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{

			if (CheckHit(Target, 14))
			{

				int nDmge = (GetAttack()*BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*BlowUpStrMultiPvE) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvE);
				OktayDamageSingle(Target, nDmge, 14);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 14);

			}
			else
			{
				_ShowBattleMiss(Target, 14);
			}
		}
		int i = 0;
		while (Around&&i< BlowUpPvEMaxHits-1)
		{
			
			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				
				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (CheckHit(Object, 14))
					{
						int nDmg = (GetAttack()*BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*BlowUpStrMultiPvE) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvE);
						OktayDamageSingle(Object, nDmg, 14);
						_ShowBattleAnimation(Object, 14);
						i++;
					}
					else
					{
						_ShowBattleMiss(Object, 14);
						i++;
					}
				}
				
			}
			Around = CBaseList::Pop((void*)Around);
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif