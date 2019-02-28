//#ifndef EGGSKILL_H
//#define EGGSKILL_H
//void __fastcall ExecuteTransformSkill(void *pSkill, void* edx, signed int SkillID, int pPacket, int pPos)
//{
//	ISkill Skill(pSkill);
//	IChar IPlayer(Skill.GetPlayer());
//
//
//	if (SkillID == 64)
//	{
//		ActivateShiny(IPlayer, pPacket, pPos);
//	}
//
//		int kappa = CPacket::Read((char*)pPacket, (char*)pPos, "bd", &SkillID);
//
//		if (!SkillID == 101 || !SkillID == 113 || !SkillID == 114 || !SkillID == 115 || !SkillID == 116)
//		{
//
//		}
//		else
//		{
//			DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;
//
//			if (CheckEggCooldownConfig.count(SkillID))
//			{
//				CdTime = CheckEggCooldownConfig.find(SkillID)->second.EggCooldownConfig;
//				DelayTime = CheckEggCooldownConfig.find(SkillID)->second.EggDelayConfig;
//			}
//
//			if (CooldownCheck > GetTickCount())
//			{
//				IPlayer.SystemMessage("Invalid egg skill time detected!", TEXTCOLOR_RED);
//				return;
//			}
//			else {
//				EggCooldownTable[IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)] = GetTickCount() + CdTime + DelayTime;
//			}
//
//			if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(), 512))
//			{
//				if (EggCooldownTable.count(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)))
//					CooldownCheck = EggCooldownTable.find(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000))->second;
//
//
//
//
//				IPlayer.SystemMessage(Int2String(SkillID), TEXTCOLOR_RED);
//				if (SkillID == 101)
//				{
//					ActivateShiny(IPlayer, kappa, pPos);
//				}
//
//				if (SkillID == 113)
//				{
//					RevolveAttack(IPlayer);
//					return;
//				}
//
//				if (SkillID == 114)
//				{
//					WhirlwindFeather(IPlayer);
//					return;
//				}
//
//
//				if (SkillID == 116)
//				{
//					EggThunderbolt(IPlayer);
//					return;
//				}
//			}
//		}
//
//	
//
//
//	CSkill::ExecuteTransformSkill(pSkill, SkillID, pPacket, pPos);
//}
//#endif