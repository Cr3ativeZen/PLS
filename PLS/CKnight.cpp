
#include "CKnight.h"


CKnight::CKnight() : ICharacter()
{
}

CKnight::CKnight(void* offset) : ICharacter(offset)
{
}

CKnight::~CKnight()
{
}


//void __fastcall CKnight::PowerfulUpwardSlash(void* pSkill, void* pPacket, void* pPos)
//{
//	ISkill skill(pSkill);
//
//	int skillGrade = skill.GetGrade();
//
//	if (!skillGrade)
//		return;
//
//	int nTargetID = 0; char bType = 0; void* pTarget = 0;
//	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
//	int nMana = skill.DecreaseMana();
//
//	if (bType == 0 && nTargetID)
//		pTarget = CPlayer::FindPlayer(nTargetID);
//
//	if (bType == 1 && nTargetID)
//		pTarget = CMonster::FindMonster(nTargetID);
//
//
//	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
//		return;
//
//
//	ICharacter target(pTarget);
//
//	if (!IsInRange(target, 20))
//	{
//		CSkill::ObjectRelease(target.GetOffset(), (int)pTarget + 352);
//		return;
//	}
//
//	if (IsValid() && target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)target.GetOffset(), 2))
//	{
//		if (CheckHit(target, 20))
//		{
//			int nDmg = (GetAttack() * PUSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * PUSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * PUSStrMultiPvE) + (skillGrade * PUSPerGradeMultiPvE);
//
//			if (target.GetType() == 0)
//				nDmg = (GetAttack() * PUSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * PUSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * PUSStrMultiPvP) + (skillGrade * PUSPerGradeMultiPvP);
//
//			OktayDamageSingle(target, nDmg, 16);
//			_ShowBattleAnimation(target, 16);
//			DecreaseMana(nMana);
//			AddDeathBlow(1);
//		}
//		else
//		{
//			_ShowBattleMiss(target, 16);
//			DecreaseMana(nMana);
//		}
//	}
//
//	CSkill::ObjectRelease(target.GetOffset(), (int)pTarget + 352);
//}
