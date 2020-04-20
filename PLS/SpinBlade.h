#ifndef SPINBLADE_H
#define SPINBLADE_H

void __fastcall ContinueSpinBlade(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(36);
	ISkill xSkill((void*)pSkill);

	int nSkillGrade = xSkill.GetGrade();

	if (!nSkillGrade)
		return;
	if (IsValid()&&!IsBuff(329))
	{
		if (CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid())
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5575);
				return;
			}

			if (IsMoved(CheckContinueSkill.find(GetPID())->second.PlayerX, CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5575);
				return;
			}

			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetAttack()*SBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SBStrMultiPvE) + (nSkillGrade*SBPerGradeMultiPvE);

					if (Object.GetType() == 0)
						nDmg = (GetAttack()*SBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SBStrMultiPvP) + (nSkillGrade*SBPerGradeMultiPvP);

					if (Object.GetType() == 0||Object.GetType() == 1)
						OktayDamageArea(Object, nDmg, 36);
				}

				Around = CBaseList::Pop((void*)Around);
			}
			AddFxToTarget("davi_M635_76", 1, 0, 0);
			_ShowBattleAnimation(IPlayer, 36);

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 900;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5575);
	return;
}

void __fastcall SpinBlade(ICharacter IPlayer)
{

	int pSkill = GetSkillPointer(36);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (int)((((nSkillGrade + GetLevel()) * nSkillGrade)*1.25) + 180);

		if (GetCurMp() < nMana)
			return;

		if (nSkillGrade && IsValid())
		{
			DecreaseMana(nMana);
			CheckContinueSkill[GetPID()].PlayerX = GetX();
			CheckContinueSkill[GetPID()].PlayerY = GetY();
			CheckContinueSkill[GetPID()].PlayerSkillID = 36;
			CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
			CheckContinueSkill[GetPID()].PlayerSkillCount = xSkill.GetGrade() + 1;
			CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			Buff(5575, xSkill.GetGrade()+1, 0);
		}
		ContinueSpinBlade(IPlayer);
	}
}
#endif