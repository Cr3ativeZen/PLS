#ifndef LIGHTNINGSLASHTHIEF_H
#define LIGHTNINGSLASHTHIEF_H
#include "ServerFunctions.h"
void __fastcall ContinueLightningSlash(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			IChar Target(pTarget);
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

			if(IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 2))
				{
					ResetContinueSkill(IPlayer);
					IPlayer.CancelBuff(5579);
					return;
				}

				if (IPlayer.IsMoved(CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerX, CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerY))
				{
					ResetContinueSkill(IPlayer);
					IPlayer.CancelBuff(5579);
					return;
				}

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack()*LSTBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*LSTAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*LSTStrMultiPvE) + (nSkillGrade*LSTPerGradeMultiPvE);


					if (Target.GetType() == 0)
						nDmg = (IPlayer.GetAttack()*LSTBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*LSTAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*LSTStrMultiPvP) + (nSkillGrade*LSTPerGradeMultiPvP);


					IPlayer.OktayDamageSingle(Target,nDmg,28);
				}

				if (IPlayer.IsOnline())
					CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 800;

				if (IPlayer.IsOnline() && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
				{
					ResetContinueSkill(IPlayer);
					IPlayer.CancelBuff(5579);
				}

				return;
			}
		}
	}

	ResetContinueSkill(IPlayer);
	IPlayer.CancelBuff(5579);
	return;
}

void __fastcall LightningSlashThief(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(28);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (nSkillGrade + IPlayer.GetLevel()) * 3 + 50;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if(bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
				return;

			if (pTarget == IPlayer.GetOffset())
				return;

			if(IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target,300))
					return;

				IPlayer.Buff(5579, xSkill.GetGrade() + 2, 0);
				IPlayer.DecreaseMana(nMana);
				CheckContinueSkill[IPlayer.GetPID()].PlayerX = IPlayer.GetX();
				CheckContinueSkill[IPlayer.GetPID()].PlayerY = IPlayer.GetY();
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 28;
				CheckContinueSkill[IPlayer.GetPID()].PlayerTarget = Target.GetOffset();
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = xSkill.GetGrade()+1;
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueLightningSlash(IPlayer);
	}
}
#endif