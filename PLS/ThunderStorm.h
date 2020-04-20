#ifndef THUNDERSTORM_H
#define THUNDERSTORM_H

void __fastcall ContinueThunderStorm(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueThunderStorm.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueThunderStorm[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueThunderStorm(IPlayer);
				CancelBuff(5558);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					if (Object.IsBuff(307))
						StormActivateShiny(IPlayer, Object);


					int nDmg = (GetMagic()*TStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*TStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*TStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*TStormIntMultiPvP;

					OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueThunderStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueThunderStorm(IPlayer);
				CancelBuff(5558);
			}

			return;
		}
	}

	ResetContinueThunderStorm(IPlayer);
	CancelBuff(5558);
	return;
}

void __fastcall ThunderStorm(int pSkill, void *pPlayer, int pPacket, int pPos)
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

			Buff(5558, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(IPlayer, 43);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(228, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueThunderStorm[GetPID()].PlayerSkillID = 43;
			CheckContinueThunderStorm[GetPID()].PlayerTarget = (void*)check;
			CheckContinueThunderStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueThunderStorm[GetPID()].PlayerSkillCount = 8;
			CheckContinueThunderStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueThunderStorm(IPlayer);
	}
}
#endif