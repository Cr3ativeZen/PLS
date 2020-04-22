#ifndef CRITICALSTRIKE_H
#define CRITICALSTRIKE_H

void __fastcall CriticalStrike(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (50 + (3 * (IPlayer.GetLevel() + nSkillGrade)));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana)
				return;

			ICharacter Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (pTarget == IPlayer.GetOffset())
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IPlayer.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int nDmg = 5000;

				if (Target.GetType() == 0)
					nDmg = 5000;

				IPlayer.OktayDamageSingle(Target, nDmg, 90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.OktayDamageSingle(Target, nDmg, 90);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}
	}
}

#endif