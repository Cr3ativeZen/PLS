#ifndef WHIRLWINDFEATHER_H
#define WHIRLWINDFEATHER_H

void __fastcall ContinueWhirlwindFeather(ICharacter IPlayer)
{
	if (IsValid() && CChar::IsGState((int)GetOffset(), 512))
	{
		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;

		if (pTarget && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5595);
				return;
			}

			int Around = Target.GetObjectListAround(2);



			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && Target.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetMagic() + GetAttack())*WFBaseDmgMultiPvE;


					if (Object.GetType() == 0)
						nDmg = (GetMagic() + GetAttack())*WFBaseDmgMultiPvP;

					OktayDamageArea(Object, nDmg, 114);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 900;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5595);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5595);
	return;
}

void __fastcall WhirlwindFeather(ICharacter IPlayer)
{
	if (IsValid() && GetRage() >= 15000)
	{
		Buff(5595, 6, 0);
		DecreaseRage(15000);
		int GetSetXY[2];
		GetSetXY[0] = GetX();
		GetSetXY[1] = GetY();
		int check = CMonsterMagic::Create(568, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 8000);

		CheckContinueSkill[GetPID()].PlayerSkillID = 114;
		CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
		CheckContinueSkill[GetPID()].PlayerX = GetX();
		CheckContinueSkill[GetPID()].PlayerY = GetY();
		CheckContinueSkill[GetPID()].PlayerSkillCount = 6;
		CheckContinueSkill[GetPID()].PlayerTarget = (void*)check;
		_ShowBattleAnimation(IPlayer, 114);
	}
}
#endif