#include "CKnight.h"

void __fastcall CKnight::BrutalAttack(int pPacket, int pPos)
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_BRUTALATTACK));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target,false,true);




	//ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_BRUTALATTACK));
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

	//if (!IsInRange(Target, 20))
	//{
	//	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//	return;
	//}

	//if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//{
	//	if (CheckHit(Target, 20))
	//	{
	//		int nDmg = 5000;

	//		/*int nDmg = static_cast<int>(((GetAttack() * BRUTBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * BRUTAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * BRUTStrMultiPvE) + (nSkillGrade * BRUTPerGradeMultiPvE)) * (0.5 + (GetDeathBlow() * 0.1)));

	//		if (Target.GetType() == 0)
	//			nDmg = static_cast<int>(((GetAttack() * BRUTBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * BRUTAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * BRUTStrMultiPvP) + (nSkillGrade * BRUTPerGradeMultiPvP)) * (0.5 + (GetDeathBlow() * 0.1)));*/


	//		OktayDamageSingle(Target, nDmg, 17);
	//		_ShowBattleAnimation(Target, 17);
	//		RemoveDeathBlow(GetDeathBlow());

	//	}
	//	else
	//	{
	//		_ShowBattleMiss(Target, 17);
	//		RemoveDeathBlow(GetDeathBlow());
	//	}
	//}

	//DecreaseMana(nMana);
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::HalfSwing( int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_HALFSWING));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	int Around = Target.GetObjectListAround(1);

	DamageMultiple(ISkill, Target, Around, 999,true,false);

}

