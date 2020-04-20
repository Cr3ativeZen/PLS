#ifndef THEWAVEOFEARTH_H
#define THEWAVEOFEARTH_H

void __fastcall ThewaveofEarth(ICharacter IPlayer)
{
	if (IsOnline())
	{
		int pSkill = GetSkillPointer(93);

		if (IsValid() && pSkill)
		{
			if (CPlayer::IsWState((int)GetOffset(), 12))
				return;

			ISkill xSkill((void*)pSkill);

			int nSkillGrade = xSkill.GetGrade();

			if (!nSkillGrade)
				return;

			int Mana = 180 + static_cast<int>((1.25 * (xSkill.GetGrade() * (GetLevel() + xSkill.GetGrade()))));

			if (GetCurMp() <= Mana)
				return;

			DecreaseMana(Mana);
			_ShowBattleAnimation(IPlayer, 93);

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

						OktayDamageArea(Object, nDmg, 93);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}
}

#endif
