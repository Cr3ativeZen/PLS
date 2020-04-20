#ifndef FIRESTORM_H
#define FIRESTORM_H

void __fastcall ContinueFireStorm(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueFireStorm.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueFireStorm.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueFireStorm.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueFireStorm[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueFireStorm(IPlayer);
				CancelBuff(5560);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{

					int nDmg = (GetMagic()*FStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*FStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*FStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*FStormIntMultiPvP;

					OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueFireStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckContinueFireStorm.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueFireStorm(IPlayer);
				CancelBuff(5560);
			}

			return;
		}
	}

	ResetContinueFireStorm(IPlayer);
	CancelBuff(5560);
	return;
}

void __fastcall FireStorm(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer((void*)pPlayer);
	ISkill xSkill((void*)pSkill);

	if (IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(5560, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(IPlayer, 48);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(230, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueFireStorm[GetPID()].PlayerSkillID = 48;
			CheckContinueFireStorm[GetPID()].PlayerTarget = (void*)check;
			CheckContinueFireStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueFireStorm[GetPID()].PlayerSkillCount = 8;
			CheckContinueFireStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueFireStorm(IPlayer);
	}
}





#endif