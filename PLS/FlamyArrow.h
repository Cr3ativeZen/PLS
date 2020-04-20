#ifndef _FLAMYARROW_H
#define _FLAMYARROW_H
#include "ServerFunctions.h"

void __fastcall FlamyArrow(int pSkill, void *pPlayer, int pPacket, int pPos)
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

	//PvP
	if (bType==0)
	{
		if (IsValid() &&Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmge = (GetAttack()*FABaseDamageMultiPvP) + (CChar::GetDex((int)GetOffset())*FAAGiMultiPvP) + (CChar::GetStr((int)GetOffset())*FAStrMultiPvP) + (ISkill.GetGrade()*FAPerGradeMultiPvP);
				Target.Buff(791, FADurationBase+ISkill.GetGrade()*FADurationPerGrade, (FADoTBasePvP+(ISkill.GetGrade()*FADoTPerGradePvP)));
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				OktayDamageSingle(Target, nDmge, 6);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 6);
			}
			else
			{
				_ShowBattleMiss(Target, 6);
			}

		}
	}
	//PvE
	if (bType == 1)
	{

		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmg = (GetAttack()*FABaseDamageMultiPvE) + (CChar::GetDex((int)GetOffset())*FAAGiMultiPvE) + (CChar::GetStr((int)GetOffset())*FAStrMultiPvE) + (ISkill.GetGrade()*FAPerGradeMultiPvE);
				Target.Buff(29, FADurationBase + ISkill.GetGrade()*FADurationPerGrade, (FADoTBasePvE + (ISkill.GetGrade()*FADoTPerGradePvE)));
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				OktayDamageSingle(Target,nDmg , 6);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 6);
			}
			else
			{
				_ShowBattleMiss(Target, 6);
			}

		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif