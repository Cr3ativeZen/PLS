#include "CMage.h"

void __fastcall CMage::Cure(int pPacket, int pPos,int skill_id)
{
	ISkill ISkill((void*)GetSkillPointer(skill_id));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana() || !ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget)
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_MONSTER)
		return;

	std::map<std::pair<int, int>, IConfig::Heals>::iterator skills;

	skills = IConfig::HealCalc.find({ GetClass(),ISkill.GetIndex() });

	if (skills == IConfig::HealCalc.end())                                                            
		return;

	int self_heal = skills->second.base_heal + (skills->second.wis * GetWisTotal()) +
		(skills->second.cast_max_hp_percent * (GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.cast_heal_per_grade_percent * (GetMaxHp() / 100)));

	int target_heal = skills->second.base_heal + (skills->second.wis * GetWisTotal()) +
		(skills->second.target_max_hp_percent * (Target.GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.target_heal_per_grade_percent * (GetMaxHp() / 100)));




	if (Target.IsValid() && IsValid())
	{
		if (Target.GetOffset() == GetOffset())
		{
			IncreaseHp(target_heal);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
		}
		else
		{
			SetDirection(Target);

			Target.IncreaseHp(target_heal);
			_ShowBattleAnimation(Target, ISkill.GetIndex());

			IncreaseHp(self_heal);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());

		}
		DecreaseMana(ISkill.DecreaseMana());
	}

}

void __fastcall CMage::Heal()
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_HEAL));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int value = 0;
	std::map<std::pair<int, int>, IConfig::Heals>::iterator skills;

	skills = IConfig::HealCalc.find({ GetClass(),ISkill.GetIndex() });

	if (skills == IConfig::HealCalc.end())
		return;

	int self_heal = skills->second.base_heal + (skills->second.wis * GetWisTotal()) +
		(skills->second.cast_max_hp_percent * (GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.cast_heal_per_grade_percent * (GetMaxHp() / 100)));

	if (IsValid())
	{
		_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
		IncreaseHp(self_heal);
		DecreaseMana(ISkill.DecreaseMana());
	}

}

void __fastcall CMage::ShockWave(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SHOCKWAVE));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana() || !ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, false);




	//ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SHOCKWAVE));
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
	//		//int nDmg = (GetMagic() * SWBaseDmgMultiPvP) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvP) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvP) + (ISkill.GetGrade() * SWPerGradeMultiPvP);
	//		int nDmg = 5000;
	//		OktayDamageSingle(Target, nDmg, 9);
	//		SetDirection(Target);
	//		_ShowBattleAnimation(Target, 9);
	//	}
	//}
	//if (bType == 1)
	//{
	//	int Around = Target.GetObjectListAround(2);
	//	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
	//	{
	//		//int nDmge = (GetMagic() * SWBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvE) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvE) + (ISkill.GetGrade() * SWPerGradeMultiPvE);
	//		int nDmge = 5000;
	//		OktayDamageSingle(Target, nDmge, 9);
	//		SetDirection(Target);
	//		_ShowBattleAnimation(Target, 9);
	//	}

	//	int i = 0;

	//	while (Around && i < /*SWPvEMaxHits - 1*/ 2)
	//	{

	//		ICharacter Object((void*)*(DWORD*)Around);

	//		if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
	//		{

	//			if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
	//			{
	//				//int nDmg = (GetMagic() * SWBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvE) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvE) + (ISkill.GetGrade() * SWPerGradeMultiPvE);
	//				int nDmg = 5000;
	//				_ShowBattleAnimation(Object, 9);
	//				OktayDamageSingle(Object, nDmg, 9);
	//				i++;
	//			}

	//		}

	//		Around = CBaseList::Pop((void*)Around);
	//	}
	//}
	//DecreaseMana(nMana);
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}

