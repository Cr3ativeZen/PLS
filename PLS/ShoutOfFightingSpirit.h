#ifndef SHOUTOFFIGHTINGSPIRIT_H
#define SHOUTOFFIGHTINGSPIRIT_H
void __fastcall ShoutOfFightingSpirit(ICharacter IPlayer)
{
	if (IsOnline())
	{
		int pSkill = GetSkillPointer(92);

		if (IsValid() && pSkill)
		{
			ISkill xSkill((void*)pSkill);

			int nSkillGrade = xSkill.GetGrade();

			if (!nSkillGrade)
				return;

			int Mana = 180 + static_cast<int>((1.25 * (xSkill.GetGrade() * (GetLevel() + xSkill.GetGrade()))));

			if (GetCurMp() <= Mana)
				return;

			DecreaseMana(Mana);
			_ShowBattleAnimation(IPlayer, 92);

			if (IsValid())
			{
				if (IsParty())
				{
					void *Party = (void *)CParty::FindParty(GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							ICharacter IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IsValid())
							{
								if (CChar::GetRange((int)GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(383) && !IMembers.IsBuff(382) && !IMembers.IsBuff(381))
								{
									IMembers.SetBuffIcon(1000 * (4 + (xSkill.GetGrade() * 3)), 0, 4243, 951);
									IMembers.Buff(380 + xSkill.GetGrade(), 6 + (xSkill.GetGrade() * 3), 0);
									IMembers.Buff(384, 4 + (xSkill.GetGrade() * 3), 0);
									IMembers.AddMaxAttack(xSkill.GetGrade() * 200);
									IMembers.AddMinAttack(xSkill.GetGrade() * 200);
								}
							}
						}
					}
				}
				else {
					if (!IsBuff(383) && !IsBuff(382) && !IsBuff(381))
					{
						AddFxToTarget("fire_flower_01", 1, 0, 0);

						AddFxToTarget("fire_flower_02", 1, 0, 0);

						AddFxToTarget("fire_flower_03", 1, 0, 0);

						SetBuffIcon(1000 * (4 + (xSkill.GetGrade() * 3)), 0, 4243, 951);
						Buff(380 + xSkill.GetGrade(), 6 + (xSkill.GetGrade() * 3), 0);
						Buff(384, 4 + (xSkill.GetGrade() * 3), 0);
						AddMaxAttack(xSkill.GetGrade() * 200);
						AddMinAttack(xSkill.GetGrade() * 200);
					}
				}
			}
		}
	}
}

#endif