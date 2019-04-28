#ifndef VITALSTRIKE_H
#define VITALSTRIKE_H

void __fastcall VitalStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(16);

	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

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
				if (!IPlayer.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (IPlayer.CheckHit(Target, 25))
				{
					int nDmg = (IPlayer.GetAttack()*VSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*VSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*VSStrMultiPvE) + (nSkillGrade*VSPerGradeMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*VSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*VSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*VSStrMultiPvP) + (nSkillGrade*VSPerGradeMultiPvP);



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

					
					IPlayer.OktayDamageSingle(Target, nDmg, 16);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 16);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}

			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}


#endif