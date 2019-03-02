#ifndef _SHIELDATTACK_H
#define _SHIELDATTACK_H
#include "ServerFunctions.h"

void __fastcall ShieldAttack(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);
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

		if (IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 15))
			{
				Target.Buff(7, ShieldAttackBaseStunTime, 0);
				IPlayer.OktayDamageSingle(Target,IPlayer.GetAttack()*ShieldAttackDamageMulti , 15);
				IPlayer._ShowBattleAnimation(Target, 15);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 15);
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			}
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif