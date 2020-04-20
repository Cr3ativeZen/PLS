#ifndef COMBATIVESPIRIT_H
#define COMBATIVESPIRIT_H
#include "ServerFunctions.h"
void __fastcall CombativeSpirit(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(51);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);	
		
		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset())
			return;

		if (IsValid() && pTarget && nSkillGrade)
		{
			ICharacter Target(pTarget);
			int nMana = (int)(((((nSkillGrade-1)+20) * nSkillGrade)+200) * 1.85);

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				DecreaseMana(nMana);


				SetDirection(Target);
				_ShowBattleAnimation(Target, 51);
				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (GetAttack()*CSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*CSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*CSStrMultiPvE) + (nSkillGrade*CSPerGradeMultiPvE);


						if (Target.GetType() == 0)
							nDmg = (GetAttack()*CSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*CSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*CSStrMultiPvP + (nSkillGrade*CSPerGradeMultiPvP));

						if (Object.GetX() <= max(GetX(), Target.GetX()) && Object.GetX() >= min(GetX(), Target.GetX()) && Object.GetY() <= max(GetY(), Target.GetY()) && Object.GetY() >= min(GetY(), Target.GetY()))
							OktayDamageArea(Object, nDmg, 51);
					}

					Around = CBaseList::Pop((void*)Around);
				}

			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}

	}
}
#endif