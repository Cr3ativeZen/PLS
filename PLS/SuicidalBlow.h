#ifndef SUICIDALBLOW_H
#define SUICIDALBLOW_H
void __fastcall SuicidalBlow(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(21);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 40 * nSkillGrade + 45;

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

				int nDmg = (GetAttack()*TSBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*TSBAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*TSBStrMultiPvE) + (nSkillGrade*TSBPerGradeMultiPvE);
				
				if (Target.GetType() == 0)
				nDmg = (GetAttack()*TSBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*TSBAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*TSBStrMultiPvP) + (nSkillGrade*TSBPerGradeMultiPvP);

				
				int Additional = 0;


				if (((GetMaxHp() * TSBHPPercent) / 100)<GetCurHp())
				{
					Additional = (GetMaxHp() * TSBHPPercent) / 100;

					if (Additional > 0 && GetCurHp() > Additional)
					{
						DecreaseHp(Additional);
						if (Target.GetType() == 0)
						{
							nDmg = nDmg + (Additional)*TSBDamagePerHPPvP; 
						}
						nDmg = nDmg + Additional * TSBDamagePerHPPvE;
					}
				}
				else
				{
					SystemMessage("Not enough HP to cast skill!", TEXTCOLOR_RED);
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				OktayDamageSingle(Target, nDmg, 21);
				SetDirection(Target);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}



#endif