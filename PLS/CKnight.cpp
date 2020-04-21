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

void __fastcall CKnight::PowerfulWideningWound(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_KNIGHT_POWERFULWIDENINGWOUND);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = xSkill.GetGrade() + 30;

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

		if (pTarget && xSkill.GetGrade() && IsValid())
		{
			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (CheckHit(Target, 10 + ((GetLevel() / 20) + xSkill.GetGrade() * 3)))
				{
					int nDmg = 5000;
					/*int nDmg = (GetAttack() * PWWBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * PWWAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * PWWStrMultiPvE) + (xSkill.GetGrade() * PWWPerGradeMultiPvE);

					if (Target.GetType() == 0)
						nDmg = (GetAttack() * PWWBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * PWWAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * PWWStrMultiPvP) + (xSkill.GetGrade() * PWWPerGradeMultiPvP);*/


					OktayDamageSingle(Target, nDmg, 41);

					if (IsOnline() && IsValid() && Target.IsOnline() && Target.IsValid() && Target.GetType() == 1 && Target.GetCurHp() > 0 && Target.IsMobAggressive() && Target.IsMobHaveTarget())
					{
						//CMonsterReal::AddHostility(Target.GetOffset(), (int)GetOffset(), nDmg * PWWHostilityMultiplier, 0);
						CMonsterReal::AddHostility(Target.GetOffset(), (int)GetOffset(), nDmg * 500, 0);
					}
				}
				else
				{
					_ShowBattleMiss(Target, 41);
				}

				SetDirection(Target);
			}
		}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		DecreaseMana(nMana);
	}
}

void __fastcall CKnight::ProvocationOfBlow(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_KNIGHT_PROVOCATIONOFBLOW);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0, nMana = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			if (nSkillGrade <= 1)
				nMana = 220;
			else if (nSkillGrade == 2)
				nMana = 242;
			else if (nSkillGrade == 3)
				nMana = 266;
			else if (nSkillGrade == 4)
				nMana = 292;
			else if (nSkillGrade >= 5)
				nMana = 320;

			if (IsOnline() && CPlayer::IsWState((int)GetOffset(), 12))
				return;

			if (GetCurMp() < nMana)
				return;

			if (pTarget == GetOffset())
				return;

			if (pTarget && IsOnline())
			{
				ICharacter Target(pTarget);

				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int Around = GetObjectListAround(2);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = 5000;

						/*int nDmg = (GetAttack() * PoBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * PoBAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * PoBStrMultiPvE) + (nSkillGrade * PoBPerGradeMultiPvE);

						if (Object.GetType() == 0)
							nDmg = (GetAttack() * PoBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * PoBAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * PoBStrMultiPvP) + (nSkillGrade * PoBPerGradeMultiPvP);

						if (Object.GetType() == 1 && IsBuff(284))
						{
							nDmg *= (PoBDmgPercentIncreasePDPvE / 100);
						}*/

						OktayDamageArea(Object, nDmg, 42);

						if (IsOnline() && IsValid() && Object.IsOnline() && Object.IsValid() && Object.GetType() == 1 && Object.GetCurHp() > 0 && Object.IsMobAggressive() && Object.IsMobHaveTarget())
						{
							//CMonsterReal::AddHostility(Object.GetOffset(), (int)GetOffset(), nDmg * PoBHostilityMultiplier, 0);
							CMonsterReal::AddHostility(Object.GetOffset(), (int)GetOffset(), nDmg * 500, 0);
						}
							
					}

					Around = CBaseList::Pop((void*)Around);
				}

				_ShowBattleAnimation(Target, 42);
				SetDirection(Target);
				DecreaseMana(nMana);
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			}

		}
	}
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
