#ifndef SWORDDANCE_H
#define SWORDDANCE_H
void __fastcall ContinueSwordDance(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && IsValid())
		{
			if (CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
			{
				ICharacter Target(pTarget);

				if (IsValid() && Target.IsValid())
				{
					CheckContinueSkill[GetPID()].PlayerSkillCount--;

					if (!IsValid())
					{
						ResetContinueSkill(IPlayer);
						CancelBuff(5585);
						return;
					}

					if (IsOnline() && !CPlayer::IsWState((int)GetOffset(), 12))
					{
						ResetContinueSkill(IPlayer);
						CancelBuff(5585);
						return;
					}

					if (IsOnline() && !IsInRange(Target, 2))
					{
						ResetContinueSkill(IPlayer);
						CancelBuff(5585);
						return;
					}

						int nDmg = (GetAttack()*SDBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SDAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SDStrMultiPvE) + (nSkillGrade*SDPerGradeMultiPvE);

						if (Target.GetType() == 0)
							nDmg = (GetAttack()*SDBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SDAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SDStrMultiPvP) + (nSkillGrade*SDPerGradeMultiPvP);


						OktayDamageSingle(Target, nDmg, 43);

						if (IsOnline())
							CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 800;

						if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
						{
							ResetContinueSkill(IPlayer);
							CancelBuff(5585);
						}

						return;
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5585);
	return;
}

void __fastcall SwordDance(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(43);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0, nMana = 0, nSkillGrade = 0; char bType = 0; void *pTarget = 0;
		nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (nSkillGrade <= 1)
			nMana = 245;
		else if (nSkillGrade == 2)
			nMana = 283;
		else if (nSkillGrade == 3)
			nMana = 325;
		else if (nSkillGrade == 4)
			nMana = 371;
		else if (nSkillGrade >= 5)
			nMana = 420;

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

			Buff(5585, xSkill.GetGrade() + 1, 0);
			if (IsValid() && Target.IsValid())
			{
				DecreaseMana(nMana);
				CheckContinueSkill[GetPID()].PlayerSkillID = 43;
				CheckContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
				CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				CheckContinueSkill[GetPID()].PlayerSkillCount = xSkill.GetGrade() + 1;
				CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueSwordDance(IPlayer);
	}
}
#endif