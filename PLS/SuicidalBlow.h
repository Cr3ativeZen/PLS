//#ifndef SUICIDALBLOW_H
//#define SUICIDALBLOW_H
//void __fastcall SuicidalBlow(ICharacter IPlayer, int pPacket, int pPos)
//{
//	int pSkill = IPlayer.GetSkillPointer(21);
//
//	if (IPlayer.IsValid() && pSkill)
//	{
//		ISkill xSkill((void*)pSkill);
//		int nSkillGrade = xSkill.GetGrade();
//
//		if (!nSkillGrade)
//			return;
//
//		int nTargetID = 0; char bType = 0; void *pTarget = 0;
//		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
//		int nMana = 40 * nSkillGrade + 45;
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
//		if (pTarget && nSkillGrade && IPlayer.IsValid())
//		{
//			ICharacter Target(pTarget);
//
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
//				int nDmg = (IPlayer.GetAttack()*TSBBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*TSBAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*TSBStrMultiPvE) + (nSkillGrade*TSBPerGradeMultiPvE);
//				
//				if (Target.GetType() == 0)
//				nDmg = (IPlayer.GetAttack()*TSBBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*TSBAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*TSBStrMultiPvP) + (nSkillGrade*TSBPerGradeMultiPvP);
//
//				
//				int Additional = 0;
//
//
//				if (((IPlayer.GetMaxHp() * TSBHPPercent) / 100)<IPlayer.GetCurHp())
//				{
//					Additional = (IPlayer.GetMaxHp() * TSBHPPercent) / 100;
//
//					if (Additional > 0 && IPlayer.GetCurHp() > Additional)
//					{
//						IPlayer.DecreaseHp(Additional);
//						if (Target.GetType() == 0)
//						{
//							nDmg = nDmg + (Additional)*TSBDamagePerHPPvP; 
//						}
//						nDmg = nDmg + Additional * TSBDamagePerHPPvE;
//					}
//				}
//				else
//				{
//					IPlayer.SystemMessage("Not enough HP to cast skill!", TEXTCOLOR_RED);
//					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//					return;
//				}
//
//				IPlayer.OktayDamageSingle(Target, nDmg, 21);
//				IPlayer.SetDirection(Target);
//				IPlayer.DecreaseMana(nMana);
//			}
//			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//		}
//	}
//}
//
//
//
//#endif