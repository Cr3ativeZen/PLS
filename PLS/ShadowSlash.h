#ifndef SHADOWSLASH_H
#define SHADOWSLASH_H
#include "ServerFunctions.h"
void __fastcall ShadowSlash(ICharacter IPlayer, int pPacket, int pPos)
{


	int pSkill = IPlayer.GetSkillPointer(32);


		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = static_cast<int>(230 + (((IPlayer.GetLevel() + nSkillGrade) * nSkillGrade) * 0.63));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
			return;
		
		if (pTarget && IPlayer.IsValid() && nSkillGrade)
		{
			ICharacter Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == IPlayer.GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{

				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (/*Object.IsValid() && IPlayer.IsValid() && Target.IsValid() &&*/ (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{

						Object.Buff(7, SHSStunDuration + nSkillGrade * SHSStunDurationPerGrade, 0);
						int nDmg = (IPlayer.GetAttack()*SHSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*SHSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*SHSStrMultiPvE) + (nSkillGrade*SHSPerGradeMultiPvE);
						if (Object.GetType() == 0)
							nDmg = (IPlayer.GetAttack()*SHSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*SHSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*SHSStrMultiPvP) + (nSkillGrade*SHSPerGradeMultiPvP);

						IPlayer.OktayDamageArea(Object, nDmg, 32);

					}

					Around = CBaseList::Pop((void*)Around);
				}
			}

			IPlayer.SetDirection(Target);
			IPlayer._ShowBattleAnimation(Target, 32);
			IPlayer.DecreaseMana(nMana);

			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
}
#endif