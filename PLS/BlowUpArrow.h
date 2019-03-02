#ifndef _BLOWUPARROW_H
#define _BLOWUPARROW_H
#include "ServerFunctions.h"

void __fastcall BlowUpArrow(int pSkill, void *pPlayer, int pPacket, int pPos)
{

	int i = 0;
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
	pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
	pTarget = CMonster::FindMonster(nTargetID);
	

	if (bType >= 2)
		return;

	IChar Target(pTarget);


	if (bType == 0 && nTargetID)
	{
		

		if (IPlayer.CheckHit(Target, 14))
		{
			int nDmg = (IPlayer.GetAttack()*BlowUpBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*BlowUpAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*BlowUpStrMultiPvP) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg, 14);
			IPlayer._ShowBattleAnimation(Target, 14);
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 14);
			IPlayer.DecreaseMana(nMana);
		}
	}
	if (bType == 1 && nTargetID)
	{
		int Around = Target.GetObjectListAround(3);
		IPlayer.SetDirection(Target);
		if (IPlayer.CheckHit(Target, 14))
		{
			int nDmge = (IPlayer.GetAttack()*BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*BlowUpAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*BlowUpStrMultiPvE) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvE);


			IPlayer.OktayDamageSingle(Target, nDmge, 14);
			IPlayer._ShowBattleAnimation(Target, 14);
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 14);
		}
		while (Around&&i< BlowUpPvEMaxHits-1)
		{
			
			IChar Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 )
			{
				if (IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
				{
					if (Object.GetOffset() != Target.GetOffset()&&CChar::IsNormal((int)Object.GetOffset()))
					{

						if (IPlayer.CheckHit(Object, 14))
						{
							int nDmg = (IPlayer.GetAttack()*BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*BlowUpAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*BlowUpStrMultiPvE) + (ISkill.GetGrade()*BlowUpPerGradeMultiPvE);


							IPlayer.OktayDamageSingle(Object, nDmg, 14);
							IPlayer._ShowBattleAnimation(Object, 14);
							i++;
						}
						else
						{
							IPlayer._ShowBattleMiss(Object, 14);
							i++;
						}
					}
				}
			}

			Around = CBaseList::Pop((void*)Around);
		}
		IPlayer.DecreaseMana(nMana);
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif