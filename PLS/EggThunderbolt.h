#ifndef EGGTHUNDERBOLT_H
#define EGGTHUNDERBOLT_H
void __fastcall ContinueEggThunderbolt(ICharacter IPlayer)
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
				CancelBuff(5596);
				return;
			}

			int Around = Target.GetObjectListAround(2);


			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{


						int nDmg = (GetMagic() + GetAttack())*EggTBBaseDmgMultiPvE;


						if (Object.GetType() == 0)
							nDmg = (GetMagic() + GetAttack())*EggTBBaseDmgMultiPvP;



					OktayDamageArea(Object, nDmg, 116);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 900;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5596);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5596);
	return;
}

void __fastcall EggThunderbolt(ICharacter IPlayer)
{
	if (IsValid() && GetRage() >= 15000)
	{
		Buff(5596, 6, 0);
		DecreaseRage(15000);
		int *GetSetXY = new int[1];
		GetSetXY[0] = GetX();
		GetSetXY[1] = GetY();
		int check = CMonsterMagic::Create(568, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 8000);
		delete[] GetSetXY;
		CheckContinueSkill[GetPID()].PlayerSkillID = 116;
		CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
		CheckContinueSkill[GetPID()].PlayerX = GetX();
		CheckContinueSkill[GetPID()].PlayerY = GetY();
		CheckContinueSkill[GetPID()].PlayerSkillCount = 6;
		CheckContinueSkill[GetPID()].PlayerTarget = (void*)check;
		_ShowBattleAnimation(IPlayer, 116);
	}
}
#endif