#ifndef _TRANSCENDENTALBLOW_H
#define _TRANSCENDENTALBLOW_H
#include "ServerFunctions.h"

void __fastcall TranscendentalBlow(IChar IPlayer,int pPacket, int pPos)
{

	ISkill ISkill((void*)IPlayer.GetSkillPointer(5));
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

	IChar Target(pTarget);


	if (bType == 0)
	{

		if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 5))
			{
				int nDmg = (IPlayer.GetAttack()*TBBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*TBAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*TBStrMultiPvP) + (ISkill.GetGrade()*TBPerGradeMultiPvP);
				IPlayer.OktayDamageSingle(Target, nDmg, 5);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 5);
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 5);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(1);
		if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 5))
			{
				int nDmge = (IPlayer.GetAttack()*TBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*TBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*TBStrMultiPvE) + (ISkill.GetGrade()*TBPerGradeMultiPvE);
				IPlayer.OktayDamageSingle(Target, nDmge, 5);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 5);
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 5);
			}
		}
		int i = 0;
		while (Around&&i < TBPvEMaxHits - 1)
		{
			IChar Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (IPlayer.CheckHit(Object, 5))
					{
						int nDmg = (IPlayer.GetAttack()*TBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*TBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*TBStrMultiPvE) + (ISkill.GetGrade()*TBPerGradeMultiPvE);
						IPlayer.OktayDamageSingle(Object, nDmg, 5);
						IPlayer._ShowBattleAnimation(Object, 5);
						i++;
					}
					else
					{
						IPlayer._ShowBattleMiss(Object, 5);
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