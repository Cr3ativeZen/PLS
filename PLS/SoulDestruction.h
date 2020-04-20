#ifndef SOULDESTRUCTION_H
#define SOULDESTRUCTION_H


void __fastcall SoulDestruction(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);

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
		int nDmg = (GetMagic()*SoulDestructionBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset())*SoulDestructionWisMultiPvE) + (ISkill.GetGrade()*SoulDestructionPerGradeMultiPvE);

		if (Target.GetType() == 0)
		{
			nDmg = (GetMagic()*SoulDestructionBaseDmgMultiPvP) + (CChar::GetWis((int)GetOffset())*SoulDestructionWisMultiPvP) + (ISkill.GetGrade()*SoulDestructionPerGradeMultiPvP);
		}
		OktayDamageSingle(Target, nDmg, 40);
		_ShowBattleAnimation(Target, 40);

	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}
#endif