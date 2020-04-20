#ifndef _FOCUSSHOT_H
#define _FOCUSSHOT_H

void __fastcall FocusShot(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;


	ICharacter Target(pTarget);

	if (pTarget && Target.IsValid() && IsValid() && nTargetID != GetID())
	{

		SetDirection(Target);
		if (CheckHit(Target, 20))
		{
			int nTime = GetTickCount() - CheckFocus[GetPID()];
			
			int nDmg = (GetAttack()*FSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*FSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*FSStrMultiPvE) + (nSkillGrade*FSPerGradeMultiPvE);

			if (Target.GetType() == 0)
				nDmg = (GetAttack()*FSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*FSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*FSStrMultiPvP) + (nSkillGrade*FSPerGradeMultiPvP);


			if (nTime > 1000)
			{
				if (nTime >= 2900)
					nDmg = nDmg * 1;
				else if (nTime >= 2600)
					nDmg = static_cast<int>(nDmg * 0.9);
				else if (nTime >= 2300)
					nDmg = static_cast<int>(nDmg * 0.85);
				else if (nTime >= 1700)
					nDmg = static_cast<int>(nDmg * 0.8);
				else
					nDmg = static_cast<int>(nDmg * 0.75);
			}
			else
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			

			OktayDamageSingle(Target, nDmg, 16);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		else
		{
			_ShowBattleMiss(Target, 16);
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
	DecreaseMana(nMana);
}
#endif