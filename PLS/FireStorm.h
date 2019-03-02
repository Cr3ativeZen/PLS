#ifndef FIRESTORM_H
#define FIRESTORM_H

void __fastcall ContinueFireStorm(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckContinueFireStorm.find(IPlayer.GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueFireStorm.find(IPlayer.GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && CheckContinueFireStorm.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			IChar Target(pTarget);
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillCount--;

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueFireStorm(IPlayer);
				IPlayer.CancelBuff(5560);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{

					int nDmg = (IPlayer.GetAttack()*FStormBaseDmgMultiPvE) + CChar::GetInt((int)IPlayer.GetOffset())*FStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*FStormBaseDmgMultiPvP) + CChar::GetInt((int)IPlayer.GetOffset())*FStormIntMultiPvP;

					IPlayer.OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckContinueFireStorm.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueFireStorm(IPlayer);
				IPlayer.CancelBuff(5560);
			}

			return;
		}
	}

	ResetContinueFireStorm(IPlayer);
	IPlayer.CancelBuff(5560);
	return;
}

void __fastcall FireStorm(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(48);

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

			IPlayer.Buff(5560, 16, 0);
			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 48);
			int *GetSetXY = new int[1];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(230, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 16000);
			delete[] GetSetXY;
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillID = 48;
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerTarget = (void*)check;
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillCount = 8;
			CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
		}
		ContinueFireStorm(IPlayer);
	}
}





#endif