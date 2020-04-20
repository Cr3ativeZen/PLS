#ifndef ARROWSOFTHEMASTER_H
#define ARROWSOFTHEMASTER_H

void __fastcall ArrowsOfTheMaster(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(92);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			nMana = static_cast<int>(1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));
			ICharacter Target(pTarget);

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

				AddFxToTarget("HellGate_FX40", 1, 0, 0);
				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						Object.AddFxToTarget("HellGate_FX40", 1, 0, 0);

						int nDmg = (GetAttack()*AOTMBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*AOTMAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*AOTMStrMultiPvE) + (nSkillGrade*AOTMPerGradeMultiPvE);

						if (Object.GetType() == 0)
							nDmg = (GetAttack()*AOTMBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*AOTMAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*AOTMStrMultiPvP) + (nSkillGrade*AOTMPerGradeMultiPvE);

						OktayDamageArea(Object, nDmg, 92);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				DecreaseMana(nMana);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 92);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}

#endif