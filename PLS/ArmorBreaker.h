#ifndef ARMORBREAKER_H
#define ARMORBREAKER_H
#include "CanAttack.h"
void __fastcall ArmorBreaker(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(22);

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

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			if (pTarget == IPlayer.GetOffset())
				return;

			int nMana = (30 * nSkillGrade) + 35;
			ICharacter Target(pTarget);

			if (IPlayer.GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!CanAttack(IPlayer.GetOffset(), 0, (int)Target.GetOffset(), 0))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!IPlayer.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				IPlayer.DecreaseMana(nMana);

				if (!Target.IsBuff(342))
				{
					Target.SendGStateEx(Target.GetGStateEx() + 131072);
					Target.Buff(342, ABreakerDuration+(ABreakerDurationPerGrade*nSkillGrade), 0);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 22, nSkillGrade);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif