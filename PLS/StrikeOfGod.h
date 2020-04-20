#ifndef STRIKEOFGOD_H
#define STRIKEOFGOD_H

void __fastcall StrikeOfGod(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(91);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = static_cast<int>(180 + (1.25 * (xSkill.GetGrade() * (GetLevel() + xSkill.GetGrade()))));

		if (GetCurMp() < nMana)
			return;

		if (IsValid())
		{
			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = 5000;

					if (Object.GetType() == 0)
						nDmg = 5000;

					OktayDamageArea(Object, nDmg, 91);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			_ShowBattleAnimation(IPlayer, 91);
			DecreaseMana(nMana);
		}
	}
}

#endif