#include "CKnight.h"

void __fastcall CKnight::PowerfulUpwardSlash(int pSkill, int pPacket, int pPos)
{
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;


	ICharacter Target(pTarget);

	if (!IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		return;
	}

	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (CheckHit(Target, 20))
		{
			//int nDmg = (GetAttack() * PUSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * PUSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * PUSStrMultiPvE) + (nSkillGrade * PUSPerGradeMultiPvE);
			int nDmg = 5000;
			if (Target.GetType() == 0)
				nDmg = 5000;

			OktayDamageSingle(Target, nDmg, 16);
			_ShowBattleAnimation(Target, 16);
			DecreaseMana(nMana);
			AddDeathBlow(1);

		}
		else
		{
			_ShowBattleMiss(Target, 16);
			DecreaseMana(nMana);
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
