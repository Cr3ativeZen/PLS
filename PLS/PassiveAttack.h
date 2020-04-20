#ifndef _PASSIVEATTACK_H
#define _PASSIVEATTACK_H
#include "ServerFunctions.h"
#include "PKKill.h"

void __fastcall PassiveAttack(int pSkill, void *pPlayer, int pPacket, int pPos)
{
	ISkill ISkill((void*)pSkill);
	ICharacter IPlayer(pPlayer);
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

		if (IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				Target.Buff(8, PassiveAttackBaseFreezeTime + PassiveAttackPerGradeFreezeTime * ISkill.GetGrade(), 0);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 4);
			}
			else
			{
				_ShowBattleMiss(Target, 4);
			}
		}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
#endif