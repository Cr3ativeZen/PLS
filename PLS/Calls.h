#ifndef _CALLS_H
#define _CALLS_H
#include "ExecuteSkill.h"
void __fastcall Calls(int pSkill, void *edx, void* Player, int pPacket, int pPos)
{
	ICharacter IPlayer(Player);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();
	int SkillID = ISkill.GetIndex();

	if (!nSkillGrade)
		return;




	//Call of Evasion
	if (ISkill.GetIndex() == 27)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void *Party = (void*)CParty::FindParty(GetPartyID());

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
								if (IsInRange(IMembers, CallRANGE))
								{
									if (IMembers.IsBuff(73))
									{
										IMembers.CancelBuff(73);
									}

									IMembers.Buff(70, 0, 0);
									IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

									IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

									_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);

									CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;

								}
							}

							else
							{
								if (IsInRange(IMembers, CallRANGE))
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
									CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;

									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);
									_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
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

					Buff(70, 0, 0);
					Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

					AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					AddFxToTarget("test_item_ef_09", 1, 0, 1);
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					if (IsBuff(73))
					{
						CancelBuff(73);
					}
					RemoveEva(*(DWORD*)(static_cast<long long>(Buff) + 12ll));
					CancelBuff(70);
					CancelBuff(550);

					Buff(70, 0, 0);
					Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
					AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					AddFxToTarget("test_item_ef_09", 1, 0, 1);
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of otp
	if (ISkill.GetIndex() == 31)
	{
		int EvaBuff = 0;
		if (IsValid())
		{
			if (IsParty())
			{
				void *Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));
						EvaBuff= CChar::FindBuff((int)IMembers.GetOffset(), 550);

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (!IMembers.IsBuff(73))
							{
								if (IsInRange(IMembers, CallRANGE))
								{
									if (IMembers.IsBuff(70) && IMembers.IsBuff(550))
									{
										IMembers.RemoveEva(*(DWORD*)(EvaBuff + 12));
										IMembers.CancelBuff(70);
										IMembers.CancelBuff(550);
									}
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
									CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;
								}
							}
							else
							{
								if (IsInRange(IMembers, CallRANGE))
								{
									if (IMembers.IsBuff(70) && IMembers.IsBuff(550))
									{
										IMembers.RemoveEva(*(DWORD*)(EvaBuff + 12));
										IMembers.CancelBuff(70);
										IMembers.CancelBuff(550);
									}
									IMembers.CancelBuff(73);
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
									CallOfEvasionOTP[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfEvasionOTP[IMembers.GetPID()].SkillID = SkillID;
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
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
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
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of Recoveryy
	if (ISkill.GetIndex() == 23)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void *Party = (void*)CParty::FindParty(GetPartyID());

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
								if (IsInRange(IMembers, CallRANGE))
								{
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
										CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
										CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
								}
							}

							else
							{
								if (IsInRange(IMembers, CallRANGE))
								{
									IMembers.CancelBuff(38);
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
										CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
										CallOfRecovery[IMembers.GetPID()].CasterOffset = GetOffset();
										CallOfRecovery[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
										CallOfRecovery[IMembers.GetPID()].SkillID = SkillID;
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
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					CancelBuff(38);

					Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of physical attack
	if (ISkill.GetIndex() == 32)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void *Party = (void*)CParty::FindParty(GetPartyID());

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
								if (IsInRange(IMembers, CallRANGE))
								{
									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
									CallOfPhysicalAttack[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfPhysicalAttack[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfPhysicalAttack[IMembers.GetPID()].SkillID = SkillID;

									_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
							else
							{
								if (IsInRange(IMembers, CallRANGE))
								{
									IMembers.RemoveMinAttack(*(DWORD*)(Buff + 12));
									IMembers.RemoveMaxAttack(*(DWORD*)(Buff + 12));
									IMembers.CancelBuff(74);
									IMembers.CancelBuff(560);


									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
									CallOfPhysicalAttack[IMembers.GetPID()].CasterOffset = GetOffset();
									CallOfPhysicalAttack[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									CallOfPhysicalAttack[IMembers.GetPID()].SkillID = SkillID;



									_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
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

					Buff(74, 0, 0);
					Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);


					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
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

					Buff(74, 0, 0);
					Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);

					_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of heal
	if (ISkill.GetIndex() == 29)
	{
		if (IsValid())
		{
			if (IsParty())
			{
				void *Party = (void*)CParty::FindParty(GetPartyID());

				if (Party)
				{
				

					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						ICharacter IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IsValid())
						{
							if (IsInRange(IMembers, CallRANGE))
							{
								IMembers.IncreaseHp(CallofHealBase + (IMembers.GetMaxHp()*CallofHealBasePercentage / 100) + (IMembers.GetMaxHp()*ISkill.GetGrade()*CallofHealPerGradePercentage/100));
								IMembers.AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
							}
						}
					}
					_ShowBattleAnimation(IPlayer, 29);

				}
			}
			else
			{
				AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
				IncreaseHp(CallofHealBase + (GetMaxHp()*CallofHealBasePercentage / 100) + (GetMaxHp()*ISkill.GetGrade()*CallofHealPerGradePercentage/100));
				_ShowBattleAnimation(IPlayer, 29);
			}
		}
	}
	//call of puri
	if (ISkill.GetIndex() == 28)
	{
		int DebuffList[22] = { 7,8,11,15,26,29,39,81,85,86,87,88,89,90,91,92,93,94,105,4001,4002,790 };

			if (IsValid())
			{
				if (IsParty())
				{
					void *Party = (void*)CParty::FindParty(GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							ICharacter IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IsValid())
							{
								if (IsInRange(IMembers, CallRANGE))
								{
									for (int i = 0; i < 22; i++)
									{
										IMembers.CancelBuff(DebuffList[i]);
										IMembers.AddFxToTarget("davi_M635_75", 1, 0, 1);
									}
									IMembers.RemoveBuffIcon(0, 0, 0, 225);
									IMembers.RemoveBuffIcon(0, 0, 0, 224);

									if (IMembers.IsBuff(350))
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
									}
									if (IMembers.IsBuff(339) || IMembers.IsBuff(340))
									{
										if (IMembers.IsBuff(339))
											IMembers.CancelBuff(339);

										if (IMembers.IsBuff(340))
											IMembers.CancelBuff(340);

										IMembers.RemoveBuffIcon(0, 0, 0, 219);

										for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
										{
											if (it->second.PlayerTarget == IMembers.GetOffset())
											{

												ICharacter Caster(it->second.CasterOffset);
												if (Caster.IsOnline())
												{
													ResetFarContinueSkill(Caster);
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

					if (IsBuff(350))
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
					}
					if (IsBuff(339) || IsBuff(340))
					{
						if (IsBuff(339))
							CancelBuff(339);

						if (IsBuff(340))
							CancelBuff(340);

						RemoveBuffIcon(0, 0, 0, 219);

						for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
						{
							if (it->second.PlayerTarget == GetOffset())
							{

								ICharacter Caster(it->second.CasterOffset);
								if (Caster.IsOnline())
								{
									ResetFarContinueSkill(Caster);
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



#endif