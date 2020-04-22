#ifndef BRUTALATTACK_H
#define BRUTALATTACK_H
void __fastcall BrutalAttack(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);
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


	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
		return;

	ICharacter Target(pTarget);

	if (!IPlayer.IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		return;
	}

	if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (IPlayer.CheckHit(Target, 20))
		{
			int nDmg = static_cast<int>(((IPlayer.GetAttack()*BRUTBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*BRUTAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*BRUTStrMultiPvE) + (nSkillGrade*BRUTPerGradeMultiPvE))*(0.5 + (IPlayer.GetDeathBlow()*0.1)));

			if (Target.GetType() == 0)
				nDmg = static_cast<int>(((IPlayer.GetAttack()*BRUTBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*BRUTAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*BRUTStrMultiPvP) + (nSkillGrade*BRUTPerGradeMultiPvP))*(0.5 + (IPlayer.GetDeathBlow()*0.1)));


			IPlayer.OktayDamageSingle(Target, nDmg, 17);
			IPlayer._ShowBattleAnimation(Target, 17);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());

		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 17);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
		}
	}

	IPlayer.DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}
#endif