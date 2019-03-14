#ifndef _LIGHTNINGSLASH_H
#define _LIGHTNINGSLASH_H
#include "ServerFunctions.h"

void __fastcall LightningSlash(IChar IPlayer,int pPacket, int pPos)
{

	int i = 0;
	ISkill ISkill((void*)IPlayer.GetSkillPointer(3));
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


	if (bType >= 2)
		return;

	IChar Target(pTarget);


	if (bType == 0 && nTargetID)
	{


		if (IPlayer.CheckHit(Target, 3))
		{
			int nDmg = (IPlayer.GetAttack()*LSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*LSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*LSStrMultiPvP) + (ISkill.GetGrade()*LSPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg, 3);
			IPlayer._ShowBattleAnimation(Target, 3);
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 3);
			IPlayer.DecreaseMana(nMana);
		}
	}
	if (bType == 1 && nTargetID)
	{
		int Around = Target.GetObjectListAround(1);
		IPlayer.SetDirection(Target);
		if (IPlayer.CheckHit(Target, 3))
		{
			int nDmge = (IPlayer.GetAttack()*LSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*LSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*LSStrMultiPvE) + (ISkill.GetGrade()*LSPerGradeMultiPvE);


			IPlayer.OktayDamageSingle(Target, nDmge, 3);
			IPlayer._ShowBattleAnimation(Target, 3);
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 3);
		}
		while (Around&&i < LSPvEMaxHits - 1)
		{

			IChar Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1)
			{
				if (IPlayer.IsValid())
				{
					if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
					{

						if (IPlayer.CheckHit(Object, 3))
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
			}

			Around = CBaseList::Pop((void*)Around);
		}
		IPlayer.DecreaseMana(nMana);
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif