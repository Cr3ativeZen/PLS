#ifndef CHAINLIGHTNING_H
#define CHAINLIGHTNING_H
void __fastcall ChainLightning(int pSkill, void *pPlayer, int pPacket, int pPos)
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

	ICharacter ITarget(pTarget);

	if (ITarget.IsValid() && IsValid())
	{
		int Around = ITarget.GetObjectListAround(3);
		_ShowBattleAnimation(ITarget, 41);
		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);
			if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				if (CChar::IsNormal((int)Object.GetOffset()))
				{
					int nDmg = (GetMagic()*CLBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*CLIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*CLBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*CLIntMultiPvP;

					OktayDamageArea(Object, nDmg, 41);

					if (Object.IsBuff(307) && Object.IsValid() && Object.GetCurHp() > 0)
						StormActivateShiny(IPlayer, Object);
				}
			}
			Around = CBaseList::Pop((void*)Around);
		}
		_ShowBattleAnimation(ITarget, 41);
	}

	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}
#endif