void __fastcall CKnight::LightningSlash(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_LIGHTNINGSLASH));

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
		DamageMultiple(ISkill, Target, Around, 1, false,true);
	}




	//ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_LIGHTNINGSLASH));

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


	//if (bType == 0)
	//{

	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		if (CheckHit(Target, 20))
	//		{
	//			int nDmg = 5000;
	//			//int nDmg = (GetAttack() * LSBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvP) + (ISkill.GetGrade() * LSPerGradeMultiPvP);
	//			SetDirection(Target);
	//			OktayDamageSingle(Target, nDmg, 3);
	//			_ShowBattleAnimation(Target, 3);
	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 3);
	//		}
	//	}
	//}
	//if (bType == 1)
	//{
	//	int Around = Target.GetObjectListAround(1);
	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		if (CheckHit(Target, 20))
	//		{
	//			int nDmge = 5000;
	//			//int nDmge = (GetAttack() * LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvE) + (ISkill.GetGrade() * LSPerGradeMultiPvE);
	//			SetDirection(Target);
	//			OktayDamageSingle(Target, nDmge, 3);
	//			_ShowBattleAnimation(Target, 3);
	//		}
	//		else
	//		{
	//			_ShowBattleMiss(Target, 3);
	//		}
	//	}
	//	int i = 0;
	//	//while (Around && i < LSPvEMaxHits - 1)
	//	while (Around && i < 2)
	//	{

	//		ICharacter Object((void*)*(DWORD*)Around);

	//		if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
	//		{

	//			if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
	//			{

	//				if (CheckHit(Object, 20))
	//				{
	//					int nDmg = 5000;
	//					//int nDmg = (GetAttack() * LSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * LSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * LSStrMultiPvE) + (ISkill.GetGrade() * LSPerGradeMultiPvE);
	//					OktayDamageSingle(Object, nDmg, 3);
	//					_ShowBattleAnimation(Object, 3);
	//					i++;
	//				}
	//				else
	//				{
	//					_ShowBattleMiss(Object, 3);
	//					i++;
	//				}
	//			}

	//		}
	//		Around = CBaseList::Pop((void*)Around);
	//	}
	//}
	//DecreaseMana(nMana);
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::PowerfulUpwardSlash(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_POWERFULUPWARDSLASH));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target,false,true);

	

	//ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_POWERFULUPWARDSLASH));
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

	//if (!IsInRange(Target, 20))
	//{
	//	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//	return;
	//}

	//if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//{
	//	if (CheckHit(Target, 20))
	//	{
	//		//int nDmg = (GetAttack() * PUSBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * PUSAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * PUSStrMultiPvE) + (nSkillGrade * PUSPerGradeMultiPvE);
	//		int nDmg = 5000;
	//		if (Target.GetType() == 0)
	//			nDmg = 5000;

	//		OktayDamageSingle(Target, nDmg, 16);
	//		_ShowBattleAnimation(Target, 16);
	//		DecreaseMana(nMana);
	//		AddDeathBlow(1);

	//	}
	//	else
	//	{
	//		_ShowBattleMiss(Target, 16);
	//		DecreaseMana(nMana);
	//	}
	//}
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::Sacrifice(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_SACRIFICE));

	if (!ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_MONSTER)
		return;

	//ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_SACRIFICE));

	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0;
	//char bType = 0;
	//void* pTarget = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	//if (bType == 0 && nTargetID)
	//	pTarget = CPlayer::FindPlayer(nTargetID);

	//if (bType == 1)
	//	return;

	//if (bType >= 2 || !pTarget || pTarget == GetOffset())
	//	return;

	//ICharacter Target((void*)pTarget);


	std::map<std::pair<int, int>, IConfig::Heals>::iterator skills;

	skills = IConfig::HealCalc.find({ GetClass(),ISkill.GetIndex() });

	if (skills == IConfig::HealCalc.end())
		return;

	int hp_loss = skills->second.base_heal + 
		(skills->second.cast_max_hp_percent * (GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.cast_heal_per_grade_percent * (GetMaxHp() / 100)));

	int target_heal = skills->second.base_heal + 
		(skills->second.target_max_hp_percent * (Target.GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.target_heal_per_grade_percent * (GetMaxHp() / 100)));

	if (Target.IsValid() && IsValid())
	{
		if (GetCurHp() - hp_loss <= 0)
		{
			SystemMessage("Your HP is too low to use this skill", RGB(255, 0, 0));
			return;
		}
		else
		{
			DecreaseHp(static_cast<int>(hp_loss));
			Target.IncreaseHp(static_cast<int>(target_heal));
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
			return;
		}
	}











	//ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_SACRIFICE));

	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0;
	//char bType = 0;
	//void* pTarget = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	//if (bType == 0 && nTargetID)
	//	pTarget = CPlayer::FindPlayer(nTargetID);

	//if (bType == 1)
	//	return;

	//if (bType >= 2 || !pTarget || pTarget == GetOffset())
	//	return;

	//ICharacter ITarget((void*)pTarget);



	////double nHealAmountSacrifice = SacrificeBaseHeal + (ITarget.GetMaxHp() * SacrificeBasePercentageHeal / 100) + (ITarget.GetMaxHp() * (ISkill.GetGrade() * SacrificeHealPerGradePercentage / 100));
	//double nHealAmountSacrifice = 1000.0;

	////double nHpLossSacrifice = SacrificeBaseLoss + (GetMaxHp() * SacrificeBasePercentageLoss / 100) + (GetMaxHp() * (ISkill.GetGrade() * SacrificeLossPerGradePercentage / 100));
	//double nHpLossSacrifice = 1000.0;


	//if (pTarget && ITarget.IsValid() && IsValid())
	//{
	//	if (GetCurHp() - nHpLossSacrifice <= 0)
	//	{
	//		//SystemMessage("Your HP is too low to use this skill", TEXTCOLOR_RED);
	//		SystemMessage("Your HP is too low to use this skill", RGB(255, 0, 0));

	//	}
	//	else
	//	{
	//		DecreaseHp(static_cast<int>(nHpLossSacrifice));
	//		ITarget.IncreaseHp(static_cast<int>(nHealAmountSacrifice));
	//		_ShowBattleAnimation(GetOffset(), SKILL_KNIGHT_SACRIFICE);

	//	}
	//}

}

