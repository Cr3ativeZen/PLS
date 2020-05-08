#ifndef PACKET_H
#define PACKET_H


void PacketSkillAnimation(ICharacter IPlayer, void* pPacket, int pPos);



void __fastcall Packet(__int32 Player, void *edx, int packet, void *pPacket, int pPos)
{
	ICharacter IPlayer((void*)Player);
	if (IPlayer.IsOnline())
	{
		switch (packet)
			{
			
			case PACKET_SKILLANIMATION:
			{
				PacketSkillAnimation(IPlayer, pPacket, pPos);
				break;
			}
			case PACKET_USESKILL:
			{
				int SkillID = 0;
				int PACKET = CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
				int pSkill = IPlayer.GetSkillPointer(SkillID);
				bool check = false;




				IPlayer.Buff(313, 3, 0);
				DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;

				if (IPlayer.IsValid() && IPlayer.IsBuff(349))
				{
					IPlayer.DisableRiding();
					return;
				}





				if (SkillID == 6 && IPlayer.GetClass() == 3 && IPlayer.IsBuff(329))
				{
					IPlayer.CancelBuff(329);
					IPlayer.CancelBuff(40);
					return;
				}

				if (CheckCooldownConfig.count(SkillID + (IPlayer.GetClass() * 100)))
				{
					CdTime = CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.CooldownConfig;
					DelayTime = CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.DelayConfig;
				}


				if (CooldownTable.count(IPlayer.GetPID() + 4000000000 + (static_cast<long long>(SkillID) * 1000000)))
					CooldownCheck = CooldownTable.find(IPlayer.GetPID() + 4000000000 + (static_cast<long long>(SkillID) * 1000000))->second;



				else if (CooldownCheck > GetTickCount())
				{

					IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
					return;

				}
				else
				{
					CooldownTable[IPlayer.GetPID() + 4000000000 + (static_cast<long long>(SkillID) * 1000000)] = GetTickCount() + CdTime + DelayTime;
				}




				if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
				{
					if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
						return;

				}


				std::map<std::pair<int, int>, bool>::iterator it;
				it = IConfig::SkillEnabled.find({ IPlayer.GetClass(),SkillID });
				if ((it != IConfig::SkillEnabled.end() && it->second))
				{

					switch (IPlayer.GetClass())
					{
					case CLASS_KNIGHT:
					{
						CKnight knight((void*)Player);
						switch (SkillID)
						{
						case SKILL_KNIGHT_POWERFULUPWARDSLASH:
						{
							knight.PowerfulUpwardSlash(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_HALFSWING:
						{
							knight.HalfSwing(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_BRUTALATTACK:
						{
							knight.BrutalAttack(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_LIGHTNINGSLASH:
						{
							knight.LightningSlash(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_SACRIFICE:
						{
							knight.Sacrifice(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_TRANSCENDENTALBLOW:
						{   
							knight.TranscendentalBlow(PACKET, pPos);
							return;
						}

						case SKILL_KNIGHT_CALLOFEVASION:
						{

							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_CALLOFEVASION);
							return;

						}
						case SKILL_KNIGHT_CALLOFONTARGETPOINT:
						{
	
							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_CALLOFONTARGETPOINT);
							return;

						}
						case SKILL_KNIGHT_CALLOFPHYSICALATTACK:
						{
							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_CALLOFPHYSICALATTACK);
							return;

						}
						case SKILL_KNIGHT_CALLOFRECOVERY:
						{
							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_CALLOFRECOVERY);
							return;
						}
						case SKILL_KNIGHT_PURGECONDITIONS:
						{
							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_PURGECONDITIONS);
							return;
						}
						case SKILL_KNIGHT_HEALASONE:
						{
							knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_HEALASONE);
							return;
						}
						case SKILL_KNIGHT_SPINSLASH:
						{
							knight.SpinSlash();
							return;
						}

						case SKILL_KNIGHT_CALLOFDEFENSE:
						{

							ICharacter Playere((void*)Player);

							void* pSkill = (void*)Playere.GetSkillPointer(SKILL_KNIGHT_CALLOFDEFENSE);
							if (Playere.IsValid())
							{
								ISkill ISkill(pSkill);
								int nSkillGrade = ISkill.GetGrade();
								int Action = 0, Check = 0;
								Check = (*(int(__thiscall**)(void*, int))(*(DWORD*)pSkill + 80))(pSkill, Player);

								if (nSkillGrade && Check && Playere.IsValid())
								{
									if (Playere.IsParty())
									{
										void* Party = (void*)CParty::FindParty(Playere.GetPartyID());

										if (Party)
										{
											for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
											{
												int Members = *(DWORD*)((void*)i);

												if (CChar::IsNormal(Members) && Playere.IsValid())
												{
													CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));


													ICharacter Member((void*)Members);

													if (Playere.IsInRange(Member, IConfig::CallRANGE))
													{
														int Buff = (*(int(__thiscall**)(DWORD))(*(DWORD*)Check + 20))(Check);

														IConfig::CallCheck callCheck = IConfig::CallCheck();

														callCheck.CasterOffset = IPlayer.GetOffset();
														callCheck.ReciverOffset = Member.GetOffset();
														callCheck.SkillID = nSkillGrade;
														IConfig::CallOfDefense[Member.GetPID()] = callCheck;
														(*(void(__thiscall**)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
													}
												}

											}
											CIOObject::Release(Party);
										}
									}
									else
									{
										CChar::CancelAllBuff(Playere.GetOffset(), 28);
										(*(void(__thiscall**)(int, int))(*(DWORD*)Player + 180))(Player, Check);
									}
								}

								Playere._ShowBattleAnimation(Playere, ISkill.GetIndex());
							}
							return;
						}

						}
						break;
					}

					case CLASS_MAGE:
					{
						CMage mage((void*)Player);
						switch (SkillID)
						{
						case SKILL_MAGE_CURE:
						case SKILL_MAGE_CURE2:
						case SKILL_MAGE_CURE3:
						{
							mage.Cure(PACKET, pPos, SkillID);
							return;
						}
						case SKILL_MAGE_HEAL:
						{
							mage.Heal();
							return;
						}
						case SKILL_MAGE_AMNESIA:
						{
							mage.Amnesia(PACKET, pPos);
							return;
						}
						case SKILL_MAGE_SUMMONS:
						{
							mage.Summons(PACKET, pPos);
							return;
						}
						case SKILL_MAGE_PURIFICATION:
						{
							mage.Purification(PACKET, pPos);
							return;
						}
						case SKILL_MAGE_SHOCKWAVE:
						{
							mage.ShockWave(PACKET, pPos);
							return;
						}
						}
						break;
					}
					case CLASS_ARCHER:
					{
						CArcher archer((void*)Player);
						switch (SkillID)
						{
						case SKILL_ARCHER_BLOWUPARROW:
						{
							archer.BlowUpArrow(PACKET, pPos);
							return;
						}
						case SKILL_ARCHER_FLAMYARROW:
						{
							archer.FlamyArrow(PACKET, pPos);
							return;
						}
						case SKILL_ARCHER_MUSCLESOLIDATION:
						{
							archer.MuscleSolidation();
							return;
						}
						case SKILL_ARCHER_PASSIVEATTACK:
						{
							archer.PassiveAttack(PACKET, pPos);
							return;
						}
						case SKILL_ARCHER_FOCUSSHOT:
						{
							archer.FocusShot(PACKET, pPos);
							return;
						}
						case SKILL_ARCHER_MYSTERIOUSARROW:
						{
							archer.MysteriousArrow(PACKET, pPos);
							return;
						}
						}

						break;
					}
					case CLASS_THIEF:
					{
						break;
					}
					default:
						break;
					}
				}
			}

		}

		CPlayer::Process((void*)Player, packet, (void*)pPacket, pPos);
	}

}



void PacketSkillAnimation(ICharacter IPlayer, void* pPacket, int pPos)
{
	int SkillID = 0;
	int ID = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID, &ID);



	if (IPlayer.GetClass() == 2 && SkillID == 16 /*&& FocusShotON == true*/)
	{
		int pSkill = IPlayer.GetSkillPointer(16);
		if (pSkill)
		{
			IConfig::CheckFocus[IPlayer.GetPID()] = GetTickCount();
		}
	}

}

#endif