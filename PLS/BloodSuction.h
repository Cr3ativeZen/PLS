#ifndef BLOODSUCTION_H
#define BLOODSUCTION_H
void __fastcall BloodSuction(ICharacter IPlayer, int pPacket, int pPos)
{
	int nDmg = 0;
	if (IsValid() && GetRage() >= 15000 && CChar::IsGState((int)GetOffset(), 512))
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset())
			return;

		if (pTarget && IsValid())
		{
			ICharacter ITarget(pTarget);

			if (ITarget.IsValid() && IsValid())
			{
				if (pTarget == GetOffset())
				{
					CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IsInRange(ITarget, 300))
				{
					CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
					return;
				}

				int nDmg = (GetMagic() + GetAttack())*BSBaseDmgMultiPvE;


				if (ITarget.GetType() == 0)
					nDmg = (GetMagic() + GetAttack())*BSBaseDmgMultiPvP;

				int realDamage = OktayDamageSingle(ITarget, nDmg, 115);

				if (realDamage > 5)
					IncreaseHp(realDamage * 30 / 75);

				DecreaseRage(15000);
			}
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);

		}

	}
}
#endif