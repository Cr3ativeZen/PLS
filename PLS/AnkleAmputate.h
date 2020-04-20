#ifndef ANKLEAMPUTATE_H
#define ANKLEAMPUTATE_H
void __fastcall AnkleAmputate(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(15);



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

		if (IsValid() && pTarget && nSkillGrade)
		{

			int nMana = (10 * nSkillGrade) + 45;
			ICharacter Target(pTarget);

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!CanAttack(GetOffset(), 0, (int)Target.GetOffset(), 0))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}



				DecreaseMana(nMana);
				Target.Buff(40, nSkillGrade * 3, -50);

				if (!Target.IsBuff(346))
					Target.SendGStateEx(Target.GetGStateEx() + 256);

				if (Target.GetType() == 0)
					Target.RemoveBuffIcon(0, 0, 0, 54);

				Target.Buff(346, nSkillGrade * 3, 0);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 15, nSkillGrade);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif