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
