#ifndef TWINBLADESTRIKE_H
#define TWINBLADESTRIKE_H
void __fastcall ContinueTwinBladeStrike(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;
		IChar Target(pTarget);

		if (pTarget && Target.IsValid() && IPlayer.IsValid())
		{
			if (CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
			{
				CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetFarContinueSkill(IPlayer);
					IPlayer.CancelBuff(5578);
					return;
				}
					int nDmg = (IPlayer.GetAttack()*TBSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*TBSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*TBSStrMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*TBSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*TBSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*TBSStrMultiPvP);


					IPlayer.OktayDamageArea(Target, nDmg, 23);
				

				if (IPlayer.IsOnline())
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

				if (IPlayer.IsOnline() && CheckFarContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
				{
					ResetFarContinueSkill(IPlayer);
					IPlayer.CancelBuff(5578);
				}

				return;
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	IPlayer.CancelBuff(5578);
	return;
}

void __fastcall TwinBladeStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(23);

	ISkill xSkill((void*)pSkill);

	int nSkillGrade = xSkill.GetGrade();

	if (!nSkillGrade)
		return;

	if (IPlayer.IsValid() && pSkill)
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset())
			return;

		if (pTarget && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < 65)
				return;

			if (pTarget == IPlayer.GetOffset())
				return;

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 20))
					return;

				if (IPlayer.CheckHit(Target, 10))
				{
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerTarget = Target.GetOffset();
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillID = 23;
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 5;
					CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;
					CheckFarContinueSkill[IPlayer.GetPID()].CasterOffset = IPlayer.GetOffset();
					if (!Target.IsBuff(339))
						Target.SendGStateEx(Target.GetGStateEx() + 262144);

					Target.Buff(339, 8, 0);
					Target.Buff(340, 12, 0);
					IPlayer.Buff(341, 20, 0);
					IPlayer.Buff(5578, 10, 0);

					if (Target.GetType() == 0)
					{
						IPlayer.RemoveBuffIcon(0, 0, 0, 219);
						Target.SetBuffIcon(10000, 0, 2021, 219);
					}

					int nDmg = (IPlayer.GetAttack()*TBSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*TBSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*TBSStrMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*TBSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*TBSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*TBSStrMultiPvP);


					IPlayer.OktayDamageSingle(Target, nDmg, 23);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 23);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(65);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueTwinBladeStrike(IPlayer);
	}
}
#endif