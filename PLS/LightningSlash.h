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


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

		ICharacter Target(pTarget);


		if (bType == 0)
		{

			if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
			{
				if (CheckHit(Target, 20))
				{
					int nDmg = (GetAttack()*LSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*LSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*LSStrMultiPvP) + (ISkill.GetGrade()*LSPerGradeMultiPvP);
					SetDirection(Target);
					OktayDamageSingle(Target, nDmg, 3);
					_ShowBattleAnimation(Target, 3);
				}
				else
				{
					_ShowBattleMiss(Target, 3);
				}
			}
		}
		if (bType == 1)
		{
			int Around = Target.GetObjectListAround(1);
			if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
			{
				if (CheckHit(Target, 20))
				{
					int nDmge = (GetAttack()*LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*LSStrMultiPvE) + (ISkill.GetGrade()*LSPerGradeMultiPvE);
					SetDirection(Target);
					OktayDamageSingle(Target, nDmge, 3);
					_ShowBattleAnimation(Target, 3);
				}
				else
				{
					_ShowBattleMiss(Target, 3);
				}
			}
			int i = 0;
			while (Around&&i < LSPvEMaxHits - 1)
			{

				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
				{

					if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
					{

						if (CheckHit(Object, 20))
						{
							int nDmg = (GetAttack()*LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*LSStrMultiPvE) + (ISkill.GetGrade()*LSPerGradeMultiPvE);
							OktayDamageSingle(Object, nDmg, 3);
							_ShowBattleAnimation(Object, 3);
							i++;
						}
						else
						{
							_ShowBattleMiss(Object, 3);
							i++;
						}
					}

				}
				Around = CBaseList::Pop((void*)Around);
			}
		}
		DecreaseMana(nMana);
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	
}
#endif