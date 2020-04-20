#ifndef _SHIELDATTACK_H
#define _SHIELDATTACK_H
#include "ServerFunctions.h"

void __fastcall ShieldAttack(int pSkill, void *pPlayer, int pPacket, int pPos)
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


	if (bType == 1)
	{
		SystemMessage("You cannot attack player with Shield Attack", TEXTCOLOR_RED);
	}
	if (bType == 0)
	{
		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 15))
			{
				Target.Buff(7, ShieldAttackBaseStunTime, 0);

				OktayDamageSingle(Target, GetAttack()*ShieldAttackDamageMulti, 15);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 15);
			}
			else
			{
				_ShowBattleMiss(Target, 15);
			}
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif