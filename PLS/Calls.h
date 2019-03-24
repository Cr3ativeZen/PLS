#ifndef _CALLS_H
#define _CALLS_H
#include "ExecuteSkill.h"
void __fastcall Calls(int pSkill, void *edx, void* Player, int pPacket, int pPos)
{
	IChar IPlayer(Player);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;


	//Call of Evasion
	if (ISkill.GetIndex() == 27)
	{
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 550);

						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (!IMembers.IsBuff(70))
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{

									IMembers.Buff(70, 0, 0);
									IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

									IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);

									//Call[IMembers.GetPID()].CasterOffset = IPlayer.GetOffset();
									//Call[IMembers.GetPID()].ReciverOffset = IMembers.GetOffset();
									//Call[IMembers.GetPID()].SkillID = nSkillGrade;

								}
							}

							else
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.RemoveEva(*(DWORD*)(Buff + 12));
									IMembers.CancelBuff(70);
									IMembers.CancelBuff(550);



									IMembers.Buff(70, 0, 0);
									IMembers.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
									IMembers.AddEva((ISkill.GetGrade() - 1) * 5 + 10);


									IMembers.AddFxToTarget("test_item_ef_09", 1, 0, 1);
									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
						}

					}
				}
			}
			else
			{
				int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

				if (!IPlayer.IsBuff(70))
				{
					IPlayer.Buff(70, 0, 0);
					IPlayer.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);

					IPlayer.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					IPlayer.AddFxToTarget("test_item_ef_09", 1, 0, 1);
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					IPlayer.RemoveEva(*(DWORD*)(Buff + 12));
					IPlayer.CancelBuff(70);
					IPlayer.CancelBuff(550);

					IPlayer.Buff(70, 0, 0);
					IPlayer.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
					IPlayer.AddEva((ISkill.GetGrade() - 1) * 5 + 10);

					IPlayer.AddFxToTarget("test_item_ef_09", 1, 0, 1);
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of otp
	if (ISkill.GetIndex() == 31)
	{
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));


						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (!IMembers.IsBuff(73))
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
								}
							}
							else
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.CancelBuff(73);
									IMembers.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
								}
							}

						}
					}
				}
			}
			else
			{
				if (!IPlayer.IsBuff(73))
				{
					IPlayer.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					IPlayer.CancelBuff(73);

					IPlayer.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of Recoveryy
	if (ISkill.GetIndex() == 23)
	{
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));


						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (!IMembers.IsBuff(38))
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
									}
								}
							}

							else
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.CancelBuff(38);
									if (IMembers.GetSpecialty() == 23 && IMembers.GetClass() == 1)
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
									}
									else
									{
										IMembers.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
									}
								}

							}
						}

					}
				}
			}
			else
			{
				if (!IPlayer.IsBuff(38))
				{
					IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					IPlayer.CancelBuff(38);

					IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}

	//Call of physical attack
	if (ISkill.GetIndex() == 32)
	{
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));
						int Buff = CChar::FindBuff((int)IMembers.GetOffset(), 560);

						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (!IMembers.IsBuff(74))
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);

									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
							else
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									IMembers.RemoveMinAttack(*(DWORD*)(Buff + 12));
									IMembers.RemoveMaxAttack(*(DWORD*)(Buff + 12));
									IMembers.CancelBuff(74);
									IMembers.CancelBuff(560);


									IMembers.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);
									IMembers.Buff(74, 0, 0);
									IMembers.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);



									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
						}

					}
				}
			}
			else
			{
				int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);


				if (!IPlayer.IsBuff(74))
				{

					IPlayer.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
					IPlayer.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

					IPlayer.Buff(74, 0, 0);
					IPlayer.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);


					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					IPlayer.RemoveMinAttack(*(DWORD*)(Buff + 12));
					IPlayer.RemoveMaxAttack(*(DWORD*)(Buff + 12));

					IPlayer.CancelBuff(74);
					IPlayer.CancelBuff(560);


					IPlayer.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
					IPlayer.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

					IPlayer.Buff(74, 0, 0);
					IPlayer.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);

					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}



	//Call of Defense
	if (ISkill.GetIndex() == 19)
	{
		int Check = (*(int(__thiscall **)(void *, int))(*(DWORD*)pSkill + 80))((void*)pSkill,(int)Player);
		int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));


						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{

							if (!IMembers.IsBuff(28))
							{
								if (IPlayer.IsInRange(IMembers, 20))
								{
									(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
							else
							{
								if (IPlayer.IsInRange(IMembers, 20) &&((void*)Members!=(void*)Player))
								{


									CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));

									(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
									IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
								}
							}
						}


					}
				}
			}
			else
			{
				
				if (!IPlayer.IsBuff(28))
				{

					(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)Player + 180))((DWORD)Player, Buff);

					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
				else
				{
					CChar::CancelAllBuff((void*)Player, *(DWORD*)(Check + 4));
					(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)Player + 180))((DWORD)Player, Buff);
					IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
					return;
				}
			}
		}
	}


	//Call of heal
	if (ISkill.GetIndex() == 29)
	{
		if (IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
				

					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (IPlayer.IsInRange(IMembers, 20))
							{
								IMembers.IncreaseHp(CallofHealBase + (IMembers.GetMaxHp()*CallofHealBasePercentage / 100) + (IMembers.GetMaxHp()*ISkill.GetGrade()*CallofHealPerGradePercentage/100));
								IMembers.AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
							}
						}
					}
					IPlayer._ShowBattleAnimation(IPlayer, 29);

				}
			}
			else
			{
				IPlayer.AddFxToTarget("davi_M573_76_bhit", 1, 0, 1);
				IPlayer.IncreaseHp(CallofHealBase + (IPlayer.GetMaxHp()*CallofHealBasePercentage / 100) + (IPlayer.GetMaxHp()*ISkill.GetGrade()*CallofHealPerGradePercentage/100));
				IPlayer._ShowBattleAnimation(IPlayer, 29);
			}
		}
	}
	//call of puri
	if (ISkill.GetIndex() == 28)
	{
		int DebuffList[22] = { 7,8,11,15,26,29,39,81,85,86,87,88,89,90,91,92,93,94,105,4001,4002,790 };

			if (IPlayer.IsValid())
			{
				if (IPlayer.IsParty())
				{
					void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (IPlayer.IsInRange(IMembers, 20))
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

												IChar Caster(it->second.CasterOffset);
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

												IChar Caster(it->second.CasterOffset);
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

												IChar Caster(it->second.CasterOffset);
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
					IPlayer.AddFxToTarget("davi_M635_75", 1, 0, 1);
					for (int i = 0; i < 22; i++)
					{
						IPlayer.CancelBuff(DebuffList[i]);
					}
					IPlayer.RemoveBuffIcon(0, 0, 0, 225);
					IPlayer.RemoveBuffIcon(0, 0, 0, 224);

					if (IPlayer.IsBuff(350))
					{
						IPlayer.CancelBuff(350);
						for (auto it = CheckRuptureContinueSkill.begin(); it != CheckRuptureContinueSkill.end(); ++it)
						{
							if (it->second.PlayerTarget == IPlayer.GetOffset())
							{

								IChar Caster(it->second.CasterOffset);
								if (Caster.IsOnline())
								{
									ResetRuptureContinueSkill(Caster);
									Caster.CancelBuff(5577);
									Caster.CancelBuff(353);
								}
							}
						}
					}
					if (IPlayer.IsBuff(348))
					{
						IPlayer.CancelBuff(348);
						for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
						{
							if (it->second.PlayerTarget == IPlayer.GetOffset())
							{

								IChar Caster(it->second.CasterOffset);
								if (Caster.IsOnline())
								{
									ResetFarContinueSkill(Caster);
									Caster.CancelBuff(5576);
								}
							}
						}
					}
					if (IPlayer.IsBuff(339) || IPlayer.IsBuff(340))
					{
						if (IPlayer.IsBuff(339))
							IPlayer.CancelBuff(339);

						if (IPlayer.IsBuff(340))
							IPlayer.CancelBuff(340);

						IPlayer.RemoveBuffIcon(0, 0, 0, 219);

						for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
						{
							if (it->second.PlayerTarget == IPlayer.GetOffset())
							{

								IChar Caster(it->second.CasterOffset);
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