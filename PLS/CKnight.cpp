#include "CKnight.h"

void __fastcall CKnight::BrutalAttack(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_BRUTALATTACK));
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
			int nDmg = 5000;

			/*int nDmg = static_cast<int>(((GetAttack() * BRUTBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BRUTAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BRUTStrMultiPvE) + (nSkillGrade * BRUTPerGradeMultiPvE)) * (0.5 + (GetDeathBlow() * 0.1)));

			if (Target.GetType() == 0)
				nDmg = static_cast<int>(((GetAttack() * BRUTBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * BRUTAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * BRUTStrMultiPvP) + (nSkillGrade * BRUTPerGradeMultiPvP)) * (0.5 + (GetDeathBlow() * 0.1)));*/


			OktayDamageSingle(Target, nDmg, 17);
			_ShowBattleAnimation(Target, 17);
			RemoveDeathBlow(GetDeathBlow());

		}
		else
		{
			_ShowBattleMiss(Target, 17);
			RemoveDeathBlow(GetDeathBlow());
		}
	}

	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::HalfSwing( int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_HALFSWING));
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
		int Around = Target.GetObjectListAround(1);

		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);
			if (Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				int nDmg = 5000;
				/*int nDmg = (GetAttack() * HSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * HSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * HSStrMultiPvE) + (nSkillGrade * HSPerGradeMultiPvE);

				if (Object.GetType() == 0)
				{
					nDmg = (GetAttack() * HSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * HSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * HSStrMultiPvP) + (nSkillGrade * HSPerGradeMultiPvP);
				}*/

				OktayDamageArea(Object, nDmg, 25);
			}
			Around = CBaseList::Pop((void*)Around);
		}

		_ShowBattleAnimation(GetOffset(), 25);
		AddDeathBlow(1);
	}

	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::LightningSlash(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_LIGHTNINGSLASH));

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


	if (bType == 0)
	{

		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmg = 5000;
				//int nDmg = (GetAttack() * LSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvP) + (ISkill.GetGrade() * LSPerGradeMultiPvP);
				SetDirection(Target);
				OktayDamageSingle(Target, nDmg, 3);
				_ShowBattleAnimation(Target, 3);
			}
			else
			{
				_ShowBattleMiss(Target, 3);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(1);
		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				int nDmge = 5000;
				//int nDmge = (GetAttack() * LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvE) + (ISkill.GetGrade() * LSPerGradeMultiPvE);
				SetDirection(Target);
				OktayDamageSingle(Target, nDmge, 3);
				_ShowBattleAnimation(Target, 3);
			}
			else
			{
				_ShowBattleMiss(Target, 3);
			}
		}
		int i = 0;
		//while (Around && i < LSPvEMaxHits - 1)
		while (Around && i < 2)
		{

			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (CheckHit(Object, 20))
					{
						int nDmg = 5000;
						//int nDmg = (GetAttack() * LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvE) + (ISkill.GetGrade() * LSPerGradeMultiPvE);
						OktayDamageSingle(Object, nDmg, 3);
						_ShowBattleAnimation(Object, 3);
						i++;
					}
					else
					{
						_ShowBattleMiss(Object, 3);
						i++;
					}
				}

			}
			Around = CBaseList::Pop((void*)Around);
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::PowerfulUpwardSlash(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_SPINSLASH));
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
	int pSkill = GetSkillPointer(SKILL_KNIGHT_SPINSLASH);

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

			_ShowBattleAnimation(GetOffset(), 38);
			RemoveDeathBlow(GetDeathBlow());
			DecreaseMana(nMana);
		}
	}
}
