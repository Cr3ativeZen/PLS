#ifndef BLOODSUCTION_H
#define BLOODSUCTION_H
void __fastcall BloodSuction(IChar IPlayer, int pPacket, int pPos)
{
	int nDmg = 0;
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000 && CChar::IsGState((int)IPlayer.GetOffset(), 512))
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset())
			return;

		if (pTarget && IPlayer.IsValid())
		{
			IChar ITarget(pTarget);

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (pTarget == IPlayer.GetOffset())
				{
					CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IPlayer.IsInRange(ITarget, 300))
				{
					CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
					return;
				}

				int nDmg = (IPlayer.GetMagic() + IPlayer.GetAttack())*BSBaseDmgMultiPvE;


				if (ITarget.GetType() == 0)
					nDmg = (IPlayer.GetMagic() + IPlayer.GetAttack())*BSBaseDmgMultiPvP;

				int realDamage = IPlayer.OktayDamageSingle(ITarget, nDmg, 115);

				if (realDamage > 5)
					IPlayer.IncreaseHp(realDamage * 30 / 75);

				IPlayer.DecreaseRage(15000);
			}
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);

		}

	}
}
#endif