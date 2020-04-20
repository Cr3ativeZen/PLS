#ifndef THUNDERBOLT_H
#define THUNDERBOLT_H
//void __fastcall ContinueThunderbolt(ICharacter IPlayer)
//{
//
//	if (IsValid())
//	{
//		int pSkill = GetSkillPointer(75);
//		ISkill xSkill((void*)pSkill);
//		void *pTarget = CheckContinueSkill.find(GetPID())->second.PlayerTarget;
//		ICharacter Target(pTarget);
//
//		if (!Target.IsValid())
//		{
//			ResetContinueSkill(IPlayer);
//
//			return;
//		}
//
//		if (CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
//		{
//			CheckContinueSkill[GetPID()].PlayerSkillCount--;
//
//			if (!IsInRange(Target, 30))
//			{
//				ResetContinueSkill(IPlayer);
//				return;
//			}
//
//			if (!IsValid() || !Target.IsValid())
//			{
//				ResetContinueSkill(IPlayer);
//				return;
//			}
//
//
//				int nDmg = (GetMagic()*TBoltMBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvE) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvE);
//
//				if (Target.GetType() == 0)
//					nDmg = (GetMagic()*TBoltMBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvP) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvP);
//
//				OktayDamageSingle(Target, nDmg, 75);
//				SetDirection(Target);
//			
//
//			if (IsOnline())
//				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 200;
//
//			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
//				ResetContinueSkill(IPlayer);
//
//			return;
//		}
//	}
//
//	ResetContinueSkill(IPlayer);
//	return;
//}

void __fastcall Thunderbolt(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(75);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 45) * xSkill.GetGrade()) + 280) * 0.75);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && xSkill.GetGrade() && IsValid())
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

			int nDmg = (GetMagic()*TBoltMBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvE) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvE);
			
				if (Target.GetType() == 0)
					nDmg = (GetMagic()*TBoltMBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvP) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvP);

				SetDirection(Target);

				for (int i = 0; i < 6; i++)
				{
					OktayDamageSingle(Target, nDmg+CTools::Rate(1,200), 75);
					Sleep(100);
				}
			
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif