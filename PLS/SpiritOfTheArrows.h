#ifndef SPIRITOFTHEARROWS_H
#define SPIRITOFTHEARROWS_H

void __fastcall SpiritOfTheArrows(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(93);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		nMana = static_cast<int>((1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1))))));

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IsOnline())
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

			if (!IsInRange(Target, 20))
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetAttack()*SOTABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*SOTAAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*SOTAStrMultiPvE) + (nSkillGrade*SOTAPerGradeMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack()*SOTABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*SOTAAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*SOTAStrMultiPvP) + (nSkillGrade*SOTAPerGradeMultiPvE);


					OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			SetDirection(Target);
			_ShowBattleAnimation(Target, 93);
			DecreaseMana(nMana);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}


#endif