#ifndef FIREBALL_H
#define FIREBALL_H

void __fastcall Fireball(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(73);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((nSkillGrade - 1) + 30) * nSkillGrade) + 300) * 0.79);

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

				int nDmg = (GetMagic()*FBBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*FBIntMultiPvE) + (xSkill.GetGrade()*FBPerGradeMultiPvE);


				if (Target.GetType() == 0)
					nDmg = (GetMagic()*FBBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*FBIntMultiPvP) + (xSkill.GetGrade()*FBPerGradeMultiPvP);


				OktayDamageSingle(Target, nDmg, 73);
				SetDirection(Target);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif