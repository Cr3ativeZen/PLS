//#ifndef POWERFULWIDENINGWOUND_H
//#define POWERFULWIDENINGWOUND_H
//
//void __fastcall PowerfulWideningWound(ICharacter IPlayer, int pPacket, int pPos)
//{
//	int pSkill = IPlayer.GetSkillPointer(41);
//
//	if (IPlayer.IsValid() && pSkill)
//	{
//		ISkill xSkill((void*)pSkill);
//		int nTargetID = 0; char bType = 0; void *pTarget = 0;
//		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
//		int nMana = xSkill.GetGrade() + 30;
//
//		if (bType == 0 && nTargetID)
//			pTarget = CPlayer::FindPlayer(nTargetID);
//
//		if (bType == 1 && nTargetID)
//			pTarget = CMonster::FindMonster(nTargetID);
//
//		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
//			return;
//
//		ICharacter Target(pTarget);
//
//		if (!IPlayer.IsInRange(Target, 20))
//		{
//			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//			return;
//		}
//
//		if (pTarget && xSkill.GetGrade() && IPlayer.IsValid())
//		{
//			if (IPlayer.GetCurMp() < nMana)
//			{
//				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//				return;
//			}
//
//			if (pTarget == IPlayer.GetOffset())
//			{
//				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//				return;
//			}
//
//			if (IPlayer.IsValid() && Target.IsValid())
//			{
//				if (!IPlayer.IsInRange(Target, 20))
//				{
//					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//					return;
//				}
//
//				if (IPlayer.CheckHit(Target, 10 + ((IPlayer.GetLevel() / 20) + xSkill.GetGrade() * 3)))
//				{
//					int nDmg = (IPlayer.GetAttack()*PWWBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*PWWAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*PWWStrMultiPvE) + (xSkill.GetGrade()*PWWPerGradeMultiPvE);
//
//					if (Target.GetType() == 0)
//						nDmg = (IPlayer.GetAttack()*PWWBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*PWWAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*PWWStrMultiPvP) + (xSkill.GetGrade()*PWWPerGradeMultiPvP);
//
//
//					IPlayer.OktayDamageSingle(Target, nDmg, 41);
//
//					if (IPlayer.IsOnline() && IPlayer.IsValid() && Target.IsOnline() && Target.IsValid() && Target.GetType() == 1 && Target.GetCurHp() > 0 && Target.IsMobAggressive() && Target.IsMobHaveTarget())
//						CMonsterReal::AddHostility(Target.GetOffset(), (int)IPlayer.GetOffset(), nDmg * PWWHostilityMultiplier, 0);
//				}
//				else 
//				{
//					IPlayer._ShowBattleMiss(Target, 41);
//				}
//
//				IPlayer.SetDirection(Target);
//			}
//		}
//		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//		IPlayer.DecreaseMana(nMana);
//	}
//
//
//}
//
//
//
//#endif