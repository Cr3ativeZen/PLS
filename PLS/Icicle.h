#ifndef ICICLE_H
#define ICICLE_H
void __fastcall ContinueIcicle(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(66);
	ISkill xSkill((void*)pSkill);
	if (IsValid())
	{
		if (CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (IsMoved(CheckContinueSkill.find(GetPID())->second.PlayerX, CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5556);
				CouldntExecuteSkill();
				return;
			}

			if (!IsValid())
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5556);
				CouldntExecuteSkill();
				return;
			}

			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetMagic()*ICIBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*ICIIntMultiPvE) + (xSkill.GetGrade()*ICIPerGradeMultiPvE);

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*ICIBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*ICIIntMultiPvP) + (xSkill.GetGrade()*ICIPerGradeMultiPvP);


	
					OktayDamageArea(Object, nDmg, 66);

					if (CTools::Rate(0, 100) < 10)
					{
						Object.Buff(8, ICIColdBindDuration, 0);
					}

				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5556);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5556);
	CouldntExecuteSkill();
	return;
}

void __fastcall Icicle(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(66);
	if (IsValid() && pSkill)
	{
		int nMana = GetLevel() * 4 + 120;

		if (GetCurMp() < nMana)
			return;

		Buff(5556, 10, 0);
		DecreaseMana(nMana);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		CheckContinueSkill[GetPID()].PlayerX = GetX();
		CheckContinueSkill[GetPID()].PlayerY = GetY();
		CheckContinueSkill[GetPID()].PlayerSkillID = 66;
		CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
		CheckContinueSkill[GetPID()].PlayerSkillCount = 5;
		CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
		_ShowBattleAnimation(IPlayer, 66);
	}
	ContinueIcicle(IPlayer);
}
#endif