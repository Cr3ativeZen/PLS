#ifndef THUNDERBOLT_H
#define THUNDERBOLT_H
//void __fastcall ContinueThunderbolt(IChar IPlayer)
//{
//
//	if (IPlayer.IsValid())
//	{
//		int pSkill = IPlayer.GetSkillPointer(75);
//		ISkill xSkill((void*)pSkill);
//		void *pTarget = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;
//		IChar Target(pTarget);
//
//		if (!Target.IsValid())
//		{
//			ResetContinueSkill(IPlayer);
//
//			return;
//		}
//
//		if (CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
//		{
//			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;
//
//			if (!IPlayer.IsInRange(Target, 30))
//			{
//				ResetContinueSkill(IPlayer);
//				return;
//			}
//
//			if (!IPlayer.IsValid() || !Target.IsValid())
//			{
//				ResetContinueSkill(IPlayer);
//				return;
//			}
//
//
//				int nDmg = (IPlayer.GetMagic()*TBoltMBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*TBoltMIntMultiPvE) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvE);
//
//				if (Target.GetType() == 0)
//					nDmg = (IPlayer.GetMagic()*TBoltMBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*TBoltMIntMultiPvP) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvP);
//
//				IPlayer.OktayDamageSingle(Target, nDmg, 75);
//				IPlayer.SetDirection(Target);
//			
//
//			if (IPlayer.IsOnline())
//				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 200;
//
//			if (IPlayer.IsOnline() && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
//				ResetContinueSkill(IPlayer);
//
//			return;
//		}
//	}
//
//	ResetContinueSkill(IPlayer);
//	return;
//}

void __fastcall Thunderbolt(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(75);

	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2)
			return;

		if (pTarget && xSkill.GetGrade() && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
				return;

			if (pTarget == IPlayer.GetOffset())
				return;

			int nDmg = (IPlayer.GetMagic()*TBoltMBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*TBoltMIntMultiPvE) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvE);
			
				if (Target.GetType() == 0)
					nDmg = (IPlayer.GetMagic()*TBoltMBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*TBoltMIntMultiPvP) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvP);

				IPlayer.SetDirection(Target);

				for (int i = 0; i < 6; i++)
				{
					IPlayer.OktayDamageSingle(Target, nDmg+CTools::Rate(1,200), 75);
					Sleep(100);
				}
			
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif