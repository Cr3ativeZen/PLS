#ifndef _LIGHTNINGSLASH_H
#define _LIGHTNINGSLASH_H
#include "ServerFunctions.h"

void __fastcall LightningSlash(int pSkill, void *pPlayer, int pPacket, int pPos)
{


	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
		return;

		ICharacter Target(pTarget);


		if (bType == 0)
		{

			if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
			{
				if (IPlayer.CheckHit(Target, 20))
				{
					int nDmg = (IPlayer.GetAttack()*LSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*LSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*LSStrMultiPvP) + (ISkill.GetGrade()*LSPerGradeMultiPvP);
					IPlayer.SetDirection(Target);
					IPlayer.OktayDamageSingle(Target, nDmg, 3);
					IPlayer._ShowBattleAnimation(Target, 3);
				}
				else
				{
					IPlayer._ShowBattleMiss(Target, 3);
				}
			}
		}
		if (bType == 1)
		{
			int Around = Target.GetObjectListAround(1);
			if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
			{
				if (IPlayer.CheckHit(Target, 20))
				{
					int nDmge = (IPlayer.GetAttack()*LSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*LSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*LSStrMultiPvE) + (ISkill.GetGrade()*LSPerGradeMultiPvE);
					IPlayer.SetDirection(Target);
					IPlayer.OktayDamageSingle(Target, nDmge, 3);
					IPlayer._ShowBattleAnimation(Target, 3);
				}
				else
				{
					IPlayer._ShowBattleMiss(Target, 3);
				}
			}
			int i = 0;
			while (Around&&i < LSPvEMaxHits - 1)
			{

				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.GetType() == 1 && Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
				{

					if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
					{

						if (IPlayer.CheckHit(Object, 20))
						{
							int nDmg = (IPlayer.GetAttack()*LSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*LSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*LSStrMultiPvE) + (ISkill.GetGrade()*LSPerGradeMultiPvE);
							IPlayer.OktayDamageSingle(Object, nDmg, 3);
							IPlayer._ShowBattleAnimation(Object, 3);
							i++;
						}
						else
						{
							IPlayer._ShowBattleMiss(Object, 3);
							i++;
						}
					}

				}
				Around = CBaseList::Pop((void*)Around);
			}
		}
		IPlayer.DecreaseMana(nMana);
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	
}
#endif