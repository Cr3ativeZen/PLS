#ifndef PACKET_H
#define PACKET_H


void PacketWoodenBox(ICharacter IPlayer);
void PacketLeaveParty(ICharacter IPlayer);
void PacketUseItem(__int32 Player, ICharacter IPlayer, void* pPacket, int pPos);
void PacketAcceptQuest(ICharacter IPlayer, void* pPacket, int pPos);
void PacketSkillAnimation(ICharacter IPlayer, void* pPacket, int pPos);
void PacketUseSkill(__int32 Player, ICharacter IPlayer, void* pPacket, int pPos);
void PacketAnimalUseSkill(ICharacter IPlayer, void* pPacket, int pPos);

void WritePacketToFile(ICharacter IPlayer,ToFile WHICH_FILE,const std::string &str_to_write)
{
	
	std::string type_for_dir;
	std::string type_for_file;
	std::string Nick = IPlayer.GetName();
	std::string FilePath = ("./ZenLogs/Characters/");

	time_t now = time(0);
	tm* timePtr = localtime(&now);
	std::string date = Int2String(timePtr->tm_mday)+ "_" + Int2String(timePtr->tm_mon)+ "_" + Int2String(timePtr->tm_year + 1900)+"_" + Int2String(timePtr->tm_hour);

	char* dt = ctime(&now);

switch (WHICH_FILE)
{

	case SpeedHack:
	{
		type_for_dir = "\\SpeedHack";
		type_for_file = "/SpeedHack/SpeedHackLog-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += Nick;
		FilePath += type_for_file;

		std::string speedlog = SpeedHackLogn+"---" + date+".txt";

		SpeedHackLog.open(speedlog, std::ios_base::out | std::ios::app);
		if (SpeedHackLog)
		{
			SpeedHackLog << str_to_write;
			SpeedHackLog.close();
		}
		ConsoleWriteBlue("Speed hack detected on character: ");
		ConsoleWriteBlue(IPlayer.GetName());
		IPlayer.SystemMessage("Speed Hack Detected, SMD!", TEXTCOLOR_RED);
		IPlayer.Kick();
		break;
	}
	case SkillLogs:
	{
		type_for_dir = "\\SkillLogs";
		type_for_file = "/SkillLogs/SkillLogs-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += Nick;
		FilePath += type_for_file;

		std::string skilllog = SkillLogFile+"---" + date+".txt";
		SkillLog.open(skilllog, std::ios_base::out | std::ios::app);
		if (SkillLog)
		{
			SkillLog << str_to_write;
			SkillLog.close();
		}
		break;
	}
	case Mails:
	{
		type_for_dir = "\\Mails";
		type_for_file = "/Mails/Mails-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += Nick;
		FilePath += type_for_file;
		break;
	}
	case WoodenBox:
	{
		type_for_dir = "\\WoodenBox";
		type_for_file = "/WoodenBox/WoodenBox-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += Nick;
		FilePath += type_for_file;
		break;
	}
	case SkillHacks:
	{
		type_for_dir = "\\SkillHacks";
		type_for_file = "/SkillHacks/SkillHacks-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += Nick;
		FilePath += type_for_file;

		std::string skillhax = "./ZenLogs/SkillHaxLog" + date + ".txt";
		SkillHaxLog.open(skillhax, std::ios_base::out | std::ios::app);
		if (SkillHaxLog)
		{
			SkillHaxLog << str_to_write;
			SkillHaxLog.close();
		}

		break;
	}
	default:
	{
		break;
	}
}
	std::ofstream Folders;
	std::string FileN = "C:\\Users\\root\\Desktop\\Server Side\\ZenLogs\\Characters\\" + Nick;
	//std::string FileN = "C:\\Users\\Admin\\Desktop\\kal\\Shaman ServSide\\ZenLogs\\Characters\\" + Nick;

	char* file = new char[FileN.size() + 1];
	strcpy(file, FileN.c_str());
	if (!dirExists(FileN))
	{
		_mkdir(file);
	}

	delete[] file;
	FileN += type_for_dir;
	file = new char[FileN.size() + 1];
	strcpy(file, FileN.c_str());

	if (!dirExists(FileN))
	{
		_mkdir(file);
	}

	Folders.open(FilePath, std::ios_base::out | std::ios::app);
	if (Folders)
	{
		Folders << str_to_write;
	}

	Folders.close();
	delete[] file;
}


