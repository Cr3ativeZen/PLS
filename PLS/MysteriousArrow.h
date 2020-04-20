#ifndef _MYSTERIOUSARROW_H
#define _MYSTERIOUSARROW_H
void __fastcall MysteriousArrow(int pSkill, void *pPlayer, int pPacket, int pPos)
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


	if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (CheckHit(Target, 20))
		{
			int nDmg = (GetAttack()*MABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*MAAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*MAStrMultiPvE) + (ISkill.GetGrade()*MAPerGradeMultiPvE);

			if (Target.GetType() == 0)
			{
				Target.Buff(39, MADoTDuration, MADoTPerGradePvP*ISkill.GetGrade());
				nDmg = (GetAttack()*MABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*MAAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*MAStrMultiPvP) + (ISkill.GetGrade()*MAPerGradeMultiPvP);
			}
			if (Target.GetType() == 1)
			{
				Target.Buff(39, MADoTDuration, MADoTPerGradePvE*ISkill.GetGrade());
			}
			OktayDamageSingle(Target, nDmg, 21);
			_ShowBattleAnimation(Target, 21);
		}
		else
		{
			_ShowBattleMiss(Target, 21);
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

	/*if (bType == 0 && nTargetID)
	{
		if (GetCurMp() < nMana)
			return;

		if (!IsInRange(Target, 20))
			return;

		if (CheckHit(Target, 21))
		{
			Target.Buff(39, MADoTDuration, MADoTPerGradePvP*ISkill.GetGrade());
			int nDmg = (GetAttack()*MABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*MAAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*MAStrMultiPvP) + (ISkill.GetGrade()*MAPerGradeMultiPvP);
			OktayDamageSingle(Target, nDmg, 21);
			_ShowBattleAnimation(Target, 21);
			DecreaseMana(nMana);
		}
		else
		{
			_ShowBattleMiss(Target, 21);
		}
	}

	if (bType == 1 && nTargetID)
	{
		if (GetCurMp() < nMana)
			return;

		if (!IsInRange(Target, 20))
			return;

		if (CheckHit(Target, 21))
		{
			Target.Buff(39, MADoTDuration, MADoTPerGradePvE*ISkill.GetGrade());
			int nDmg = (GetAttack()*MABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*MAAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*MAStrMultiPvE) + (ISkill.GetGrade()*MAPerGradeMultiPvE);
			OktayDamageSingle(Target, nDmg, 21);
			_ShowBattleAnimation(Target, 21);
		}
		else
		{
			_ShowBattleMiss(Target, 21);

		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);*/
}
#endif