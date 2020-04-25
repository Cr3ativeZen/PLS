#include "CMage.h"

void __fastcall CMage::Cure(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_CURE));


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
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_CURE2));

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
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_CURE3));

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

	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_HEAL));

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
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SHOCKWAVE));
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
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_AMNESIA));

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

void __fastcall CMage::Purification(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_PURIFICATION));

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

	ICharacter ITarget((void*)pTarget);
	if (pTarget && ITarget.IsValid() && IsValid())
	{

		if (ITarget.IsBuff(339) || ITarget.IsBuff(340))
		{
			if(ITarget.IsBuff(339))
				ITarget.CancelBuff(339);

			if (ITarget.IsBuff(340))
				ITarget.CancelBuff(340);

			ITarget.RemoveBuffIcon(0, 0, 0, 219);
		}

		ITarget.CancelBuff(307);
		ITarget.CancelBuff(342);
		ITarget.CancelBuff(346);
		ITarget.CancelBuff(356);
		ITarget.CancelBuff(390);
		ITarget.CancelBuff(391);
		ITarget.CancelBuff(358);
		ITarget.CancelBuff(359);
		ITarget.CancelBuff(40);
		ITarget.CancelBuff(4002);
		ITarget.CancelBuff(4001);
		ITarget.CancelBuff(4003);
		ITarget.CancelBuff(790);
		ITarget.RemoveBuffIcon(0, 0, 0, 225);
		ITarget.RemoveBuffIcon(0, 0, 0, 224);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);

}

void __fastcall CMage::Summons(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SUMMONS));

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

	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);

	if (IsValid())
	{
		if (ITarget.IsParty()&&CChar::IsGState((int)ITarget.GetOffset(), 2))
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					ICharacter IMembers((void*)*(DWORD*)((void*)i));


					if (CChar::IsGState((int)IMembers.GetOffset(), 2)&& (IsInRange(IMembers, 10)))
					{
						_ShowBattleAnimation(IMembers, SKILL_MAGE_SUMMONS);
						IMembers.Revive();
						IMembers.Buff(4, 60, -50);
					}
				}
			}
		}
		else
		{
			if (CChar::IsGState((int)ITarget.GetOffset(), 2) && (IsInRange(ITarget, 10)))
			{
				_ShowBattleAnimation(ITarget, SKILL_MAGE_SUMMONS);
				ITarget.Revive();
				ITarget.Buff(4, 60,-50);
			}
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}

void __fastcall CMage::ChainLightning(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_CHAINLIGHTNING));

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);


	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget(pTarget);

	if (ITarget.IsValid() && IsValid())
	{
		int Around = ITarget.GetObjectListAround(3);
		_ShowBattleAnimation(ITarget, 41);
		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);
			if (Object.IsValid() && IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 2))
			{
				if (CChar::IsNormal((int)Object.GetOffset()))
				{
					/*int nDmg = (GetMagic() * CLBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset()) * CLIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic() * CLBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset()) * CLIntMultiPvP;*/
					int nDmg = 5000;

					OktayDamageArea(Object, nDmg, 41);

					if (Object.IsBuff(307) && Object.IsValid() && Object.GetCurHp() > 0)
						StormActivateShiny(Object);
				}
			}
			Around = CBaseList::Pop((void*)Around);
		}
		_ShowBattleAnimation(ITarget, 41);
	}

	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}

void __fastcall CMage::SoulDestruction(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_SOULDESTRUCTION));

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
		/*int nDmg = (GetMagic() * SoulDestructionBaseDmgMultiPvE) + (CChar::GetWis((int)GetOffset()) * SoulDestructionWisMultiPvE) + (ISkill.GetGrade() * SoulDestructionPerGradeMultiPvE);

		if (Target.GetType() == 0)
		{
			nDmg = (GetMagic() * SoulDestructionBaseDmgMultiPvP) + (CChar::GetWis((int)GetOffset()) * SoulDestructionWisMultiPvP) + (ISkill.GetGrade() * SoulDestructionPerGradeMultiPvP);
		}*/
		int nDmg = 5000;
		OktayDamageSingle(Target, nDmg, 40);
		_ShowBattleAnimation(Target, 40);

	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}

void __fastcall CMage::ContinueFireStorm()
{
	if (IsValid())
	{
		int nSkillGrade = IConfig::CheckContinueFireStorm.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = IConfig::CheckContinueFireStorm.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && IConfig::CheckContinueFireStorm.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueFireStorm();
				CancelBuff(BUFF_FIRESTORMUSE);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{

					/*int nDmg = (GetMagic()*FStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*FStormIntMultiPvE;

					if (Object.GetType() == 0)
						nDmg = (GetMagic()*FStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*FStormIntMultiPvP;*/
					int nDmg = 5000;

					OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && IConfig::CheckContinueFireStorm.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueFireStorm();
				CancelBuff(BUFF_FIRESTORMUSE);
			}

			return;
		}
	}

	ResetContinueFireStorm();
	CancelBuff(BUFF_FIRESTORMUSE);
	return;
}

void __fastcall CMage::FireStorm(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_FIRESTORM));

	if (IsValid() && GetSkillPointer(SKILL_MAGE_FIRESTORM))
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		int nSkillGrade = ISkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(BUFF_FIRESTORMUSE, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(GetOffset(), 48);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(230, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillID = SKILL_MAGE_FIRESTORM;
			IConfig::CheckContinueFireStorm[GetPID()].PlayerTarget = (void*)check;
			IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillCount = 8;
			IConfig::CheckContinueFireStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueFireStorm();
	}
}

void __fastcall CMage::ContinueThunderStorm()
{
	if (IsValid())
			{
				int nSkillGrade = IConfig::CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillGrade;
				void *pTarget = IConfig::CheckContinueThunderStorm.find(GetPID())->second.PlayerTarget;
		
				if (pTarget && nSkillGrade && IConfig::CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillCount)
				{
					ICharacter Target(pTarget);
					IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillCount--;
		
					if (!IsValid() || !Target.IsValid())
					{
						ResetContinueThunderStorm();
						CancelBuff(BUFF_THUNDERSTORMUSE);
						return;
					}
		
					int Around = Target.GetObjectListAround(3);
		
					while (Around)
					{
						ICharacter Object((void*)*(DWORD*)Around);
		
						if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (Object.IsBuff(307))
								StormActivateShiny(Object);
							
							int nDmg = 5000;
		
							//int nDmg = (GetMagic()*TStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*TStormIntMultiPvE;
		
							//if (Object.GetType() == 0)
							//	nDmg = (GetMagic()*TStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*TStormIntMultiPvP;
		
							OktayDamageStorm(Object, nDmg);
						}
		
						Around = CBaseList::Pop((void*)Around);
					}
		
					if (IsOnline())
						IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;
		
					if (IsOnline() && IConfig::CheckContinueThunderStorm.find(GetPID())->second.PlayerSkillCount == 0)
					{
						ResetContinueThunderStorm();
						CancelBuff(BUFF_THUNDERSTORMUSE);
					}
		
					return;
				}
			}
		
	ResetContinueThunderStorm();
	CancelBuff(BUFF_THUNDERSTORMUSE);
	return;
}

void __fastcall CMage::ThunderStorm(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_THUNDERSTORM));

	if (IsValid() && GetSkillPointer(SKILL_MAGE_THUNDERSTORM))
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		int nSkillGrade = ISkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(BUFF_THUNDERSTORMUSE, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(GetOffset(), 43);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(228, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillID = SKILL_MAGE_THUNDERSTORM;
			IConfig::CheckContinueThunderStorm[GetPID()].PlayerTarget = (void*)check;
			IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillCount = 8;
			IConfig::CheckContinueThunderStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueThunderStorm();
	}
}

void __fastcall CMage::ContinueIceStorm()
{
		if (IsValid())
	{
		int nSkillGrade = IConfig::CheckContinueIceStorm.find(GetPID())->second.PlayerSkillGrade;
		void *pTarget = IConfig::CheckContinueIceStorm.find(GetPID())->second.PlayerTarget;

		if (pTarget && nSkillGrade && IConfig::CheckContinueIceStorm.find(GetPID())->second.PlayerSkillCount)
		{
			ICharacter Target(pTarget);
			IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillCount--;

			if (!IsValid() || !Target.IsValid())
			{
				ResetContinueIceStorm();
				CancelBuff(BUFF_ICESTORMUSE);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = 5000;
					//int nDmg = (GetMagic()*IStormBaseDmgMultiPvE) + CChar::GetInt((int)GetOffset())*IStormIntMultiPvE;

					//if (Object.GetType() == 0)
					//	nDmg = (GetMagic()*IStormBaseDmgMultiPvP) + CChar::GetInt((int)GetOffset())*IStormIntMultiPvP;

					OktayDamageStorm(Object, nDmg);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && IConfig::CheckContinueIceStorm.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueIceStorm();
				CancelBuff(BUFF_ICESTORMUSE);
			}

			return;
		}
	}

	ResetContinueIceStorm();
	CancelBuff(BUFF_ICESTORMUSE);
	return;
}

void __fastcall CMage::IceStorm(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_MAGE_ICESTORM));

	if (IsValid() && GetSkillPointer(SKILL_MAGE_ICESTORM))
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		int nSkillGrade = ISkill.GetGrade();


		if (!nSkillGrade)
			return;

		int nMana = 20 + (GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IsValid())
		{
			if (GetCurMp() < nMana)
				return;

			Buff(BUFF_ICESTORMUSE, 16, 0);
			DecreaseMana(nMana);
			_ShowBattleAnimation(GetOffset(), 45);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(229, GetMap(), (int)GetSetXY, 1, (int)GetOffset(), 0, 16000);
			delete[] GetSetXY;
			IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillID = SKILL_MAGE_ICESTORM;
			IConfig::CheckContinueIceStorm[GetPID()].PlayerTarget = (void*)check;
			IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillGrade = nSkillGrade;
			IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillCount = 8;
			IConfig::CheckContinueIceStorm[GetPID()].PlayerSkillDelay = 0;
		}
		ContinueIceStorm();
	}
}

void __fastcall CMage::Fireball(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_FIREBALL);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((nSkillGrade - 1) + 30) * nSkillGrade) + 300) * 0.79);

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
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				//int nDmg = (GetMagic()*FBBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*FBIntMultiPvE) + (xSkill.GetGrade()*FBPerGradeMultiPvE);
				int nDmg = 5000;


				//if (Target.GetType() == 0)
				//	nDmg = (GetMagic()*FBBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*FBIntMultiPvP) + (xSkill.GetGrade()*FBPerGradeMultiPvP);


				OktayDamageSingle(Target, nDmg, 73);
				SetDirection(Target);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}

void __fastcall CMage::ContinueFlameInjection()
{
	if (IsValid())
	{
		int nSkillGrade = IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (!IsValid())
			{
				ResetContinueSkill();
				CancelBuff(BUFF_FLAMEINJECTIONUSE);
				return;
			}

			if (IsMoved(IConfig::CheckContinueSkill.find(GetPID())->second.PlayerX, IConfig::CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill();
				CancelBuff(BUFF_FLAMEINJECTIONUSE);
				return;
			}

			int Around = GetObjectListAround(4);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					//int nDmg = (GetMagic()*FIBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*FIIntMultiPvE) + (nSkillGrade*FIPerGradeMultiPvE);

					int nDmg = 5000;
					//if (Object.GetType() == 0)
					//	nDmg = (GetMagic()*FIBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*FIIntMultiPvP) + (nSkillGrade*FIPerGradeMultiPvP);


					OktayDamageArea(Object, nDmg, SKILL_MAGE_FLAMEINJECTION);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				CancelBuff(BUFF_FLAMEINJECTIONUSE);
				ResetContinueSkill();
			}

			return;
		}
	}

	ResetContinueSkill();
	CancelBuff(BUFF_FLAMEINJECTIONUSE);
	return;
}

void __fastcall CMage::FlameInjection(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_FLAMEINJECTION);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = GetLevel() * 4 + 120;

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
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				Buff(5557, 10, 0);
				DecreaseMana(nMana);
				IConfig::CheckContinueSkill[GetPID()].PlayerX = GetX();
				IConfig::CheckContinueSkill[GetPID()].PlayerY = GetY();
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillID = SKILL_MAGE_FLAMEINJECTION;
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount = 6;
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
				_ShowBattleAnimation(GetOffset(), 65);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
		ContinueFlameInjection();
	}
}

void __fastcall CMage::ContinueIcicle()
{
	int pSkill = GetSkillPointer(66);
	ISkill xSkill((void*)pSkill);
	if (IsValid())
	{
		if (IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount)
		{
			IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount--;

			if (IsMoved(IConfig::CheckContinueSkill.find(GetPID())->second.PlayerX, IConfig::CheckContinueSkill.find(GetPID())->second.PlayerY))
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ICICLEUSE);
				CouldntExecuteSkill();
				return;
			}

			if (!IsValid())
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ICICLEUSE);
				CouldntExecuteSkill();
				return;
			}

			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
				{
					//int nDmg = (GetMagic()*ICIBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*ICIIntMultiPvE) + (xSkill.GetGrade()*ICIPerGradeMultiPvE);
					int nDmg = 5000;
					//if (Object.GetType() == 0)
					//	nDmg = (GetMagic()*ICIBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*ICIIntMultiPvP) + (xSkill.GetGrade()*ICIPerGradeMultiPvP);


	
					OktayDamageArea(Object, nDmg, 66);

					if (CTools::Rate(0, 100) < 10)
					{
						//Object.Buff(8, ICIColdBindDuration, 0);
						Object.Buff(8, 5, 0);
					}

				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IsOnline())
				IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = GetTickCount() + 1800;

			if (IsOnline() && IConfig::CheckContinueSkill.find(GetPID())->second.PlayerSkillCount == 0)
			{
				ResetContinueSkill();
				CancelBuff(BUFF_ICICLEUSE);
			}

			return;
		}
	}

	ResetContinueSkill();
	CancelBuff(BUFF_ICICLEUSE);
	CouldntExecuteSkill();
	return;
}

void __fastcall CMage::Icicle()
{
	int pSkill = GetSkillPointer(SKILL_MAGE_ICICLE);
	if (IsValid() && pSkill)
	{
		int nMana = GetLevel() * 4 + 120;

		if (GetCurMp() < nMana)
			return;

		Buff(5556, 10, 0);
		DecreaseMana(nMana);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		IConfig::CheckContinueSkill[GetPID()].PlayerX = GetX();
		IConfig::CheckContinueSkill[GetPID()].PlayerY = GetY();
		IConfig::CheckContinueSkill[GetPID()].PlayerSkillID = SKILL_MAGE_ICICLE;
		IConfig::CheckContinueSkill[GetPID()].PlayerSkillGrade = xSkill.GetGrade();
		IConfig::CheckContinueSkill[GetPID()].PlayerSkillCount = 5;
		IConfig::CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
		_ShowBattleAnimation(GetOffset(), SKILL_MAGE_ICICLE);
	}
	ContinueIcicle();
}

void __fastcall CMage::Thunderbolt(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_THUNDERBOLT);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 45) * xSkill.GetGrade()) + 280) * 0.75);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		if (pTarget && xSkill.GetGrade() && IsValid())
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

			//int nDmg = (GetMagic()*TBoltMBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvE) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvE);
			int nDmg = 5000;
			
			//if (Target.GetType() == 0)
			//	nDmg = (GetMagic()*TBoltMBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*TBoltMIntMultiPvP) + (xSkill.GetGrade()*TBoltMPerGradeMultiPvP);

			SetDirection(Target);
			for (int i = 0; i < 6; i++)
			{
				OktayDamageSingle(Target, nDmg+CTools::Rate(1,200), SKILL_MAGE_THUNDERBOLT);
			}
			
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}

