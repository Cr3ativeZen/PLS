void __fastcall Cure(int pSkill, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	ISkill ISkill((void*)pSkill);

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)Target, (char*)a3, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);

	int nCure1HealAmount = CureBase + ((ITarget.GetMaxHp() * (CureBasePercentage / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*CureWisdom);
	int Self1 = CureBase + ((IPlayer.GetMaxHp() * (CureBasePercentage / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*CureWisdom)/2;

	int nCure2HealAmount = CureBase2 + ((ITarget.GetMaxHp() * (CureBasePercentage2 / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage2 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure2Wisdom);
	int Self2 = CureBase2 + ((IPlayer.GetMaxHp() * (CureBasePercentage2 / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage2 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure2Wisdom)/2;

	int nCure3HealAmount = CureBase3 + ((ITarget.GetMaxHp() * (CureBasePercentage3 / 100)) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage3 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure3Wisdom);
	int Self3 = CureBase3 + ((IPlayer.GetMaxHp() * (CureBasePercentage3 / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*CurePerGradePercentage3 / 100)) + CChar::GetWis((int)IPlayer.GetOffset())*Cure3Wisdom)/2;



	if (pTarget && ITarget.IsValid() && IPlayer.IsValid())
	{
		//Cure
		if (pSkill == IPlayer.GetSkillPointer(10) && CureON == true)
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



		//Cure2
		else if (pSkill == IPlayer.GetSkillPointer(22) && CureON == true)
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



		//Cure3
		else if (pSkill == IPlayer.GetSkillPointer(35) && CureON == true)
		{
			if (nTargetID == IPlayer.GetID())
			{
				IPlayer.IncreaseHp(Self3);
				IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
				return;
			}
			else
			{
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



		//Perfect Cure
		else if (pSkill == IPlayer.GetSkillPointer(55))
		{
			if (nTargetID == IPlayer.GetID())
			{
				IPlayer.IncreaseHp(IPlayer.GetMaxHp()*static_cast<int>(0.35 + ((ISkill.GetGrade() - 1)*0.20)));
				IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
				return;
			}
			ITarget.IncreaseHp(ITarget.GetMaxHp()*static_cast<int>(0.35 + ((ISkill.GetGrade() - 1)*0.20)));
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());

			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;


		}



		//Restore
		else if (pSkill == IPlayer.GetSkillPointer(29))
		{
			if (nTargetID == IPlayer.GetID())
			{
				IPlayer.IncreaseHp(IPlayer.GetMaxHp()*static_cast<int>(0.25*(ISkill.GetGrade())));
				IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
				IPlayer.DecreaseMana(nMana);
				CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
				return;
			}
			ITarget.IncreaseHp(ITarget.GetMaxHp()*static_cast<int>(0.25*(ISkill.GetGrade())));
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
			IPlayer.DecreaseMana(nMana);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;


		}

	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}