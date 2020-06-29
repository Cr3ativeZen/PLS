#ifndef _PLAYER_H
#define _PLAYER_H
#include "Resources.h"
int __fastcall Tick(void *Player, void *edx)
{
	ICharacter IPlayer(Player);




	//if (IPlayer.IsOnline() && !IPlayer.IsBuff(70) && IPlayer.IsBuff(550))
	//{
	//	int BuffValue = 0;
	//	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//	int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

	//	if (Buff)
	//		BuffValue = *(DWORD*)(Buff + 12);

	//	CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));

	//	IPlayer.RemoveEva(BuffValue);

	//	IPlayer.CancelBuff(70);
	//	IPlayer.CancelBuff(550);
	//}

	//if (IPlayer.IsOnline() && !IPlayer.IsBuff(74) && IPlayer.IsBuff(560))
	//{
	//	int BuffValue = 0;
	//	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//	int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

	//	if (Buff)
	//		BuffValue = *(DWORD*)(Buff + 12);

	//	CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));

	//	IPlayer.RemoveMinAttack(BuffValue);
	//	IPlayer.RemoveMaxAttack(BuffValue);

	//	IPlayer.CancelBuff(74);
	//	IPlayer.CancelBuff(560);
	//}

	//if (IPlayer.IsOnline() && !IPlayer.IsBuff(10) && IPlayer.IsBuff(500) && IPlayer.IsBuff(501))
	//{
	//	int BuffValue = 0;
	//	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//	int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 500);

	//	if (Buff)
	//		BuffValue = *(DWORD*)(Buff + 12);

	//	int BuffValue2 = 0;
	//	int Buff2 = CChar::FindBuff((int)IPlayer.GetOffset(), 501);

	//	if (Buff2)
	//		BuffValue2 = *(DWORD*)(Buff2 + 12);

	//	CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));


	//	IPlayer.RemoveMinPhysAttack(BuffValue);
	//	IPlayer.RemoveMaxPhysAttack(BuffValue2);

	//	IPlayer.CancelBuff(10);
	//	IPlayer.CancelBuff(500);
	//	IPlayer.CancelBuff(501);
	//}

	//if (IPlayer.IsOnline() && IPlayer.IsBuff(791))
	//{
	//	int BuffValue = 0;
	//	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//	int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 791);

	//	if (Buff)
	//		BuffValue = *(DWORD*)(Buff + 12);

	//	CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));

	//	if (IPlayer.GetCurHp() > 200 && !(CChar::IsGState((int)IPlayer.GetOffset(), 2)))
	//	{
	//		IPlayer.DecreaseHp(BuffValue);
	//	}

	//}

	//std::map<std::pair<int, int>, bool>::iterator it;
	//it = IConfig::SkillEnabled.find({ 0,31 });
	//if (it != IConfig::SkillEnabled.end() && it->second)
	//{
	//	//evasion off
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(550) && IPlayer.IsBuff(70))
	//	{
	//		void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;

	//		ICharacter Caster(CasterOffset);
	//		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) || !Caster.IsValid() && IPlayer.GetOffset() != Caster.GetOffset())
	//		{
	//			//int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);
	//			int BuffValue = 0;
	//			CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//			int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 550);

	//			if (Buff)
	//				BuffValue = *(DWORD*)(Buff + 12);

	//			CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));

	//			IPlayer.RemoveEva(BuffValue);

	//			IPlayer.CancelBuff(70);
	//			IPlayer.CancelBuff(550);
	//		}


	//	}
	//	//evasion on
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(550) && IConfig::CallOfEvasionOTP[IPlayer.GetPID()].SkillID == SKILL_KNIGHT_CALLOFEVASION && IConfig::CallOfEvasionOTP.find(IPlayer.GetPID()) != IConfig::CallOfEvasionOTP.end())
	//	{
	//		void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset() && Caster.IsValid())
	//		{
	//			if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
	//			{
	//				ISkill ISkill((void*)Caster.GetSkillPointer(SKILL_KNIGHT_CALLOFEVASION));
	//				if (ISkill.GetGrade())
	//				{
	//					IPlayer.Buff(70, 0, 0);
	//					IPlayer.Buff(550, 9999999, (ISkill.GetGrade() - 1) * 5 + 10);
	//					IPlayer.AddEva((ISkill.GetGrade() - 1) * 5 + 10);
	//				}
	//			}
	//		}
	//	}

	//	//Copa off
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(560) && IPlayer.IsBuff(74))
	//	{
	//		void* CasterOffset = IConfig::CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) || !Caster.IsValid() && IPlayer.GetOffset() != Caster.GetOffset())
	//		{
	//			int BuffValue = 0;
	//			CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 364));
	//			int Buff = CChar::FindBuff((int)IPlayer.GetOffset(), 560);

	//			if (Buff)
	//				BuffValue = *(DWORD*)(Buff + 12);

	//			CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 364));

	//			IPlayer.RemoveMinAttack(BuffValue);
	//			IPlayer.RemoveMaxAttack(BuffValue);

	//			IPlayer.CancelBuff(74);
	//			IPlayer.CancelBuff(560);

	//		}
	//	}

	//	//Copa on
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(560) && IConfig::CallOfPhysicalAttack.find(IPlayer.GetPID()) != IConfig::CallOfPhysicalAttack.end())
	//	{
	//		void* CasterOffset = IConfig::CallOfPhysicalAttack[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset() && Caster.IsValid())
	//		{
	//			if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
	//			{
	//				ISkill ISkill((void*)Caster.GetSkillPointer(SKILL_KNIGHT_CALLOFPHYSICALATTACK));
	//				if (ISkill.GetGrade())
	//				{
	//					IPlayer.AddMinAttack((ISkill.GetGrade() - 1) * 25 + 50);
	//					IPlayer.AddMaxAttack((ISkill.GetGrade() - 1) * 25 + 50);

	//					IPlayer.Buff(74, 0, 0);
	//					IPlayer.Buff(560, 9999999, (ISkill.GetGrade() - 1) * 25 + 50);
	//				}
	//			}
	//		}
	//	}
	//	//otp off
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(73))
	//	{

	//		void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) || !Caster.IsValid() && IPlayer.GetOffset() != Caster.GetOffset())
	//		{
	//			IPlayer.CancelBuff(73);
	//		}
	//	}

	//	//otp on
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(73) && IConfig::CallOfEvasionOTP[IPlayer.GetPID()].SkillID == SKILL_KNIGHT_CALLOFONTARGETPOINT && IConfig::CallOfEvasionOTP.find(IPlayer.GetPID()) != IConfig::CallOfEvasionOTP.end())
	//	{

	//		void* CasterOffset = IConfig::CallOfEvasionOTP[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset() && Caster.IsValid())
	//		{
	//			if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
	//			{
	//				ISkill ISkill((void*)Caster.GetSkillPointer(SKILL_KNIGHT_CALLOFONTARGETPOINT));
	//				if(ISkill.GetGrade())
	//					IPlayer.Buff(73, 0, ((ISkill.GetGrade() - 1) * 5 + 10));
	//			}
	//		}
	//	}


	//	//cor off
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(38))
	//	{
	//		void* CasterOffset = IConfig::CallOfRecovery[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) || !Caster.IsValid() && IPlayer.GetOffset() != Caster.GetOffset())
	//		{
	//			IPlayer.CancelBuff(38);

	//		}
	//	}

	//	//cor on
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(38) && IConfig::CallOfRecovery.find(IPlayer.GetPID()) != IConfig::CallOfRecovery.end())
	//	{
	//		void* CasterOffset = IConfig::CallOfRecovery[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset()  && Caster.IsValid())
	//		{
	//			if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
	//			{
	//				ISkill ISkill((void*)Caster.GetSkillPointer(SKILL_KNIGHT_CALLOFRECOVERY));
	//				if (ISkill.GetGrade())
	//				{
	//					if (IPlayer.GetSpecialty() == 23 && IPlayer.GetClass() == 1)
	//					{
	//						IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 180 + 200));
	//					}
	//					else
	//					{
	//						IPlayer.Buff(38, 0, ((ISkill.GetGrade() - 1) * 50 + 50));
	//					}
	//				}
	//			}

	//		}
	//	}

	//	//cod off
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && IPlayer.IsBuff(28))
	//	{
	//		void* CasterOffset = IConfig::CallOfDefense[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);

	//		if (IPlayer.GetPartyID() != Caster.GetPartyID() || !IPlayer.IsInRange(Caster, IConfig::CallRANGE) || !Caster.IsValid() && IPlayer.GetOffset() != Caster.GetOffset())
	//		{
	//			CChar::CancelAllBuff(IPlayer.GetOffset(), 28);
	//		}
	//	}

	//	//cod on
	//	if (IPlayer.IsOnline() && IPlayer.IsParty() && !IPlayer.IsBuff(28) && IConfig::CallOfDefense.find(IPlayer.GetPID()) != IConfig::CallOfDefense.end())
	//	{

	//		void* CasterOffset = IConfig::CallOfDefense[IPlayer.GetPID()].CasterOffset;
	//		ICharacter Caster(CasterOffset);
	//		int Check = 0;
	//		ISkill ISkill((void*)Caster.GetSkillPointer(SKILL_KNIGHT_CALLOFDEFENSE));
	//		if (ISkill.GetGrade() && IPlayer.GetPartyID() == Caster.GetPartyID() && IPlayer.GetOffset() != Caster.GetOffset() && Caster.IsValid())
	//		{
	//			if (IPlayer.IsInRange(Caster, IConfig::CallRANGE))
	//			{
	//				int Value = ((ISkill.GetGrade() - 1) * 7) + 16;
	//				int Value2 = ((ISkill.GetGrade() - 1) * 3) + 12;
	//				CChar::CancelAllBuff(IPlayer.GetOffset(), 28);
	//				int AddBuff = CBuff::CreateBuff(28, 0, Value, Value2);
	//				(*(int(__thiscall**)(int, int))(*(DWORD*)IPlayer.GetOffset() + 180))((int)IPlayer.GetOffset(), AddBuff);
	//			}
	//		}
	//	}
	//}

	return CPlayer::Tick(Player);
}
#endif