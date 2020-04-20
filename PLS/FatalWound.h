#ifndef FATALWOUND_H
#define FATALWOUND_H
void __fastcall ContinueFatalWound(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckFarContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckFarContinueSkill.find(GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && CheckFarContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckFarContinueSkill[GetPID()].PlayerSkillCount--;

			if (!Target.IsValid() || !IsValid())
			{
				ResetFarContinueSkill(IPlayer);
				CancelBuff(5576);
				return;
			}

			if (!IsInRange(Target, 20))
			{
				ResetFarContinueSkill(IPlayer);
				CancelBuff(5576);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				int nDmg = (GetAttack()*FWBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*FWAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*FWStrMultiPvE) + (nSkillGrade*FWPerGradeMultiPvE);

				if (Target.GetType() == 0)
				{
					nDmg = (GetAttack()*FWBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*FWAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*FWStrMultiPvP) + (nSkillGrade*FWPerGradeMultiPvP);
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


				OktayDamageArea(Target, nDmg, 14);
			}

			if (IsOnline())
				CheckFarContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckFarContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetFarContinueSkill(IPlayer);
				CancelBuff(5576);
			}

			return;
		}
	}

	ResetFarContinueSkill(IPlayer);
	CancelBuff(5576);
	return;
}

void __fastcall FatalWound(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(14);

	if (IsValid() && pSkill)
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

				if (!Target.IsBuff(348))
				{
					
					Target.SendGStateEx(Target.GetGStateEx() + 32768);
					Target.Buff(348, 16, 0);
					CheckFarContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
					CheckFarContinueSkill[GetPID()].PlayerSkillID = 14;
					CheckFarContinueSkill[GetPID()].PlayerSkillCount = 8;
					CheckFarContinueSkill[GetPID()].PlayerSkillDelay = 0;
					CheckFarContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
					CheckFarContinueSkill[GetPID()].CasterOffset = GetOffset();
					Buff(5576, 16, 0);
				}

				SetDirection(Target);
				DecreaseMana(nMana);
				_ShowBattleAnimation(Target, 14, nSkillGrade);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif