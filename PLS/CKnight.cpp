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


	DamageMultiple(ISkill, Target, 1, 999,true,false);

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
		DamageMultiple(ISkill, Target, 1, 1, false,true);
	}

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
		DamageMultiple(ISkill, Target, 1, 2, false, true);
	}

}

void __fastcall CKnight::Calls(int pPacket, int pPos, int SkillID)
{
	ISkill ISkill((void*)GetSkillPointer(SkillID));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;




	//Call of Evasion
	if (SkillID == SKILL_KNIGHT_CALLOFEVASION)
	{
		if (IsParty() && IsValid())
		{
			void* Party = (void*)CParty::FindParty(GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					ICharacter IMembers((void*)*(DWORD*)((void*)i));
					int BuffValue = 0;
					CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IMembers.GetOffset() + 364));
					int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 550);

					if (Buff)
						BuffValue = *(DWORD*)(Buff + 12);

					CIOCriticalSection::Leave((void*)((char*)IMembers.GetOffset() + 364));

					if (CChar::IsNormal(Members) && IsValid() && IMembers.GetClass() == CLASS_MAGE)
					{
						if (!IMembers.IsBuff(70))
						{
							if (IsInRange(IMembers, IConfig::CallRANGE))
							{
								IMembers.Buff(70, 0, 0);
								IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

								IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

								_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);



								IConfig::CallCheck callCheck = IConfig::CallCheck();

								callCheck.CasterOffset = GetOffset();
								callCheck.ReciverOffset = IMembers.GetOffset();
								callCheck.SkillID = SkillID;
								IConfig::CallOfEvasionOTP[IMembers.GetPID()] = callCheck;

							}
						}
						else
						{
							if (IsInRange(IMembers, IConfig::CallRANGE))
							{
								IMembers.RemoveEva(BuffValue);
								IMembers.CancelBuff(70);
								IMembers.CancelBuff(550);



								IMembers.Buff(70, 0, 0);
								IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
								IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

								IConfig::CallCheck callCheck = IConfig::CallCheck();

								callCheck.CasterOffset = GetOffset();
								callCheck.ReciverOffset = IMembers.GetOffset();
								callCheck.SkillID = SkillID;
								IConfig::CallOfEvasionOTP[IMembers.GetPID()] = callCheck;

								IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);
								_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
							}
						}
					}

				}
				CIOObject::Release(Party);
			}

		}
	}

	//Call of otp
	if (SkillID == SKILL_KNIGHT_CALLOFONTARGETPOINT)
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

						int BuffValue = 0;
						CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IMembers.GetOffset() + 364));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 550);

						if (Buff)
							BuffValue = *(DWORD*)(Buff + 12);

						CIOCriticalSection::Leave((void*)((char*)IMembers.GetOffset() + 364));

						if (CChar::IsNormal(Members) && IsValid() && IMembers.GetClass() != CLASS_MAGE)
						{
							if (IsInRange(IMembers, IConfig::CallRANGE))
							{
								IMembers.CancelBuff(73);
								IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));

								IConfig::CallCheck callCheck = IConfig::CallCheck();

								callCheck.CasterOffset = GetOffset();
								callCheck.ReciverOffset = IMembers.GetOffset();
								callCheck.SkillID = SkillID;
								IConfig::CallOfEvasionOTP[IMembers.GetPID()] = callCheck;
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else
			{
				int BuffValue = 0;
				CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)GetOffset() + 364));
				int Buff = CChar::FindBuff((int)GetOffset(), 560);

				if (Buff)
					BuffValue = *(DWORD*)(Buff + 12);

				CIOCriticalSection::Leave((void*)((char*)GetOffset() + 364));
				if (!IsBuff(73))
				{
					this->Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
				else
				{
					CancelBuff(73);

					this->Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of Recovery
	if (SkillID == SKILL_KNIGHT_CALLOFRECOVERY)
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
							IConfig::CallCheck callCheck = IConfig::CallCheck();
							if (!IMembers.IsBuff(38))
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IConfig::CallCheck callCheck = IConfig::CallCheck();
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == CLASS_MAGE)
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
									else
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));


									callCheck.CasterOffset = GetOffset();
									callCheck.ReciverOffset = IMembers.GetOffset();
									callCheck.SkillID = SkillID;
									IConfig::CallOfRecovery[IMembers.GetPID()] = callCheck;
								}
							}

							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IMembers.CancelBuff(38);
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
									else
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));

									callCheck.CasterOffset = GetOffset();
									callCheck.ReciverOffset = IMembers.GetOffset();
									callCheck.SkillID = SkillID;
									IConfig::CallOfRecovery[IMembers.GetPID()] = callCheck;
								}

							}
						}

					}
					CIOObject::Release(Party);
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
	if (SkillID == SKILL_KNIGHT_CALLOFPHYSICALATTACK)
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
						int BuffValue = 0;
						CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IMembers.GetOffset() + 364));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 560);

						if (Buff)
							BuffValue = *(DWORD*)(Buff + 12);

						CIOCriticalSection::Leave((void*)((char*)IMembers.GetOffset() + 364));

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

									IConfig::CallCheck callCheck = IConfig::CallCheck();

									callCheck.CasterOffset = GetOffset();
									callCheck.ReciverOffset = IMembers.GetOffset();
									callCheck.SkillID = SkillID;

									IConfig::CallOfPhysicalAttack[IMembers.GetPID()] = callCheck;

									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								}
							}
							else
							{
								if (IsInRange(IMembers, IConfig::CallRANGE))
								{
									IMembers.RemoveMinAttack(BuffValue);
									IMembers.RemoveMaxAttack(BuffValue);
									IMembers.CancelBuff(74);
									IMembers.CancelBuff(560);


									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);

									IConfig::CallCheck callCheck = IConfig::CallCheck();

									callCheck.CasterOffset = GetOffset();
									callCheck.ReciverOffset = IMembers.GetOffset();
									callCheck.SkillID = SkillID;

									IConfig::CallOfPhysicalAttack[IMembers.GetPID()] = callCheck;

									_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
								}
							}
						}

					}
					CIOObject::Release(Party);
				}
			}
			else
			{

				int BuffValue = 0;
				CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)GetOffset() + 364));
				int Buff = CChar::FindBuff((int)GetOffset(), 560);

				if (Buff)
					BuffValue = *(DWORD*)(Buff + 12);

				CIOCriticalSection::Leave((void*)((char*)GetOffset() + 364));


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
					RemoveMinAttack(BuffValue);
					RemoveMaxAttack(BuffValue);

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
	if (SkillID == SKILL_KNIGHT_HEALASONE)
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
								IMembers.AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
							}
						}
					}
					_ShowBattleAnimation(GetOffset(), 29);
					CIOObject::Release(Party);
				}
			}
			else
			{

				AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
				IncreaseHp(self_heal);
				_ShowBattleAnimation(GetOffset(), 29);
			}
		}
	}

	//call of puri
	if (SkillID == SKILL_KNIGHT_PURGECONDITIONS)
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
					CIOObject::Release(Party);
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


void __fastcall CKnight::SpinSlash()
{
	int pSkill = GetSkillPointer(SKILL_KNIGHT_SPINSLASH);

	if (IsValid() && pSkill)
	{
		ISkill ISkill((void*)pSkill);
		int nMana = (ISkill.GetGrade() == 1) ? 209 : (200 + (ISkill.GetGrade() * 20));

		if (!ISkill.GetGrade() || GetCurMp() < nMana)
			return;

		if (IsValid() && CPlayer::IsWState((int)GetOffset(), 12))
		{
			int Around = GetObjectListAround(3);

			while (Around)
			{
				ICharacter Object((void*)*(DWORD*)Around);

				if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
					OktayDamageArea(Object, CalculateFormula(ISkill,Object), ISkill.GetIndex());

				Around = CBaseList::Pop((void*)Around);
			}

			_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());
			RemoveDeathBlow(GetDeathBlow());
			DecreaseMana(nMana);
		}
	}
}