void __fastcall CMage::StormActivateShiny(ICharacter Target)
{
	if (Target.IsValid() && IsValid() && IConfig::CheckShiny.count((int)Target.GetOffset()))
	{
		if (IConfig::CheckShiny.find((int)Target.GetOffset())->second.Delay >= GetTickCount())
			return;

		if (IConfig::CheckShiny.find((int)Target.GetOffset())->second.Target && Target.IsBuff(307))
		{
			ICharacter Caster(IConfig::CheckShiny.find((int)Target.GetOffset())->second.Target);
			IConfig::CheckShiny[(int)Target.GetOffset()].Delay = GetTickCount() + 300;

			if (IsValid() && Caster.IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
					return;

				if (!Caster.IsInRange(Target, 300))
					return;

				int pSkill = Caster.GetSkillPointer(67);

				if (pSkill && Target.IsValid())
				{
					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int Around = Target.GetObjectListAround(3);

					while (Around)
					{
						ICharacter Object((void*)*(DWORD*)Around);

						if (Object.IsValid() && Caster.IsValid() && IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)Caster.GetOffset() + 176))((int)Caster.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (Target.GetType() == 0 && CChar::IsGState((int)Offset, 128) && !CChar::IsGState((int)Object.Offset, 128)) {
							}
							else if (Target.GetType() == 0 && CChar::IsGState((int)Target.Offset, 256) && Object.GetID() != Target.GetID()) {
							}
							else {
								/*int nDmg = (Caster.GetMagic() * LAActivationBaseDmgMultiPvE) + (CChar::GetInt((int)Caster.GetOffset()) * LAActivationIntMultiPvE) + (nSkillGrade * LAActivationPerGradeMultiPvE);

								if (Object.GetType() == 0)
									nDmg = (Caster.GetMagic() * LAActivationBaseDmgMultiPvP) + (CChar::GetInt((int)Caster.GetOffset()) * LAActivationIntMultiPvP) + (nSkillGrade * LAActivationPerGradeMultiPvP);*/
								int nDmg = 5000;

								Caster.OktayDamageArea(Object, nDmg, 67);

								if (Object.GetType() == 0 && Caster.GetID() != Object.GetID() && Object.GetID() != GetID())
									Object.AddFxToTarget("davi_ef129_05", 1, 0, 0);

								if (Object.GetType() == 1)
									Object.AddFxToTarget("davi_ef129", 1, 0, 0);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
			}
			else {
				if (Target.IsValid())
				{
					Target.CancelBuff(307);
					IConfig::CheckShiny[(int)Target.GetOffset()].Target = 0;
				}
			}
		}
	}
}

void __fastcall CMage::ActivateShiny(int pPacket, int pPos)
{
	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2 || !pTarget || pTarget == GetOffset())
		return;

	ICharacter Target(pTarget);

	if (pTarget && IsValid() && Target.IsValid() && IConfig::CheckShiny.count((int)Target.GetOffset()))
	{
		if (IConfig::CheckShiny.find((int)Target.GetOffset())->second.Delay >= GetTickCount())
		{
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
			return;
		}

		if (IConfig::CheckShiny.find((int)Target.GetOffset())->second.Target && Target.IsBuff(307))
		{
			ICharacter Caster(IConfig::CheckShiny.find((int)Target.GetOffset())->second.Target);
			IConfig::CheckShiny[(int)Target.GetOffset()].Delay = GetTickCount() + 500;

			if (IsValid() && Caster.IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (!Caster.IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				int pSkill = Caster.GetSkillPointer(67);

				if (pSkill && Target.IsValid())
				{
					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int Around = Target.GetObjectListAround(3);

					while (Around)
					{
						ICharacter Object((void*)*(DWORD*)Around);

						if (Object.IsValid() && Caster.IsValid() && IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)Caster.GetOffset() + 176))((int)Caster.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (Target.GetType() == 0 && CChar::IsGState((int)Offset, 128) && !CChar::IsGState((int)Object.Offset, 128)) {
							}
							else if (Target.GetType() == 0 && CChar::IsGState((int)Target.Offset, 256) && Object.GetID() != Target.GetID()) {
							}
							else {
								/*int nDmg = (Caster.GetMagic() * LAActivationBaseDmgMultiPvE) + (CChar::GetInt((int)Caster.GetOffset()) * LAActivationIntMultiPvE) + (nSkillGrade * LAActivationPerGradeMultiPvE);

								if (Object.GetType() == 0)
									nDmg = (Caster.GetMagic() * LAActivationBaseDmgMultiPvP) + (CChar::GetInt((int)Caster.GetOffset()) * LAActivationIntMultiPvP) + (nSkillGrade * LAActivationPerGradeMultiPvP);*/
								int nDmg = 5000;

								Caster.OktayDamageArea(Object, nDmg, 67);

								if (Object.GetType() == 0 && Caster.GetID() != Object.GetID() && Object.GetID() != GetID())
									Object.AddFxToTarget("davi_ef129_05", 1, 0, 0);

								if (Object.GetType() == 1)
									Object.AddFxToTarget("davi_ef129", 1, 0, 0);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
			}
			else {
				if (Target.IsValid())
				{
					Target.CancelBuff(307);
					IConfig::CheckShiny[(int)Target.GetOffset()].Target = 0;
				}
			}
		}
	}
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}

void __fastcall CMage::LightningArrow(int pPacket, int pPos)
{
		int pSkill = GetSkillPointer(SKILL_MAGE_LIGHTNINGARROW);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = GetLevel() * 4 + 120;

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType == 1 && nTargetID)
			pTarget = CMonster::FindMonster(nTargetID);

		if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
			return;

		ICharacter Target(pTarget);

		if (pTarget && IsValid() && Target.IsValid())
		{
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

			/*int nDmg = (GetMagic()*LABaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*LAIntMultiPvE) + (xSkill.GetGrade()*LAPerGradeMultiPvE);

			if (Target.GetType() == 0)
			nDmg = (GetMagic()*LABaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*LAIntMultiPvP) + (xSkill.GetGrade()*LAPerGradeMultiPvP);*/
			int nDmg = 5000;


			if (IsValid() && Target.IsValid())
			{
				if (!IsInRange(Target, 20))
				{
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
					return;
				}

				if (Target.IsBuff(307))
					StormActivateShiny(Target);

				if(!Target.IsBuff(307))
					IConfig::CheckShiny[(int)Target.GetOffset()].Target = GetOffset();

				SetDirection(Target);

				OktayDamageSingle(Target, nDmg, 67);
				//Target.Buff(307, LADuration, 0);
				//Target.Buff(5099, LADuration, 0);
				Target.Buff(307, 900, 0);
				Target.Buff(5099, 900, 0);
				DecreaseMana(nMana);
			}
		}
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
	}
}

int __cdecl CMage::CMonsterMagicCreate(int Index, int Value, int Argument, int Arg, int Player, int Damage, int Time)
{
		int check = CMonsterMagic::Create(Index, Value, Argument, Arg, Player, Damage, Time);

	if (check)
	{
		ICharacter Object((void*)Player);

		if (Object.IsOnline() && Object.GetType() == 0 && Index == 228)
			IConfig::CheckShiny[check].Target = (void*)Player;

		*(DWORD*)(check + 512) = Index;
	}

	return check;
}

int __fastcall CMage::MagicTick(void *Monster, void *edx)
{
	ICharacter IMonster(Monster);
	int result = CMonster::IsRemoved(Monster);

	if (IMonster.IsValid() && !result)
	{
		CChar::Lock(Monster);
		ICharacter IPlayer((void*)*(DWORD*)((int)Monster + 484));

		if (*(DWORD*)((int)Monster + 468) < GetTickCount())
		{
			CChar::Unlock(Monster);
			return CSkill::MagicTick(Monster);
		}

		if (*(DWORD*)((int)Monster + 484))
		{
			if (CBase::IsDeleted(*(DWORD*)((int)Monster + 484)))
			{
				CChar::Unlock(Monster);
				return CSkill::MagicTick(Monster);
			}

			if (IsValid() && IMonster.IsValid())
			{
				if (GetType() == 0 && IsValid() && IMonster.IsValid())
				{
					if (IMonster.GetMobIndex() == 231)
					{
						int Around = IMonster.GetObjectListAround(4);

						while (Around)
						{
							ICharacter Object((void*)*(DWORD*)Around);

							if (Object.IsValid() && IsValid() && IMonster.IsValid() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
							{
								if (Object.GetType() == 0)
									OktayDamageStorm(Object, *(DWORD*)((int)Monster + 136));
								else
									OktayDamageStorm(Object, *(DWORD*)((int)Monster + 136) * 3);
							}

							Around = CBaseList::Pop((void*)Around);
						}
					}
					else {
						int Around = IMonster.GetObjectListAround(4);
						IConfig::MageMICheck[GetPID()] = 43;

						while (Around)
						{
							ICharacter Object((void*)*(DWORD*)Around);

							if (Object.IsValid() && IsValid() && IMonster.IsValid() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
								OktayDamageStorm(Object, *(DWORD*)((int)Monster + 136));

							Around = CBaseList::Pop((void*)Around);
						}
					}

					if (IMonster.IsValid() && IMonster.GetMobIndex() == 228 && IConfig::CheckShiny.count((int)IMonster.GetOffset()) && IConfig::CheckShiny.find((int)IMonster.GetOffset())->second.Target)
					{
						ICharacter IPlayer(IConfig::CheckShiny.find((int)IMonster.GetOffset())->second.Target);

						if (IsValid() && IMonster.IsValid())
						{
							int Around = IMonster.GetObjectListAround(3);

							while (Around)
							{
								ICharacter Object((void*)*(DWORD*)Around);

								if (IMonster.IsValid() && Object.IsValid() && IsValid() && GetOffset() != Object.GetOffset() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
								{
									if (Object.IsBuff(307)&&(Object.IsBuff(5099)))
										StormActivateShiny(Object);
								}

								Around = CBaseList::Pop((void*)Around);
							}
						}
					}
				}
				else {
					if (GetType() == 1 && IsValid() && IMonster.IsValid())
					{
						int Around = GetObjectListAround(4);

						while (Around)
						{
							ICharacter Object((void*)*(DWORD*)Around);

							if (IsValid() && GetOffset() != Object.GetOffset() && Object.GetType() == 0)
								OktayDamageStorm(Object, CTools::Rate(5000, 5100));

							Around = CBaseList::Pop((void*)Around);
						}
					}
				}
			}
		}

		result = CChar::Unlock(Monster);
	}

	return result;
}


void __fastcall CMage::IceArrow(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_ICEARROW);
	__int64 GState = 536870912, State = 64, StateEx = 65, CancelState = 1;



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

		if (pTarget && nSkillGrade && IsValid())
		{
			ICharacter Target(pTarget);

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

				if (IsBuff(295))
				{
					if (IConfig::CheckIceArrow[GetPID()].Cooldown > GetTickCount())
					{
						CancelBuff(5600);
						CancelBuff(5605);
						SendGStateExIceArrow(GState / 2);
						SendGStateExIceArrow(State << 32);
						for (int i = 0; i < 6; i++)
						{
							CancelBuff(290 + i);
						}
						SystemMessage("Invalid skill time detected!", IConfig::TEXTCOLOR_RED);
						CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
						return;
					}

					if (IConfig::CheckIceArrow.find(GetPID())->second.Cooldown < GetTickCount())
					{
						IConfig::CheckIceArrow[GetPID()].Cooldown = GetTickCount() + 70000;
						IConfig::CheckIceArrow[GetPID()].Delay = GetTickCount() + 200;
					}
					CancelBuff(295);

					if (xSkill.GetGrade() == 1)
					{
						Buff(5600, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 2)
					{
						Buff(5601, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 2);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 3)
					{
						Buff(5602, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 4);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 4)
					{
						Buff(5603, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 8);
						SendGStateExIceArrow(State << 32);
					}
					else if (xSkill.GetGrade() == 5)
					{
						Buff(5604, 18, 0);
						Buff(5605, 18, 0);
						SendGStateExIceArrow(GState * 16);
						SendGStateExIceArrow(StateEx << 32);
					}
					else {
						CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
						return;
					}

				}



				if (IsValid() && IsBuff(5604))
				{
					CancelBuff(5604);
					Buff(5603, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 8);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5603))
				{
					CancelBuff(5603);
					Buff(5602, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 4);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5602))
				{
					CancelBuff(5602);
					Buff(5601, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState * 2);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5601))
				{
					CancelBuff(5601);
					Buff(5600, 18, 0);
					Buff(5605, 18, 0);
					SendGStateExIceArrow(GState);
					SendGStateExIceArrow(State << 32);
				}
				else if (IsValid() && IsBuff(5600))
				{
					CancelBuff(5600);
					CancelBuff(5605);
					SendGStateExIceArrow(GState / 2);
					SendGStateExIceArrow(State << 32);
					for (int i = 0; i < 6; i++)
					{
						CancelBuff(290 + i);
					}
				}
				else {
					CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				}


				//int nDmg = (GetMagic()*IAMBaseDmgMultiPvE) + (CChar::GetInt((int)GetOffset())*IAMIntMultiPvE) + (nSkillGrade*IAMPerGradeMultiPvE);

				int nDmg = 5000;
				//if (Target.GetType() == 0)
				//	nDmg = (GetMagic()*IAMBaseDmgMultiPvP) + (CChar::GetInt((int)GetOffset())*IAMIntMultiPvP) + (nSkillGrade*IAMPerGradeMultiPvP);

				OktayDamageSingle(Target, nDmg, SKILL_MAGE_ICEARROW);
				SetDirection(Target);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}

void __fastcall CMage::TherapeuticTouch(int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(SKILL_MAGE_THERAPEUTICTOUCH);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 50) * xSkill.GetGrade()) + 100) * 1.98);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType >= 1)
			return;

		if (bType >= 2 || !pTarget || GetCurMp() < nMana)
			return;

		if (pTarget && IsValid())
		{
			ICharacter Target(pTarget);

			if (!IsInRange(Target, 20))
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				//Target.Buff(45, TTDuration, TTBaseHeal+ xSkill.GetGrade() *TTPerGradeHeal + CChar::GetWis((int)GetOffset())*TTWisdom);
				Target.Buff(45, 12, 500);
				Target.RemoveBuffIcon(0, 0, 803, 59);
				_ShowBattleAnimation(Target, SKILL_MAGE_THERAPEUTICTOUCH);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
