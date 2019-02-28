#ifndef _AMNESIA_H
#define _AMNESIA_H
void __fastcall Amnesia(void *pSkill, void *pPlayer, int pPacket, int pPos)
{
	IChar IPlayer(pPlayer);
	ISkill ISkill(pSkill);

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
	{
		IPlayer.SystemMessage("You cannot attack player with Amnesia", TEXTCOLOR_RED);
		return;
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

			
			if (Object.GetType()==1&&Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0) && CChar::IsNormal((int)Object.GetOffset()))
			{
				int nDmg = (IPlayer.GetAttack()*AmensiaBaseDmgMulti)+IPlayer.GetWis()*AmnesiaWisMulti;


				IPlayer.OktayDamageArea(Object, nDmg, 61);
				IPlayer._ShowBattleAnimation(Object, 61);
			}

			Around = CBaseList::Pop((void*)Around);
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	IPlayer.DecreaseMana(nMana);
}
#endif