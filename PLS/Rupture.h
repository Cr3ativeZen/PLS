//#ifndef RUPTURE_H
//#define RUPTURE_H
//
//void __fastcall ContinueRupture(ICharacter IPlayer)
//{
//	if (IPlayer.IsValid())
//	{
//		int nSkillGrade = CheckRuptureContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillGrade;
//		void *pTarget = CheckRuptureContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;
//
//		if (nSkillGrade && pTarget && CheckRuptureContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
//		{
//			ICharacter Target(pTarget);
//			CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;
//
//
//
//
//
//			if (!Target.IsValid() || !IPlayer.IsValid())
//			{
//				ResetRuptureContinueSkill(IPlayer);
//				IPlayer.CancelBuff(5577);
//				return;
//			}
//
//			if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
//			{
//				ResetRuptureContinueSkill(IPlayer);
//				IPlayer.CancelBuff(5577);
//				return;
//			}
//
//			if (IPlayer.IsValid() && Target.IsValid())
//			{
//
//				if (Target.GetType() == 0)
//				{
//					int nDmg = (IPlayer.GetAttack()*RupBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*RupAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*RupStrMultiPvP) + (nSkillGrade*RupPerGradeMultiPvP);
//					
//					if (Target.IsBuff(346))
//					{
//						nDmg = nDmg +(nDmg*(AnkleAPercentDamageIncreasePvP) / 100);
//						
//					}
//					
//					IPlayer.OktayDamageArea(Target, nDmg, 17);
//				}
//				else
//				{
//					int Around = Target.GetObjectListAround(3);
//					int nDmg = ((IPlayer.GetAttack()*RupBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*RupAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*RupStrMultiPvE) + (nSkillGrade*RupPerGradeMultiPvE));
//					
//					int ntankerDmg = nDmg / 2;
//
//
//					if (Target.IsBuff(346))
//					{
//						ntankerDmg = ntankerDmg + (ntankerDmg * (AnkleAPercentDamageIncreasePvE) / 100);
//						nDmg = nDmg + (nDmg*(AnkleAPercentDamageIncreasePvE) / 100);
//					}
//
//					IPlayer.OktayDamageArea(Target, ntankerDmg, 17);
//					while (Around)
//					{
//						ICharacter Object((void*)*(DWORD*)Around);
//						if (Object.GetType() == 1&&Object.IsBuff(350)&&Object.GetOffset()!=IPlayer.GetOffset()&&Object.GetOffset()!=Target.GetOffset())
//						{
//							IPlayer.OktayDamageArea(Object, nDmg, 17);
//						}
//						Around = CBaseList::Pop((void*)Around);
//					}
//				}
//				
//				
//
//
//				
//			}
//
//			if (IPlayer.IsOnline())
//				CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;
//
//			if (IPlayer.IsOnline() && CheckRuptureContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
//			{
//				ResetRuptureContinueSkill(IPlayer);
//				IPlayer.CancelBuff(5577);
//			}
//
//			return;
//		}
//	}
//
//	ResetRuptureContinueSkill(IPlayer);
//	IPlayer.CancelBuff(5577);
//	return;
//}
//
//void __fastcall Rupture(ICharacter IPlayer, int pPacket, int pPos)
//{
//	int pSkill = IPlayer.GetSkillPointer(17);
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
//		int nMana = (int)(30 * nSkillGrade + 35);
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
//		if (pTarget && IPlayer.IsValid() && nSkillGrade)
//		{
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
//				if (IPlayer.CheckHit(Target, 35))
//				{
//					IPlayer.Buff(5577, 18, 0);
//					int Around = Target.GetObjectListAround(4);
//					IPlayer._ShowBattleAnimation(IPlayer, 17, nSkillGrade);
//					IPlayer.Buff(353, 20, 0);
//
//					if (Target.GetType() == 1)
//					{
//
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerTarget = Target.GetOffset();
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillID = 17;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 9;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1000;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
//
//						while (Around)
//						{
//							ICharacter Object((void*)*(DWORD*)Around);
//
//							if (Object.GetOffset() != IPlayer.GetOffset() && Object.GetType() == 1)
//							{
//								if (!Object.IsBuff(350))
//									Object.SendGStateEx(Target.GetGStateEx() + 65536);
//
//								Object.Buff(350, 18, 0);
//
//							}
//							Around = CBaseList::Pop((void*)Around);
//
//						}
//					}
//					if (Target.GetType() == 0)
//					{
//						if (!Target.IsBuff(350))
//							Target.SendGStateEx(Target.GetGStateEx() + 65536);
//
//						Target.Buff(350, 18, 0);
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerTarget = Target.GetOffset();
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillID = 17;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 9;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1000;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = nSkillGrade;
//						CheckRuptureContinueSkill[IPlayer.GetPID()].CasterOffset = IPlayer.GetOffset();
//					}
//
//				}
//				else 
//				{
//					IPlayer._ShowBattleMiss(Target, 17);
//					IPlayer.CancelBuff(5577);
//				}
//
//				IPlayer.SetDirection(Target);
//				IPlayer.DecreaseMana(nMana);
//			}
//		}
//		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//	}
//}
//
//
//#endif