#ifndef _PASSIVEATTACK_H
#define _PASSIVEATTACK_H
#include "ServerFunctions.h"
#include "PKKill.h"

void __fastcall PassiveAttack(IChar IPlayer,int pPacket, int pPos)
{

	ISkill ISkill((void*)IPlayer.GetSkillPointer(4));
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

	if (bType >= 2)
		return;

	IChar Target(pTarget);

	if (nTargetID)
	{

		if (IPlayer.IsValid())
		{
			if (IPlayer.CheckHit(Target, 4))
			{
				Target.Buff(8, PassiveAttackBaseFreezeTime + PassiveAttackPerGradeFreezeTime * ISkill.GetGrade(), 0);
				IPlayer._ShowBattleAnimation(Target, 4);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 4);
				IPlayer.DecreaseMana(nMana);
			}
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif