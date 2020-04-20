#ifndef ONEHITSTRIKE_H
#define ONEHITSTRIKE_H

void __fastcall OneHitStrike(ICharacter IPlayer, int pPacket, int pPos)
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
		int nMana = static_cast<int>((1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1))))));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2)
			return;

		ICharacter Target(pTarget);

		if (pTarget && nSkillGrade && IsValid())
		{


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

				Target.AddFxToTarget("test_item_ef_small_11", 1, 0, 0);
					AddFxToTarget("davi_M598_71", 1, 0, 0);

				int nDmg = (GetAttack()*OHSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*OHSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*OHSStrMultiPvE) + (nSkillGrade*OHSPerGradeMultiPvE);

				if (Target.GetType() == 0)
					nDmg = (GetAttack()*OHSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*OHSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*OHSStrMultiPvP) + (nSkillGrade*OHSPerGradeMultiPvE);


				OktayDamageSingle(Target, nDmg, 90);
				SetDirection(Target);
				DecreaseMana(nMana);
			}

		}
		else {
			CouldntExecuteSkill();
		}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	}
}

#endif