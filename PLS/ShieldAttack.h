#ifndef _SHIELDATTACK_H
#define _SHIELDATTACK_H
#include "ServerFunctions.h"

void __fastcall ShieldAttack(IChar IPlayer, int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(15));
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


	if (bType == 1 && nTargetID)
	{
		IPlayer.SystemMessage("You cannot attack player with Shield Attack", TEXTCOLOR_RED);
		return;
	}
	if (nTargetID)
	{

		if (IPlayer.IsValid())
		{
			if (IPlayer.CheckHit(Target, 15))
			{
				Target.Buff(7, ShieldAttackBaseStunTime, 0);

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 15);
				IPlayer.OktayDamageSingle(Target, IPlayer.GetAttack()*ShieldAttackDamageMulti, 15);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleMiss(Target, 15);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			}
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif