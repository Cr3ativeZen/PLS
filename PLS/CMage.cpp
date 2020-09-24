#include "CMage.h"

void __fastcall CMage::Cure(int pPacket, int pPos,int skill_id)
{
	ISkill ISkill((void*)GetSkillPointer(skill_id));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
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
	self_heal /= 2;

	int target_heal = skills->second.base_heal + (skills->second.wis * GetWisTotal()) +
		(skills->second.target_max_hp_percent * (Target.GetMaxHp() / 100) + (ISkill.GetGrade() * skills->second.target_heal_per_grade_percent * (GetMaxHp() / 100)));




	if (Target.IsValid() && IsValid()  && IsInRange(Target,7))
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

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

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

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	char bType = 0;
	int nTargetID = 0;

	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);
	//DamageSingle(ISkill, Target, false, false);
	//(*(int (__thiscall **)(int, int, int))(*(DWORD *)Target.GetOffset() + 72))((int)Target.GetOffset(), nTargetID, 5000);
	_ShowBattleAnimation(Target, SKILL_MAGE_SHOCKWAVE);
	(*(void(__cdecl**)(void*, int, int, int))(*(DWORD*)raii.pTarget + 0x58))(raii.pTarget, 7, 0, 1300);
	(*(void(__thiscall**)(void*, void*))(*(DWORD*)raii.pTarget + 0x50))(raii.pTarget, GetOffset());
	CChar::WriteInSight(this->GetOffset(), 63, "bddbbwwbd", SKILL_MAGE_SHOCKWAVE, this->GetID(), Target.GetID(), 1, 1, 500, 200, TYPE_MONSTER, 0);



	//(*(void(__thiscall**)(void*, int, int, int, int, int))(*(DWORD*)ISkill.GetOffset() + 84))(
	//	ISkill.GetOffset(),
	//	nTargetID,
	//	(int)Target.GetOffset(),
	//	10000,
	//	3,
	//	700);

	


}

void __fastcall CMage::IceRestriction(int pPacket, int pPos)
{

}

void __fastcall CMage::Amnesia(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_AMNESIA));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
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


	DamageMultiple(ISkill, Target, 4, 999, true, false);

}

void __fastcall CMage::Purification(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_PURIFICATION));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
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
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SUMMONS));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
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
				CIOObject::Release(Party);
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