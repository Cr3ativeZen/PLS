#ifndef THUNDERSTORM_H
#define THUNDERSTORM_H

void __fastcall ContinueThunderStorm(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckContinueThunderStorm.find(IPlayer.GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueThunderStorm.find(IPlayer.GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueThunderStorm.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			IChar Target(pTarget);
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillCount--;

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueThunderStorm(IPlayer);
				IPlayer.CancelBuff(5558);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					if (Object.IsBuff(307))
						StormActivateShiny(IPlayer, Object);


					int nDmg = (IPlayer.GetMagic()*TStormBaseDmgMultiPvE) + CChar::GetInt((int)IPlayer.GetOffset())*TStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetMagic()*TStormBaseDmgMultiPvP) + CChar::GetInt((int)IPlayer.GetOffset())*TStormIntMultiPvP;

					IPlayer.OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckContinueThunderStorm.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueThunderStorm(IPlayer);
				IPlayer.CancelBuff(5558);
			}

			return;
		}
	}

	ResetContinueThunderStorm(IPlayer);
	IPlayer.CancelBuff(5558);
	return;
}

void __fastcall ThunderStorm(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(43);



	if (IPlayer.IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (IPlayer.GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana)
				return;

			IPlayer.Buff(5558, 16, 0);
			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 43);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(228, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillID = 43;
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerTarget = (void*)check;
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillCount = 8;
			CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
		}
		ContinueThunderStorm(IPlayer);
	}
}
#endif