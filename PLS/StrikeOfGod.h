#ifndef STRIKEOFGOD_H
#define STRIKEOFGOD_H

void __fastcall StrikeOfGod(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = static_cast<int>(180 + (1.25 * (xSkill.GetGrade() * (IPlayer.GetLevel() + xSkill.GetGrade()))));

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (IPlayer.IsValid())
		{
			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = 5000;

					if (Object.GetType() == 0)
						nDmg = 5000;

					IPlayer.OktayDamageArea(Object, nDmg, 91);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 91);
			IPlayer.DecreaseMana(nMana);
		}
	}
}

#endif