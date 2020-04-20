#ifndef SPINSLASH_H
#define SPINSLASH_H
#include "ServerFunctions.h"
void __fastcall SpinSlash(ICharacter IPlayer)
{
	int pSkill = GetSkillPointer(38);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = (xSkill.GetGrade() == 1) ? 209 : (200 + (xSkill.GetGrade() * 20));
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		if (GetCurMp() < nMana)
			return;

		if (IsValid() && CPlayer::IsWState((int)GetOffset(), 12))
		{
			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = static_cast<int>(((GetAttack()*SSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SSStrMultiPvE) + (xSkill.GetGrade()*SSPerGradeMultiPvE))*(0.5+(GetDeathBlow()*0.1)));

					if (IsBuff(69) && Object.GetType() == 1)
					{
						nDmg = nDmg + SSAdditonalDMG;
					}
				

					if (Object.GetType() == 0)
						nDmg = static_cast<int>((GetAttack()*SSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SSStrMultiPvP) + (xSkill.GetGrade()*SSPerGradeMultiPvP)*(0.5 + (GetDeathBlow()*0.1)));


					OktayDamageArea(Object, nDmg, 38);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			_ShowBattleAnimation(IPlayer, 38);
			RemoveDeathBlow(GetDeathBlow());
			DecreaseMana(nMana);
		}
	}
}
#endif