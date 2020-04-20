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


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter Target(pTarget);

	if (!IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		return;
	}

	if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (CheckHit(Target, 20))
		{
			int nDmg = static_cast<int>(((GetAttack()*BRUTBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*BRUTAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*BRUTStrMultiPvE) + (nSkillGrade*BRUTPerGradeMultiPvE))*(0.5 + (GetDeathBlow()*0.1)));

			if (Target.GetType() == 0)
				nDmg = static_cast<int>(((GetAttack()*BRUTBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*BRUTAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*BRUTStrMultiPvP) + (nSkillGrade*BRUTPerGradeMultiPvP))*(0.5 + (GetDeathBlow()*0.1)));


			OktayDamageSingle(Target, nDmg, 17);
			_ShowBattleAnimation(Target, 17);
			RemoveDeathBlow(GetDeathBlow());

		}
		else
		{
			_ShowBattleMiss(Target, 17);
			RemoveDeathBlow(GetDeathBlow());
		}
	}

	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}
#endif