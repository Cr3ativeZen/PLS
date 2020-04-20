#ifndef TWINBLADESTRIKE_H
#define TWINBLADESTRIKE_H
void __fastcall ContinueTwinBladeStrike(ICharacter IPlayer)
{
	if (IsValid())
	{
		void *pTarget = CheckFarContinueSkill.find(GetPID())->second.PlayerTarget;
		ICharacter Target(pTarget);

		if (pTarget && Target.IsValid() && IsValid())
		{
			if (CheckFarContinueSkill.find(GetPID())->second.PlayerSkillCount)
			{
				CheckFarContinueSkill[GetPID()].PlayerSkillCount--;

				if (CChar::GetRange((int)GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetFarContinueSkill(IPlayer);
					CancelBuff(5578);
					return;
				}
					int nDmg = (GetAttack()*TBSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*TBSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*TBSStrMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack()*TBSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*TBSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*TBSStrMultiPvP);


					OktayDamageArea(Target, nDmg, 23);
				

				if (IsOnline())
					CheckFarContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

				if (IsOnline() && CheckFarContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
				{
					ResetFarContinueSkill(IPlayer);
					CancelBuff(5578);
				}

				return;
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	CancelBuff(5578);
	return;
}

void __fastcall TwinBladeStrike(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(23);

	ISkill xSkill((void*)pSkill);

	int nSkillGrade = xSkill.GetGrade();

	if (!nSkillGrade)
		return;

	if (IsValid() && pSkill)
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset())
			return;

		if (pTarget && IsValid())
		{
			ICharacter Target(pTarget);

			if (GetCurMp() < 65)
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

				if (CheckHit(Target, 10))
				{
					CheckFarContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
					CheckFarContinueSkill[GetPID()].PlayerSkillID = 23;
					CheckFarContinueSkill[GetPID()].PlayerSkillCount = 5;
					CheckFarContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;
					CheckFarContinueSkill[GetPID()].CasterOffset = GetOffset();
					if (!Target.IsBuff(339))
						Target.SendGStateEx(Target.GetGStateEx() + 262144);

					Target.Buff(339, 8, 0);
					Target.Buff(340, 12, 0);
					Buff(341, 20, 0);
					Buff(5578, 10, 0);

					if (Target.GetType() == 0)
					{
						RemoveBuffIcon(0, 0, 0, 219);
						Target.SetBuffIcon(10000, 0, 2021, 219);
					}

					int nDmg = (GetAttack()*TBSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*TBSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*TBSStrMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack()*TBSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*TBSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*TBSStrMultiPvP);


					OktayDamageSingle(Target, nDmg, 23);
				}
				else {
					_ShowBattleMiss(Target, 23);
				}

				SetDirection(Target);
				DecreaseMana(65);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueTwinBladeStrike(IPlayer);
	}
}
#endif