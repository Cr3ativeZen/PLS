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

void __fastcall CKnight::SpinSlash()
{
	int pSkill = GetSkillPointer(38);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = (xSkill.GetGrade() == 1) ? 209 : (200 + (xSkill.GetGrade() * 20));
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		if (GetCurMp() < nMana)
			return;

		if (IsValid() && CPlayer::IsWState((int)GetOffset(), 12))
		{
			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					/*int nDmg = static_cast<int>(((GetAttack() * SSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * SSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * SSStrMultiPvE) + (xSkill.GetGrade() * SSPerGradeMultiPvE)) * (0.5 + (GetDeathBlow() * 0.1)));

					if (IsBuff(69) && Object.GetType() == 1)
					{
						nDmg = nDmg + SSAdditonalDMG;
					}


					if (Object.GetType() == 0)
						nDmg = static_cast<int>((GetAttack() * SSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * SSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * SSStrMultiPvP) + (xSkill.GetGrade() * SSPerGradeMultiPvP) * (0.5 + (GetDeathBlow() * 0.1)));*/

					int nDmg = 5000;
					OktayDamageArea(Object, nDmg, 38);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			_ShowBattleAnimation(this, 38);
			RemoveDeathBlow(GetDeathBlow());
			DecreaseMana(nMana);
		}
	}
}
