#ifndef WRATHOFHEAVEN_H
#define WRATHOFHEAVEN_H

void __fastcall WrathOfHeaven(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(33);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (IPlayer.GetLevel() + nSkillGrade) * 3 + 50;

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
				if (!IPlayer.IsInRange(Target,300))
					return;

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack()*WOHBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*WOHAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*ARStrMultiPvE) + (nSkillGrade*WOHPerGradeMultiPvE);


					if (Target.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*WOHBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*WOHAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*ARStrMultiPvP) + (nSkillGrade*WOHPerGradeMultiPvP);

					IPlayer.OktayDamageSingle(Target,nDmg,33);
				} else {
					IPlayer._ShowBattleMiss(Target, 33);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif