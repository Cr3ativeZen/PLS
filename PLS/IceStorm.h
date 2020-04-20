#ifndef ICESTORM_H
#define ICESTORM_H

void __fastcall ContinueIceStorm(ICharacter IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckContinueIceStorm.find(IPlayer.GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueIceStorm.find(IPlayer.GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueIceStorm.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillCount--;

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueIceStorm(IPlayer);
				IPlayer.CancelBuff(5559);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{

					int nDmg = (IPlayer.GetMagic()*IStormBaseDmgMultiPvE) + CChar::GetInt((int)IPlayer.GetOffset())*IStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetMagic()*IStormBaseDmgMultiPvP) + CChar::GetInt((int)IPlayer.GetOffset())*IStormIntMultiPvP;

					IPlayer.OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckContinueIceStorm.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueIceStorm(IPlayer);
				IPlayer.CancelBuff(5559);
			}

			return;
		}
	}

	ResetContinueIceStorm(IPlayer);
	IPlayer.CancelBuff(5559);
	return;
}

void __fastcall IceStorm(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer((void*)pPlayer);
	ISkill xSkill((void*)pSkill);

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

			IPlayer.Buff(5559, 16, 0);
			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 45);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(229, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillID = 45;
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerTarget = (void*)check;
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillCount = 8;
			CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
		}
		ContinueIceStorm(IPlayer);
	}
}





#endif