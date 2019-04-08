#ifndef MASSIVEARROW_H
#define MASSIVEARROW_H
void __fastcall MassiveFire(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (pSkill && IPlayer.IsValid())
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

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
				return;

			if (pTarget == IPlayer.GetOffset())
				return;

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 20))
					return;

				int nDmg = (IPlayer.GetAttack()*MFBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*MFAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*MFStrMultiPvE) + (nSkillGrade*MFPerGradeMultiPvE);

				if (Target.GetType() == 0)
					nDmg = (IPlayer.GetAttack()*MFBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*MFAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*MFStrMultiPvP) + (nSkillGrade*MFPerGradeMultiPvE);


				IPlayer.OktayDamageSingle(Target, nDmg, 91);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}


#endif