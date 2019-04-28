#ifndef SPINATTACK_H
#define SPINATTACK_H
void __fastcall SpinAttack(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(19);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 50 + 25;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == IPlayer.GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int Around = IPlayer.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack()*SABaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*SAAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*SAStrMultiPvE) + (nSkillGrade*SAPerGradeMultiPvE);


						if (Object.GetType() == 0)
							nDmg = (IPlayer.GetAttack()*SABaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*SAAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*SAStrMultiPvP) + (nSkillGrade*SAPerGradeMultiPvP);


						IPlayer.OktayDamageArea(Object, nDmg, 19);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 19);
				IPlayer.DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif