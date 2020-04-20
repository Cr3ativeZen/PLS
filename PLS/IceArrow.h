#ifndef ICEARROW_H
#define ICEARROW_H
void __fastcall IceArrow(ICharacter IPlayer, int pPacket, int pPos)
{

	int pSkill = GetSkillPointer(74);
	__int64 GState = 536870912, State = 64, StateEx = 65, CancelState = 1;



	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset())
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			ICharacter Target(pTarget);

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

				if (IsBuff(295))
				{
					if (CheckIceArrow[GetPID()].Cooldown > GetTickCount())
					{
						CancelBuff(5600);
						CancelBuff(5605);
						SendGStateExIceArrow(GState / 2);
						SendGStateExIceArrow(State << 32);
						for (int i = 0; i < 6; i++)
						{
							CancelBuff(290 + i);
						}
						SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
						CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
						return;
					}

					if (CheckIceArrow.find(GetPID())->second.Cooldown < GetTickCount())
					{
						CheckIceArrow[GetPID()].Cooldown = GetTickCount() + 70000;
						CheckIceArrow[GetPID()].Delay = GetTickCount() + 200;
					}
					CancelBuff(295);

					if (xSkill.GetGrade() == 1)
					{
						Buff(5600, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 2)
					{
						Buff(5601, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 2);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 3)
					{
						Buff(5602, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 4);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 4)
					{
						Buff(5603, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 8);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 5)
					{
						Buff(5604, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 16);
						SendGStateExIceArrow(StateEx << 32);
					}
					else {
						CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
						return;
					}

				}



				if (IsValid() && IsBuff(5604))
				{
					CancelBuff(5604);
					Buff(5603, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 8);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5603))
				{
					CancelBuff(5603);
					Buff(5602, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 4);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5602))
				{
					CancelBuff(5602);
					Buff(5601, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 2);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5601))
				{
					CancelBuff(5601);
					Buff(5600, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5600))
				{
					CancelBuff(5600);
					CancelBuff(5605);
					SendGStateExIceArrow(GState / 2);
					SendGStateExIceArrow(State << 32);
					for (int i = 0; i < 6; i++)
					{
						CancelBuff(290 + i);
					}
				}
				else {
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				}


				int nDmg = (GetMagic()*IAMBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*IAMIntMultiPvE) + (nSkillGrade*IAMPerGradeMultiPvE);


				if (Target.GetType() == 0)
					nDmg = (GetMagic()*IAMBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*IAMIntMultiPvP) + (nSkillGrade*IAMPerGradeMultiPvP);

				OktayDamageSingle(Target, nDmg, 74);
				SetDirection(Target);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif