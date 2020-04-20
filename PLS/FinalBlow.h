#ifndef FINALBLOW_H
#define FINALBLOW_H
void __fastcall FinalBlow(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(18);

	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			ICharacter Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == IPlayer.GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

					if (Target.GetCurHp() < Target.GetMaxHp() / 2)
					{
						int nDmg = ((IPlayer.GetAttack()*FinalBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*FinalBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*FinalBStrMultiPvE) + (nSkillGrade*FinalBPerGradeMultiPvE))*(FinalBMultiWhenBelowPvE / 100);

						if (Target.GetType() == 0)
							nDmg = ((IPlayer.GetAttack()*FinalBBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*FinalBAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*FinalBStrMultiPvP) + (nSkillGrade*FinalBPerGradeMultiPvE))*(FinalBMultiWhenBelowPvP / 100);
						IPlayer.OktayDamageSingle(Target, nDmg, 18);
					}
					else
					{
						int nDmg = ((IPlayer.GetAttack()*FinalBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*FinalBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*FinalBStrMultiPvE) + (nSkillGrade*FinalBPerGradeMultiPvE));

						if (Target.GetType() == 0)
							nDmg = ((IPlayer.GetAttack()*FinalBBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*FinalBAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*FinalBStrMultiPvP) + (nSkillGrade*FinalBPerGradeMultiPvE));
						IPlayer.OktayDamageSingle(Target, nDmg, 18);
					}


				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 18);
				IPlayer.DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif