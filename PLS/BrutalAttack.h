#ifndef BRUTALATTACK_H
#define BRUTALATTACK_H
void __fastcall BrutalAttack(void *pSkill, void *pPlayer, int pPacket, int pPos)
{
	ISkill ISkill(pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);
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

		if (IPlayer.CheckHit(Target, 17))
		{
			int nDmg = static_cast<int>(((IPlayer.GetAttack()*BRUTBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*BRUTAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*BRUTStrMultiPvP) + (nSkillGrade*BRUTPerGradeMultiPvP))*(0.5 + (IPlayer.GetDeathBlow()*0.1)));
			IPlayer.OktayDamageSingle(Target, nDmg, 17);
			IPlayer._ShowBattleAnimation(Target, 17);
			IPlayer.DecreaseMana(nMana);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;

		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 17);
			IPlayer.DecreaseMana(nMana);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
		}

	}

	if (bType == 1 && nTargetID)
	{
		if (IPlayer.CheckHit(Target, 17))
		{
			int nDmg = static_cast<int>(((IPlayer.GetAttack()*BRUTBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*BRUTAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*BRUTStrMultiPvE) + (nSkillGrade*BRUTPerGradeMultiPvE))*(0.5 + (IPlayer.GetDeathBlow()*0.1)));
			IPlayer.OktayDamageSingle(Target, nDmg, 17);
			IPlayer._ShowBattleAnimation(Target, 17);
			IPlayer.DecreaseMana(nMana);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;

		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 17);
			IPlayer.DecreaseMana(nMana);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}
#endif