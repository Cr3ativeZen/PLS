#ifndef ICICLE_H
#define ICICLE_H
void __fastcall ContinueIcicle(ICharacter IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(66);
	ISkill xSkill((void*)pSkill);
	if (IPlayer.IsValid())
	{
		if (CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

			if (IPlayer.IsMoved(CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerX, CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5556);
				IPlayer.CouldntExecuteSkill();
				return;
			}

			if (!IPlayer.IsValid())
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5556);
				IPlayer.CouldntExecuteSkill();
				return;
			}

			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic()*ICIBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*ICIIntMultiPvE) + (xSkill.GetGrade()*ICIPerGradeMultiPvE);

					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetMagic()*ICIBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*ICIIntMultiPvP) + (xSkill.GetGrade()*ICIPerGradeMultiPvP);


	
					IPlayer.OktayDamageArea(Object, nDmg, 66);

					if (CTools::Rate(0, 100) < 10)
					{
						Object.Buff(8, ICIColdBindDuration, 0);
					}

				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5556);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	IPlayer.CancelBuff(5556);
	IPlayer.CouldntExecuteSkill();
	return;
}

void __fastcall Icicle(ICharacter IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(66);
	if (IPlayer.IsValid() && pSkill)
	{
		int nMana = IPlayer.GetLevel() * 4 + 120;

		if (IPlayer.GetCurMp() < nMana)
			return;

		IPlayer.Buff(5556, 10, 0);
		IPlayer.DecreaseMana(nMana);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		CheckContinueSkill[IPlayer.GetPID()].PlayerX = IPlayer.GetX();
		CheckContinueSkill[IPlayer.GetPID()].PlayerY = IPlayer.GetY();
		CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 66;
		CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = xSkill.GetGrade();
		CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 5;
		CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
		IPlayer._ShowBattleAnimation(IPlayer, 66);
	}
	ContinueIcicle(IPlayer);
}
#endif