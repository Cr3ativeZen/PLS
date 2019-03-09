
int __fastcall FinalDamage(void *Target, void *edx, int Player, int Damage, int Argument)
{
	IChar IPlayer((void*)Player);
	IChar ITarget(Target);
	int CheckDamage = CChar::GetFinalDamage(Target, Player, Damage, Argument);

	if (IPlayer.IsValid() && IPlayer.GetType() == 0)
		IPlayer.Buff(313, 3, 0);

	if (ITarget.IsValid() && ITarget.GetType() == 0)
		ITarget.Buff(313, 3, 0);


	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 0 &&IPlayer.IsBuff(LawlessZone::BuffID)&& ITarget.IsBuff(LawlessZone::BuffID) &&IPlayer.GetPartyID()==ITarget.GetPartyID()&&IPlayer.IsParty()&&ITarget.IsParty())
	{
		IPlayer.SystemMessage("You cannot attack your party members at Lawless Zone!", TEXTCOLOR_RED);
		return 0;
	}

	if (ITarget.IsValid() && CheckDamage > 100 && ITarget.IsBuff(342) && ArmorBreakerON == true)
		CheckDamage += (CheckDamage * ABreakerAdditionalDamage) / 100;

	if (ITarget.IsValid() && ITarget.GetType() == 0 && ITarget.GetClass() == 3 && CheckDamage &&CounterOffensiveON == true)
	{
		if (ITarget.IsBuff(4877))
		{
			int pSkill = ITarget.GetSkillPointer(63);
			ISkill xSkill((void*)pSkill);
			int nSkillGrade = xSkill.GetGrade();

			if (pSkill && ITarget.IsValid() && IPlayer.IsValid() && GetTickCount() >= CODelay.find(ITarget.GetPID())->second && (int)CTools::Rate(1, 1000) <= (COChanceToPopBase + (COChanceToPopPerGrade*nSkillGrade)) * 10)
			{
				int Around = IPlayer.GetObjectListAround(3);
				int nDmg = CheckDamage * (CODamageMultiPvE / 100) + COBaseDamagePvE;

				while (Around)
				{
					IChar Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && ITarget.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)ITarget.GetOffset() + 176))((int)ITarget.GetOffset(), (int)Object.GetOffset(), 0))
					{
						if (Object.GetType() == 0)
							nDmg = CheckDamage * (CODamageMultiPvP / 100) + COBaseDamagePvP;

						ITarget.OktayDamageNoAgro(Object, nDmg, 63);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				CODelay[ITarget.GetPID()] = GetTickCount() + 300;
				ITarget._ShowBattleAnimation(IPlayer, 63);
			}
		}
	}
		if (ITarget.IsValid() && ITarget.GetType() == 0 && ITarget.GetClass() == 3 && CheckDamage && ITarget.IsBuff(4848) && CounterAttackON==true)
		{
			int pSkill = ITarget.GetSkillPointer(20);
			ISkill xSkill((void*)pSkill);
			int nSkillGrade = xSkill.GetGrade();

			if (pSkill && ITarget.IsValid() && IPlayer.IsValid() && (int)CTools::Rate(1, 1000) <= (CAChanceToPopBase + (CAChanceToPopPerGrade*nSkillGrade)) * 10)
			{
				if (IPlayer.GetCurHp() > 1)
				{

					int nDmg = CheckDamage * (CADamageMultiPvE / 100) + CABaseDamagePvE;

					if (IPlayer.GetType() == 0)
						nDmg = CheckDamage * (CADamageMultiPvP / 100) + CABaseDamagePvP;

					ITarget.OktayDamageNoAgro(IPlayer, nDmg, 20);
					ITarget._ShowBattleAnimation(IPlayer, 20);

				}
			}
		}


	
	return CheckDamage;
}