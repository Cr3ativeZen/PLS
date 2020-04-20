#ifndef FINALBLOW_H
#define FINALBLOW_H
void __fastcall FinalBlow(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(18);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0; int nMana = 450;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

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
				if (CChar::GetRange((int)GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

					if (Target.GetCurHp() < Target.GetMaxHp() / 2)
					{
						int nDmg = ((GetAttack()*FinalBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*FinalBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*FinalBStrMultiPvE) + (nSkillGrade*FinalBPerGradeMultiPvE))*(FinalBMultiWhenBelowPvE / 100);

						if (Target.GetType() == 0)
							nDmg = ((GetAttack()*FinalBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*FinalBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*FinalBStrMultiPvP) + (nSkillGrade*FinalBPerGradeMultiPvE))*(FinalBMultiWhenBelowPvP / 100);
						OktayDamageSingle(Target, nDmg, 18);
					}
					else
					{
						int nDmg = ((GetAttack()*FinalBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*FinalBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*FinalBStrMultiPvE) + (nSkillGrade*FinalBPerGradeMultiPvE));

						if (Target.GetType() == 0)
							nDmg = ((GetAttack()*FinalBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*FinalBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*FinalBStrMultiPvP) + (nSkillGrade*FinalBPerGradeMultiPvE));
						OktayDamageSingle(Target, nDmg, 18);
					}


				SetDirection(Target);
				_ShowBattleAnimation(Target, 18);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif