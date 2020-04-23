//#ifndef _AMNESIA_H
//#define _AMNESIA_H
//void __fastcall Amnesia(int pSkill, void *pPlayer, int pPacket, int pPos)
//{
//	ICharacter IPlayer(pPlayer);
//	ISkill ISkill((void*)pSkill);
//
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
//	{
//		IPlayer.SystemMessage("You cannot attack player with Amnesia", TEXTCOLOR_RED);
//		return;
//	}
//
//	if (bType == 1 && nTargetID)
//		pTarget = CMonster::FindMonster(nTargetID);
//
//	if (bType >= 2 ||!pTarget||pTarget==IPlayer.GetOffset()||IPlayer.GetCurMp()<nMana)
//		return;
//
//	ICharacter Target(pTarget);
//
//	if (bType == 1)
//	{
//		IPlayer._ShowBattleAnimation(Target, 61);
//		int Around = Target.GetObjectListAround(3);
//		while (Around)
//		{
//			ICharacter Object((void*)*(DWORD*)Around);
//
//			if (Object.GetType() == 1 && Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
//			{
//				if (CChar::IsNormal((int)Object.GetOffset()))
//				{
//					int nDmg = (IPlayer.GetMagic()*AmensiaBaseDmgMulti) + IPlayer.GetWis()*AmnesiaWisMulti;
//					if (IPlayer.IsBuff(24))
//					{
//						nDmg *= (AmnesiaDmgPercentIncreaseBless / 100);
//					}
//					IPlayer.OktayDamageArea(Object, nDmg, 61);
//				}
//			}
//			Around = CBaseList::Pop((void*)Around);
//		}
//	
//	}
//	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
//	IPlayer.DecreaseMana(nMana);
//}
//#endif