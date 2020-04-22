//#ifndef HALFSWING_H
//#define HALFSWING_H
//void __fastcall HalfSwing(int pSkill, void *pPlayer, int pPacket, int pPos)
//{
//	ICharacter IPlayer(pPlayer);
//	ISkill ISkill((void*)pSkill);
//	int nSkillGrade = ISkill.GetGrade();
//
//	if (!nSkillGrade)
//		return;
//
//	int nTargetID = 0; char bType = 0; void *pTarget = 0;
//	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
//	int nMana = ISkill.DecreaseMana();
//
//	if (bType == 0 && nTargetID)
//		pTarget = CPlayer::FindPlayer(nTargetID);
//
//	if (bType == 1 && nTargetID)
//		pTarget = CMonster::FindMonster(nTargetID);
//
//
//	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
//		return;
//
//	ICharacter Target(pTarget);
//
//	if (!IPlayer.IsInRange(Target, 20))
//	{
//		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//		return;
//	}
//
//	if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
//	{
//		int Around = Target.GetObjectListAround(1);
//
//		while (Around)
//		{
//			ICharacter Object((void*)*(DWORD*)Around);
//			if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
//			{
//				int nDmg = (IPlayer.GetAttack()*HSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*HSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*HSStrMultiPvE) + (nSkillGrade*HSPerGradeMultiPvE);
//
//				if (Object.GetType() == 0)
//				{
//					nDmg = (IPlayer.GetAttack()*HSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*HSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*HSStrMultiPvP) + (nSkillGrade*HSPerGradeMultiPvP);
//				}
//				IPlayer.OktayDamageArea(Object, nDmg, 25);
//			}
//			Around = CBaseList::Pop((void*)Around);
//		}
//		IPlayer._ShowBattleAnimation(IPlayer, 25);
//		IPlayer.AddDeathBlow(1);
//	}	
//	IPlayer.DecreaseMana(nMana);
//	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//}
//#endif