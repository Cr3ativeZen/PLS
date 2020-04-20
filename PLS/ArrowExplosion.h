#ifndef ARROWEXPLOSION_H
#define ARROWEXPLOSION_H
#include "ServerFunctions.h"
void __fastcall ContinueArrowExplosion(ICharacter IPlayer)
{
	if (IsValid())
	{
		CancelBuff(300);
		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;
		int nSkillGrade = CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && pTarget && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[GetPID()].PlayerSkillCount--;
			ICharacter Target(pTarget);

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target,300))
				{
					ResetContinueSkill(IPlayer);
					CancelBuff(5566);
					return;
				}

				int Around = Target.GetObjectListAround(3);
				Target.AddFxToTarget("davi_ef131_05", 1, 0, 0);
				while(Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (GetAttack()*AEBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*AEAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*AEStrMultiPvE) + (nSkillGrade*AEPerGradeMultiPvE);


						if (Object.GetType() == 0)
							nDmg = (GetAttack()*AEBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*AEAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*AEStrMultiPvP) + (nSkillGrade*AEPerGradeMultiPvP);


						OktayDamageArea(Object,nDmg,49);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5566);
	return;
}

void __fastcall ArrowExplosion(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(49);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 20 + (GetLevel() * 4);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (IsValid() && pTarget && nSkillGrade)
		{
			ICharacter Target(pTarget);

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target,300))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				DecreaseMana(nMana);
				SetDirection(Target);
				_ShowBattleAnimation(Target,49);
				Buff(300,5,0);
				Buff(5566, 4, 0);
				Target.AddFxToTarget("davi_ef131_04",1,0,0);
				CheckContinueSkill[GetPID()].PlayerSkillID = 49;
				CheckContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
				CheckContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
				CheckContinueSkill[GetPID()].PlayerSkillCount = 1;
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount64() + 3000;

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() && Target.GetMobTanker() != (int)GetOffset())
					Target.SetMobHostility(0);

				if (Target.GetType() == 1)
					OktayDamageSingle(Target,CTools::Rate(500,750),42);


				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() == (int)GetOffset())
					Target.SetMobHostility(25000);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}

}
#endif