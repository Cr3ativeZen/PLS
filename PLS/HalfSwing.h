#ifndef HALFSWING_H
#define HALFSWING_H
void __fastcall HalfSwing(int pSkill, void *pPlayer, int pPacket, int pPos)
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
		int Around = Target.GetObjectListAround(1);

		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);
			if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				int nDmg = (GetAttack()*HSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*HSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*HSStrMultiPvE) + (nSkillGrade*HSPerGradeMultiPvE);

				if (Object.GetType() == 0)
				{
					nDmg = (GetAttack()*HSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*HSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*HSStrMultiPvP) + (nSkillGrade*HSPerGradeMultiPvP);
				}
				OktayDamageArea(Object, nDmg, 25);
			}
			Around = CBaseList::Pop((void*)Around);
		}
		_ShowBattleAnimation(IPlayer, 25);
		AddDeathBlow(1);
	}	
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif