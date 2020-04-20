#ifndef FLAMEINJECTION_H
#define FLAMEINJECTION_H
void __fastcall ContinueFlameInjection(ICharacter IPlayer)
{

	if (IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid())
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5557);
				return;
			}

			if (IsMoved(CheckContinueSkill.find(GetPID())->second.PlayerX, CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				CancelBuff(5557);
				return;
			}

			int Around = GetObjectListAround(4);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (GetMagic()*FIBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*FIIntMultiPvE) + (nSkillGrade*FIPerGradeMultiPvE);


					if (Object.GetType() == 0)
						nDmg = (GetMagic()*FIBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*FIIntMultiPvP) + (nSkillGrade*FIPerGradeMultiPvP);


					OktayDamageArea(Object, nDmg, 65);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				CancelBuff(5557);
				ResetContinueSkill(IPlayer);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	CancelBuff(5557);
	return;
}

void __fastcall FlameInjection(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(65);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = GetLevel() * 4 + 120;

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

				Buff(5557, 10, 0);
				DecreaseMana(nMana);
				CheckContinueSkill[GetPID()].PlayerX = GetX();
				CheckContinueSkill[GetPID()].PlayerY = GetY();
				CheckContinueSkill[GetPID()].PlayerSkillID = 65;
				CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				CheckContinueSkill[GetPID()].PlayerSkillCount = 6;
				CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
				_ShowBattleAnimation(IPlayer, 65);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueFlameInjection(IPlayer);
	}
}
#endif