#ifndef ONEHITSTRIKE_H
#define ONEHITSTRIKE_H

void __fastcall OneHitStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
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
				if (!IPlayer.IsInRange(Target, 300))
					return;

				Target.AddFxToTarget("test_item_ef_small_11", 1, 0, 0);
					IPlayer.AddFxToTarget("davi_M598_71", 1, 0, 0);

				int nDmg = (IPlayer.GetAttack()*OHSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*OHSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*OHSStrMultiPvE) + (nSkillGrade*OHSPerGradeMultiPvE);

				if (Target.GetType() == 0)
					nDmg = (IPlayer.GetAttack()*OHSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*OHSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*OHSStrMultiPvP) + (nSkillGrade*OHSPerGradeMultiPvE);


				IPlayer.OktayDamageSingle(Target, nDmg, 90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}

#endif