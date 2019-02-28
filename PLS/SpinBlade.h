#ifndef SPINBLADE_H
#define SPINBLADE_H

void __fastcall ContinueSpinBlade(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(36);
	ISkill xSkill((void*)pSkill);
	int nSkillGrade = xSkill.GetGrade();
	if (IPlayer.IsValid()&&!IPlayer.IsBuff(329))
	{
		if (CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

			if (!IPlayer.IsValid())
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5575);
				return;
			}

			if (IPlayer.IsMoved(CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerX, CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5575);
				return;
			}

			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack()*SBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*SBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*SBStrMultiPvE) + (nSkillGrade*SBPerGradeMultiPvE);

					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*SBBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*SBAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*SBStrMultiPvP) + (nSkillGrade*SBPerGradeMultiPvP);

					if (Object.GetType() == 0||Object.GetType() == 1)
						IPlayer.OktayDamageArea(Object, nDmg, 36);
				}

				Around = CBaseList::Pop((void*)Around);
			}
			IPlayer.AddFxToTarget("davi_M635_76", 1, 0, 0);
			IPlayer._ShowBattleAnimation(IPlayer, 36);

			if (IPlayer.IsOnline())
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 900;

			if (IPlayer.IsOnline() && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	IPlayer.CancelBuff(5575);
	return;
}

void __fastcall SpinBlade(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(36);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (int)((((nSkillGrade + IPlayer.GetLevel()) * nSkillGrade)*1.25) + 180);

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			IPlayer.DecreaseMana(nMana);
			CheckContinueSkill[IPlayer.GetPID()].PlayerX = IPlayer.GetX();
			CheckContinueSkill[IPlayer.GetPID()].PlayerY = IPlayer.GetY();
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 36;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = xSkill.GetGrade();
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = xSkill.GetGrade() + 1;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
			IPlayer.Buff(5575, xSkill.GetGrade()+1, 0);
		}
		ContinueSpinBlade(IPlayer);
	}
}
#endif