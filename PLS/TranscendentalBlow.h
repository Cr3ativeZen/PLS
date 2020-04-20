#ifndef _TRANSCENDENTALBLOW_H
#define _TRANSCENDENTALBLOW_H
#include "ServerFunctions.h"

void __fastcall TranscendentalBlow(int pSkill, void *pPlayer, int pPacket, int pPos)
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


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter Target(pTarget);


	if (bType == 0)
	{

		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmg = (GetAttack()*TBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*TBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*TBStrMultiPvP) + (ISkill.GetGrade()*TBPerGradeMultiPvP);
				OktayDamageSingle(Target, nDmg, 5);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 5);
			}
			else
			{
				_ShowBattleMiss(Target, 5);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(1);
		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmge = (GetAttack()*TBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*TBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*TBStrMultiPvE) + (ISkill.GetGrade()*TBPerGradeMultiPvE);
				OktayDamageSingle(Target, nDmge, 5);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 5);
			}
			else
			{
				_ShowBattleMiss(Target, 5);
			}
		}
		int i = 0;
		while (Around&&i < TBPvEMaxHits - 1)
		{
			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (CheckHit(Object, 20))
					{
						int nDmg = (GetAttack()*TBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*TBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*TBStrMultiPvE) + (ISkill.GetGrade()*TBPerGradeMultiPvE);
						OktayDamageSingle(Object, nDmg, 5);
						_ShowBattleAnimation(Object, 5);
						i++;
					}
					else
					{
						_ShowBattleMiss(Object, 5);
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