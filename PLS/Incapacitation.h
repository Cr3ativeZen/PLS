#ifndef INCAPACITATION_H
#define INCAPACITATION_H

void __fastcall Incapacitation(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(91);

	if (pSkill && IsValid())
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int Mana = static_cast<int>((1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1))))));

		if (GetCurMp() < Mana)
			return;
		else
			DecreaseMana(Mana);

		if (IsValid() && nSkillGrade)
		{
			_ShowBattleAnimation(IPlayer, 91);
			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					if (!Object.IsBuff(395) && Object.GetDef() >= 140)
					{
						Object.Buff(395, 8 + (xSkill.GetGrade() * 2), 0);
						Object.Buff(391 + xSkill.GetGrade(), 15 + (xSkill.GetGrade() * 2), 0);
						Object.RemoveDef(80 + (xSkill.GetGrade() * 20));

						if (Object.GetType() == 0)
							Object.SetBuffIcon(8000 + (2000 * xSkill.GetGrade()), 0, 4242, 950);
					}
				}

				Around = CBaseList::Pop((void*)Around);
			}
		}
	}
}
#endif