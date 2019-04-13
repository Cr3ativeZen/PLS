#ifndef SPINSLASH_H
#define SPINSLASH_H
#include "ServerFunctions.h"
void __fastcall SpinSlash(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(38);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = (xSkill.GetGrade() == 1) ? 209 : (200 + (xSkill.GetGrade() * 20));
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (IPlayer.IsValid() && CPlayer::IsWState((int)IPlayer.GetOffset(), 12))
		{
			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = static_cast<int>(((IPlayer.GetAttack()*SSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*SSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*SSStrMultiPvE) + (xSkill.GetGrade()*SSPerGradeMultiPvE))*(0.5+(IPlayer.GetDeathBlow()*0.1)));

					if (IPlayer.IsBuff(69) && Object.GetType() == 1)
					{
						nDmg = nDmg +(nDmg*( SSMultiWhenZerk/100));
					}
				

					if (Object.GetType() == 0)
						nDmg = static_cast<int>((IPlayer.GetAttack()*SSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*SSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*SSStrMultiPvP) + (xSkill.GetGrade()*SSPerGradeMultiPvP)*(0.5 + (IPlayer.GetDeathBlow()*0.1)));


					IPlayer.OktayDamageArea(Object, nDmg, 38);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 38);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
			IPlayer.DecreaseMana(nMana);
		}
	}
}
#endif