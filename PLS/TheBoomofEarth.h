#ifndef THEBOOMOFEARTH_H
#define THEBOOMOFEARTH_H

void __fastcall TheBoomOfEarth(ICharacter IPlayer)
{
	if (IsOnline())
	{
		int pSkill = GetSkillPointer(91);

		if (pSkill && IsValid())
		{
			if (CPlayer::IsWState((int)GetOffset(), 12))
				return;

			ISkill xSkill((void*)pSkill);
			int Mana = 200 + (xSkill.GetGrade() * (20 + (xSkill.GetGrade() - 1)));

			int nSkillGrade = xSkill.GetGrade();

			if (!nSkillGrade)
				return;

			if (GetCurMp() <= Mana)
				return;

			DecreaseMana(Mana);
			_ShowBattleAnimation(IPlayer, 91);

			if (IsValid())
			{
				int Around = GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
						Object.Buff(7, 2 * xSkill.GetGrade(), 0);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}
}
#endif