#include "CArcher.h"

void __fastcall CArcher::BlowUpArrow(int pPacket, int pPos)
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BLOWUPARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_PLAYER)
		DamageSingle(ISkill, Target, false, true);
	else if (Target.GetType() == TYPE_MONSTER)
	{
		int Around = Target.GetObjectListAround(1);
		DamageMultiple(ISkill, Target, Around, 1, false, true);
	}



	//ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BLOWUPARROW));
	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0; char bType = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	//int nMana = ISkill.DecreaseMana();

	////if (bType == 0 && nTargetID)
	////	pTarget = CPlayer::FindPlayer(nTargetID);

	////if (bType == 1 && nTargetID)
	////	pTarget = CMonster::FindMonster(nTargetID);

	//RAII raii(nTargetID, bType);

	////if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	//if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	//	return;


	//ICharacter Target(raii.pTarget);

	//if (!IsInRange(Target, 20))
	//{
	//	CSkill::ObjectRelease(Target.GetOffset(), (int)raii.pTarget + 352);
	//	return;
	//}

	//if (bType == 0)
	//{

	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		if (CheckHit(Target, 14))
	//		{
	//			//int nDmg = (GetAttack() * BlowUpBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvP) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvP);
	//			int nDmg = 5000;
	//			OktayDamageSingle(Target, nDmg, 14);
	//			SetDirection(Target);
	//			_ShowBattleAnimation(Target, 14);
	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 14);
	//		}
	//	}
	//}
	//if (bType == 1)
	//{
	//	int Around = Target.GetObjectListAround(3);
	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{

	//		if (CheckHit(Target, 14))
	//		{

	//			//int nDmge = (GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
	//			int nDmge = 5000;
	//			OktayDamageSingle(Target, nDmge, 14);
	//			SetDirection(Target);
	//			_ShowBattleAnimation(Target, 14);

	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 14);
	//		}
	//	}
	//	int i = 0;
	//	while (Around && i < 2)
	//	{

	//		ICharacter Object((void*)*(DWORD*)Around);

	//		if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
	//		{

	//			if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
	//			{

	//				if (CheckHit(Object, 14))
	//				{
	//					//int nDmg = (GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
	//					int nDmg = 5000;
	//					OktayDamageSingle(Object, nDmg, 14);
	//					_ShowBattleAnimation(Object, 14);
	//					i++;
	//				}
	//				else
	//				{
	//					_ShowBattleMiss(Object, 14);
	//					i++;
	//				}
	//			}

	//		}
	//		Around = CBaseList::Pop((void*)Around);
	//	}
	//}
	//DecreaseMana(nMana);
}

void __fastcall CArcher::FlamyArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FLAMYARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);



	//ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FLAMYARROW));
	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0; char bType = 0; void* pTarget = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	//int nMana = ISkill.DecreaseMana();

	////if (bType == 0 && nTargetID)
	////	pTarget = CPlayer::FindPlayer(nTargetID);

	////if (bType == 1 && nTargetID)
	////	pTarget = CMonster::FindMonster(nTargetID);

	//RAII raii(nTargetID, bType);

	////if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	//if (raii.pTarget == GetOffset() || GetCurMp() < nMana)
	//	return;

	//ICharacter Target(raii.pTarget);

	////PvP
	//if (bType == 0)
	//{
	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		if (CheckHit(Target, 20))
	//		{
	//			//int nDmge = (GetAttack() * FABaseDamageMultiPvP) + (CChar::GetDex((int)GetOffset()) * FAAGiMultiPvP) + (CChar::GetStr((int)GetOffset()) * FAStrMultiPvP) + (ISkill.GetGrade() * FAPerGradeMultiPvP);
	//			int nDmge = 5000;
	//			//Target.Buff(791, FADurationBase + ISkill.GetGrade() * FADurationPerGrade, (FADoTBasePvP + (ISkill.GetGrade() * FADoTPerGradePvP)));
	//			Target.Buff(791, 500, 10);
	//			Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
	//			OktayDamageSingle(Target, nDmge, 6);
	//			SetDirection(Target);
	//			_ShowBattleAnimation(Target, 6);
	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 6);
	//		}

	//	}
	//}
	////PvE
	//if (bType == 1)
	//{

	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		if (CheckHit(Target, 20))
	//		{
	//			//int nDmg = (GetAttack() * FABaseDamageMultiPvE) + (CChar::GetDex((int)GetOffset()) * FAAGiMultiPvE) + (CChar::GetStr((int)GetOffset()) * FAStrMultiPvE) + (ISkill.GetGrade() * FAPerGradeMultiPvE);
	//			//Target.Buff(29, FADurationBase + ISkill.GetGrade() * FADurationPerGrade, (FADoTBasePvE + (ISkill.GetGrade() * FADoTPerGradePvE)));
	//			int nDmg = 5000;
	//			Target.Buff(791, 500, 10);
	//			Target.AddFxToTarget("davi_M564_71", 1, 0, 0);
	//			OktayDamageSingle(Target, nDmg, 6);
	//			SetDirection(Target);
	//			_ShowBattleAnimation(Target, 6);
	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 6);
	//		}

	//	}
	//}
	//DecreaseMana(nMana);
}

void __fastcall CArcher::MuscleSolidation()
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MUSCLESOLIDATION));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
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
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_PASSIVEATTACK));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);
	//ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_PASSIVEATTACK));
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

	//if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//{
	//	if (CheckHit(Target, 20))
	//	{
	//		//Target.Buff(8, PassiveAttackBaseFreezeTime + PassiveAttackPerGradeFreezeTime * ISkill.GetGrade(), 0);
	//		Target.Buff(8, 10, 0);
	//		SetDirection(Target);
	//		_ShowBattleAnimation(Target, 4);
	//	}
	//	else
	//	{
	//		_ShowBattleMiss(Target, 4);
	//	}
	//}
	//DecreaseMana(nMana);
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CArcher::BuffRemover(int pPacket, int pPos)
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BUFFREMOVER));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);


	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 0))
	{
		Target.CancelBuff(282);
		Target.CancelBuff(283);
		Target.CancelBuff(284);
		Target.CancelBuff(24);
		Target.CancelBuff(305);
		Target.CancelBuff(306);
		Target.CancelBuff(379);
		Target.CancelBuff(380);
		Target.CancelBuff(381);
		Target.CancelBuff(382);
		Target.CancelBuff(383);
		Target.CancelBuff(384);
	}
}

void __fastcall CArcher::FocusShot(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FOCUSSHOT));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);

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

void __fastcall CArcher::MysteriousArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MYSTERIOUSARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);

	//ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MYSTERIOUSARROW));

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


	//if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//{
	//	if (CheckHit(Target, 20))
	//	{
	//		//int nDmg = (GetAttack() * MABaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * MAAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * MAStrMultiPvE) + (ISkill.GetGrade() * MAPerGradeMultiPvE);
	//		int nDmg = 5000;
	//		if (Target.GetType() == 0)
	//		{
	//			//Target.Buff(39, MADoTDuration, MADoTPerGradePvP * ISkill.GetGrade());
	//			//nDmg = (GetAttack() * MABaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * MAAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * MAStrMultiPvP) + (ISkill.GetGrade() * MAPerGradeMultiPvP);
	//			Target.Buff(39, 10, 500);
	//			
	//		}
	//		if (Target.GetType() == 1)
	//		{
	//			//Target.Buff(39, MADoTDuration, MADoTPerGradePvE * ISkill.GetGrade());
	//			Target.Buff(39, 10,500);
	//		}
	//		OktayDamageSingle(Target, nDmg, 21);
	//		_ShowBattleAnimation(Target, 21);
	//	}
	//	else
	//	{
	//		_ShowBattleMiss(Target, 21);
	//	}
	//}
	//DecreaseMana(nMana);
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}



