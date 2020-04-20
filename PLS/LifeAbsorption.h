#ifndef LIFEABSORPTION_H
#define LIFEABSORPTION_H

void __fastcall LifeAbsorption(int pSkill, void *edx, void *pPlayer, char *pPacket, char *pPos)
{

	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.GetGrade() * 6 + 20;
	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget(pTarget);

	if (pTarget && ITarget.IsValid() && IsValid() && nTargetID != GetID())
	{

		int nDmg = (GetAttack()*LAbsBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*LAbsAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*LAbsStrMultiPvE) + (nSkillGrade*LAbsPerGradeMultiPvE);

		if (ITarget.GetType() == 0)
			nDmg = (GetAttack()*LAbsBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*LAbsAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*LAbsStrMultiPvP) + (nSkillGrade*LAbsPerGradeMultiPvP);

		if (CheckHit(ITarget.GetOffset(), 50))
		{
			unsigned int GetAttackSpeed = CChar::GetASpeed((int)GetOffset());
			unsigned int GetASpeedValue = GetAttackSpeed;
			int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
			TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)ITarget.GetOffset() + 148))((int)ITarget.GetOffset(), GetOffset());
			Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), GetOffset(), GetASpeedValue * nDmg / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
			GetType = Check | 2 * DamageArgument | 4 * TypeKind;

			if (NormalDamage > 0)
				IncreaseHp(NormalDamage *LAbsHealPerGrade*nSkillGrade/100);

				CChar::WriteInSight(GetOffset(), 63, "bddbbwwb", ISkill.GetIndex(), GetID(), ITarget.GetID(), 1, 1, NormalDamage, 0, GetType);
		}
		else 
		{
			_ShowBattleMiss(ITarget, ISkill.GetIndex());
		}

		DecreaseMana(nMana);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}


#endif