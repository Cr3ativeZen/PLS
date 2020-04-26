#include "CArcher.h"

void __fastcall CArcher::BlowUpArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BLOWUPARROW));
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	//if (bType == 0 && nTargetID)
	//	pTarget = CPlayer::FindPlayer(nTargetID);

	//if (bType == 1 && nTargetID)
	//	pTarget = CMonster::FindMonster(nTargetID);

	RAII raii(nTargetID, bType);

	//if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
		return;


	ICharacter Target(raii.pTarget);

	if (!IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)raii.pTarget + 352);
		return;
	}

	if (bType == 0)
	{

		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 14))
			{
				//int nDmg = (GetAttack() * BlowUpBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvP) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvP);
				int nDmg = 5000;
				OktayDamageSingle(Target, nDmg, 14);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 14);
			}
			else
			{
				_ShowBattleMiss(Target, 14);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(3);
		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{

			if (CheckHit(Target, 14))
			{

				//int nDmge = (GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
				int nDmge = 5000;
				OktayDamageSingle(Target, nDmge, 14);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 14);

			}
			else
			{
				_ShowBattleMiss(Target, 14);
			}
		}
		int i = 0;
		while (Around && i < 2)
		{

			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (CheckHit(Object, 14))
					{
						//int nDmg = (GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
						int nDmg = 5000;
						OktayDamageSingle(Object, nDmg, 14);
						_ShowBattleAnimation(Object, 14);
						i++;
					}
					else
					{
						_ShowBattleMiss(Object, 14);
						i++;
					}
				}

			}
			Around = CBaseList::Pop((void*)Around);
		}
	}
	DecreaseMana(nMana);
}

void __fastcall CArcher::FlamyArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FLAMYARROW));
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	//if (bType == 0 && nTargetID)
	//	pTarget = CPlayer::FindPlayer(nTargetID);

	//if (bType == 1 && nTargetID)
	//	pTarget = CMonster::FindMonster(nTargetID);

	RAII raii(nTargetID, bType);

	//if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter Target(raii.pTarget);

	//PvP
	if (bType == 0)
	{
		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				//int nDmge = (GetAttack() * FABaseDamageMultiPvP) + (CChar::GetDex((int)GetOffset()) * FAAGiMultiPvP) + (CChar::GetStr((int)GetOffset()) * FAStrMultiPvP) + (ISkill.GetGrade() * FAPerGradeMultiPvP);
				int nDmge = 5000;
				//Target.Buff(791, FADurationBase + ISkill.GetGrade() * FADurationPerGrade, (FADoTBasePvP + (ISkill.GetGrade() * FADoTPerGradePvP)));
				Target.Buff(791, 500, 10);
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				OktayDamageSingle(Target, nDmge, 6);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 6);
			}
			else
			{
				_ShowBattleMiss(Target, 6);
			}

		}
	}
	//PvE
	if (bType == 1)
	{

		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (CheckHit(Target, 20))
			{
				//int nDmg = (GetAttack() * FABaseDamageMultiPvE) + (CChar::GetDex((int)GetOffset()) * FAAGiMultiPvE) + (CChar::GetStr((int)GetOffset()) * FAStrMultiPvE) + (ISkill.GetGrade() * FAPerGradeMultiPvE);
				//Target.Buff(29, FADurationBase + ISkill.GetGrade() * FADurationPerGrade, (FADoTBasePvE + (ISkill.GetGrade() * FADoTPerGradePvE)));
				int nDmg = 5000;
				Target.Buff(791, 500, 10);
				Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
				OktayDamageSingle(Target, nDmg, 6);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 6);
			}
			else
			{
				_ShowBattleMiss(Target, 6);
			}

		}
	}
	DecreaseMana(nMana);
}

void __fastcall CArcher::MuscleSolidation()
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MUSCLESOLIDATION));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());


	Buff(10, 900, 0);
	Buff(500, 910, static_cast<int>(GetMinPhyAttack() * 0.10));
	Buff(501, 910, static_cast<int>(GetMaxPhyAttack() * 0.10));

	AddMinPhysAttack(static_cast<int>(GetMinPhyAttack() * 0.10));
	AddMaxPhysAttack(static_cast<int>(GetMaxPhyAttack() * 0.10));
}

