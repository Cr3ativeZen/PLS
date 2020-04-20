#ifndef CRITICALDIFFUSION_H
#define CRITICALDIFFUSION_H

void __fastcall CriticalDiffusion(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(92);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int Mana = 180 + static_cast<int>((1.25 * (nSkillGrade * (GetLevel() + nSkillGrade))));

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
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void *)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (CChar::GetRange((int)GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(388) && !IMembers.IsBuff(387) && !IMembers.IsBuff(386))
							{
								IMembers.SetBuffIcon(1000 * (5 + (nSkillGrade * 5)), 0, 4245, 953);
								IMembers.Buff(385 + nSkillGrade, 7 + (nSkillGrade * 5), 0);
								IMembers.Buff(389, 5 + (nSkillGrade * 5), 0);
								IMembers.IncreaseCritRate((nSkillGrade * 10) + 10);
								IMembers.IncreaseCritDamage((nSkillGrade * 10) + 10);
							}
						}
					}
				}
			}
			else {
				if (!IsBuff(388) && !IsBuff(387) && !IsBuff(386))
				{
					SetBuffIcon(1000 * (5 + (nSkillGrade * 5)), 0, 4245, 953);
					Buff(385 + nSkillGrade, 7 + (nSkillGrade * 5), 0);
					Buff(389, 5 + (nSkillGrade * 5), 0);
					IncreaseCritRate((nSkillGrade * 10) + 10);
					IncreaseCritDamage((nSkillGrade * 10) + 10);
				}
			}
		}
	}
}



#endif
