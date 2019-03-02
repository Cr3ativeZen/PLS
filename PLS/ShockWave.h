#ifndef _SHOCKWAVE_H
#define _SHOCKWAVE_H
#include "ServerFunctions.h"

void __fastcall ShockWave(IChar IPlayer,int pPacket, int pPos)
{

	int i = 0;
	ISkill ISkill((void*)IPlayer.GetSkillPointer(9));
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

			int nDmg = (IPlayer.GetAttack()*SWBaseDmgMultiPvP) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvP) + (ISkill.GetGrade()*SWPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg,9);
			IPlayer._ShowBattleAnimation(Target, 9);
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;
	}
	if (bType == 1 && nTargetID)
	{
		int Around = Target.GetObjectListAround(2);
		IPlayer.SetDirection(Target);
		int nDmge = (IPlayer.GetAttack()*SWBaseDmgMultiPvE) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvE) + (ISkill.GetGrade()*SWPerGradeMultiPvE);
		IPlayer.OktayDamageSingle(Target, nDmge, 9);
		IPlayer._ShowBattleAnimation(Target, 9);
		while (Around &&i < SWPvEMaxHits - 1)
		{

			IChar Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1)
			{
				if (IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
				{
					if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
					{
						int nDmg = (IPlayer.GetAttack()*SWBaseDmgMultiPvE) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvE) + (ISkill.GetGrade()*SWPerGradeMultiPvE);
						IPlayer.OktayDamageSingle(Object, nDmg, 9);
						IPlayer._ShowBattleAnimation(Object, 9);
						i++;
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