void __fastcall CArcher::PassiveAttack(int pPacket, int pPos)
{
	//SkillOnTarget(CLASS_ARCHER, SKILL_ARCHER_PASSIVEATTACK, pPacket, pPos);
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_PASSIVEATTACK));
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

	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (CheckHit(Target, 20))
		{
			//Target.Buff(8, PassiveAttackBaseFreezeTime + PassiveAttackPerGradeFreezeTime * ISkill.GetGrade(), 0);
			Target.Buff(8, 10, 0);
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

void __fastcall CArcher::BuffRemover(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BUFFREMOVER));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0;
	char bType = 0;
	void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);

	if (pTarget && ITarget.IsValid() && IsValid())
	{
		ITarget.CancelBuff(282);
		ITarget.CancelBuff(283);
		ITarget.CancelBuff(284);
		ITarget.CancelBuff(24);
		ITarget.CancelBuff(305);
		ITarget.CancelBuff(306);
		ITarget.CancelBuff(379);
		ITarget.CancelBuff(380);
		ITarget.CancelBuff(381);
		ITarget.CancelBuff(382);
		ITarget.CancelBuff(383);
		ITarget.CancelBuff(384);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall CArcher::FocusShot(int pPacket, int pPos)
{
	//ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BUFFREMOVER));

	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0; char bType = 0; void* pTarget = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	//int nMana = ISkill.DecreaseMana();

	//if (bType == 0 && nTargetID)
	//	pTarget = CPlayer::FindPlayer(nTargetID);

	//if (bType == 1 && nTargetID)
	//	pTarget = CMonster::FindMonster(nTargetID);


	//if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
	//	return;


	//ICharacter Target(pTarget);

	//if (pTarget && Target.IsValid() && IsValid() && nTargetID != GetID())
	//{

	//	SetDirection(Target);
	//	if (CheckHit(Target, 20))
	//	{
	//		int nTime = GetTickCount() - CheckFocus[GetPID()];

	//		//int nDmg = (GetAttack() * FSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * FSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * FSStrMultiPvE) + (nSkillGrade * FSPerGradeMultiPvE);

	//		//if (Target.GetType() == 0)
	//		//	nDmg = (GetAttack() * FSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * FSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * FSStrMultiPvP) + (nSkillGrade * FSPerGradeMultiPvP);

	//		int nDmg = 5000;

	//		if (nTime > 1000)
	//		{
	//			if (nTime >= 2900)
	//				nDmg = nDmg * 1;
	//			else if (nTime >= 2600)
	//				nDmg = static_cast<int>(nDmg * 0.9);
	//			else if (nTime >= 2300)
	//				nDmg = static_cast<int>(nDmg * 0.85);
	//			else if (nTime >= 1700)
	//				nDmg = static_cast<int>(nDmg * 0.8);
	//			else
	//				nDmg = static_cast<int>(nDmg * 0.75);
	//		}
	//		else
	//		{
	//			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//			return;
	//		}


	//		OktayDamageSingle(Target, nDmg, 16);
	//		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//	}
	//	else
	//	{
	//		_ShowBattleMiss(Target, 16);
	//		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//	}
	//}
	//DecreaseMana(nMana);
}

void __fastcall CArcher::LifeAbsorption(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_LIFEABSORPTION));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.GetGrade() * 6 + 20;
	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);


	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget(pTarget);

	if (pTarget && ITarget.IsValid() && IsValid() && nTargetID != GetID())
	{

		//int nDmg = (GetAttack() * LAbsBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * LAbsAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * LAbsStrMultiPvE) + (nSkillGrade * LAbsPerGradeMultiPvE);
		int nDmg = 5000;
		//if (ITarget.GetType() == 0)
		//	nDmg = (GetAttack() * LAbsBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * LAbsAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * LAbsStrMultiPvP) + (nSkillGrade * LAbsPerGradeMultiPvP);
			


		if (CheckHit(ITarget.GetOffset(), 50))
		{
			unsigned int GetAttackSpeed = CChar::GetASpeed((int)GetOffset());
			unsigned int GetASpeedValue = GetAttackSpeed;
			int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
			TypeKind = (*(int(__thiscall**)(LONG, void*))(*(DWORD*)ITarget.GetOffset() + 148))((int)ITarget.GetOffset(), GetOffset());
			Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), GetOffset(), GetASpeedValue * nDmg / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
			GetType = Check | 2 * DamageArgument | 4 * TypeKind;

			if (NormalDamage > 0)
				//IncreaseHp(NormalDamage * LAbsHealPerGrade * nSkillGrade / 100);
				IncreaseHp(500);

			CChar::WriteInSight(GetOffset(), 63, "bddbbwwb", ISkill.GetIndex(), GetID(), ITarget.GetID(), 1, 1, NormalDamage, 0, GetType);
		}
		else
		{
			_ShowBattleMiss(ITarget, ISkill.GetIndex());
		}

		DecreaseMana(nMana);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall CArcher::MysteriousArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MYSTERIOUSARROW));

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


	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	{
		if (CheckHit(Target, 20))
		{
			//int nDmg = (GetAttack() * MABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * MAAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * MAStrMultiPvE) + (ISkill.GetGrade() * MAPerGradeMultiPvE);
			int nDmg = 5000;
			if (Target.GetType() == 0)
			{
				//Target.Buff(39, MADoTDuration, MADoTPerGradePvP * ISkill.GetGrade());
				//nDmg = (GetAttack() * MABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * MAAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * MAStrMultiPvP) + (ISkill.GetGrade() * MAPerGradeMultiPvP);
				Target.Buff(39, 10, 500);
				
			}
			if (Target.GetType() == 1)
			{
				//Target.Buff(39, MADoTDuration, MADoTPerGradePvE * ISkill.GetGrade());
				Target.Buff(39, 10,500);
			}
			OktayDamageSingle(Target, nDmg, 21);
			_ShowBattleAnimation(Target, 21);
		}
		else
		{
			_ShowBattleMiss(Target, 21);
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CArcher::ContinueArrowExplosion()
{
	if (IsValid())
	{
		CancelBuff(300);
		void* pTarget = IConfig::CheckContinueSkill.find(GetPID())->second.PlayerTarget;
		int nSkillGrade = IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && pTarget && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount--;
			ICharacter Target(pTarget);

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 300))
				{
					ResetContinueSkill();
					CancelBuff(BUFF_ARROWEXPLOSIONUSE);
					return;
				}

				int Around = Target.GetObjectListAround(3);
				Target.AddFxToTarget("davi_ef131_05", 1, 0, 0);
				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						//int nDmg = (GetAttack() * AEBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * AEAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * AEStrMultiPvE) + (nSkillGrade * AEPerGradeMultiPvE);

						int nDmg = 5000;
						//if (Object.GetType() == 0)
							//nDmg = (GetAttack() * AEBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * AEAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * AEStrMultiPvP) + (nSkillGrade * AEPerGradeMultiPvP);


						OktayDamageArea(Object, nDmg, 49);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}

	ResetContinueSkill();
	CancelBuff(BUFF_ARROWEXPLOSIONUSE);
	return;
}

