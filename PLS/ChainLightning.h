#ifndef CHAINLIGHTNING_H
#define CHAINLIGHTNING_H
void __fastcall ChainLightning(void *pSkill, void *pPlayer, int pPacket, int pPos)
{
	IChar IPlayer(pPlayer);
	ISkill ISkill(pSkill);

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
	{
		pTarget = CPlayer::FindPlayer(nTargetID);
	}

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

		int Around = ITarget.GetObjectListAround(3);

		while (Around)
		{
			IChar Object((void*)*(DWORD*)Around);


			if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0) && CChar::IsNormal((int)Object.GetOffset()))
			{
				int nDmg = (IPlayer.GetAttack()*CLBaseDmgMultiPvE) + CChar::GetInt((int)IPlayer.GetOffset())*CLIntMultiPvE;

				if(Object.GetType()==0)
					nDmg = (IPlayer.GetAttack()*CLBaseDmgMultiPvP) + CChar::GetInt((int)IPlayer.GetOffset())*CLIntMultiPvP;

				IPlayer.OktayDamageArea(Object, nDmg, 41);
				IPlayer._ShowBattleAnimation(Object, 41);

				if (Object.IsBuff(307)&&Object.IsValid()&&Object.GetCurHp()>0)
					StormActivateShiny(IPlayer, Object);
			}

			Around = CBaseList::Pop((void*)Around);
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	IPlayer.DecreaseMana(nMana);
}
#endif