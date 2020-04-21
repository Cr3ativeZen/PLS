#ifndef FLAMEINJECTION_H
#define FLAMEINJECTION_H
void __fastcall ContinueFlameInjection(ICharacter IPlayer)
{

	if (IPlayer.IsValid())
	{
		int nSkillGrade = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;

			if (!IPlayer.IsValid())
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5557);
				return;
			}

			if (IPlayer.IsMoved(CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerX, CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerY))
			{
				ResetContinueSkill(IPlayer);
				IPlayer.CancelBuff(5557);
				return;
			}

			int Around = IPlayer.GetObjectListAround(4);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic()*FIBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*FIIntMultiPvE) + (nSkillGrade*FIPerGradeMultiPvE);


					if (Object.GetType() == 0)
						nDmg = (IPlayer.GetMagic()*FIBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*FIIntMultiPvP) + (nSkillGrade*FIPerGradeMultiPvP);


					IPlayer.OktayDamageArea(Object, nDmg, 65);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IPlayer.IsOnline() && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount == 0)
			{
				IPlayer.CancelBuff(5557);
				ResetContinueSkill(IPlayer);
			}

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	IPlayer.CancelBuff(5557);
	return;
}

void __fastcall FlameInjection(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(65);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = IPlayer.GetLevel() * 4 + 120;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			ICharacter Target(pTarget);

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

				IPlayer.Buff(5557, 10, 0);
				IPlayer.DecreaseMana(nMana);
				CheckContinueSkill[IPlayer.GetPID()].PlayerX = IPlayer.GetX();
				CheckContinueSkill[IPlayer.GetPID()].PlayerY = IPlayer.GetY();
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 65;
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 6;
				CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
				IPlayer._ShowBattleAnimation(IPlayer, 65);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueFlameInjection(IPlayer);
	}
}
#endif