void __fastcall Packet(__int32 Player, void *edx, int packet, void *pPacket, int pPos)
{
	ICharacter IPlayer((void*)Player);
	if (IPlayer.IsOnline())
	{
		switch (packet)
			{
			case PACKET_WOODENBOX:
			{
				if(Logs == true)
					PacketWoodenBox(IPlayer);
				break;
			}
			case PACKET_LEAVEPARTY:
			{
				PacketLeaveParty(IPlayer);
				break;
			}
			case PACKET_USEITEM:
			{
				PacketUseItem(Player, IPlayer, pPacket, pPos);
				break;
			}
			case PACKET_ACCEPTQUEST:
			{
				PacketAcceptQuest(IPlayer, pPacket, pPos);
				break;
			}
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

				if (Logs == true)
				{
					time_t now = time(0);

					char* dt = ctime(&now);

					std::string to_file = "------|Name: ";
					to_file += IPlayer.GetName();
					to_file += "------|Class: ";
					to_file += Int2String(IPlayer.GetClass());
					to_file += "------ | SkillID: ";
					to_file += Int2String(SkillID) + " ";
					to_file += dt;
					WritePacketToFile(IPlayer, SkillLogs, to_file);

					if (CastProtection[IPlayer.GetPID()].animation_check == false && !(SkillID >= 88 && SkillID <= 94))
					{
						switch (IPlayer.GetClass())
						{
						case 0:
						{
							itt = std::find(Kn8WhiteListSkills.begin(), Kn8WhiteListSkills.end(), SkillID);
							if (itt != Kn8WhiteListSkills.end())
							{

								check = true;
							}
							break;

						}
						case 1:
						{
							itt = std::find(MageWhiteListSkills.begin(), MageWhiteListSkills.end(), SkillID);
							if (itt != MageWhiteListSkills.end())
							{

								check = true;
							}
							break;

						}
						case 2:
						{
							itt = std::find(ArcherWhiteListSkills.begin(), ArcherWhiteListSkills.end(), SkillID);
							if (itt != ArcherWhiteListSkills.end())
							{

								check = true;
							}
							break;

						}
						default:
							break;
						}

						if (check == false && IPlayer.GetClass() != 3 && SkillID != 1 && SkillID != 0)
						{
							IPlayer.SystemMessage("Hax Detected!", TEXTCOLOR_RED);
							WritePacketToFile(IPlayer, SkillHacks, to_file);
							IPlayer.Kick();

						}
					}
				}

				if (CastProtection[IPlayer.GetPID()].animation_check == true)
				{
					CastProtection[IPlayer.GetPID()].animation_check = false;
					CastProtection[IPlayer.GetPID()].SkillID = 0;
				}

				if (SkillID == 74 && IPlayer.GetClass() == 1)
				{
					SkillID = 99;
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


				if (CooldownTable.count(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)))
					CooldownCheck = CooldownTable.find(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000))->second;


				if ((IPlayer.IsBuff(5605) && (SkillID == 99 || SkillID == 74)))
				{

				}
				else if (CooldownCheck > GetTickCount())
				{

					IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
					return;

				}
				else
				{
					CooldownTable[IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)] = GetTickCount() + CdTime + DelayTime;
				}




				if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
				{
					if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
						return;

				}

				//if (IPlayer.IsValid() && IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 && (SkillID == 4 || SkillID == 9 || SkillID == 23 || SkillID == 31 || SkillID == 42 || SkillID == 75))
				//{
				//	CMage mage((void*)Player);
				//	mage.ActivateShiny(PACKET, pPos);
				//	// no return here because it still needs to execute the proper skill.
				//}

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

														IConfig::CallOfDefense[Member.GetPID()].CasterOffset = IPlayer.GetOffset();
														IConfig::CallOfDefense[Member.GetPID()].ReciverOffset = Member.GetOffset();
														IConfig::CallOfDefense[Member.GetPID()].SkillID = nSkillGrade;

														(*(void(__thiscall**)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
													}
												}

											}
										}
									}
									else
									{
										CChar::CancelAllBuff(Playere.GetOffset(), 28);
										(*(void(__thiscall**)(int, int))(*(DWORD*)Player + 180))(Player, Check);
									}

									Playere._ShowBattleAnimation(Playere, ISkill.GetIndex());
								}
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
			case PACKET_ANIMALUSESKILL:
			{
				PacketAnimalUseSkill(IPlayer, pPacket, pPos);
				break;
			}

		}

		CPlayer::Process((void*)Player, packet, (void*)pPacket, pPos);
	}

}

void PacketWoodenBox(ICharacter IPlayer)
{
	time_t now = time(0);

	char* dt = ctime(&now);
	std::string to_file = "WOODEN BOX OPENNED BY: ";
	to_file += IPlayer.GetName();
	to_file += "--- X " + Int2String(IPlayer.GetX()) + "--- Y " + Int2String(IPlayer.GetY()) + "--- Z " + Int2String(IPlayer.GetX()) + "--- " + dt;
	WritePacketToFile(IPlayer, WoodenBox, to_file);
}

void PacketLeaveParty(ICharacter IPlayer)
{
	if (D4Instance::IsUp == true && D4Instance::PartyMembers.count(IPlayer.GetPID()))
	{
		D4Instance::PartySize--;
		D4Instance::PartyMembers.erase(IPlayer.GetPID());
		if (D4Instance::PartySize <= 1)
		{
			CPlayer::WriteInMap(D4Instance::MapNumber, 0xFF, "dsd", 247, "Party destroyed, instance failed", 1);
			D4Instance::IsUp = false;
			D4Instance::StageNumber = 0;
			D4Instance::MobsKilled = 0;
			InstaConfig();
		}
	}
}
void PacketUseItem(__int32 Player, ICharacter IPlayer, void* pPacket, int pPos)
{
	int IID = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "d", &IID);
	int Recheck = 0, Check = 0, Value = 0, Item = 0;
	Undefined::CreateMonsterValue((char*)Player + 1068, (int)&Value, (int)&IID);
	Check = Undefined::Check((int)((char*)Player + 1068), (int)&Recheck);

	if (!Undefined::CheckValues(&Value, Check))
		return;

	Item = *(DWORD*)(Undefined::GetValue(&Value) + 4);

	if (Item && IID)
	{
		IItem Itemx((void*)Item);
		int ItemID = Itemx.CheckIndex();
		if (ZenTP.count(ItemID))
		{
			if (ZenTP[ItemID].LevelLimit < IPlayer.GetLevel())
			{
				IPlayer.Teleport(ZenTP[ItemID].Map, ZenTP[ItemID].TeleportX, ZenTP[ItemID].TeleportY);
			}
			else
			{
				std::string st = "Your character must be level ";
				st += Int2String(ZenTP[ItemID].LevelLimit);
				st += " or above to use this item!";
				IPlayer.SystemMessage(st, TEXTCOLOR_RED);
				return;
			}
		}

		if (Itemx.CheckIndex() == ScrollItemID)
		{
			if (!IPlayer.IsBuff(60) && !IPlayer.IsBuff(61) && !IPlayer.IsBuff(62) && !IPlayer.IsBuff(63) && !IPlayer.IsBuff(64) && !IPlayer.IsBuff(51) && !IPlayer.IsBuff(52) && !IPlayer.IsBuff(54) && !IPlayer.IsBuff(56) && !IPlayer.IsBuff(57))
			{
				IPlayer.Buff(60, 7200, 5);
				IPlayer.Buff(61, 7200, 10);
				IPlayer.Buff(62, 7200, 5);
				IPlayer.Buff(63, 7200, 10);
				IPlayer.Buff(64, 7200, 5);
				IPlayer.Buff(51, 7200, 10);
				IPlayer.Buff(52, 7200, 10);
				IPlayer.Buff(54, 7200, 5);
				IPlayer.Buff(56, 7200, 10);
				IPlayer.Buff(57, 7200, 5);

				IPlayer.RemoveBuffIcon(0, 0, 0, 60);
				IPlayer.RemoveBuffIcon(0, 0, 0, 61);
				IPlayer.RemoveBuffIcon(0, 0, 0, 63);
				IPlayer.RemoveBuffIcon(0, 0, 0, 64);
				IPlayer.RemoveBuffIcon(0, 0, 0, 65);
				IPlayer.RemoveBuffIcon(0, 0, 0, 67);
				IPlayer.RemoveBuffIcon(0, 0, 0, 68);
				IPlayer.RemoveBuffIcon(0, 0, 0, 69);
				IPlayer.RemoveBuffIcon(0, 0, 0, 70);
				IPlayer.RemoveBuffIcon(0, 0, 0, 71);
				IPlayer.SetBuffIcon(7200, 0, 0, ScrollItemIconKey);
			}
			else
			{
				IPlayer.SystemMessage("Your scrolls and potions are still active!", TEXTCOLOR_RED);
				return;
			}
		}

		if (Itemx.CheckIndex() == InstanceResetScrollID)
		{
			if (IPlayer.IsBuff(240))
			{
				IPlayer.CancelBuff(240);
				IPlayer.SystemMessage("Instance cooldown has been reseted!", TEXTCOLOR_GREEN);
			}
			else
			{
				IPlayer.SystemMessage("You have no instance cooldown!", TEXTCOLOR_GREEN);
				return;
			}
		}

		if (Itemx.CheckIndex() == TradeSystemResetScrollID)
		{
			if (IPlayer.IsBuff(222))
			{
				IPlayer.CancelBuff(222);
				IPlayer.SystemMessage("Delivery cooldown has been reseted!", TEXTCOLOR_GREEN);
			}
			else
			{
				IPlayer.SystemMessage("You have no delivery cooldown!", TEXTCOLOR_GREEN);
				return;
			}
		}

	}

}

