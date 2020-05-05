#ifndef _PLAYER_H
#define _PLAYER_H
#include "Packet.h"
int __fastcall Tick(void *Player, void *edx)
{
	ICharacter IPlayer(Player);

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(70) && IPlayer.IsBuff(550))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

		IPlayer.RemoveEva(*(DWORD*)(Buff + 12));

		IPlayer.CancelBuff(70);
		IPlayer.CancelBuff(550);
	}

	if (IPlayer.IsOnline() && !IPlayer.IsBuff(74) && IPlayer.IsBuff(560))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

		IPlayer.RemoveMinAttack(*(DWORD*)(Buff + 12));
		IPlayer.RemoveMaxAttack(*(DWORD*)(Buff + 12));

		IPlayer.CancelBuff(74);
		IPlayer.CancelBuff(560);
	}




	if (IPlayer.IsOnline() && !IPlayer.IsBuff(10) && IPlayer.IsBuff(500) && IPlayer.IsBuff(501))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 500);
		int Buff2 = CChar::FindBuff((int)IPlayer.GetOffset(), 501);

		IPlayer.RemoveMinPhysAttack(*(DWORD*)(Buff + 12));
		IPlayer.RemoveMaxPhysAttack(*(DWORD*)(Buff2 + 12));

		IPlayer.CancelBuff(10);
		IPlayer.CancelBuff(500);
		IPlayer.CancelBuff(501);
	}




	if (IPlayer.IsBuff(790))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 790);
		if (IPlayer.GetCurHp() > 1000 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
		{
			IPlayer.DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	if (IPlayer.IsBuff(791))
	{
		int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 791);
		if (IPlayer.GetCurHp() > 200 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
		{
			IPlayer.DecreaseHp(*(DWORD*)(Buff + 12));
		}

	}

	std::map<std::pair<int, int>, bool>::iterator it;
	it = IConfig::SkillEnabled.find({ 0,31 });
	if (it != IConfig::SkillEnabled.end() && it->second)
	{
		//evasion off
		if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(550) && IPlayer.IsBuff(70))
		{
			void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);
			if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
			{
				int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

				IPlayer.RemoveEva(*(DWORD*)(Buff + 12));

				IPlayer.CancelBuff(70);
				IPlayer.CancelBuff(550);
			}


		}
		//evasion on
		if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(550) && IConfig::CallOfEvasionOTP[IPlayer.GetPID()].SkillID == 27)
		{
			void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
			{
				if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
				{
					ISkill ISkill((void*)Caster.GetSkillPointer(27));
					IPlayer.Buff(70, 0, 0);
					IPlayer.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
					IPlayer.AddEva((ISkill.GetGrade() - 1) * 5 + 10);
				}
			}
		}

		//Copa off
		if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(560) && IPlayer.IsBuff(74))
		{
			void* CasterOffset = IConfig::CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
			{
				int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

				IPlayer.RemoveMinAttack(*(DWORD*)(Buff + 12));
				IPlayer.RemoveMaxAttack(*(DWORD*)(Buff + 12));

				IPlayer.CancelBuff(74);
				IPlayer.CancelBuff(560);

			}
		}

		//Copa on
		if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(560))
		{
			void* CasterOffset = IConfig::CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
			{
				if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
				{
					ISkill ISkill((void*)Caster.GetSkillPointer(32));

					IPlayer.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
					IPlayer.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

					IPlayer.Buff(74, 0, 0);
					IPlayer.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
				}
			}
		}
		//otp off
		if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(73))
		{

			void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
			{
				IPlayer.CancelBuff(73);

			}
		}

		//otp on
		if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(73) && IConfig::CallOfEvasionOTP[IPlayer.GetPID()].SkillID == 31)
		{

			void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
			{
				if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
				{
					ISkill ISkill((void*)Caster.GetSkillPointer(31));
					IPlayer.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
				}
			}
		}


		//cor off
		if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(38))
		{
			void* CasterOffset = IConfig::CallOfRecovery[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
			{
				IPlayer.CancelBuff(38);

			}
		}

		//cor on
		if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(38))
		{
			void* CasterOffset = IConfig::CallOfRecovery[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
			{
				if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
				{
					ISkill ISkill((void*)Caster.GetSkillPointer(23));
					if (IPlayer.GetSpecialty() == 23 && IPlayer.GetClass() == 1)
					{
						IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
					}
					else
					{
						IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
					}
				}
			}
		}

		//codoff
		if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(28))
		{
			void* CasterOffset = IConfig::CallOfDefense[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);

			if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) && IPlayer.GetOffset() != Caster.GetOffset())
			{
				IPlayer.CancelBuff(28);
			}
		}

		//cod on
		if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(28))
		{
			void* CasterOffset = IConfig::CallOfDefense[IPlayer.GetPID()].CasterOffset;
			ICharacter Caster(CasterOffset);
			int Check = 0;
			void* pSkill = (void*)Caster.GetSkillPointer(19);

			if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset())
			{
				if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
				{
					Check = (*(int(__thiscall**)(void*, int))(*(DWORD*)pSkill + 80))(pSkill, (int)Caster.GetOffset());
					int Buff = (*(int(__thiscall**)(DWORD))(*(DWORD*)Check + 20))(Check);
					(*(void(__thiscall**)(DWORD, DWORD))(*(DWORD*)IPlayer.GetOffset() + 180))((DWORD)IPlayer.GetOffset(), Buff);
				}
			}
		}
	}

	return CPlayer::Tick(Player);
}
#endif