void __fastcall CKnight::TranscendentalBlow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_TRANSCENDENTALBLOW));

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
		DamageMultiple(ISkill, Target, Around, 2, false, true);
	}



	//	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_TRANSCENDENTALBLOW));
	//	int nSkillGrade = ISkill.GetGrade();
	//
	//	if (!nSkillGrade)
	//		return;
	//
	//	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	//	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	//	int nMana = ISkill.DecreaseMana();
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
	//	ICharacter Target(pTarget);
	//
	//
	//	if (bType == 0)
	//	{
	//
	//		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//		{
	//			if (CheckHit(Target, 20))
	//			{
	//				//int nDmg = (GetAttack() * TBBaseDmgMultiPvP) + (CChar::GetDex((int)GetOffset()) * TBAgiMultiPvP) + (CChar::GetStr((int)GetOffset()) * TBStrMultiPvP) + (ISkill.GetGrade() * TBPerGradeMultiPvP);
	//				int nDmg = 5000;
	//				OktayDamageSingle(Target, nDmg, 5);
	//				SetDirection(Target);
	//				_ShowBattleAnimation(Target, 5);
	//			}
	//			else
	//			{
	//				_ShowBattleMiss(Target, 5);
	//			}
	//		}
	//	}
	//	if (bType == 1)
	//	{
	//		int Around = Target.GetObjectListAround(1);
	//		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//		{
	//			if (CheckHit(Target, 20))
	//			{
	//				//int nDmge = (GetAttack() * TBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * TBAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * TBStrMultiPvE) + (ISkill.GetGrade() * TBPerGradeMultiPvE);
	//				int nDmge = 5000;
	//				OktayDamageSingle(Target, nDmge, 5);
	//				SetDirection(Target);
	//				_ShowBattleAnimation(Target, 5);
	//			}
	//			else
	//			{
	//				_ShowBattleMiss(Target, 5);
	//			}
	//		}
	//		int i = 0;
	//		while (Around && i < /*TBPvEMaxHits - 1*/ 2)
	//		{
	//			ICharacter Object((void*)*(DWORD*)Around);
	//
	//			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
	//			{
	//
	//				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
	//				{
	//
	//					if (CheckHit(Object, 20))
	//					{
	//						//int nDmg = (GetAttack() * TBBaseDmgMultiPvE) + (CChar::GetDex((int)GetOffset()) * TBAgiMultiPvE) + (CChar::GetStr((int)GetOffset()) * TBStrMultiPvE) + (ISkill.GetGrade() * TBPerGradeMultiPvE);
	//						int nDmg = 5000;
	//						OktayDamageSingle(Object, nDmg, 5);
	//						_ShowBattleAnimation(Object, 5);
	//						i++;
	//					}
	//					else
	//					{
	//						_ShowBattleMiss(Object, 5);
	//						i++;
	//					}
	//				}
	//			}
	//			Around = CBaseList::Pop((void*)Around);
	//		}
	//	}
	//	DecreaseMana(nMana);
	//	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CKnight::Calls(int pPacket, int pPos, int SkillID)
{
	ISkill ISkill((void*)GetSkillPointer(SkillID));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;




	//Call of Evasion
	if (SkillID == 27)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 550);

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (!IMembers.IsBuff(70))
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									if (IMembers.IsBuff(73))
									{
										IMembers.CancelBuff(73);
									}

									IMembers.Buff(70, 0, 0);
									IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

									IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);

									IConfig::CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;

								}
							}

							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{

									if (IMembers.IsBuff(73))
									{
										IMembers.CancelBuff(73);
									}

									IMembers.RemoveEva(*(DWORD*)(Buff + 12));
									IMembers.CancelBuff(70);
									IMembers.CancelBuff(550);



									IMembers.Buff(70, 0, 0);
									IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
									IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;

									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);
									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								}
							}
						}

					}
				}
			}
			else
			{
				int Buff = CChar::FindBuff((int)GetOffset(), 550);

				if (!IsBuff(70))
				{
					if (IsBuff(73))
					{
						CancelBuff(73);
					}

					this->Buff(70, 0, 0);
					this->Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

					AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					AddFxToTarget("test_item_ef_09", 1, 0, 1);
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
				else
				{
					if (IsBuff(73))
					{
						CancelBuff(73);
					}
					RemoveEva(*(DWORD*)(Buff + 12));
					CancelBuff(70);
					CancelBuff(550);

					this->Buff(70, 0, 0);
					this->Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
					AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					AddFxToTarget("test_item_ef_09", 1, 0, 1);
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of otp
	if (SkillID == 31)
	{
		int EvaBuff = 0;
		if (IsValid())
		{
			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));
						EvaBuff = CChar::FindBuff((int)IMembers.GetOffset(), 550);

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (!IMembers.IsBuff(73))
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									if (IMembers.IsBuff(70) && IMembers.IsBuff(550))
									{
										IMembers.RemoveEva(*(DWORD*)(EvaBuff + 12));
										IMembers.CancelBuff(70);
										IMembers.CancelBuff(550);
									}
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;
								}
							}
							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									if (IMembers.IsBuff(70) && IMembers.IsBuff(550))
									{
										IMembers.RemoveEva(*(DWORD*)(EvaBuff + 12));
										IMembers.CancelBuff(70);
										IMembers.CancelBuff(550);
									}
									IMembers.CancelBuff(73);
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;
								}
							}

						}
					}
				}
			}
			else
			{
				EvaBuff = CChar::FindBuff((int)GetOffset(), 550);
				if (!IsBuff(73))
				{
					if (IsBuff(70) && IsBuff(550))
					{
						RemoveEva(*(DWORD*)(EvaBuff + 12));
						CancelBuff(70);
						CancelBuff(550);
					}
					Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
				else
				{
					if (IsBuff(70) && IsBuff(550))
					{
						RemoveEva(*(DWORD*)(EvaBuff + 12));
						CancelBuff(70);
						CancelBuff(550);
					}
					CancelBuff(73);

					Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of Recoveryy
	if (SkillID == 23)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));


						if (CChar::IsNormal(Members) && IsValid())
						{
							if (!IMembers.IsBuff(38))
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
										IConfig::CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
										IConfig::CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
								}
							}

							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IMembers.CancelBuff(38);
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
										IConfig::CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
										IConfig::CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										IConfig::CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
								}

							}
						}

					}
				}
			}
			else
			{
				if (!IsBuff(38))
				{
					Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
				else
				{
					CancelBuff(38);

					Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of physical attack
	if (SkillID == 32)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 560);

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (!IMembers.IsBuff(74))
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].SkillID = SkillID;

									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								}
							}
							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IMembers.RemoveMinAttack(*(DWORD*)(Buff + 12));
									IMembers.RemoveMaxAttack(*(DWORD*)(Buff + 12));
									IMembers.CancelBuff(74);
									IMembers.CancelBuff(560);


									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].CasterOffset = GetOffset();
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									IConfig::CallOfPhysicalAttack[IMembers.GetPID()].SkillID = SkillID;



									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								}
							}
						}

					}
				}
			}
			else
			{
				int Buff = CChar::FindBuff((int)GetOffset(), 560);


				if (!IsBuff(74))
				{

					AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
					AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

					this->Buff(74, 0, 0);
					this->Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);


					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
				else
				{
					RemoveMinAttack(*(DWORD*)(Buff + 12));
					RemoveMaxAttack(*(DWORD*)(Buff + 12));

					CancelBuff(74);
					CancelBuff(560);


					AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
					AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

					this->Buff(74, 0, 0);
					this->Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);

					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
			}
		}
		return;
	}

	//Call of heal
	if (SkillID == 29)
	{

		std::map<std::pair<int, int>, IConfig::Heals>::iterator skills;

		skills = IConfig::HealCalc.find({ GetClass(),ISkill.GetIndex() });

		if (skills == IConfig::HealCalc.end())
			return;

		int self_heal = skills->second.base_heal +
			(skills->second.cast_max_hp_percent * (GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.cast_heal_per_grade_percent * (GetMaxHp() / 100)));

		if (IsValid())
		{

			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{

					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (IsInRange(IMembers, IConfig::CallRANGE))
							{
								int target_heal = skills->second.base_heal +
									(skills->second.target_max_hp_percent * (IMembers.GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.target_heal_per_grade_percent * (GetMaxHp() / 100)));

								IMembers.IncreaseHp(target_heal);
								//IMembers.IncreaseHp(CallofHealBase + (IMembers.GetMaxHp() * CallofHealBasePercentage / 100) + (IMembers.GetMaxHp() * ISkill.GetGrade() * CallofHealPerGradePercentage / 100));
								IMembers.AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
							}
						}
					}
					_ShowBattleAnimation(GetOffset(), 29);

				}
			}
			else
			{

				AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
				//IncreaseHp(CallofHealBase + (GetMaxHp() * CallofHealBasePercentage / 100) + (GetMaxHp() * ISkill.GetGrade() * CallofHealPerGradePercentage / 100));
				IncreaseHp(self_heal);
				_ShowBattleAnimation(GetOffset(), 29);
			}
		}
	}
	//call of puri
	if (SkillID == 28)
	{
		int DebuffList[22] = { 7,8,11,15,26,29,39,81,85,86,87,88,89,90,91,92,93,94,105,4001,4002,790 };

		if (IsValid())
		{
			if (IsParty())
			{
				void* Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (IsInRange(IMembers, IConfig::CallRANGE))
							{
								for (int i = 0; i < 22; i++)
								{
									IMembers.CancelBuff(DebuffList[i]);
									IMembers.AddFxToTarget("davi_M635_75", 1, 0, 1);
								}
								IMembers.RemoveBuffIcon(0, 0, 0, 225);
								IMembers.RemoveBuffIcon(0, 0, 0, 224);

								//rupture and fatal would (thief skills) - not needed anymore.
								/*if (IMembers.IsBuff(350))
								{
									IMembers.CancelBuff(350);
									for (auto it = CheckRuptureContinueSkill.begin(); it != CheckRuptureContinueSkill.end(); ++it)
									{
										if (it->second.PlayerTarget == IMembers.GetOffset())
										{

											ICharacter Caster(it->second.CasterOffset);
											if (Caster.IsOnline())
											{
												ResetRuptureContinueSkill(Caster);
												Caster.CancelBuff(5577);
												Caster.CancelBuff(353);
											}
										}
									}
								}
								if (IMembers.IsBuff(348))
								{
									IMembers.CancelBuff(348);
									for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
									{
										if (it->second.PlayerTarget == IMembers.GetOffset())
										{

											ICharacter Caster(it->second.CasterOffset);
											if (Caster.IsOnline())
											{
												ResetFarContinueSkill(Caster);
												Caster.CancelBuff(5576);
											}
										}
									}
								}*/
								if (IMembers.IsBuff(339) || IMembers.IsBuff(340))
								{
									if (IMembers.IsBuff(339))
										IMembers.CancelBuff(339);

									if (IMembers.IsBuff(340))
										IMembers.CancelBuff(340);

									IMembers.RemoveBuffIcon(0, 0, 0, 219);

									for (auto it = IConfig::CheckFarContinueSkill.begin(); it != IConfig::CheckFarContinueSkill.end(); ++it)
									{
										if (it->second.PlayerTarget == IMembers.GetOffset())
										{

											ICharacter Caster(it->second.CasterOffset);
											if (Caster.IsOnline())
											{
												ResetFarContinueSkill();
												Caster.CancelBuff(5578);
												Caster.CancelBuff(341);
											}
										}
									}
								}

							}
						}
					}

				}
			}
			else
			{
				AddFxToTarget("davi_M635_75", 1, 0, 1);
				for (int i = 0; i < 22; i++)
				{
					CancelBuff(DebuffList[i]);
				}
				RemoveBuffIcon(0, 0, 0, 225);
				RemoveBuffIcon(0, 0, 0, 224);

				//rupture and fatal would (thief skills) - not needed anymore.
				/*if (IsBuff(350))
				{
					CancelBuff(350);
					for (auto it = CheckRuptureContinueSkill.begin(); it != CheckRuptureContinueSkill.end(); ++it)
					{
						if (it->second.PlayerTarget == GetOffset())
						{

							ICharacter Caster(it->second.CasterOffset);
							if (Caster.IsOnline())
							{
								ResetRuptureContinueSkill(Caster);
								Caster.CancelBuff(5577);
								Caster.CancelBuff(353);
							}
						}
					}
				}
				if (IsBuff(348))
				{
					CancelBuff(348);
					for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
					{
						if (it->second.PlayerTarget == GetOffset())
						{

							ICharacter Caster(it->second.CasterOffset);
							if (Caster.IsOnline())
							{
								ResetFarContinueSkill(Caster);
								Caster.CancelBuff(5576);
							}
						}
					}
				}*/
				if (IsBuff(339) || IsBuff(340))
				{
					if (IsBuff(339))
						CancelBuff(339);

					if (IsBuff(340))
						CancelBuff(340);

					RemoveBuffIcon(0, 0, 0, 219);

					for (auto it = IConfig::CheckFarContinueSkill.begin(); it != IConfig::CheckFarContinueSkill.end(); ++it)
					{
						if (it->second.PlayerTarget == GetOffset())
						{

							ICharacter Caster(it->second.CasterOffset);
							if (Caster.IsOnline())
							{
								ResetFarContinueSkill();
								Caster.CancelBuff(5578);
								Caster.CancelBuff(341);
							}
						}
					}
				}

			}
		}

	}
}