#ifndef ARROWSOFTHEMASTER_H
#define ARROWSOFTHEMASTER_H

void __fastcall ArrowsOfTheMaster(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsValid() && pSkill)
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

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			nMana = static_cast<int>((1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1))))));
			ICharacter Target(pTarget);

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

				IPlayer.AddFxToTarget("HellGate_FX40", 1, 0, 0);
				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						Object.AddFxToTarget("HellGate_FX40", 1, 0, 0);

						int nDmg = (IPlayer.GetAttack()*AOTMBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*AOTMAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*AOTMStrMultiPvE) + (nSkillGrade*AOTMPerGradeMultiPvE);

						if (Object.GetType() == 0)
							nDmg = (IPlayer.GetAttack()*AOTMBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*AOTMAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*AOTMStrMultiPvP) + (nSkillGrade*AOTMPerGradeMultiPvE);

						IPlayer.OktayDamageArea(Object, nDmg, 92);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				IPlayer.DecreaseMana(nMana);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 92);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}

#endif