void PacketAcceptQuest(ICharacter IPlayer, void* pPacket, int pPos)
{

	int ID = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "d", &ID);
	ID /= 65536;

	if (IPlayer.IsOnline() && ID == D4Instance::QuestID && D4InstanceON == true)
	{
		if (IPlayer.IsBuff(240))
		{
			int Time = IPlayer.GetBuffRemain(240) / 60;
			std::string msg = "You need to wait ";

			if (Time > 0)
			{
				msg = msg + Int2String(Time);
				msg = msg + " minutes to re-join Instance";
			}
			else {
				msg = msg + " less then a minute to re-join Instance";
			}

			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
			return;
		}

		if (D4Instance::IsUp == true)
		{
			IPlayer.SystemMessage("Instance already started try again later", TEXTCOLOR_RED);
			return;
		}
		D4Instance::Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

		if (IPlayer.GetLevel() < D4Instance::MinLevel)
		{
			IPlayer.SystemMessage("Your level is too low to start instance", TEXTCOLOR_RED);
			return;
		}

		if (!D4Instance::Party)
		{
			IPlayer.SystemMessage("You need to be in party to start Instance", TEXTCOLOR_RED);
			return;
		}

		if (!CParty::IsHead((int)D4Instance::Party, (int)IPlayer.Offset))
		{
			IPlayer.SystemMessage("You are not the party leader so you cannot start Instance", TEXTCOLOR_RED);
			return;
		}




		int PartySize = 0;

		if (D4Instance::Party)
		{
			int sizecheck = 0;
			for (int i = CParty::GetPlayerList(D4Instance::Party); i; i = CBaseList::Pop((void*)i))
			{
				int Members = *(DWORD*)((void*)i);
				ICharacter IMembers((void*)*(DWORD*)((void*)i));
				sizecheck++;
				if (IMembers.GetLevel() < D4Instance::MinLevel)
				{
					IPlayer.SystemMessage("Some of your partymates level is too low to start instance", TEXTCOLOR_RED);
					return;
				}
				if (IMembers.IsBuff(240))
				{
					IPlayer.SystemMessage("Some of your partymates still have Instance Cooldown.", TEXTCOLOR_RED);
					return;
				}
			}

			if (sizecheck < D4Instance::MinPartyMembers)
			{
				std::string mes = "Your party need ";
				mes += Int2String(D4Instance::MinPartyMembers);
				mes += " members to start instance";
				IPlayer.SystemMessage(mes, TEXTCOLOR_RED);
				return;
			}

			D4Instance::Party = (void*)CParty::FindParty(IPlayer.GetPartyID());


			for (int i = CParty::GetPlayerList(D4Instance::Party); i; i = CBaseList::Pop((void*)i))
			{
				int Members = *(DWORD*)((void*)i);
				ICharacter IMembers((void*)*(DWORD*)((void*)i));

				IMembers.Buff(666, D4Instance::Time, 0);
				IMembers.Teleport(D4Instance::MapNumber, D4Instance::SpawnX, D4Instance::SpawnY);
				IMembers.ScreenTime(D4Instance::Time);
				IMembers.SystemMessage("Instance started! GL&HF", TEXTCOLOR_GREEN);
				PartySize++;
			}

			D4Instance::PartySize = PartySize;
			D4Instance::IsUp = true;
			D4Instance::Countdown = GetTickCount();


			for (int i = CParty::GetPlayerList(D4Instance::Party); i; i = CBaseList::Pop((void*)i))
			{
				int Members = *(DWORD*)((void*)i);
				ICharacter IMembers((void*)*(DWORD*)((void*)i));
				D4Instance::PartyMembers.insert(IPlayer.GetPID());
			}

		}

		return;
	}


	//if (IPlayer.IsOnline() && ID == TradeSystem::StartQuestID)
	//{
	//	if (IPlayer.GetLevel() < TradeSystem::MinLvl)
	//	{
	//		IPlayer.SystemMessage("Your level is too low to start delivery", TEXTCOLOR_RED);
	//		return;
	//	}
	//	if (IPlayer.IsBuff(104) && IPlayer.IsBuff(477))
	//	{
	//		IPlayer.SystemMessage("You cannot take more than 1 package", TEXTCOLOR_RED);
	//		return;
	//	}



	//	if (IPlayer.IsBuff(222))
	//	{
	//		IPlayer.SystemMessage("Cooldown", TEXTCOLOR_RED);
	//		return;
	//	}

	//	std::string deli = "Trading delivery started ! TRY TO KILL: ";
	//	std::string trader = IPlayer.GetName();
	//	deli = deli + trader;
	//	deli = deli + " and try to steal his trade package!";
	//	CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
	//	IPlayer.Buff(104, 3600, 0);
	//	IPlayer.Buff(477, 3610, 0);
	//	CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::ItemID, 0, 1, 0);

	//}

	//	if (IPlayer.IsOnline() && ID == TradeSystem::EndQuestID)
	//	{
	//		if (!IPlayer.IsBuff(104) && !IPlayer.IsBuff(477))
	//		{
	//			IPlayer.SystemMessage("You are not in delivery mode right now.", TEXTCOLOR_RED);
	//			return;
	//		}
	//		if (!CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::ItemID, 1))
	//		{
	//			IPlayer.SystemMessage("You have no delivery item in inventory", TEXTCOLOR_RED);
	//			return;
	//		}

	//		CPlayer::RemoveItem(IPlayer.GetOffset(), 9, TradeSystem::ItemID, 1);
	//		std::string deli = "Successful deliver by: ";
	//		std::string trader = IPlayer.GetName();
	//		deli = deli + trader;
	//		CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
	//		IPlayer.CancelBuff(104);
	//		IPlayer.CancelBuff(477);
	//		IPlayer.Buff(222, 3600, 0);
	//		CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::RewardItemID, 0, TradeSystem::RewardItemAmount, 0);
	//	}

	//Start quest
	if (TradeSystemON == true)
	{
		if (IPlayer.IsOnline() && ID > TradeSystem::QuestRangeMin && ID < TradeSystem::QuestRangeMax)
		{
			for (TradeSystem::it = TradeSystem::Quest.begin(); TradeSystem::it != TradeSystem::Quest.end(); TradeSystem::it++)
			{
				if (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::it->first.second, 1) && ID == TradeSystem::it->first.first)
				{
					if (IPlayer.GetLevel() < TradeSystem::MinLvl)
					{
						IPlayer.SystemMessage("Your level is too low to start delivery", TEXTCOLOR_RED);
						return;
					}
					if (IPlayer.IsBuff(104) && IPlayer.IsBuff(477))
					{
						IPlayer.SystemMessage("You cannot take more than 1 package", TEXTCOLOR_RED);
						return;
					}

					if (IPlayer.IsBuff(222))
					{
						int Time = IPlayer.GetBuffRemain(222) / 60;
						std::string msg = "You need to wait ";

						if (Time > 0)
						{
							msg = msg + Int2String(Time);
							msg = msg + " minutes to take package";
						}
						else {
							msg = msg + " less then a minute to take package";
						}
						IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
						return;
					}

					IPlayer.SystemMessage("Item found!", TEXTCOLOR_RED);
					CPlayer::RemoveItem(IPlayer.GetOffset(), 9, (TradeSystem::it->first.second), 1);
					CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::it->second, 256, 1, 0);

					std::string deli = "Trading delivery started ! TRY TO KILL ";
					std::string trader = IPlayer.GetName();
					deli = deli + trader;
					deli = deli + " and try to steal his trade package!";
					CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
					IPlayer.Buff(104, 3600, 0);
					IPlayer.Buff(477, 3610, 0);
					return;

				}
			}
		}


		////End quest
		if (IPlayer.IsOnline() && ID > TradeSystem::QuestRangeMin && ID < TradeSystem::QuestRangeMax)
		{

			bool message = false;
			for (TradeSystem::iterat = TradeSystem::Reward.begin(); TradeSystem::iterat != TradeSystem::Reward.end(); TradeSystem::iterat++)
			{
				if (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::iterat->first.second, 1) && ID == TradeSystem::iterat->first.first)
				{
					while (CPlayer::FindItem(IPlayer.GetOffset(), TradeSystem::iterat->first.second, 1))
					{
						CPlayer::RemoveItem(IPlayer.GetOffset(), 9, (TradeSystem::iterat->first.second), 1);
						CItem::InsertItem((int)IPlayer.GetOffset(), 0, TradeSystem::ItemID, 0, TradeSystem::iterat->second, 0);
					}
					IPlayer.SystemMessage("Item found!", TEXTCOLOR_RED);
					message = true;

				}

			}
			if (message == true)
			{
				std::string deli = "Successful deliver by: ";
				std::string trader = IPlayer.GetName();
				deli = deli + trader;
				CPlayer::WriteAll(0xFF, "dsd", 247, deli, 2);
				IPlayer.CancelBuff(104);
				IPlayer.CancelBuff(477);
				IPlayer.Buff(222, TradeSystem::Cooldown, 0);
				IPlayer.SystemMessage("Successful delivery", TEXTCOLOR_BLUE);
				return;
			}
			return;
		}
	}

	if (LawlessZoneON == true)
	{
		if (IPlayer.IsOnline() && ID == LawlessZone::QuestID)
		{
			if (IPlayer.GetLevel() < LawlessZone::MinLvl)
			{
				IPlayer.SystemMessage("Your level is too low to join Lawless Zone", TEXTCOLOR_RED);
				return;
			}

			//if (!CPlayer::FindItem(IPlayer.GetOffset(), LawlessZone::MovingTrinketID, 1))
			//{
			//	IPlayer.SystemMessage("You dont have Moving Trinket", TEXTCOLOR_RED);
			//	return;
			//}

			if (!CPlayer::FindItem(IPlayer.GetOffset(), LawlessZone::TicketID, 1))
			{
				IPlayer.SystemMessage("You dont have the ticket to join Lawless Zone", TEXTCOLOR_RED);
				return;
			}
			else
			{
				CPlayer::RemoveItem(IPlayer.GetOffset(), 0, LawlessZone::TicketID, 1);
			}

			IPlayer.Teleport(LawlessZone::Map, LawlessZone::StartTeleportX, LawlessZone::StartTeleportY);

			IPlayer.SystemMessage("WELCOME TO LAWLESS ZONE!", TEXTCOLOR_PINK);
			IPlayer.SystemMessage("GOOD LUCK HAVE FUN!", TEXTCOLOR_PINK);

			IPlayer.Buff(LawlessZone::BuffID, LawlessZone::Time, 0);
			if (IPlayer.IsBuff(104))
				IPlayer.CancelBuff(104);

			IPlayer.Buff(104, LawlessZone::Time, 0);

			LawlessZone::PointCounter[IPlayer.GetPID()] = 0;
			return;
		}

		if (IPlayer.IsOnline() && ID == LawlessZone::QuitQuestID)
		{
			IPlayer.CancelBuff(LawlessZone::BuffID);
			for (int i = 0; i < 10; i++)
			{
				if (IPlayer.IsBuff(LawlessZone::ExpBuffID[i]))
				{
					IPlayer.CancelBuff(LawlessZone::ExpBuffID[i]);
					IPlayer.RemoveBuffIcon(0, 0, 4500 + i, 1500 + i);
				}
			}
			if (IPlayer.IsBuff(104))
				IPlayer.CancelBuff(104);

			IPlayer.Teleport(0, LawlessZone::ReturnTeleportX, LawlessZone::ReturnTeleportY);
			LawlessZone::PointCounter[IPlayer.GetPID()] = 0;

			IPlayer.SystemMessage("You left the Lawless Zone", TEXTCOLOR_PINK);
			return;
		}
	}

	if (MautaretaON == true)
	{
		if (IPlayer.IsOnline() && ID == Mautareta::QuestID/*&&CPlayer::FindItem(IPlayer.GetOffset(),Mautareta::QuestItemID,1)&&Mautareta::IsUp==false &&Mautareta::PartyLimit<2*/)
		{
			void* Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Mautareta::IsUp == true && Mautareta::PartyLimit == 2)
			{
				IPlayer.SystemMessage("Mautareta already started please try again later...", TEXTCOLOR_RED);
				return;
			}

			if (!Partyia)
			{
				IPlayer.SystemMessage("You need to be in party to start Mautareta", TEXTCOLOR_RED);
				return;
			}

			if (!CParty::IsHead((int)Partyia, (int)IPlayer.Offset))
			{
				IPlayer.SystemMessage("You are not the party leader so you cannot start Mautareta", TEXTCOLOR_RED);
				return;
			}

			if (Mautareta::PartyLimit > 1)
			{
				IPlayer.SystemMessage("There are already 2 parties in.", TEXTCOLOR_RED);
				return;
			}
			IPlayer.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);

			int sizecheck = 0;

			if (Partyia)
			{
				for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
				{
					sizecheck++;
				}
				if (sizecheck < 1)
				{
					IPlayer.SystemMessage("Your party need to be full(2 members for test) to start Mautareta raid!", TEXTCOLOR_RED);
					return;
				}

				for (int i = CParty::GetPlayerList(Partyia); i; i = CBaseList::Pop((void*)i))
				{
					IPlayer.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
					int Members = *(DWORD*)((void*)i);
					ICharacter IMembers((void*)*(DWORD*)((void*)i));
					IMembers.Teleport(Mautareta::Map, Mautareta::StartTeleportX, Mautareta::StartTeleportY);
					IMembers.Buff(254, 1800, 0);
					IMembers.ScreenTime(1800);
				}
				Mautareta::PartyLimit++;
			}
			Mautareta::IsUp = true;
			if (Mautareta::PartyLimit == 2)
			{

				CPlayer::WriteInMap(0, 0xFF, "dsd", 247, "Mautareta spawned!", 1);
				Summon(0, Mautareta::Map, Mautareta::SpawnMautX, Mautareta::SpawnMautY, Mautareta::BossID, 1, 1, 0, 1800, 0);
			}
		}

	}
}

