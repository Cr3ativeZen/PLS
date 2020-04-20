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


	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
		return;

	ICharacter Target(pTarget);


	if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (IPlayer.CheckHit(Target, 20))
		{
			int nDmg = (IPlayer.GetAttack()*MABaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*MAAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*MAStrMultiPvE) + (ISkill.GetGrade()*MAPerGradeMultiPvE);

			if (Target.GetType() == 0)
			{
				Target.Buff(39, MADoTDuration, MADoTPerGradePvP*ISkill.GetGrade());
				nDmg = (IPlayer.GetAttack()*MABaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*MAAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*MAStrMultiPvP) + (ISkill.GetGrade()*MAPerGradeMultiPvP);
			}
			if (Target.GetType() == 1)
			{
				Target.Buff(39, MADoTDuration, MADoTPerGradePvE*ISkill.GetGrade());
			}
			IPlayer.OktayDamageSingle(Target, nDmg, 21);
			IPlayer._ShowBattleAnimation(Target, 21);
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 21);
		}
	}
	IPlayer.DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

	/*if (bType == 0 && nTargetID)
	{
		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsInRange(Target, 20))
			return;

		if (IPlayer.CheckHit(Target, 21))
		{
			Target.Buff(39, MADoTDuration, MADoTPerGradePvP*ISkill.GetGrade());
			int nDmg = (IPlayer.GetAttack()*MABaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*MAAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*MAStrMultiPvP) + (ISkill.GetGrade()*MAPerGradeMultiPvP);
			IPlayer.OktayDamageSingle(Target, nDmg, 21);
			IPlayer._ShowBattleAnimation(Target, 21);
			IPlayer.DecreaseMana(nMana);
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 21);
		}
	}

	if (bType == 1 && nTargetID)
	{
		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsInRange(Target, 20))
			return;

		if (IPlayer.CheckHit(Target, 21))
		{
			Target.Buff(39, MADoTDuration, MADoTPerGradePvE*ISkill.GetGrade());
			int nDmg = (IPlayer.GetAttack()*MABaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*MAAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*MAStrMultiPvE) + (ISkill.GetGrade()*MAPerGradeMultiPvE);
			IPlayer.OktayDamageSingle(Target, nDmg, 21);
			IPlayer._ShowBattleAnimation(Target, 21);
		}
		else
		{
			IPlayer._ShowBattleMiss(Target, 21);

		}
	}
	IPlayer.DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);*/
}
#endif