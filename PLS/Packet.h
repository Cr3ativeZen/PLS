#ifndef PACKET_H
#define PACKET_H
#include "Resources.h"
#include "ICharacter.h"
#include "IConfig.h"
#include "CDungeon.h"
#include "ExecuteSkill.h"
void PacketSkillAnimation(ICharacter IPlayer, void* pPacket, int pPos);
void PacketAcceptQuest(ICharacter IPlayer, void* pPacket, int pPos);


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

				if (IPlayer.IsValid() && IPlayer.IsBuff(349))
				{
					IPlayer.DisableRiding();
					return;
				}

				std::map<std::pair<int, int>, IConfig::MySkills>::iterator ite;
				ite = IConfig::SkillCastCheck.find({ IPlayer.GetClass(),SkillID });

				if (ite != IConfig::SkillCastCheck.end() && ite->second.enabled)
				{
					DWORD casttime = IConfig::SkillCastCheck[{IPlayer.GetClass(), SkillID}].casttime;

					std::map<int, IConfig::SkillCheck> ::iterator itsc;
					itsc = IConfig::CastProtection.find(IPlayer.GetPID());

					if (ite->second.animation)
					{

						if (itsc == IConfig::CastProtection.end() || itsc->second.animation_check == false)
						{
							IPlayer.SystemMessage("Invalid skill cast time!", IConfig::TEXTCOLOR_RED);
							return;
						}
						else
							itsc->second.animation_check = false;
					}

					if (itsc != IConfig::CastProtection.end() && casttime + itsc->second.time_used > GetTickCount())
					{
						IPlayer.SystemMessage("Invalid skill cast time!", IConfig::TEXTCOLOR_RED);
						return;
					}


					std::map<std::pair<int, int>, DWORD>::iterator cdit;
					cdit = IConfig::CooldownProtection.find({IPlayer.GetPID(), SkillID});

					if (cdit != IConfig::CooldownProtection.end() && IConfig::CooldownProtection[{IPlayer.GetPID(), SkillID}] > GetTickCount())
					{

						IPlayer.SystemMessage("Invalid cooldown time!", IConfig::TEXTCOLOR_RED);
						return;
					}
					else
						IConfig::CooldownProtection[{IPlayer.GetPID(), SkillID}] = GetTickCount() + ite->second.cooldown;

				}

				if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
				{
					if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48))
						return;
				}

				if (IPlayer.GetClass() == CLASS_MAGE && SkillID == SKILL_MAGE_AMNESIA && IPlayer.GetX() >> 13 == 28 && IPlayer.GetY() >> 13 == 29 )
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}


				if (IPlayer.GetClass() == CLASS_MAGE && SkillID == SKILL_MAGE_AMNESIA && IPlayer.GetX() >> 13 == 29 && IPlayer.GetY() >> 13 == 28)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_MAGE && SkillID == SKILL_MAGE_AMNESIA && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 6)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_MAGE && SkillID == SKILL_MAGE_AMNESIA && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_MAGE && SkillID == SKILL_MAGE_AMNESIA && IPlayer.GetX() >> 13 == 2 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_KNIGHT && SkillID == SKILL_KNIGHT_SPINSLASH && IPlayer.GetX() >> 13 == 28 && IPlayer.GetY() >> 13 == 29)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}


				if (IPlayer.GetClass() == CLASS_KNIGHT && SkillID == SKILL_KNIGHT_SPINSLASH && IPlayer.GetX() >> 13 == 29 && IPlayer.GetY() >> 13 == 28)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_KNIGHT && SkillID == SKILL_KNIGHT_SPINSLASH && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 6)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_KNIGHT && SkillID == SKILL_KNIGHT_SPINSLASH && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_KNIGHT && SkillID == SKILL_KNIGHT_SPINSLASH && IPlayer.GetX() >> 13 == 2 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}


				if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_VIRULENTARROW && IPlayer.GetX() >> 13 == 29 && IPlayer.GetY() >> 13 == 28)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_VIRULENTARROW && IPlayer.GetX() >> 13 == 28 && IPlayer.GetY() >> 13 == 29)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_VIRULENTARROW && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 6)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_VIRULENTARROW && IPlayer.GetX() >> 13 == 0 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
					return;
				}

				if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_VIRULENTARROW && IPlayer.GetX() >> 13 == 2 && IPlayer.GetY() >> 13 == 8)
				{
					IPlayer.SystemMessage("Skill is disabled on this map!", RGB(255, 0, 0));
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
						/*case SKILL_KNIGHT_POWERFULUPWARDSLASH:
						{
							knight.PowerfulUpwardSlash(PACKET, pPos);
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
						}*/
						//case SKILL_KNIGHT_CALLOFDEFENSE:
						//{
						//	knight.Calls((int)pPacket, pPos, SKILL_KNIGHT_CALLOFDEFENSE);
						//	return;
						//}
						//case SKILL_KNIGHT_THEBOOMOFEARTH:
						//{
						//	knight.TheBoomOfEarth();
						//	return;
						//}
						//case SKILL_KNIGHT_COALESCENCEOFRUIN:
						//{
						//	knight.CoalescenceOfRuin(PACKET,pPos);
						//	return;
						//}

						case SKILL_KNIGHT_SPINSLASH:
						{
							knight.SpinSlash();
							return;
						}
						case SKILL_KNIGHT_BRUTALATTACK:
						{
							knight.BrutalAttack(PACKET, pPos);
							return;
						}
						case SKILL_KNIGHT_HALFSWING:
						{
							knight.HalfSwing(PACKET, pPos);
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
						//case SKILL_MAGE_CURE:
						//case SKILL_MAGE_CURE2:
						//case SKILL_MAGE_CURE3:
						//{
						//	mage.Cure(PACKET, pPos, SkillID);
						//	return;
						//}
						//case SKILL_MAGE_HEAL:
						//{
						//	mage.Heal();
						//	return;
						//}

						//case SKILL_MAGE_SUMMONS:
						//{
						//	mage.Summons(PACKET, pPos);
						//	return;
						//}
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
						case SKILL_MAGE_AMNESIA:
						{
							mage.Amnesia(PACKET, pPos);
							return;
						}
						//case SKILL_MAGE_ICERESTRICTION:
						//{
						//	mage.IceRestriction(PACKET, pPos);
						//	return;
						//}
						}
						break;
					}
					case CLASS_ARCHER:
					{
						CArcher archer((void*)Player);
						switch (SkillID)
						{
						/*case SKILL_ARCHER_BLOWUPARROW:
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
						}*/

						//case SKILL_ARCHER_MYSTERIOUSARROW:
						//{
						//	archer.MysteriousArrow(PACKET, pPos);
						//	return;
						//}
						//case SKILL_ARCHER_ARROWDRIZZLE:
						//{
						//	archer.ArrowDrizzle();
						//	return;
						//}
						case SKILL_ARCHER_VIRULENTARROW:
						{
							archer.VirulentArrow(PACKET, pPos);
							return;
						}
						case SKILL_ARCHER_FOCUSSHOT:
						{
							archer.FocusShot(PACKET, pPos);
							return;
						}
						//case SKILL_ARCHER_PAIN:
						//{
						//	archer.Pain(PACKET, pPos);
						//	return;
						//}
						//case SKILL_ARCHER_POISONARROW:
						//{
						//	archer.PoisonArrow(PACKET, pPos);
						//	return;
						//}
						//case SKILL_ARCHER_ARROWEXPLOSION:
						//{
						//	archer.ArrowExplosion(PACKET, pPos);
						//	return;
						//}
						}

						break;
					}
					case CLASS_THIEF:
					{
						CThief thief((void*)Player);
						switch (SkillID)
						{
						case SKILL_THIEF_SHADOWSLASH:
						{
							thief.ShadowSlash(PACKET, pPos);
							return;
						}
						//case SKILL_THIEF_DANCEOFKILLING:
						//{
						//	thief.DanceOfKilling();
						//	return;
						//}
						}
						break;
					}
					default:
						break;
					}

				}
				break;
			}
			case PACKET_ACCEPTQUEST:
			{
				PacketAcceptQuest(IPlayer, pPacket, pPos);
				break;
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

	std::map<std::pair<int, int>, IConfig::MySkills>::iterator it;
	it = IConfig::SkillCastCheck.find({ IPlayer.GetClass(),SkillID});
	
	if (it != IConfig::SkillCastCheck.end() && it->second.animation && it->second.enabled)
	{
		IConfig::SkillCheck castCheck = IConfig::SkillCheck();
		castCheck.animation_check = true;
		castCheck.skillID = SkillID;
		castCheck.time_used = GetTickCount();

		IConfig::CastProtection[IPlayer.GetPID()] = castCheck;
	}


	if (IPlayer.GetClass() == CLASS_ARCHER && SkillID == SKILL_ARCHER_FOCUSSHOT)
	{
		int pSkill = IPlayer.GetSkillPointer(SKILL_ARCHER_FOCUSSHOT);
		if (pSkill)
		{
			IConfig::CheckFocus[IPlayer.GetPID()] = GetTickCount();
		}
	}

}


void PacketAcceptQuest(ICharacter IPlayer, void* pPacket, int pPos)
{
	int ID = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "d", &ID);
	ID = ID >> 16;
	auto it = std::find_if(IConfig::dungeon_map.begin(), IConfig::dungeon_map.end(), [index = ID](const auto& c) {return c.second.quest_id == index;  });
	if (it != IConfig::dungeon_map.end())
		it->second.TeleportIn(IPlayer);
}

#endif