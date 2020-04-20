#ifndef POWERFULWIDENINGWOUND_H
#define POWERFULWIDENINGWOUND_H

void __fastcall PowerfulWideningWound(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(41);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = xSkill.GetGrade() + 30;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		ICharacter Target(pTarget);

		if (!IsInRange(Target, 20))
		{
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;
		}

		if (pTarget && xSkill.GetGrade() && IsValid())
		{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

			if (IPlayer.GetCurMp() < nMana || pTarget == IPlayer.GetOffset())

			if (GetCurMp() < nMana)
=======
			if (IPlayer.GetCurMp() < nMana)
>>>>>>> parent of e123e09... pus
=======
			if (IPlayer.GetCurMp() < nMana)
>>>>>>> parent of e123e09... pus
=======
			if (IPlayer.GetCurMp() < nMana)
>>>>>>> parent of e123e09... pus
=======
			if (IPlayer.GetCurMp() < nMana)
>>>>>>> parent of e123e09... pus
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
			if (pTarget == GetOffset())

=======
			if (pTarget == IPlayer.GetOffset())
>>>>>>> parent of e123e09... pus
=======
			if (pTarget == IPlayer.GetOffset())
>>>>>>> parent of e123e09... pus
=======
			if (pTarget == IPlayer.GetOffset())
>>>>>>> parent of e123e09... pus
=======
			if (pTarget == IPlayer.GetOffset())
>>>>>>> parent of e123e09... pus
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

				if (CheckHit(Target, 10 + ((GetLevel() / 20) + xSkill.GetGrade() * 3)))
				{
					int nDmg = (GetAttack()*PWWBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*PWWAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*PWWStrMultiPvE) + (xSkill.GetGrade()*PWWPerGradeMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack()*PWWBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*PWWAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*PWWStrMultiPvP) + (xSkill.GetGrade()*PWWPerGradeMultiPvP);


					OktayDamageSingle(Target, nDmg, 41);

					if (IsOnline() && IsValid() && Target.IsOnline() && Target.IsValid() && Target.GetType() == 1 && Target.GetCurHp() > 0 && Target.IsMobAggressive() && Target.IsMobHaveTarget())
						CMonsterReal::AddHostility(Target.GetOffset(), (int)GetOffset(), nDmg * PWWHostilityMultiplier, 0);
				}
				else 
				{
					_ShowBattleMiss(Target, 41);
				}

				SetDirection(Target);
			}
		}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		DecreaseMana(nMana);
	}


}



#endif