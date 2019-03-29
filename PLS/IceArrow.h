#ifndef ICEARROW_H
#define ICEARROW_H
void __fastcall IceArrow(IChar IPlayer, int pPacket, int pPos)
{

	int pSkill = IPlayer.GetSkillPointer(74);
	__int64 GState = 536870912, State = 64, StateEx = 65, CancelState = 1;



	if (IPlayer.IsValid() && pSkill)
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

		if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset())
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (pTarget == IPlayer.GetOffset())
				return;

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300))
					return;

				if (IPlayer.IsBuff(295))
				{
					if (CheckIceArrow[IPlayer.GetPID()].Cooldown > GetTickCount())
					{
						IPlayer.CancelBuff(5600);
						IPlayer.CancelBuff(5605);
						IPlayer.SendGStateExIceArrow(GState / 2);
						IPlayer.SendGStateExIceArrow(State << 32);
						for (int i = 0; i < 6; i++)
						{
							IPlayer.CancelBuff(290 + i);
						}
						IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
						return;
					}

					if (CheckIceArrow.find(IPlayer.GetPID())->second.Cooldown < GetTickCount())
					{
						CheckIceArrow[IPlayer.GetPID()].Cooldown = GetTickCount() + 70000;
						CheckIceArrow[IPlayer.GetPID()].Delay = GetTickCount() + 200;
					}
					IPlayer.CancelBuff(295);

					if (xSkill.GetGrade() == 1)
					{
						IPlayer.Buff(5600, 18, 0);
						IPlayer.Buff(5605, 18, 0);
						IPlayer.SendGStateExIceArrow(GState);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 2)
					{
						IPlayer.Buff(5601, 18, 0);
						IPlayer.Buff(5605, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 2);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 3)
					{
						IPlayer.Buff(5602, 18, 0);
						IPlayer.Buff(5605, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 4);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 4)
					{
						IPlayer.Buff(5603, 18, 0);
						IPlayer.Buff(5605, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 8);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 5)
					{
						IPlayer.Buff(5604, 18, 0);
						IPlayer.Buff(5605, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 16);
						IPlayer.SendGStateExIceArrow(StateEx << 32);
					}
					else {
						return;
					}

				}



				if (IPlayer.IsValid() && IPlayer.IsBuff(5604))
				{
					IPlayer.CancelBuff(5604);
					IPlayer.Buff(5603, 18, 0);
					IPlayer.Buff(5605, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 8);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(5603))
				{
					IPlayer.CancelBuff(5603);
					IPlayer.Buff(5602, 18, 0);
					IPlayer.Buff(5605, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 4);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(5602))
				{
					IPlayer.CancelBuff(5602);
					IPlayer.Buff(5601, 18, 0);
					IPlayer.Buff(5605, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 2);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(5601))
				{
					IPlayer.CancelBuff(5601);
					IPlayer.Buff(5600, 18, 0);
					IPlayer.Buff(5605, 18, 0);
					IPlayer.SendGStateExIceArrow(GState);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(5600))
				{
					IPlayer.CancelBuff(5600);
					IPlayer.CancelBuff(5605);
					IPlayer.SendGStateExIceArrow(GState / 2);
					IPlayer.SendGStateExIceArrow(State << 32);
					for (int i = 0; i < 6; i++)
					{
						IPlayer.CancelBuff(290 + i);
					}
				}
				else {
					return;
				}


				int nDmg = (IPlayer.GetMagic()*IAMBaseDmgMultiPvE) + (CChar::GetInt((int)IPlayer.GetOffset())*IAMIntMultiPvE) + (nSkillGrade*IAMPerGradeMultiPvE);


				if (Target.GetType() == 0)
					nDmg = (IPlayer.GetMagic()*IAMBaseDmgMultiPvP) + (CChar::GetInt((int)IPlayer.GetOffset())*IAMIntMultiPvP) + (nSkillGrade*IAMPerGradeMultiPvP);

				IPlayer.OktayDamageSingle(Target, nDmg, 74);
				IPlayer.SetDirection(Target);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif