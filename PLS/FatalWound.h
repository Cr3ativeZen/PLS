#ifndef FATALWOUND_H
#define FATALWOUND_H
void __fastcall ContinueFatalWound(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			IChar Target(pTarget);
			CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

			if (!Target.IsValid() || !IPlayer.IsValid())
			{
				ResetFarContinueSkill(IPlayer);
				IPlayer.CancelBuff(5576);
				return;
			}

			if (!IPlayer.IsInRange(Target, 300))
			{
				ResetFarContinueSkill(IPlayer);
				IPlayer.CancelBuff(5576);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				int nDmg = (IPlayer.GetAttack()*FWBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*FWAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*FWStrMultiPvE) + (nSkillGrade*FWPerGradeMultiPvE);

				if (Target.GetType() == 0)
				{
					nDmg = (IPlayer.GetAttack()*FWBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*FWAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*FWStrMultiPvP) + (nSkillGrade*FWPerGradeMultiPvP);
					if (Target.IsBuff(346))
					{
						nDmg +=(nDmg * (AnkleAPercentDamageIncreasePvP)/100);
					}
				}
				else
				{
					if (Target.IsBuff(346))
					{
						nDmg +=(nDmg * (AnkleAPercentDamageIncreasePvE) / 100);
					}
				}


				IPlayer.OktayDamageArea(Target, nDmg, 14);
			}

			if (IPlayer.IsOnline())
				CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				ResetFarContinueSkill(IPlayer);
				IPlayer.CancelBuff(5576);
			}

			return;
		}
	}

	ResetFarContinueSkill(IPlayer);
	IPlayer.CancelBuff(5576);
	return;
}

void __fastcall FatalWound(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(14);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 15);

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

				if (!Target.IsBuff(348))
				{
					
					Target.SendGStateEx(Target.GetGStateEx() + 32768);
					Target.Buff(348, 16, 0);
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerTarget = Target.GetOffset();
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillID = 14;
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 8;
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
					CheckFarContinueSkill[IPlayer.GetPID()].CasterOffset = IPlayer.GetOffset();
					IPlayer.Buff(5576, 16, 0);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(Target, 14, nSkillGrade);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif