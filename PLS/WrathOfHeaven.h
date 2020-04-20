#ifndef WRATHOFHEAVEN_H
#define WRATHOFHEAVEN_H

void __fastcall WrathOfHeaven(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(33);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (GetLevel() + nSkillGrade) * 3 + 50;

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
				if (!IsInRange(Target,300))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (CheckHit(Target, 30))
				{
					int nDmg = (GetAttack()*WOHBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*WOHAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvE) + (nSkillGrade*WOHPerGradeMultiPvE);


					if (Target.GetType() == 0)
						nDmg = (GetAttack()*WOHBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*WOHAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvP) + (nSkillGrade*WOHPerGradeMultiPvP);

					OktayDamageSingle(Target,nDmg,33);
				} else 
				{
					_ShowBattleMiss(Target, 33);
				}

				SetDirection(Target);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif