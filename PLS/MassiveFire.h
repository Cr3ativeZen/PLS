#ifndef MASSIVEARROW_H
#define MASSIVEARROW_H
void __fastcall MassiveFire(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(91);

	if (pSkill && IsValid())
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
					return;

				int nDmg = (GetAttack()*MFBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*MFAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*MFStrMultiPvE) + (nSkillGrade*MFPerGradeMultiPvE);

				if (Target.GetType() == 0)
					nDmg = (GetAttack()*MFBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*MFAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*MFStrMultiPvP) + (nSkillGrade*MFPerGradeMultiPvE);


				OktayDamageSingle(Target, nDmg, 91);
				SetDirection(Target);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}


#endif