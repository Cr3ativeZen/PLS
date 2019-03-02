void __fastcall Cure(IChar IPlayer,int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(10));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);


	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);

	int nCure1HealAmount = CureBase + ((ITarget.GetMaxHp() * (CureBasePercentage / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*CureWisdom);
	int Self1 = (CureBase + ((IPlayer.GetMaxHp() * (CureBasePercentage / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*CureWisdom))/2;

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && CureON == true)
	{
		if (nTargetID == IPlayer.GetID())
		{

			IPlayer.IncreaseHp(Self1);
			IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}

		IPlayer.SetDirection(ITarget);
		ITarget.IncreaseHp(nCure1HealAmount);
		IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());

		IPlayer.IncreaseHp(Self1);
		IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());

		IPlayer.DecreaseMana(nMana);
		CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
		return;

	}

	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}

void __fastcall Cure2(IChar IPlayer, int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(22));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);

	int nCure2HealAmount = CureBase2 + ((ITarget.GetMaxHp() * (CureBasePercentage2 / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage2 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure2Wisdom);
	int Self2 = (CureBase2 + ((IPlayer.GetMaxHp() * (CureBasePercentage2 / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage2 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure2Wisdom))/2;

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && CureON == true)
	{
		if (nTargetID == IPlayer.GetID())
		{
			IPlayer.IncreaseHp(Self2);
			IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}

		IPlayer.SetDirection(ITarget);
		ITarget.IncreaseHp(nCure2HealAmount);
		IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());

		IPlayer.IncreaseHp(Self2);
		IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());

		IPlayer.DecreaseMana(nMana);
		CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
		return;

	}

}

void __fastcall Cure3(IChar IPlayer, int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(35));

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);

	int nCure3HealAmount = CureBase3 + ((ITarget.GetMaxHp() * (CureBasePercentage3 / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage3 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure3Wisdom);
	int Self3 = (CureBase3 + ((IPlayer.GetMaxHp() * (CureBasePercentage3 / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage3 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure3Wisdom)) / 2;

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && CureON == true)
	{
		if (nTargetID == IPlayer.GetID())
		{
			IPlayer.IncreaseHp(Self3);
			IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}

		IPlayer.SetDirection(ITarget);
		ITarget.IncreaseHp(nCure3HealAmount);
		IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());

		IPlayer.IncreaseHp(Self3);
		IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());

		IPlayer.DecreaseMana(nMana);
		CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
		return;

	}

}