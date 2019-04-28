#ifndef COMBATIVESPIRIT_H
#define COMBATIVESPIRIT_H
#include "ServerFunctions.h"
void __fastcall CombativeSpirit(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(51);

	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset())
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			IChar Target(pTarget);
			int nMana = (int)(((((nSkillGrade-1)+20) * nSkillGrade)+200) * 1.85);

			if (pTarget == IPlayer.GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				IPlayer.DecreaseMana(nMana);


				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 51);
				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack()*CSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*CSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*CSStrMultiPvE) + (nSkillGrade*CSPerGradeMultiPvE);


						if (Target.GetType() == 0)
							nDmg = (IPlayer.GetAttack()*CSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*CSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*CSStrMultiPvP + (nSkillGrade*CSPerGradeMultiPvP));

						if (Object.GetX() <= max(IPlayer.GetX(), Target.GetX()) && Object.GetX() >= min(IPlayer.GetX(), Target.GetX()) && Object.GetY() <= max(IPlayer.GetY(), Target.GetY()) && Object.GetY() >= min(IPlayer.GetY(), Target.GetY()))
							IPlayer.OktayDamageArea(Object, nDmg, 51);
					}

					Around = CBaseList::Pop((void*)Around);
				}

			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}

	}
}
#endif