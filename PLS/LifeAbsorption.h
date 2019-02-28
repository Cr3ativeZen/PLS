#ifndef LIFEABSORPTION_H
#define LIFEABSORPTION_H

void __fastcall LifeAbsorption(void *pSkill, void *edx, void *pPlayer, char *pPacket, char *pPos)
{
	ISkill ISkill(pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read(pPacket, pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.GetGrade() * 6 + 20;

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2)
		return;

	IChar ITarget(pTarget);

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && nTargetID != IPlayer.GetID())
	{
		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsInRange(ITarget, 300))
			return;

		(*(void(__thiscall **)(int, int))(*(DWORD*)ITarget.GetOffset() + 80))((int)ITarget.GetOffset(), (int)IPlayer.GetOffset());
		int nDmg = (IPlayer.GetAttack()*LAbsBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*LAbsAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*LAbsStrMultiPvE) + (nSkillGrade*LAbsPerGradeMultiPvE);

		if (ITarget.GetType() == 0)
			nDmg = (IPlayer.GetAttack()*LAbsBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*LAbsAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*LAbsStrMultiPvP) + (nSkillGrade*LAbsPerGradeMultiPvP);

		if (IPlayer.CheckHit(ITarget.GetOffset(), 50))
		{
			unsigned int GetAttackSpeed = CChar::GetASpeed((int)IPlayer.GetOffset());
			unsigned int GetASpeedValue = GetAttackSpeed;
			int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
			TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)ITarget.GetOffset() + 148))((int)ITarget.GetOffset(), IPlayer.GetOffset());
			Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), IPlayer.GetOffset(), GetASpeedValue * nDmg / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
			GetType = Check | 2 * DamageArgument | 4 * TypeKind;

			if (NormalDamage > 0)
				IPlayer.IncreaseHp(NormalDamage *LAbsHealPerGrade*nSkillGrade/100);

				CChar::WriteInSight(IPlayer.GetOffset(), 63, "bddbbwwb", ISkill.GetIndex(), IPlayer.GetID(), ITarget.GetID(), 1, 1, NormalDamage, 0, GetType);
		}
		else {
			IPlayer._ShowBattleMiss(ITarget, ISkill.GetIndex());
		}

		IPlayer.DecreaseMana(nMana);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}


#endif