void __fastcall CMage::Amnesia(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_AMNESIA));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana() || !ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_PLAYER)
	{
		SystemMessage("You cannot attack player with Amnesia", RGB(255,0,0));
		return;
	}

	int Around = Target.GetObjectListAround(3);

	DamageMultiple(ISkill, Target, Around, 999, true, false);

	//ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_AMNESIA));

	//int nSkillGrade = ISkill.GetGrade();

	//if (!nSkillGrade)
	//	return;

	//int nTargetID = 0; char bType = 0; void* pTarget = 0;
	//CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	//int nMana = ISkill.DecreaseMana();

	//if (bType == 0 && nTargetID)
	//{
	//	//SystemMessage("You cannot attack player with Amnesia", TEXTCOLOR_RED);   //potem odkomentowac
	//	return;
	//}

	//if (bType == 1 && nTargetID)
	//	pTarget = CMonster::FindMonster(nTargetID);

	//if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
	//	return;

	//ICharacter Target(pTarget);

	//if (bType == 1)
	//{
	//	_ShowBattleAnimation(Target, 61);
	//	int Around = Target.GetObjectListAround(3);
	//	while (Around)
	//	{
	//		ICharacter Object((void*)*(DWORD*)Around);

	//		if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
	//		{
	//			if (CChar::IsNormal((int)Object.GetOffset()))
	//			{
	//				//int nDmg = (GetMagic() * AmensiaBaseDmgMulti) + GetWis() * AmnesiaWisMulti;
	//				//if (IsBuff(24))
	//				//{
	//				//	nDmg *= (AmnesiaDmgPercentIncreaseBless / 100);
	//				//}
	//				int nDmg = 5000;
	//				OktayDamageArea(Object, nDmg, 61);
	//			}
	//		}
	//		Around = CBaseList::Pop((void*)Around);
	//	}

	//}
	//CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	//DecreaseMana(nMana);
}

void __fastcall CMage::Purification(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_PURIFICATION));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana() || !ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget)
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_MONSTER)
		return;

	if (Target.IsValid() && IsValid())
	{

		if (Target.IsBuff(339) || Target.IsBuff(340))
		{
			if(Target.IsBuff(339))
				Target.CancelBuff(339);

			if (Target.IsBuff(340))
				Target.CancelBuff(340);

			Target.RemoveBuffIcon(0, 0, 0, 219);
		}

		Target.CancelBuff(307);
		Target.CancelBuff(342);
		Target.CancelBuff(346);
		Target.CancelBuff(356);
		Target.CancelBuff(390);
		Target.CancelBuff(391);
		Target.CancelBuff(358);
		Target.CancelBuff(359);
		Target.CancelBuff(40);
		Target.CancelBuff(4002);
		Target.CancelBuff(4001);
		Target.CancelBuff(4003);
		Target.CancelBuff(790);
		Target.RemoveBuffIcon(0, 0, 0, 225);
		Target.RemoveBuffIcon(0, 0, 0, 224);
	}
	DecreaseMana(ISkill.DecreaseMana());
}

void __fastcall CMage::Summons(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_KNIGHT_BRUTALATTACK));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana() || !ISkill.GetGrade())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_MONSTER)
		return;


	if (IsValid())
	{
		if (Target.IsParty()&&CChar::IsGState((int)Target.GetOffset(), 2))
		{
			void *Party = (void*)CParty::FindParty(Target.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					ICharacter IMembers((void*)*(DWORD*)((void*)i));


					if (CChar::IsGState((int)IMembers.GetOffset(), 2)&& (IsInRange(IMembers, 10)))
					{
						_ShowBattleAnimation(IMembers, ISkill.GetIndex());
						IMembers.Revive();
						IMembers.Buff(4, 60, -50);
					}
				}
			}
		}
		else
		{
			if (CChar::IsGState((int)Target.GetOffset(), 2) && (IsInRange(Target, 10)))
			{
				_ShowBattleAnimation(Target, ISkill.GetIndex());
				Target.Revive();
				Target.Buff(4, 60,-50);
			}
		}
		DecreaseMana(ISkill.DecreaseMana());
	}
}