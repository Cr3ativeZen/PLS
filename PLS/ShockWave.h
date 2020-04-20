#ifndef _SHOCKWAVE_H
#define _SHOCKWAVE_H
#include "ServerFunctions.h"

void __fastcall ShockWave(int pSkill, void *pPlayer, int pPacket, int pPos)
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
			int nDmg = (IPlayer.GetMagic()*SWBaseDmgMultiPvP) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvP) + (ISkill.GetGrade()*SWPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg, 9);
			IPlayer.SetDirection(Target);
			IPlayer._ShowBattleAnimation(Target, 9);
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(2);
		if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			int nDmge = (IPlayer.GetMagic()*SWBaseDmgMultiPvE) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvE) + (ISkill.GetGrade()*SWPerGradeMultiPvE);
			IPlayer.OktayDamageSingle(Target, nDmge, 9);
			IPlayer.SetDirection(Target);
			IPlayer._ShowBattleAnimation(Target, 9);
		}

		int i = 0;

		while (Around &&i < SWPvEMaxHits - 1)
		{

			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{
					int nDmg = (IPlayer.GetMagic()*SWBaseDmgMultiPvE) + (CChar::GetWis((int)IPlayer.GetOffset())*SWWisMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*SWIntMultiPvE) + (ISkill.GetGrade()*SWPerGradeMultiPvE);
					IPlayer._ShowBattleAnimation(Object, 9);
					IPlayer.OktayDamageSingle(Object, nDmg, 9);
					i++;
				}

			}

			Around = CBaseList::Pop((void*)Around);
		}
	}
	IPlayer.DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}
#endif