#ifndef SHADOWSLASH_H
#define SHADOWSLASH_H
#include "ServerFunctions.h"
void __fastcall ShadowSlash(ICharacter IPlayer, int pPacket, int pPos)
{


	int pSkill = GetSkillPointer(32);


		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = static_cast<int>(230 + (((GetLevel() + nSkillGrade) * nSkillGrade) * 0.63));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;
		
		if (pTarget && IsValid() && nSkillGrade)
		{
			ICharacter Target(pTarget);

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{

				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (/*Object.IsValid() && IsValid() && Target.IsValid() &&*/ (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{

						Object.Buff(7, SHSStunDuration + nSkillGrade * SHSStunDurationPerGrade, 0);
						int nDmg = (GetAttack()*SHSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SHSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SHSStrMultiPvE) + (nSkillGrade*SHSPerGradeMultiPvE);
						if (Object.GetType() == 0)
							nDmg = (GetAttack()*SHSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SHSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SHSStrMultiPvP) + (nSkillGrade*SHSPerGradeMultiPvP);

						OktayDamageArea(Object, nDmg, 32);

					}

					Around = CBaseList::Pop((void*)Around);
				}
			}

			SetDirection(Target);
			_ShowBattleAnimation(Target, 32);
			DecreaseMana(nMana);

			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
}
#endif