#ifndef ICESTORM_H
#define ICESTORM_H

void __fastcall ContinueIceStorm(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueIceStorm.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueIceStorm.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueIceStorm.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueIceStorm[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueIceStorm(IPlayer);
				CancelBuff(5559);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{

					int nDmg = (GetMagic()*IStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*IStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*IStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*IStormIntMultiPvP;

					OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueIceStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckContinueIceStorm.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueIceStorm(IPlayer);
				CancelBuff(5559);
			}

			return;
		}
	}

	ResetContinueIceStorm(IPlayer);
	CancelBuff(5559);
	return;
}

void __fastcall IceStorm(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer((void*)pPlayer);
	ISkill xSkill((void*)pSkill);

	if (IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
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

			Buff(5559, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(IPlayer, 45);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(229, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueIceStorm[GetPID()].PlayerSkillID = 45;
			CheckContinueIceStorm[GetPID()].PlayerTarget = (void*)check;
			CheckContinueIceStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueIceStorm[GetPID()].PlayerSkillCount = 8;
			CheckContinueIceStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueIceStorm(IPlayer);
	}
}





#endif