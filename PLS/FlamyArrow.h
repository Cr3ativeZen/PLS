#ifndef _FLAMYARROW_H
#define _FLAMYARROW_H
#include "ServerFunctions.h"

void __fastcall FlamyArrow(void *pSkill, void *pPlayer, int pPacket, int pPos)
{

	ISkill ISkill(pSkill);
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
	IPlayer.SetDirection(Target);
	//PvP
	if (pTarget && Target.IsValid() && IPlayer.IsValid() && nTargetID != IPlayer.GetID()&&bType==0)
	{
		if (IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 6))
			{
				int nDmge = (IPlayer.GetAttack()*FABaseDamageMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*FAAGiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*FAStrMultiPvP) + (ISkill.GetGrade()*FAPerGradeMultiPvP);
				Target.Buff(791, FADurationBase+ISkill.GetGrade()*FADurationPerGrade, (FADoTBasePvP+(ISkill.GetGrade()*FADoTPerGradePvP)));
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				IPlayer.OktayDamageSingle(Target, nDmge, 6);
				IPlayer._ShowBattleAnimation(Target, 6);
				IPlayer.DecreaseMana(nMana);

				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 6);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

		}
	}
	//PvE
	if (pTarget && Target.IsValid() && IPlayer.IsValid() && nTargetID != IPlayer.GetID() && bType == 1)
	{

		if (IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 6))
			{
				int nDmg = (IPlayer.GetAttack()*FABaseDamageMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*FAAGiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*FAStrMultiPvE) + (ISkill.GetGrade()*FAPerGradeMultiPvE);

				Target.Buff(29, FADurationBase + ISkill.GetGrade()*FADurationPerGrade, (FADoTBasePvE + (ISkill.GetGrade()*FADoTPerGradePvE)));
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				IPlayer.OktayDamageSingle(Target,nDmg , 6);
				IPlayer._ShowBattleAnimation(Target, 6);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 6);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

		}
	}
}
#endif