#ifndef LIGHTNINGSLASHTHIEF_H
#define LIGHTNINGSLASHTHIEF_H
#include "ServerFunctions.h"
void __fastcall ContinueLightningSlash(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if(IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 2))
				{
					ResetContinueSkill(IPlayer);
					CancelBuff(5579);
					return;
				}

				if (IsMoved(CheckContinueSkill.find(GetPID())->second.PlayerX, CheckContinueSkill.find(GetPID())->second.PlayerY))
				{
					ResetContinueSkill(IPlayer);
					CancelBuff(5579);
					return;
				}

					int nDmg = (GetAttack()*LSTBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*LSTAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*LSTStrMultiPvE) + (nSkillGrade*LSTPerGradeMultiPvE);


					if (Target.GetType() == 0)
						nDmg = (GetAttack()*LSTBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*LSTAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*LSTStrMultiPvP) + (nSkillGrade*LSTPerGradeMultiPvP);


					OktayDamageSingle(Target,nDmg,28);


				if (IsOnline())
					CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 800;

				if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
				{
					ResetContinueSkill(IPlayer);
					CancelBuff(5579);
				}

				return;
			}
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5579);
	return;
}

void __fastcall LightningSlashThief(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(28);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (nSkillGrade + GetLevel()) * 3 + 50;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			ICharacter Target(pTarget);

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if(IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target,300))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				Buff(5579, xSkill.GetGrade() + 2, 0);
				DecreaseMana(nMana);
				CheckContinueSkill[GetPID()].PlayerX = GetX();
				CheckContinueSkill[GetPID()].PlayerY = GetY();
				CheckContinueSkill[GetPID()].PlayerSkillID = 28;
				CheckContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
				CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				CheckContinueSkill[GetPID()].PlayerSkillCount = xSkill.GetGrade()+1;
				CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueLightningSlash(IPlayer);
	}
}
#endif