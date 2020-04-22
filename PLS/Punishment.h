//#ifndef PUNISHMENT_H
//#define PUNISHMENT_H
//void __fastcall Punishment(ICharacter IPlayer, int pPacket, int pPos)
//{
//	int pSkill = IPlayer.GetSkillPointer(90);
//
//	if (IPlayer.IsValid() && pSkill)
//	{
//		ISkill xSkill((void*)pSkill);
//		int nSkillGrade = xSkill.GetGrade();
//
//		if (!nSkillGrade)
//			return;
//
//
//		int nTargetID = 0; char bType = 0; void *pTarget = 0;
//		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
//		int nMana = (300 - (20 * (nSkillGrade - 1)));
//
//		if (bType == 0 && nTargetID)
//			pTarget = CPlayer::FindPlayer(nTargetID);
//
//		if (bType == 1 && nTargetID)
//			pTarget = CMonster::FindMonster(nTargetID);
//
//		if (bType >= 2)
//			return;
//
//		if (pTarget && nSkillGrade && IPlayer.IsValid())
//		{
//			if (IPlayer.GetCurMp() < nMana)
//				return;
//
//			if (pTarget == IPlayer.GetOffset())
//				return;
//
//			ICharacter Target(pTarget);
//
//			if (IPlayer.IsValid() && Target.IsValid())
//			{
//				if (!IPlayer.IsInRange(Target, 20))
//				{
//					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//					return;
//				}
//
//				int nDmg = 5000;
//
//				if (Target.GetType() == 0)
//					nDmg = 5000;
//				
//				
//				Target.AddFxToTarget("HellGate_FX40", 1, 0, 0);
//				IPlayer.AddFxToTarget("island_boss03", 1, 0, 0);
//				IPlayer.SetDirection(Target);
//				IPlayer.OktayDamageSingle(Target, nDmg, 90);
//				IPlayer.DecreaseMana(nMana);
//			}
//			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//		}
//	}
//}
//#endif