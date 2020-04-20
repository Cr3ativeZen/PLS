#ifndef RUPTURE_H
#define RUPTURE_H

void __fastcall ContinueRupture(ICharacter IPlayer)
{
	if (IsValid())
	{
		int nSkillGrade = CheckRuptureContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = CheckRuptureContinueSkill.find(GetPID())->second.PlayerTarget;

		if (nSkillGrade && pTarget && CheckRuptureContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			CheckRuptureContinueSkill[GetPID()].PlayerSkillCount--;





			if (!Target.IsValid() || !IsValid())
			{
				ResetRuptureContinueSkill(IPlayer);
				CancelBuff(5577);
				return;
			}

			if (CChar::GetRange((int)GetOffset() + 332, (int)pTarget + 332) > 300)
			{
				ResetRuptureContinueSkill(IPlayer);
				CancelBuff(5577);
				return;
			}

			if (IsValid() && Target.IsValid())
			{

				if (Target.GetType() == 0)
				{
					int nDmg = (GetAttack()*RupBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*RupAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*RupStrMultiPvP) + (nSkillGrade*RupPerGradeMultiPvP);
					
					if (Target.IsBuff(346))
					{
						nDmg = nDmg +(nDmg*(AnkleAPercentDamageIncreasePvP) / 100);
						
					}
					
					OktayDamageArea(Target, nDmg, 17);
				}
				else
				{
					int Around = Target.GetObjectListAround(3);
					int nDmg = ((GetAttack()*RupBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*RupAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*RupStrMultiPvE) + (nSkillGrade*RupPerGradeMultiPvE));
					
					int ntankerDmg = nDmg / 2;


					if (Target.IsBuff(346))
					{
						ntankerDmg = ntankerDmg + (ntankerDmg * (AnkleAPercentDamageIncreasePvE) / 100);
						nDmg = nDmg + (nDmg*(AnkleAPercentDamageIncreasePvE) / 100);
					}

					OktayDamageArea(Target, ntankerDmg, 17);
					while (Around)
					{
						ICharacter Object((void*)*(DWORD*)Around);
						if (Object.GetType() == 1&&Object.IsBuff(350)&&Object.GetOffset()!=GetOffset()&&Object.GetOffset()!=Target.GetOffset())
						{
							OktayDamageArea(Object, nDmg, 17);
						}
						Around = CBaseList::Pop((void*)Around);
					}
				}
				
				


				
			}

			if (IsOnline())
				CheckRuptureContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && CheckRuptureContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetRuptureContinueSkill(IPlayer);
				CancelBuff(5577);
			}

			return;
		}
	}

	ResetRuptureContinueSkill(IPlayer);
	CancelBuff(5577);
	return;
}

void __fastcall Rupture(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(17);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 35);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		ICharacter Target(pTarget);

		if (pTarget && IsValid() && nSkillGrade)
		{

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

				if (CheckHit(Target, 35))
				{
					Buff(5577, 18, 0);
					int Around = Target.GetObjectListAround(4);
					_ShowBattleAnimation(IPlayer, 17, nSkillGrade);
					Buff(353, 20, 0);

					if (Target.GetType() == 1)
					{

						CheckRuptureContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
						CheckRuptureContinueSkill[GetPID()].PlayerSkillID = 17;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillCount = 9;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1000;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;

						while (Around)
						{
							ICharacter Object((void*)*(DWORD*)Around);

							if (Object.GetOffset() != GetOffset() && Object.GetType() == 1)
							{
								if (!Object.IsBuff(350))
									Object.SendGStateEx(Target.GetGStateEx() + 65536);

								Object.Buff(350, 18, 0);

							}
							Around = CBaseList::Pop((void*)Around);

						}
					}
					if (Target.GetType() == 0)
					{
						if (!Target.IsBuff(350))
							Target.SendGStateEx(Target.GetGStateEx() + 65536);

						Target.Buff(350, 18, 0);
						CheckRuptureContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
						CheckRuptureContinueSkill[GetPID()].PlayerSkillID = 17;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillCount = 9;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1000;
						CheckRuptureContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
						CheckRuptureContinueSkill[GetPID()].CasterOffset = GetOffset();
					}

				}
				else 
				{
					_ShowBattleMiss(Target, 17);
					CancelBuff(5577);
				}

				SetDirection(Target);
				DecreaseMana(nMana);
			}
		}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	}
}


#endif