void __fastcall CArcher::VirulentArrow(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_ARCHER_VIRULENTARROW);

	if (IsValid() && pSkill)
	{
		ISkill ISkill((void*)pSkill);
		int nSkillGrade = ISkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((nSkillGrade - 1) + 25) * nSkillGrade) + 230) * 0.98);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && nSkillGrade && IsValid())
		{
			ICharacter Target(pTarget);

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
				if (!IsInRange(Target,300))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int Item = CPlayer::FindItem(Offset, 360, 2);

				if (Item)
					(*(int (__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item,GetOffset(),9,-2);
				else
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				DecreaseMana(nMana);
				_ShowBattleAnimation(Target, SKILL_ARCHER_VIRULENTARROW);
				SetDirection(Target);
				int Around = Target.GetObjectListAround(4);
				//int nDmg = nSkillGrade * VAPerGradeDoTPvE + VABaseDoTPvE;
				int nDmg = 5000;
				while(Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{

						//OktayDamageArea(Object, CalculateFormula(GetClass(), ISkill.GetIndex(), ISkill.GetGrade(),Object.GetType()) , SKILL_ARCHER_VIRULENTARROW);

						//Object.Buff(11, VADuration, nDmg);
						Object.Buff(11, 10, nDmg);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}

}

void __fastcall CArcher::CombativeSpirit(int pPacket, int pPos)
{
		int pSkill = GetSkillPointer(SKILL_ARCHER_COMBATIVESPIRIT);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);	
		
		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset())
			return;

		if (IsValid() && pTarget && nSkillGrade)
		{
			ICharacter Target(pTarget);
			int nMana = (int)(((((nSkillGrade-1)+20) * nSkillGrade)+200) * 1.85);

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (GetCurMp() < nMana)
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

				DecreaseMana(nMana);


				SetDirection(Target);
				_ShowBattleAnimation(Target, SKILL_ARCHER_COMBATIVESPIRIT);
				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = 5000;
						/*int nDmg = (GetAttack()*CSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*CSAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*CSStrMultiPvE) + (nSkillGrade*CSPerGradeMultiPvE);


						if (Target.GetType() == 0)
							nDmg = (GetAttack()*CSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*CSAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*CSStrMultiPvP + (nSkillGrade*CSPerGradeMultiPvP));*/

						if (Object.GetX() <= max(GetX(), Target.GetX()) && Object.GetX() >= min(GetX(), Target.GetX()) && Object.GetY() <= max(GetY(), Target.GetY()) && Object.GetY() >= min(GetY(), Target.GetY()))
							//OktayDamageArea(Object, nDmg, SKILL_ARCHER_COMBATIVESPIRIT);
							OktayDamageArea(Object, nDmg, SKILL_ARCHER_COMBATIVESPIRIT);
					}

					Around = CBaseList::Pop((void*)Around);
				}

			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}

	}
}

void __fastcall CArcher::ContinueArrowRain()
{
	if (IsValid())
	{
		int nSkillGrade = IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = IConfig::CheckContinueSkill.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ARROWRAINUSE);
				return;
			}

			if (IsMoved(IConfig::CheckContinueSkill.find(GetPID())->second.PlayerX, IConfig::CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ARROWRAINUSE);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while(Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = 5000;
					//int nDmg = (GetAttack()*ARBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvE) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvE) + (nSkillGrade*ARPerGradeMultiPvE);

					//if (Object.GetType() == 0)
					//	nDmg = (GetAttack()*ARBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset())*ARAgiMultiPvP) + (CChar::GetStr((int)GetOffset())*ARStrMultiPvP) + (nSkillGrade*ARPerGradeMultiPvP);


					OktayDamageArea(Object,nDmg,SKILL_ARCHER_ARROWRAIN);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 900;

			if (IsOnline() && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ARROWRAINUSE);
			}

			return;
		}
	}

	ResetContinueSkill();
	CancelBuff(5565);
	return;
}

void __fastcall CArcher::ArrowRain(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_ARCHER_ARROWRAIN);

	if (IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(5565, 10, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(this, SKILL_ARCHER_ARROWRAIN);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(567,GetMap(),(int)GetSetXY,1,(int)GetOffset(),0,10000);
			delete[] GetSetXY;
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillID = SKILL_ARCHER_ARROWRAIN;
			IConfig::CheckContinueSkill[GetPID()].PlayerTarget = (void*)check;
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount = 10;
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			IConfig::CheckContinueSkill[GetPID()].PlayerX = GetX();
			IConfig::CheckContinueSkill[GetPID()].PlayerY = GetY();
		}
		ContinueArrowRain();
	}
}

void __fastcall CArcher::ArrowExplosion(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_ARCHER_ARROWEXPLOSION);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 20 + (GetLevel() * 4);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (IsValid() && pTarget && nSkillGrade)
		{
			ICharacter Target(pTarget);

			if (pTarget == GetOffset())
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (GetCurMp() < nMana)
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 300))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				DecreaseMana(nMana);
				SetDirection(Target);
				_ShowBattleAnimation(Target, 49);
				Buff(300, 5, 0);
				Buff(5566, 4, 0);
				Target.AddFxToTarget("davi_ef131_04", 1, 0, 0);
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillID = 49;
				IConfig::CheckContinueSkill[GetPID()].PlayerTarget = Target.GetOffset();
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillGrade = nSkillGrade;
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount = 1;
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 3000;

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() && Target.GetMobTanker() != (int)GetOffset())
					Target.SetMobHostility(0);

				if (Target.GetType() == 1)
					OktayDamageSingle(Target, CTools::Rate(500, 750), 42);


				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() == (int)GetOffset())
					Target.SetMobHostility(25000);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}

}
