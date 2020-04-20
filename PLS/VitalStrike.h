#ifndef VITALSTRIKE_H
#define VITALSTRIKE_H

void __fastcall VitalStrike(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(16);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 30 + 35;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
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
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (CheckHit(Target, 25))
				{
					int nDmg = (GetAttack()*VSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*VSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*VSStrMultiPvE) + (nSkillGrade*VSPerGradeMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack()*VSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*VSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*VSStrMultiPvP) + (nSkillGrade*VSPerGradeMultiPvP);



					if (Target.GetCurHp() <= (Target.GetMaxHp() / 2))
					{
						Target.Buff(7, nSkillGrade * 2, 0);
						Target.Buff(344, nSkillGrade * 2, 0);
						Target.Buff(345, nSkillGrade * 10, 0);
						Target.SetBuffIcon(nSkillGrade * 2000, 0, 2016, 211);

						if (Target.GetType() == 0)
						{
							nDmg = nDmg * (VSDmgMultiWhenBelowPvP/100);
						}
						nDmg = nDmg * (VSDmgMultiWhenBelowPvE/100);
					}

					
					OktayDamageSingle(Target, nDmg, 16);
				}
				else {
					_ShowBattleMiss(Target, 16);
				}

				SetDirection(Target);
				DecreaseMana(nMana);
			}

			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}


#endif