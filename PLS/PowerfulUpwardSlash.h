#ifndef POWERFULUPWARDSLASH_H
#define POWERFULUPWARDSLASH_H
void __fastcall PowerfulUpwardSlash(IChar IPlayer,int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(16));
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2)
		return;

	IChar Target(pTarget);



	if (bType == 0 && nTargetID)
	{
		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsInRange(Target, 300))
			return;

		if (IPlayer.CheckHit(Target, 16))
		{
			
			int nDmg = (IPlayer.GetAttack()*PUSBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*PUSAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*PUSStrMultiPvP) + (nSkillGrade*PUSPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg, 16);
			IPlayer._ShowBattleAnimation(Target, 16);
			IPlayer.DecreaseMana(nMana);
			IPlayer.AddDeathBlow(1);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;

		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 16);
			IPlayer.DecreaseMana(nMana);
		}

	}

	if (bType == 1 && nTargetID)
	{
		if (IPlayer.CheckHit(Target, 16))
		{
			int nDmg = (IPlayer.GetAttack()*PUSBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*PUSAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*PUSStrMultiPvE) + (nSkillGrade*PUSPerGradeMultiPvE);
			IPlayer.OktayDamageSingle(Target, nDmg, 16);
			IPlayer._ShowBattleAnimation(Target, 16);
			IPlayer.DecreaseMana(nMana);
			IPlayer.AddDeathBlow(1);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;

		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 16);
			IPlayer.DecreaseMana(nMana);
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}
#endif