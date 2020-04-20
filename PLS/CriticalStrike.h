#ifndef CRITICALSTRIKE_H
#define CRITICALSTRIKE_H

void __fastcall CriticalStrike(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(90);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (50 + (3 * (GetLevel() + nSkillGrade)));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			ICharacter Target(pTarget);

			if (IsValid() && Target.IsValid())
			{
				if (pTarget == GetOffset())
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int nDmg = 5000;

				if (Target.GetType() == 0)
					nDmg = 5000;

				OktayDamageSingle(Target, nDmg, 90);
				SetDirection(Target);
				DecreaseMana(nMana);
				OktayDamageSingle(Target, nDmg, 90);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		else {
			CouldntExecuteSkill();
		}
	}
}

#endif