void PacketSkillAnimation(ICharacter IPlayer, void* pPacket, int pPos)
{
	int SkillID = 0;
	int ID = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID, &ID);



	CastProtection[IPlayer.GetPID()].animation_check = true;
	CastProtection[IPlayer.GetPID()].SkillID = SkillID;
	CastProtection[IPlayer.GetPID()].time_used = GetTickCount();



	if (IPlayer.GetClass() == 2 && SkillID == 16 /*&& FocusShotON == true*/)
	{
		int pSkill = IPlayer.GetSkillPointer(16);
		if (pSkill)
		{
			IConfig::CheckFocus[IPlayer.GetPID()] = GetTickCount();
		}
	}

}
void PacketUseSkill(__int32 Player,ICharacter IPlayer, void* pPacket, int pPos)
{
	//int SkillID = 0;
	//int PACKET = CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
	//int pSkill = IPlayer.GetSkillPointer(SkillID);
	//bool check = false;

	//IPlayer.Buff(313, 3, 0);
	//DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;

	//if (IPlayer.IsValid() && IPlayer.IsBuff(349))
	//{
	//	IPlayer.DisableRiding();
	//	return;
	//}

	//if (Logs == true)
	//{
	//	time_t now = time(0);

	//	char* dt = ctime(&now);

	//	std::string to_file = "------|Name: ";
	//	to_file += IPlayer.GetName();
	//	to_file += "------|Class: ";
	//	to_file += Int2String(IPlayer.GetClass());
	//	to_file += "------ | SkillID: ";
	//	to_file += Int2String(SkillID) + " ";
	//	to_file += dt;
	//	WritePacketToFile(IPlayer, SkillLogs, to_file);

	//	if (CastProtection[IPlayer.GetPID()].animation_check == false && !(SkillID >= 88 && SkillID <= 94))
	//	{
	//		switch (IPlayer.GetClass())
	//		{
	//		case 0:
	//		{
	//			itt = std::find(Kn8WhiteListSkills.begin(), Kn8WhiteListSkills.end(), SkillID);
	//			if (itt != Kn8WhiteListSkills.end())
	//			{

	//				check = true;
	//			}
	//			break;

	//		}
	//		case 1:
	//		{
	//			itt = std::find(MageWhiteListSkills.begin(), MageWhiteListSkills.end(), SkillID);
	//			if (itt != MageWhiteListSkills.end())
	//			{

	//				check = true;
	//			}
	//			break;

	//		}
	//		case 2:
	//		{
	//			itt = std::find(ArcherWhiteListSkills.begin(), ArcherWhiteListSkills.end(), SkillID);
	//			if (itt != ArcherWhiteListSkills.end())
	//			{

	//				check = true;
	//			}
	//			break;

	//		}
	//		default:
	//			break;
	//		}

	//		if (check == false && IPlayer.GetClass() != 3 && SkillID != 1 && SkillID != 0)
	//		{
	//			IPlayer.SystemMessage("Hax Detected!", TEXTCOLOR_RED);
	//			WritePacketToFile(IPlayer, SkillHacks, to_file);
	//			IPlayer.Kick();

	//		}
	//	}
	//}

	//if (CastProtection[IPlayer.GetPID()].animation_check == true)
	//{
	//	CastProtection[IPlayer.GetPID()].animation_check = false;
	//	CastProtection[IPlayer.GetPID()].SkillID = 0;
	//}

	//if (SkillID == 74 && IPlayer.GetClass() == 1)
	//{
	//	SkillID = 99;
	//}

	//if (SkillID == 6 && IPlayer.GetClass() == 3 && IPlayer.IsBuff(329))
	//{
	//	IPlayer.CancelBuff(329);
	//	IPlayer.CancelBuff(40);
	//	return;
	//}

	//if (CheckCooldownConfig.count(SkillID + (IPlayer.GetClass() * 100)))
	//{
	//	CdTime = CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.CooldownConfig;
	//	DelayTime = CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.DelayConfig;
	//}


	//if (CooldownTable.count(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)))
	//	CooldownCheck = CooldownTable.find(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000))->second;


	//if ((IPlayer.IsBuff(5605) && (SkillID == 99 || SkillID == 74)))
	//{

	//}
	//else if (CooldownCheck > GetTickCount())
	//{

	//	IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
	//	return;

	//}
	//else
	//{
	//	CooldownTable[IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)] = GetTickCount() + CdTime + DelayTime;
	//}




	//if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
	//{
	//	if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
	//		return;

	//}

	//if (IPlayer.IsValid() && IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 && (SkillID == 4 || SkillID == 9 || SkillID == 23 || SkillID == 31 || SkillID == 42 || SkillID == 75))
	//{
	//	//ActivateShiny(IPlayer, PACKET, pPos);
	//	// no return here because it still needs to execute the proper skill.
	//}





	//switch (IPlayer.GetClass())
	//{
	//case CLASS_KNIGHT:
	//{
	//	CKnight knight((void*)Player);
	//	switch (SkillID)
	//	{
	//		case SKILL_KNIGHT_POWERFULUPWARDSLASH:
	//		{
	//			knight.PowerfulUpwardSlash(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_SPINSLASH:
	//		{
	//			knight.SpinSlash();
	//			return;
	//		}
	//		case SKILL_KNIGHT_HALFSWING:
	//		{
	//			knight.HalfSwing(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_BRUTALATTACK:
	//		{
	//			knight.BrutalAttack(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_LIGHTNINGSLASH:
	//		{
	//			knight.LightningSlash(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_POWERFULWIDENINGWOUND:
	//		{
	//			knight.PowerfulWideningWound(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_PROVOCATIONOFBLOW:
	//		{
	//			knight.ProvocationOfBlow(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_SACRIFICE:
	//		{
	//			knight.Sacrifice(PACKET, pPos);
	//			return;
	//		}
	//		case SKILL_KNIGHT_SHOUTOFDEFENSE:
	//		{
	//			knight.ShoutOfDefense();
	//			return;
	//		}
	//		case SKILL_KNIGHT_SHOUTOFFIGHTINGSPIRIT:
	//		{
	//			knight.ShoutOfFightingSpirit();
	//			return;
	//		}
	//		case SKILL_KNIGHT_THEWAVEOFEARTH:
	//		{
	//			knight.TheWaveOfEarth();
	//			return;
	//		}
	//		case SKILL_KNIGHT_THEBOOMOFEARTH:
	//		{
	//			knight.TheBoomOfEarth();
	//			return;
	//		}
	//		case SKILL_KNIGHT_TRANSCENDENTALBLOW:
	//		{
	//			knight.TranscendentalBlow(PACKET, pPos);
	//			return;
	//		}
	//		
	//	}
	//break;
	//}

	//case CLASS_MAGE:
	//{
	//	CMage mage((void*)Player);
	//	switch (SkillID)
	//	{
	//	case SKILL_MAGE_CURE:
	//	{
	//		mage.Cure(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_MAGE_CURE2:
	//	{
	//		mage.Cure2(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_MAGE_CURE3:
	//	{
	//		mage.Cure3(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_MAGE_HEAL:
	//	{
	//		mage.Heal();
	//		return;
	//	}
	//	case SKILL_MAGE_CHAINLIGHTNING:
	//	{
	//		mage.ChainLightning(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_MAGE_AMNESIA:
	//	{
	//		mage.Amnesia(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_MAGE_SOULDESTRUCTION:
	//	{
	//		mage.SoulDestruction(PACKET, pPos);
	//		return;
	//	}
	//	}
	//	break;
	//}
	//case CLASS_ARCHER:
	//{
	//	CArcher archer((void*)Player);
	//	switch (SkillID)
	//	{
	//	case SKILL_ARCHER_BLOWUPARROW:
	//	{
	//		archer.BlowUpArrow(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_FLAMYARROW:
	//	{
	//		archer.FlamyArrow(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_MUSCLESOLIDATION:
	//	{
	//		archer.MuscleSolidation();
	//		return;
	//	}
	//	case SKILL_ARCHER_PASSIVEATTACK:
	//	{
	//		archer.PassiveAttack(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_FOCUSSHOT:
	//	{
	//		archer.FocusShot(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_LIFEABSORPTION:
	//	{
	//		archer.LifeAbsorption(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_MYSTERIOUSARROW:
	//	{
	//		archer.MysteriousArrow(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_ARROWEXPLOSION:
	//	{
	//		archer.ArrowExplosion(PACKET, pPos);
	//		return;
	//	}

	//	case SKILL_ARCHER_ARROWRAIN:
	//	{
	//		archer.ArrowRain(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_VIRULENTARROW:
	//	{
	//		archer.VirulentArrow(PACKET, pPos);
	//		return;
	//	}
	//	case SKILL_ARCHER_COMBATIVESPIRIT:
	//	{
	//		archer.CombativeSpirit(PACKET, pPos);
	//		return;
	//	}
	//	}

	//	break;
	//}
	//case CLASS_THIEF:
	//{
	//	break;
	//}
	//default:
	//	break;
	//}

	////Knight Skills

	//if (IPlayer.GetClass() == 0)
	//{
	//	if (SkillID == 38 && IPlayer.GetSpecialty() == 23 &&SpinSlashON == true)
	//	{
	//		SpinSlash(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 43 && IPlayer.GetSpecialty() == 23 && SwordDanceON == true)
	//	{
	//		SwordDance(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 42 && IPlayer.GetSpecialty() == 43&& ProvocationOfBlowON== true)
	//	{
	//		ProvocationOfBlow(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 41 &&  PowerfulWideningWoundON == true)
	//	{
	//		PowerfulWideningWound(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if ((SkillID == 23 || SkillID == 27 || SkillID == 28 || SkillID == 29 || SkillID == 31 || SkillID == 32) && CallsON == true)
	//	{
	//		Calls(pSkill, edx, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 19 && CallsON == true)
	//	{
	//		ICharacter Playere((void*)Player);

	//		void* pSkill = (void*)Playere.GetSkillPointer(19);
	//		if (Playere.IsValid())
	//		{
	//			ISkill ISkill(pSkill);
	//			int nSkillGrade = ISkill.GetGrade();
	//			int Action = 0, Check = 0;
	//			Check = (*(int(__thiscall **)(void *, int))(*(DWORD*)pSkill + 80))(pSkill, Player);

	//			if (nSkillGrade && Check && Playere.IsValid())
	//			{
	//				if (Playere.IsParty())
	//				{
	//					void *Party = (void*)CParty::FindParty(Playere.GetPartyID());

	//					if (Party)
	//					{
	//						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
	//						{
	//							int Members = *(DWORD*)((void*)i);

	//							if (CChar::IsNormal(Members) && Playere.IsValid())
	//							{
	//								CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));


	//								ICharacter Member((void*)Members);

	//								if (Playere.IsInRange(Member, CallRANGE))
	//								{
	//									int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);

	//									CallOfDefense[Member.GetPID()].CasterOffset = IPlayer.GetOffset();
	//									CallOfDefense[Member.GetPID()].ReciverOffset = Member.GetOffset();
	//									CallOfDefense[Member.GetPID()].SkillID = nSkillGrade;

	//									(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
	//								}
	//							}

	//						}
	//					}
	//				}
	//				else 
	//				{
	//					CChar::CancelAllBuff(Playere.GetOffset(),28);
	//					(*(void(__thiscall **)(int, int))(*(DWORD*)Player + 180))(Player, Check);
	//				}

	//				Playere._ShowBattleAnimation(Playere, ISkill.GetIndex());
	//			}
	//		}
	//		return;
	//	}

	//	if (SkillID == 26 && SacrificeON == true)
	//	{
	//		Sacrifice(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 15 && ShieldAttackON== true)
	//	{
	//		ShieldAttack(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}


	//	if (SkillID == 3 && LightningSlashON == true)
	//	{
	//		LightningSlash(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}


	//	if (SkillID == 5 && TranscendentalBlowON == true)
	//	{
	//		TranscendentalBlow(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}


	//	if (SkillID == 16 && PowerfulUpwardSlashON == true)
	//	{
	//		PowerfulUpwardSlash(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 17 && BrutalAttackON == true)
	//	{
	//		BrutalAttack(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 25 && HalfSwingON == true)
	//	{
	//		HalfSwing(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && TheBoomofEarthON == true)
	//	{
	//		TheBoomOfEarth(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && ThewaveofEarthON == true)
	//	{
	//		ThewaveofEarth(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && ShoutOfDefenseON == true)
	//	{
	//		ShoutOfDefense(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ShoutOfFightingSpiritON == true)
	//	{
	//		ShoutOfFightingSpirit(IPlayer);
	//		return;
	//	}

	//}

	////Mage skills

	//if (IPlayer.GetClass() == 1)
	//{
	//	if (SkillID == 8 && HealON == true)
	//	{
	//		Heal(pSkill, pPacket, (int)IPlayer.GetOffset());
	//		return;
	//	}

	//	if ((SkillID == 10) && CureON == true)
	//	{
	//		Cure(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if ((SkillID == 22) && CureON == true)
	//	{
	//		Cure2(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if ((SkillID == 35) && CureON == true)
	//	{
	//		Cure3(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 9 && ShockWaveON == true)
	//	{
	//		ShockWave(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 61 && AmnesiaON == true)
	//	{
	//		Amnesia(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 54 && PurificationON == true)
	//	{
	//		Purification(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//	}

	//	

	//	if (SkillID == 34 && SummonsON == true)
	//	{
	//		Summons(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}


	//	if (SkillID == 41 &&ChainLightningON==true)
	//	{
	//		ChainLightning(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 40 && SoulDestructionON == true)
	//	{
	//		SoulDestruction(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}


	//	if (SkillID == 45 && IceStormON == true)
	//	{
	//		IceStorm(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 48 && FireStormON == true)
	//	{
	//		FireStorm(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 43 && ThunderStormON == true)
	//	{
	//		ThunderStorm(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 65 && IPlayer.GetSpecialty() == 23 &&FlameInjectionON==true)
	//	{
	//		FlameInjection(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 66 && IPlayer.GetSpecialty() == 23&&IcicleON==true)
	//	{
	//		Icicle(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 67 && IPlayer.GetSpecialty() == 23 &&LightningArrowON==true)
	//	{
	//		LightningArrow(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 72 && IPlayer.GetSpecialty() == 43 && TherapeuticTouchON == true)
	//	{
	//		TherapeuticTouch(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 73 && IPlayer.GetSpecialty() == 23 && FireballON == true)
	//	{
	//		Fireball(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 99 && IPlayer.GetSpecialty() == 23 &&IceArrowON == true&&(IPlayer.IsBuff(295)||IPlayer.IsBuff(5605)))
	//	{
	//		IceArrow(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 75 && IPlayer.GetSpecialty() == 23 && ThunderboltON == true)
	//	{
	//		Thunderbolt(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && PunishmentON == true)
	//	{
	//		Punishment(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ReleasingTheEnergyON == true)
	//	{
	//		ReleasingTheEnergy(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && IncapacitationON == true)
	//	{
	//		Incapacitation(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && BombingON == true)
	//	{
	//		Bombing(IPlayer);
	//		return;
	//	}

	//}

	////Archer skills

	//if (IPlayer.GetClass() == 2)
	//{
	//	if (SkillID == 18 &&LifeAbsorptionON==true)
	//	{
	//		LifeAbsorption(pSkill, edx, IPlayer.GetOffset(), (char*)pPacket, (char*)pPos);
	//		return;
	//	}

	//	if (SkillID == 16 && IPlayer.IsValid() && FocusShotON== true)
	//	{
	//		FocusShot(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 21 && MysteriousArrowON == true)
	//	{
	//		MysteriousArrow(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 6 && FlamyArrowON == true)
	//	{
	//		FlamyArrow(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 4 && PassiveAttackON == true)
	//	{
	//		PassiveAttack(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 14 && BlowUpArrowON == true)
	//	{
	//		BlowUpArrow(pSkill, IPlayer.GetOffset(), pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 10 && MuscleSolidationON == true)
	//	{
	//		MuscleSolidation(pSkill, pPacket, (int)IPlayer.GetOffset());
	//		return;
	//	}
	//	if (SkillID == 45 && BuffRemoverON == true)
	//	{
	//		BuffRemover(pSkill, edx, (int)IPlayer.GetOffset(), pPacket, pPos);
	//	}

	//	if (SkillID == 47 && IPlayer.GetSpecialty() == 23 && ArrowRainON == true)
	//	{
	//		ArrowRain(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 49 && IPlayer.GetSpecialty() == 43 && ArrowExplosionON==true)
	//	{
	//		ArrowExplosion(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 50 && IPlayer.GetSpecialty() == 43 && VirulentArrowON==true)
	//	{
	//		VirulentArrow(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 51 && IPlayer.GetSpecialty() == 23 && CombativeSpiritON == true)
	//	{
	//		CombativeSpirit(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ArrowsoftheMasterON == true)
	//	{
	//		ArrowsOfTheMaster(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && OneHitStrikeON == true)
	//	{
	//		OneHitStrike(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && MassiveFireON == true)
	//	{
	//		MassiveFire(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && SpiritOfTheArrowsON == true)
	//	{
	//		SpiritOfTheArrows(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	
	//}

	////Thief skills

	//if (IPlayer.GetClass() == 3)
	//{
	//	if (SkillID == 33 && IPlayer.GetSpecialty() == 23 && WrathOfHeavenON==true)
	//	{
	//		IPlayer.CancelBuff(329);
	//		IPlayer.CancelBuff(40);
	//		WrathOfHeaven(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 32 &&ShadowSlashON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		ShadowSlash(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 36 &&SpinBladeON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		SpinBlade(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 28 && LightningSlashThiefON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		LightningSlashThief(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 19 &&SpinAttackON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		SpinAttack(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 22 &&ArmorBreakerON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		ArmorBreaker(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 23 &&TwinBladeStrikeON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		TwinBladeStrike(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 18 && FinalBlowON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		FinalBlow(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 15 && AnkleAmputateON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		AnkleAmputate(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 16 && VitalStrikeON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		VitalStrike(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 14 && FatalWoundON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		FatalWound(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 17 &&RuptureON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		Rupture(IPlayer, pPacket, pPos);
	//		return;
	//	}

	//	if (SkillID == 21 &&SuicidalBlowON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		SuicidalBlow(IPlayer, pPacket, pPos);
	//		return;

	//	}

	//	if (SkillID == 20 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(4848) && CounterAttackON == true)
	//	{
	//		int pSkill = IPlayer.GetSkillPointer(20);

	//		if (pSkill)
	//		{
	//			ISkill xSkill((void*)pSkill);
	//			int nSkillGrade = xSkill.GetGrade();
	//			int nMana = nSkillGrade * 30 + 45;

	//			if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
	//			{
	//				IPlayer.Buff(4848, 30, 0);
	//				IPlayer.Buff(4849, 35, 0);
	//				IPlayer.SetBuffIcon(30000, 0, 2019, 217);
	//				IPlayer.DecreaseMana(nMana);
	//				IPlayer._ShowBattleAnimation(IPlayer, 20);
	//				CChar::CancelAllBuff(IPlayer.GetOffset(), 4877);
	//			}
	//		}

	//		return;
	//	}

	//	if (SkillID == 63 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(4877) && CounterOffensiveON==true)
	//	{
	//		int pSkill = IPlayer.GetSkillPointer(63);

	//		if (pSkill)
	//		{
	//			ISkill xSkill((void*)pSkill);
	//			int nSkillGrade = xSkill.GetGrade();
	//			int nMana = nSkillGrade * 30 + 50;

	//			if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
	//			{
	//				IPlayer.Buff(4877, 30, 0);
	//				IPlayer.Buff(4878, 35, 0);
	//				IPlayer.SetBuffIcon(30000, 0, 2427, 323);
	//				IPlayer.DecreaseMana(nMana);
	//				IPlayer._ShowBattleAnimation(IPlayer, 63);
	//				CChar::CancelAllBuff(IPlayer.GetOffset(), 4848);
	//			}
	//		}
	//		return;
	//	}

	//	if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && CriticalDiffusionON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		CriticalDiffusion(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && CriticalStrikeON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		CriticalStrike(IPlayer,pPacket,pPos);
	//		return;
	//	}

	//	if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && StrikeOfGodON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		StrikeOfGod(IPlayer);
	//		return;
	//	}

	//	if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && DestroyingArmorON == true)
	//	{
	//		if (IPlayer.IsBuff(329))
	//		{
	//			IPlayer.CancelBuff(329);
	//			IPlayer.CancelBuff(40);
	//		}
	//		DestroyingArmor(IPlayer);
	//		return;
	//	}

	//}

}
void PacketAnimalUseSkill(ICharacter IPlayer, void* pPacket, int pPos)
{

	int SkillID = 0;
	int PACKET = CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);

	DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;

	if (CheckEggCooldownConfig.count(SkillID))
	{
		CdTime = CheckEggCooldownConfig.find(SkillID)->second.EggCooldownConfig;
		DelayTime = CheckEggCooldownConfig.find(SkillID)->second.EggDelayConfig;
	}

	if (CooldownCheck > GetTickCount())
	{
		IPlayer.SystemMessage("Invalid egg skill time detected!", TEXTCOLOR_RED);
		return;
	}
	else {
		EggCooldownTable[IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)] = GetTickCount() + CdTime + DelayTime;
	}

	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(), 512))
	{
		if (EggCooldownTable.count(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)))
			CooldownCheck = EggCooldownTable.find(IPlayer.GetPID() + 4000000000 + (SkillID * 1000000))->second;


		//if (SkillID == 101)
		//{
		//	//ActivateShiny(IPlayer, PACKET, pPos);
		//}

		//if (SkillID == 113 && RevolveAttackON == true)
		//{
		//	RevolveAttack(IPlayer);
		//	return;
		//}

		//if (SkillID == 114 && WhirlwindFeatherON == true)
		//{
		//	//WhirlwindFeather(IPlayer);
		//	return;
		//}

		//if (SkillID == 115 && BloodSuctionON == true)
		//{
		//	BloodSuction(IPlayer, PACKET, pPos);
		//	return;
		//}


		//if (SkillID == 116 && EggThunderboltON == true)
		//{
		//	//EggThunderbolt(IPlayer);
		//	return;
		//}
	}
}


#endif