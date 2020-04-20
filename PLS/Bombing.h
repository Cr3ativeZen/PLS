#ifndef BOMBING_H
#define BOMBING_H
void __fastcall Bombing(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(93);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;


		if (IsValid() && nSkillGrade)
		{
			int nMana = 180 + static_cast<int>(1.25 * (nSkillGrade * (GetLevel() + nSkillGrade)));

			if (GetCurMp() < nMana)
				return;

			int Around = GetObjectListAround(3);

			AddFxToTarget("MonTargetHit_023", 1, 0, 0);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					Object.AddFxToTarget("HellGate_FX47", 1, 0, 0);
					int nDmg = 5000;

					if (Object.GetType() == 0)
						nDmg = 5000;

					OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			DecreaseMana(nMana);
			_ShowBattleAnimation(IPlayer, 93);
		}
	}
}
#endif