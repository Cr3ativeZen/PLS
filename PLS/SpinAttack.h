#ifndef SPINATTACK_H
#define SPINATTACK_H
void __fastcall SpinAttack(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(19);

	if (IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			ICharacter Target(pTarget);

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int Around = GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (GetAttack()*SABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SAAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SAStrMultiPvE) + (nSkillGrade*SAPerGradeMultiPvE);


						if (Object.GetType() == 0)
							nDmg = (GetAttack()*SABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SAAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SAStrMultiPvP) + (nSkillGrade*SAPerGradeMultiPvP);


						OktayDamageArea(Object, nDmg, 19);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				SetDirection(Target);
				_ShowBattleAnimation(Target, 19);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif