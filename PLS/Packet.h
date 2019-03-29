void __fastcall Packet(__int32 Player, void *edx, int packet, void *pPacket, int pPos)
{
	IChar IPlayer((void*)Player);
	if (IPlayer.IsOnline())
	{
		//IPlayer.SystemMessage(Int2String(packet), TEXTCOLOR_PUPIL);

		if (packet == 33)
		{
			int IID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &IID);
			int Recheck = 0, Check = 0, Value = 0, Item = 0;
			Undefined::CreateMonsterValue((char *)Player + 1068, (int)&Value, (int)&IID);
			Check = Undefined::Check((int)((char *)Player + 1068), (int)&Recheck);

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
				if (Buffs.count(Itemx.CheckIndex()))
				{
					if (!IPlayer.IsBuff(Buffs[ItemID].BuffIndex))
					{
						IPlayer.Buff(Buffs[ItemID].BuffIndex, Buffs[ItemID].Duration, 0);
						IPlayer.Buff(Buffs[ItemID].SecondBuffIndex, Buffs[ItemID].Duration + 10,0);
						int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), Buffs[ItemID].BuffIndex);

						if (Buffs[ItemID].PhysAttack)
						{
							(*(DWORD*)(Buff + 12)) = IPlayer.GetMinPhyAttack() / Buffs[ItemID].PhysAttack;
							IPlayer.AddMinPhysAttack((*(DWORD*)(Buff + 12)));

							(*(DWORD*)(Buff + 16)) = IPlayer.GetMaxPhyAttack() / Buffs[ItemID].PhysAttack;
							IPlayer.AddMaxPhysAttack((*(DWORD*)(Buff + 16)));
						}
						else if(Buffs[ItemID].MagicAttack)
						{
							(*(DWORD*)(Buff + 12)) = IPlayer.GetMinMagAttack() / Buffs[ItemID].MagicAttack;
							IPlayer.AddMinMagicAttack((*(DWORD*)(Buff + 12)));

							(*(DWORD*)(Buff + 16)) = IPlayer.GetMaxMagAttack() / Buffs[ItemID].MagicAttack;
							IPlayer.AddMaxMagicAttack((*(DWORD*)(Buff + 16)));
						}

						if (Buffs[ItemID].IconKey != 0)
						{
							IPlayer.SetBuffIcon(Buffs[ItemID].Duration*1000, 0, 0, Buffs[ItemID].IconKey);
						}
						if (Buffs[ItemID].Strength)
						{
							IPlayer.AddStr(Buffs[ItemID].Strength);
						}
						if (Buffs[ItemID].Health)
						{
							IPlayer.AddHp(Buffs[ItemID].Health);
						}
						if (Buffs[ItemID].Int)
						{
							IPlayer.AddInt(Buffs[ItemID].Int);
						}
						if (Buffs[ItemID].Wisdom)
						{
							IPlayer.AddWis(Buffs[ItemID].Wisdom);
						}
						if (Buffs[ItemID].Agility)
						{
							IPlayer.AddAgi(Buffs[ItemID].Agility);
						}

						if (Buffs[ItemID].OTP)
						{
							IPlayer.AddOTP(Buffs[ItemID].OTP);
						}

						if (Buffs[ItemID].Evasion)
						{
							IPlayer.AddEva(Buffs[ItemID].Evasion);
						}

						if (Buffs[ItemID].DEF)
						{
							IPlayer.AddDef(Buffs[ItemID].DEF);
						}

						if (Buffs[ItemID].HP)
						{
							IPlayer.IncreaseMaxHp(Buffs[ItemID].HP);
						}

						if (Buffs[ItemID].MP)
						{
							IPlayer.IncreaseMaxMp(Buffs[ItemID].MP);
						}

					}
					else
					{
						IPlayer.SystemMessage("This buff is already active, try again later!",TEXTCOLOR_RED);
						return;
					}
				}

				if (Itemx.CheckIndex() == ScrollItemID)
				{
					//if (!IPlayer.IsBuff(60) && !IPlayer.IsBuff(61) && !IPlayer.IsBuff(62) && !IPlayer.IsBuff(63) && !IPlayer.IsBuff(64) && !IPlayer.IsBuff(51) && !IPlayer.IsBuff(52) && !IPlayer.IsBuff(54) && !IPlayer.IsBuff(56) && !IPlayer.IsBuff(57))
					//{
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
						//IPlayer.SetBuffIcon(7200, 0, 0, 62);
						return;
					//}
					/*else
					{
						IPlayer.SystemMessage("Your scrolls and potions are still active!", TEXTCOLOR_RED);
						return;
					}*/
				}


				//if (IPlayer.IsOnline() && Itemx.CheckIndex() == 2359)
				//{
				//	IPlayer.CancelBuff(222);
				//	IPlayer.CancelBuff(240);
				//}
			}

		}

		if (packet == 51)
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
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (IPlayer.GetLevel() < D4Instance::MinLevel)
				{
					IPlayer.SystemMessage("Your level is too low to start instance", TEXTCOLOR_RED);
					return;
				}

				if (!Party)
				{
					IPlayer.SystemMessage("You need to be in party to start Instance", TEXTCOLOR_RED);
					return;
				}

				if (!CParty::IsHead((int)Party, (int)IPlayer.Offset))
				{
					IPlayer.SystemMessage("You are not the party leader so you cannot start Instance", TEXTCOLOR_RED);
					return;
				}


				int PartySize = 0;

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));
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

					void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());


					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));

						IMembers.Buff(666, D4Instance::Time, 0);
						IMembers.Teleport(D4Instance::MapNumber, D4Instance::SpawnX, D4Instance::SpawnY);
						IMembers.ScreenTime(D4Instance::Time);
						IMembers.SystemMessage("Instance started! GL&HF", TEXTCOLOR_GREEN);
						PartySize++;
					}

					D4Instance::PartySize = PartySize;
				}



				D4Instance::IsUp = true;
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



							//if (IPlayer.IsBuff(222))
							//{
							//	IPlayer.SystemMessage("Cooldown", TEXTCOLOR_RED);
							//	return;
							//}

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
						IPlayer.Buff(222, 3600, 0);
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

					if (!CPlayer::FindItem(IPlayer.GetOffset(), LawlessZone::MovingTrinketID, 1))
					{
						IPlayer.SystemMessage("You dont have Moving Trinket", TEXTCOLOR_RED);
						return;
					}

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

					IPlayer.SetBuffIcon(LawlessZone::Time, 1, 4510, 430);

					IPlayer.Buff(LawlessZone::BuffID, LawlessZone::Time, 0);
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
					void *Partyia = (void*)CParty::FindParty(IPlayer.GetPartyID());

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
							IChar IMembers((void*)*(DWORD*)((void*)i));
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

		if (packet == 43)
		{
			int SkillID = 0;
			int ID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID,&ID);



			if (IPlayer.GetClass() == 2 && SkillID == 16 &&FocusShotON == true)
			{
				int pSkill = IPlayer.GetSkillPointer(16);
				if (pSkill)
				{
					CheckFocus[IPlayer.GetPID()] = GetTickCount();
				}
			}

			if (IPlayer.GetClass() == 1 && SkillID == 74 && IPlayer.GetSpecialty() == 23 && IceArrowON == true)
			{
				if (CheckIceArrow.count(IPlayer.GetPID()) && CheckIceArrow.find(IPlayer.GetPID())->second.Delay > GetTickCount())
				{
					IPlayer.SystemMessage("Invalid skill prepare time detected!", TEXTCOLOR_RED);
					return;
				}

				if (CheckIceArrow.count(IPlayer.GetPID()) && CheckIceArrow.find(IPlayer.GetPID())->second.Cooldown > GetTickCount())
				{
					IPlayer.SystemMessage("Invalid skill cooldown time detected!", TEXTCOLOR_RED);
					return;
				}
			}
		}
		if (packet == 16)
		{

			int SkillID = 0;
			int kappa = CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
			int pSkill = IPlayer.GetSkillPointer(SkillID);

			IPlayer.Buff(313, 3, 0);
			DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;
			
			if (SkillID == 74 && IPlayer.GetClass() == 1)
			{
				SkillID = 99;
			}

			if (SkillID == 6 && IPlayer.GetClass() == 3&&IPlayer.IsBuff(329))
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

			if (CooldownCheck > GetTickCount()&&(!IPlayer.IsBuff(5605)&&!IPlayer.IsBuff(295)))
			{

					IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
					return;

			}
			else {
				CooldownTable[IPlayer.GetPID() + 4000000000 + (SkillID * 1000000)] = GetTickCount() + CdTime + DelayTime;
			}

			std::ofstream SkillLog;
			time_t my_time = time(NULL);
			std::string SkillLogFile = "./Log/LogSkillUse.txt";
			SkillLog.open(SkillLogFile, std::ios_base::out | std::ios::app);
			SkillLog << "------|Name: " << IPlayer.GetName() << "------|Class: " << IPlayer.GetClass() << "------|SkillID: " <<SkillID << std::endl;
			SkillLog.close();
			
			if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
			{
				if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
					return;

			}

			if (IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 &&(SkillID == 4 || SkillID == 9 || SkillID == 23 || SkillID == 31 ||SkillID == 42 || SkillID == 75))
			{
				ActivateShiny(IPlayer, kappa, pPos);
			}

			//Knight Skills

			if (IPlayer.GetClass() == 0)
			{
				if (SkillID == 38 && IPlayer.GetSpecialty() == 23 &&SpinSlashON == true)
				{
					SpinSlash(IPlayer);
					return;
				}

				if (SkillID == 43 && IPlayer.GetSpecialty() == 23 && SwordDanceON == true)
				{
					SwordDance(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 42 && IPlayer.GetSpecialty() == 43&& ProvocationOfBlowON== true)
				{
					ProvocationOfBlow(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 41 &&  PowerfulWideningWoundON == true)
				{
					PowerfulWideningWound(IPlayer, kappa, pPos);
					return;
				}

				if ((SkillID == 23 || SkillID == 27 || SkillID == 28 || SkillID == 29 || SkillID == 31 || SkillID == 32) && CallsON == true)
				{
					Calls(pSkill, edx, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 26 && SacrificeON == true)
				{
					Sacrifice(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 15 && ShieldAttackON== true)
				{
					ShieldAttack(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 3 && LightningSlashON == true)
				{
					LightningSlash(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 5 && TranscendentalBlowON == true)
				{
					TranscendentalBlow(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}


				if (SkillID == 16 && PowerfulUpwardSlashON == true)
				{
					PowerfulUpwardSlash(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 17 && BrutalAttackON == true)
				{
					BrutalAttack(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 25 && HalfSwingON == true)
				{
					HalfSwing(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && TheBoomofEarthON == true)
				{
					TheBoomOfEarth(IPlayer);
					return;
				}

				if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && ThewaveofEarthON == true)
				{
					ThewaveofEarth(IPlayer);
					return;
				}

				if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && ShoutOfDefenseON == true)
				{
					ShoutOfDefense(IPlayer);
					return;
				}

				if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ShoutOfFightingSpiritON == true)
				{
					ShoutOfFightingSpirit(IPlayer);
					return;
				}

			}

			//Mage skills

			if (IPlayer.GetClass() == 1)
			{
				if (SkillID == 8 && HealON == true)
				{
					Heal(pSkill, kappa, (int)IPlayer.GetOffset());
					return;
				}

				if ((SkillID == 10) && CureON == true)
				{
					Cure(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if ((SkillID == 22) && CureON == true)
				{
					Cure2(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if ((SkillID == 35) && CureON == true)
				{
					Cure3(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 9 && ShockWaveON == true)
				{
					ShockWave(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 61 && AmnesiaON == true)
				{
					Amnesia(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 54 && PurificationON == true)
				{
					Purification(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
				}

				

				if (SkillID == 34 && SummonsON == true)
				{
					Summons(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
					return;
				}


				if (SkillID == 41 &&ChainLightningON==true)
				{
					ChainLightning(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 40 && SoulDestructionON == true)
				{
					SoulDestruction(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}


				if (SkillID == 45 && IceStormON == true)
				{
					IceStorm(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 48 && FireStormON == true)
				{
					FireStorm(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 43 && ThunderStormON == true)
				{
					ThunderStorm(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 65 && IPlayer.GetSpecialty() == 23 &&FlameInjectionON==true)
				{
					FlameInjection(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 66 && IPlayer.GetSpecialty() == 23&&IcicleON==true)
				{
					Icicle(IPlayer);
					return;
				}

				if (SkillID == 67 && IPlayer.GetSpecialty() == 23 &&LightningArrowON==true)
				{
					LightningArrow(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 72 && IPlayer.GetSpecialty() == 43 && TherapeuticTouchON == true)
				{
					TherapeuticTouch(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 73 && IPlayer.GetSpecialty() == 23 && FireballON == true)
				{
					Fireball(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 99 && IPlayer.GetSpecialty() == 23 &&IceArrowON == true&&(IPlayer.IsBuff(295)||IPlayer.IsBuff(5605)))
				{
					IceArrow(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 75 && IPlayer.GetSpecialty() == 23 && ThunderboltON == true)
				{
					Thunderbolt(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && PunishmentON == true)
				{
					Punishment(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ReleasingTheEnergyON == true)
				{
					ReleasingTheEnergy(IPlayer);
					return;
				}

				if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && IncapacitationON == true)
				{
					Incapacitation(IPlayer);
					return;
				}

				if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && BombingON == true)
				{
					Bombing(IPlayer);
					return;
				}

			}

			//Archer skills

			if (IPlayer.GetClass() == 2)
			{
				if (SkillID == 18 &&LifeAbsorptionON==true)
				{
					LifeAbsorption(pSkill, edx, IPlayer.GetOffset(), (char*)kappa, (char*)pPos);
					return;
				}

				if (SkillID == 16 && IPlayer.IsValid() && FocusShotON== true)
				{
					FocusShot(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 21 && MysteriousArrowON == true)
				{
					MysteriousArrow(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 6 && FlamyArrowON == true)
				{
					FlamyArrow(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 4 && PassiveAttackON == true)
				{
					PassiveAttack(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 14 && BlowUpArrowON == true)
				{
					BlowUpArrow(pSkill, IPlayer.GetOffset(), kappa, pPos);
					return;
				}

				if (SkillID == 10 && MuscleSolidationON == true)
				{
					MuscleSolidation(pSkill, kappa, (int)IPlayer.GetOffset());
					return;
				}
				if (SkillID == 45 && BuffRemoverON == true)
				{
					BuffRemover(pSkill, edx, (int)IPlayer.GetOffset(), kappa, pPos);
				}

				if (SkillID == 47 && IPlayer.GetSpecialty() == 23 && ArrowRainON == true)
				{
					ArrowRain(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 49 && IPlayer.GetSpecialty() == 43 && ArrowExplosionON==true)
				{
					ArrowExplosion(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 50 && IPlayer.GetSpecialty() == 43 && VirulentArrowON==true)
				{
					VirulentArrow(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 51 && IPlayer.GetSpecialty() == 23 && CombativeSpiritON == true)
				{
					CombativeSpirit(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && ArrowsoftheMasterON == true)
				{
					ArrowsOfTheMaster(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && OneHitStrikeON == true)
				{
					OneHitStrike(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && MassiveFireON == true)
				{
					MassiveFire(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && SpiritOfTheArrowsON == true)
				{
					SpiritOfTheArrows(IPlayer, kappa, pPos);
					return;
				}

				
			}

			//Thief skills

			if (IPlayer.GetClass() == 3)
			{
				if (SkillID == 33 && IPlayer.GetSpecialty() == 23 && WrathOfHeavenON==true)
				{
					IPlayer.CancelBuff(329);
					IPlayer.CancelBuff(40);
					WrathOfHeaven(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 32 &&ShadowSlashON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					ShadowSlash(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 36 &&SpinBladeON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					SpinBlade(IPlayer);
					return;
				}

				if (SkillID == 28 && LightningSlashThiefON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					LightningSlashThief(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 19 &&SpinAttackON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					SpinAttack(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 22 &&ArmorBreakerON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					ArmorBreaker(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 23 &&TwinBladeStrikeON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					TwinBladeStrike(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 18 && FinalBlowON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					FinalBlow(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 15 && AnkleAmputateON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					AnkleAmputate(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 16 && VitalStrikeON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					VitalStrike(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 14 && FatalWoundON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					FatalWound(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 17 &&RuptureON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					Rupture(IPlayer, kappa, pPos);
					return;
				}

				if (SkillID == 21 &&SuicidalBlowON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					SuicidalBlow(IPlayer, kappa, pPos);
					return;

				}

				if (SkillID == 20 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(4848) && CounterAttackON == true)
				{
					int pSkill = IPlayer.GetSkillPointer(20);

					if (pSkill)
					{
						ISkill xSkill((void*)pSkill);
						int nSkillGrade = xSkill.GetGrade();
						int nMana = nSkillGrade * 30 + 45;

						if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
						{
							IPlayer.Buff(4848, 30, 0);
							IPlayer.Buff(4849, 35, 0);
							IPlayer.SetBuffIcon(30000, 0, 2019, 217);
							IPlayer.DecreaseMana(nMana);
							IPlayer._ShowBattleAnimation(IPlayer, 20);
							CChar::CancelAllBuff(IPlayer.GetOffset(), 4877);
						}
					}

					return;
				}

				if (SkillID == 63 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(4877) && CounterOffensiveON==true)
				{
					int pSkill = IPlayer.GetSkillPointer(63);

					if (pSkill)
					{
						ISkill xSkill((void*)pSkill);
						int nSkillGrade = xSkill.GetGrade();
						int nMana = nSkillGrade * 30 + 50;

						if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
						{
							IPlayer.Buff(4877, 30, 0);
							IPlayer.Buff(4878, 35, 0);
							IPlayer.SetBuffIcon(30000, 0, 2427, 323);
							IPlayer.DecreaseMana(nMana);
							IPlayer._ShowBattleAnimation(IPlayer, 63);
							CChar::CancelAllBuff(IPlayer.GetOffset(), 4848);
						}
					}
					return;
				}

				if (SkillID == 92 && IPlayer.GetSpecialty() == 23 && CriticalDiffusionON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					CriticalDiffusion(IPlayer);
					return;
				}

				if (SkillID == 90 && IPlayer.GetSpecialty() == 23 && CriticalStrikeON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					CriticalStrike(IPlayer,kappa,pPos);
					return;
				}

				if (SkillID == 91 && IPlayer.GetSpecialty() == 43 && StrikeOfGodON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					StrikeOfGod(IPlayer);
					return;
				}

				if (SkillID == 93 && IPlayer.GetSpecialty() == 43 && DestroyingArmorON == true)
				{
					if (IPlayer.IsBuff(329))
					{
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
					DestroyingArmor(IPlayer);
					return;
				}

			}

		}

		if (packet == 84)
		{
			int SkillID = 0;
			int kappa = CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);

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




				//IPlayer.SystemMessage(Int2String(SkillID), TEXTCOLOR_RED);
				if (SkillID == 101)
				{
					ActivateShiny(IPlayer, kappa, pPos);
				}

				if (SkillID == 113 && RevolveAttackON == true)
				{
					RevolveAttack(IPlayer);
					return;
				}

				if (SkillID == 114 &&WhirlwindFeatherON == true)
				{
					WhirlwindFeather(IPlayer);
					return;
				}

				if (SkillID == 115&& BloodSuctionON == true)
				{
					BloodSuction(IPlayer, kappa, pPos);
					return;
				}


				if (SkillID == 116 &&EggThunderboltON == true)
				{
					EggThunderbolt(IPlayer);
					return;
				}
			}
			
			
		}

		CPlayer::Process((void*)Player, packet, (void*)pPacket, pPos);
	}

}
