#ifndef FIREBALL_H
#define FIREBALL_H

void __fastcall Fireball(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(73);

	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
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

				int nDmg = (IPlayer.GetMagic()*FBBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*FBIntMultiPvE) + (xSkill.GetGrade()*FBPerGradeMultiPvE);


				if (Target.GetType() == 0)
					nDmg = (IPlayer.GetMagic()*FBBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*FBIntMultiPvP) + (xSkill.GetGrade()*FBPerGradeMultiPvP);


				IPlayer.OktayDamageSingle(Target, nDmg, 73);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif