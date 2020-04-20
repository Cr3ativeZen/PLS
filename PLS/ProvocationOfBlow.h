#ifndef PROVOCATIONOFBLOW_H
#define PROVOCATIONOFBLOW_H
void __fastcall ProvocationOfBlow(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(42);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			if (nSkillGrade <= 1)
				nMana = 220;
			else if (nSkillGrade == 2)
				nMana = 242;
			else if (nSkillGrade == 3)
				nMana = 266;
			else if (nSkillGrade == 4)
				nMana = 292;
			else if (nSkillGrade >= 5)
				nMana = 320;

			if (IsOnline() && CPlayer::IsWState((int)GetOffset(), 12))
				return;

			if (GetCurMp() < nMana)
				return;

			if (pTarget == GetOffset())
				return;

			if (pTarget && IsOnline())
			{
				ICharacter Target(pTarget);

				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int Around = GetObjectListAround(2);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (GetAttack()*PoBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*PoBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*PoBStrMultiPvE) + (nSkillGrade*PoBPerGradeMultiPvE);

						if (Object.GetType() == 0)
							nDmg = (GetAttack()*PoBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*PoBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*PoBStrMultiPvP) + (nSkillGrade*PoBPerGradeMultiPvP);

						if (Object.GetType() == 1&&IsBuff(284))
						{
							nDmg *= (PoBDmgPercentIncreasePDPvE / 100);
						}

						OktayDamageArea(Object, nDmg, 42);

						if (IsOnline() && IsValid() && Object.IsOnline() && Object.IsValid() && Object.GetType() == 1 && Object.GetCurHp() > 0 && Object.IsMobAggressive() && Object.IsMobHaveTarget())
							CMonsterReal::AddHostility(Object.GetOffset(), (int)GetOffset(), nDmg * PoBHostilityMultiplier, 0);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				_ShowBattleAnimation(Target, 42);
				SetDirection(Target);
				DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			}

		}
	}
}
#endif