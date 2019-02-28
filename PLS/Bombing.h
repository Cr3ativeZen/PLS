#ifndef BOMBING_H
#define BOMBING_H
void __fastcall Bombing(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(93);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (IPlayer.IsValid() && nSkillGrade)
		{
			int nMana = 180 + static_cast<int>((1.25 * (nSkillGrade * (IPlayer.GetLevel() + nSkillGrade))));

			if (IPlayer.GetCurMp() < nMana)
				return;

			int Around = IPlayer.GetObjectListAround(3);

			IPlayer.AddFxToTarget("MonTargetHit_023", 1, 0, 0);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					Object.AddFxToTarget("HellGate_FX47", 1, 0, 0);
					int nDmg = 5000;

					if (Object.GetType() == 0)
						nDmg = 5000;

					IPlayer.OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 93);
		}
	}
}
#endif