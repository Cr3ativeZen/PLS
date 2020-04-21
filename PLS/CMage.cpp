#include "CMage.h"

void __fastcall CMage::Cure(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_CURE);
	ISkill ISkill((void*)pSkill);


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

	if (bType >= 2 || !pTarget || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);

	
	
	
	//int nCure1HealAmount = CureBase + ((ITarget.GetMaxHp() * (CureBasePercentage / 100)) + (ITarget.GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage / 100)) + CChar::GetWis((int)GetOffset()) * CureWisdom);
	int nCure1HealAmount = 1000;
	int Self1 = 1000;
	
	//int Self1 = (CureBase + ((GetMaxHp() * (CureBasePercentage / 100)) + (GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage / 100)) + CChar::GetWis((int)GetOffset()) * CureWisdom)) / 2;

	if (ITarget.IsValid() && IsValid() /*&& CureON == true*/)
	{
		if (nTargetID == GetID())
		{

			IncreaseHp(Self1);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
			DecreaseMana(nMana);
		}
		else
		{


			SetDirection(ITarget);
			ITarget.IncreaseHp(nCure1HealAmount);
			_ShowBattleAnimation(ITarget, ISkill.GetIndex());

			IncreaseHp(Self1);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());

			DecreaseMana(nMana);
		}
	}

	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall CMage::Cure2(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_CURE2);
	ISkill ISkill((void*)pSkill);

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

	if (bType >= 2 || !pTarget || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);

	//int nCure2HealAmount = CureBase2 + ((ITarget.GetMaxHp() * (CureBasePercentage2 / 100)) + (ITarget.GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage2 / 100)) + CChar::GetWis((int)GetOffset()) * Cure2Wisdom);
	
	
	int nCure2HealAmount = 1000;
	int Self2 = 1000;
	//int Self2 = (CureBase2 + ((GetMaxHp() * (CureBasePercentage2 / 100)) + (GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage2 / 100)) + CChar::GetWis((int)GetOffset()) * Cure2Wisdom)) / 2;

	if (ITarget.IsValid() && IsValid() /*&& CureON == true*/)
	{
		if (nTargetID == GetID())
		{
			IncreaseHp(Self2);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
			DecreaseMana(nMana);

		}
		else
		{
			SetDirection(ITarget);
			ITarget.IncreaseHp(nCure2HealAmount);
			_ShowBattleAnimation(ITarget, ISkill.GetIndex());

			IncreaseHp(Self2);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());

			DecreaseMana(nMana);
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall CMage::Cure3(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_CURE);
	ISkill ISkill((void*)pSkill);

	int nTargetID = 0;
	char bType = 0;
	void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2 || !pTarget || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);
	
	//int nCure3HealAmount = CureBase3 + ((ITarget.GetMaxHp() * (CureBasePercentage3 / 100)) + (ITarget.GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage3 / 100)) + CChar::GetWis((int)GetOffset()) * Cure3Wisdom);
	//int Self3 = (CureBase3 + ((GetMaxHp() * (CureBasePercentage3 / 100)) + (GetMaxHp() * (ISkill.GetGrade() * CurePerGradePercentage3 / 100)) + CChar::GetWis((int)GetOffset()) * Cure3Wisdom)) / 2;
	int nCure3HealAmount = 1000;
	int Self3 = 1000;
	if (ITarget.IsValid() && IsValid() /*&& CureON == true*/)
	{
		if (nTargetID == GetID())
		{
			IncreaseHp(Self3);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
			DecreaseMana(nMana);
		}
		else
		{


			SetDirection(ITarget);
			ITarget.IncreaseHp(nCure3HealAmount);
			_ShowBattleAnimation(ITarget, ISkill.GetIndex());

			IncreaseHp(Self3);
			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());

			DecreaseMana(nMana);
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall CMage::Heal()
{

	int pSkill = GetSkillPointer(SKILL_MAGE_HEAL);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	//int nHealAmount = HealBase + ((GetMaxHp() * (HealBasePercentage / 100)) + (GetMaxHp() * (ISkill.GetGrade() * HealPerGradePercentage / 100)) + CChar::GetWis((int)GetOffset()) * HealWisdom);
	int nHealAmount = 1000;

	_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
	IncreaseHp(nHealAmount);
	DecreaseMana((ISkill.GetGrade() * 4) + 16);

}

void __fastcall CMage::ShockWave(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_SHOCKWAVE);
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


	if (bType == 0)
	{
		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			//int nDmg = (GetMagic() * SWBaseDmgMultiPvP) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvP) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvP) + (ISkill.GetGrade() * SWPerGradeMultiPvP);
			int nDmg = 5000;
			OktayDamageSingle(Target, nDmg, 9);
			SetDirection(Target);
			_ShowBattleAnimation(Target, 9);
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(2);
		if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 2))
		{
			//int nDmge = (GetMagic() * SWBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvE) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvE) + (ISkill.GetGrade() * SWPerGradeMultiPvE);
			int nDmge = 5000;
			OktayDamageSingle(Target, nDmge, 9);
			SetDirection(Target);
			_ShowBattleAnimation(Target, 9);
		}

		int i = 0;

		while (Around && i < /*SWPvEMaxHits - 1*/ 2)
		{

			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{
					//int nDmg = (GetMagic() * SWBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset()) * SWWisMultiPvE) + (CChar::GetInt((int)GetOffset()) * SWIntMultiPvE) + (ISkill.GetGrade() * SWPerGradeMultiPvE);
					int nDmg = 5000;
					_ShowBattleAnimation(Object, 9);
					OktayDamageSingle(Object, nDmg, 9);
					i++;
				}

			}

			Around = CBaseList::Pop((void*)Around);
		}
	}
	DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);

}

void __fastcall CMage::Amnesia(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_AMNESIA);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
	{
		//SystemMessage("You cannot attack player with Amnesia", TEXTCOLOR_RED);   //potem odkomentowac
		return;
	}

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter Target(pTarget);

	if (bType == 1)
	{
		_ShowBattleAnimation(Target, 61);
		int Around = Target.GetObjectListAround(3);
		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				if (CChar::IsNormal((int)Object.GetOffset()))
				{
					//int nDmg = (GetMagic() * AmensiaBaseDmgMulti) + GetWis() * AmnesiaWisMulti;
					//if (IsBuff(24))
					//{
					//	nDmg *= (AmnesiaDmgPercentIncreaseBless / 100);
					//}
					int nDmg = 5000;
					OktayDamageArea(Object, nDmg, 61);
				}
			}
			Around = CBaseList::Pop((void*)Around);
		}

	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}
