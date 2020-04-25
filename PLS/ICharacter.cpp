#include <windows.h>
#define HIDWORD(l) ((DWORD)(((DWORDLONG)(l)>>32)&0xFFFFFFFF))
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "ICharacter.h"
#pragma warning (disable : 4244)
#pragma warning (disable : 4018)

ICharacter::ICharacter(void *Offset)
{
	this->Offset = Offset;
}

ICharacter::~ICharacter()
{
}

void *ICharacter::GetOffset()
{
	return this->Offset;
}

int ICharacter::IsOnline()
{
	if ((int)this->GetOffset())
	{
		if (CBase::IsDeleted((int)this->GetOffset()))
			return 0;
		else
			return 1;
	} else {
		return 0;
	}

	return 0;
}

void ICharacter::Announcement(std::string msg, int color)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dsd", 247, msg.c_str(), color);
}

void ICharacter::SystemMessage(std::string msg, int color)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dsd", 248, msg.c_str(), color);
}

int ICharacter::Buff(int id, int time, int value)
{
	if(time < 0)
		return 0;

	if(!this->IsOnline())
		return 0;

	if(this->IsBuff(159) && id != 159)
		return 0;

	CChar::CancelAllBuff(this->GetOffset(), id);
	int AddBuff = CBuff::CreateBuff(id, time, value, (int)this->GetOffset());
	*(DWORD*)(AddBuff + 12) = value;
	(*(int (__thiscall **)(int, int))(*(DWORD *)(int)this->GetOffset() + 180))((int)this->GetOffset(), AddBuff);
	return 1;
}

int ICharacter::GetAdmin()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 456);
	else
		return 0;
}

int ICharacter::GetMinPhyAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 128);
	else
		return 0;
}



int ICharacter::GetMaxPhyAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 132);
	else
		return 0;
}

int ICharacter::GetMinMagAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 136);
	else
		return 0;
}

int ICharacter::GetMaxMagAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 140);
	else
		return 0;
}

int ICharacter::GetX()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset()+0x14c);
	else
		return 0;
}

int ICharacter::GetY()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset()+0x150);
	else
		return 0;
}

int ICharacter::GetZ()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset()+0x154);
	else
		return 0;
}

int ICharacter::GetMap()
{
	if (this->IsOnline())
	{
		int* offset = (int*)this->GetOffset();
		return offset[79];
	} else {
		return 0;
	}
}

void ICharacter::Teleport(int Map, int X, int Y)
{
	if (this->IsOnline() && X > 0 && Y > 0)
	{
		if (this->IsBuff(349))
			this->DisableRiding();

		if (CChar::IsGState((int)this->GetOffset(),2))
			this->Revive();

		int *GetSetXY = new int[1];
			GetSetXY[0] = X;
	GetSetXY[1] = Y;
		CPlayer::Teleport((int)this->GetOffset(), Map, (int)GetSetXY, 0, 1);
		delete[] GetSetXY;
	}
}

void ICharacter::Kick()
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 45, "b", 1);
		Undefined::ForKick(*(void **)((int)this->GetOffset() + 1676), 1);
	}
}

void ICharacter::SetX(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset()+332) = Value;
}

void ICharacter::SetY(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset()+336) = Value;
}

void ICharacter::SetZ(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset()+340) = Value;
}

int ICharacter::IsValid()
{
	if (this->IsOnline())
	{
		if (this->GetType() == 0)
		{
			if(CChar::IsNormal((int)this->GetOffset()))
				return 1;
			else
				return 0;
		}

		if (this->GetType() == 1)
		{
			if(!CMonster::IsRemoved(this->GetOffset()))
				return 1;
			else
				return 0;
		}

		return 0;
	} else {
		return 0;
	}
}

int ICharacter::IsParty()
{
	if (this->IsOnline())
	{
		if(*(DWORD*)((int)this->GetOffset() + 1016))
			return 1;
		else
			return 0;
	} else {
		return 0;
	}
}

int ICharacter::GetPartyID()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 1016);
	else
		return 0;
}

int ICharacter::GetID()
{
	if (this->GetOffset())
		return *(DWORD*)((int)this->GetOffset() + 28);
	else
		return 0;
}

int ICharacter::GetUID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 448);
	else
		return 0;
}

int ICharacter::GetPID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 452);
	else
		return 0;
}

int ICharacter::GetCurHp()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 272);
	else
		return 0;
}

int ICharacter::GetCurMp()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 276);
	else
		return 0;
}

void ICharacter::DecreaseMana(int amount)
{
	if (this->IsOnline())
	{
		if (this->GetCurMp() >= amount)
			(*(int (__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 8, 0, amount);
	}
}

void ICharacter::IncreaseMana(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 8, 1, amount);
}

int ICharacter::GetType()
{
	if (this->IsOnline())
	{
		return *(DWORD*)((int)this->GetOffset() + 24) - 1;
	} else {
		return 2;
	}
}

void ICharacter::_ShowBattleAnimation(ICharacter Target, int skillID, int SkillGrade)
{
	if (this->IsValid())
		CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwb", skillID, this->GetID(), Target.GetID(), Target.GetType(), SkillGrade, 0, 0, true);
}

int ICharacter::GetClass()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 460);
	else
		return 10;
}

int ICharacter::GetTransformGrade()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 1112);
	else
		return 0;
}

void ICharacter::CancelBuff(int BuffID)
{
	if (this->IsOnline())
		CChar::CancelAllBuff(this->GetOffset(),BuffID);
}

int ICharacter::IsBuff(int id)
{
	if (this->IsOnline() && id >= 0 && id <= 7000)
	{
		if (CChar::GetBuffRemain(this->GetOffset(),id))
			return 1;
		else
			return 0;
	} else {
		return 0;
	}
}

int ICharacter::GetLevel()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 60);
	else
		return 0;
}

void ICharacter::BoxMsg(std::string msg)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "ds", 249, msg.c_str());
}

const char *ICharacter::GetName()
{
	if (this->IsOnline())
		return (const char*)((int)this->GetOffset() + 32);
	else
		return "Nothing";
}

int ICharacter::GetSkillPointer(int SkillID)
{
	if (this->IsOnline() && this->GetType() == 0)
		return *((DWORD *)((int)this->GetOffset() + 624) + SkillID + 2);
	else
		return 0;
}

void ICharacter::AddMinAttack(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),27,1,amount,amount);
}

void ICharacter::RemoveMinAttack(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),27,0,amount,amount);
}

void ICharacter::AddMaxAttack(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),28,1,amount,amount);
}

void ICharacter::RemoveMaxAttack(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),28,0,amount,amount);
}

void ICharacter::DecreaseMaxHp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 5, 0, amount);
}

void ICharacter::IncreaseMaxHp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 5, 1, amount);
}

void ICharacter::DecreaseMaxMp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 6, 0, amount);
}

void ICharacter::IncreaseMaxMp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 6, 1, amount);
}

void ICharacter::AddHp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 1, amount);
}

void ICharacter::RemoveHp(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 0, amount);
}

void ICharacter::AddStr(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 1, amount);
}

void ICharacter::RemoveStr(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 0, amount);
}

void ICharacter::AddInt(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 1, amount);
}

void ICharacter::RemoveInt(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 0, amount);
}

void ICharacter::AddWis(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 1, amount);
}

void ICharacter::RemoveWis(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 0, amount);
}

void ICharacter::AddAgi(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 1, amount);
}

void ICharacter::RemoveAgi(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 0, amount);
}

void ICharacter::AddOTP(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),9,1,amount,amount);
}

void ICharacter::RemoveOTP(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),9,0,amount,amount);
}

void ICharacter::AddEva(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),10,1,amount);
}

void ICharacter::RemoveEva(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),10,0,amount);
}

void ICharacter::AddDef(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),15,1,amount,amount);
}

void ICharacter::RemoveDef(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),15,0,amount,amount);
}

void ICharacter::AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced)
{
	if (this->IsOnline())
	{
		if (this->IsBuff(159) || this->IsBuff(327) || this->IsBuff(329) || this->IsBuff(331))
			return;

		CChar::WriteInSight(this->GetOffset(), 0xFF, "ddsdddd", 239, this->GetID(), effectName.c_str(), AutoRemove, Continues, nForced, 0);
	}
}

void ICharacter::AddParticle(int Bone, const char *ParticleName)
{
	if (this->IsOnline() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(), 0xFF, "dsdd", 247, ParticleName, *(DWORD *)((int)this->GetOffset() + 28), Bone);
}

int ICharacter::GetSpecialty()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 464);
	else
		return 0;
}



int ICharacter::IsMobMoving()
{
	if (this->IsOnline() && this->IsValid())
	{
		if(*(DWORD *)((int)this->GetOffset() + 656) == 1)
			return 1;
		else
			return 0;
	} else {
		return 0;
	}
}

int ICharacter::IsMobAggressive()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD *)((int)this->Offset + 476);
	else
		return 0;
}

int ICharacter::GetMobIndex()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD *)((int)this->GetOffset() + 512);
	else
		return 0;
}

int ICharacter::IsMobHaveTarget()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD*)((int)this->GetOffset() + 464);
	else
		return 0;
}

void ICharacter::SetMobTarget(int target)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (this->GetMobTanker() && !target)
		{
			(*(void (__thiscall **)(int, DWORD))(*(DWORD *)this->GetOffset() + 132))((int)this->GetOffset(), *(DWORD *)((int)this->GetOffset() + 464));
			(*(void (__thiscall **)(int, DWORD))(*(DWORD *)this->GetOffset() + 188))((int)this->GetOffset(), 0);
			return;
		}

		if (!this->GetMobTanker() && target)
		{
			ICharacter ITarget((void*)target);

			if (ITarget.IsValid())
			{
				if (CChar::GetRange((int)ITarget.GetOffset() + 332, (int)this->GetOffset() + 332) <= 200)
					(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 188))((int)this->GetOffset(), target);
			}
		}
	}
}

DWORD ICharacter::MobUnAttack(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if ( amount )
			return *(DWORD *)((int)this->GetOffset() + 468) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 468) = 0;
	} else {
		return 0;
	}
}

DWORD ICharacter::MobDelay(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if ( amount )
			return *(DWORD *)((int)this->GetOffset() + 556) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 556) = 0;
	} else {
		return 0;
	}
}

void ICharacter::MobDelete()
{
	if (this->IsOnline() && this->IsValid())
	{
		this->SetMobTarget(0);
		CChar::CancelAllBuff2(this->GetOffset());
		CChar::WriteInSight(this->GetOffset(), 56, "db", this->GetID(), 7);
		CChar::WriteInSight(this->GetOffset(), 61, "db", this->GetID(), 9);
		CBase::Delete(this->GetOffset());
	}
}

void ICharacter::Blob()
{
	if (this->IsOnline() && this->IsValid())
	{
		this->SetMobTarget(0);
		CChar::CancelAllBuff2(this->GetOffset());
		CChar::WriteInSight(this->GetOffset(), 73, "db", this->GetID(), 52);
		CChar::WriteInSight(this->GetOffset(), 56, "db", this->GetID(), 7);
		CChar::WriteInSight(this->GetOffset(), 61, "db", this->GetID(), 9);
		CBase::Delete(this->GetOffset());
	}
}

void ICharacter::UpdateHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP)
{
	if (this->IsOnline())
		CDBSocket::Write(81,"ddddddddddd", this->GetPID(), HP,HK,HD,DKPT,DKPW,PLT,PLW,SVT,SVW,RP);
}

void ICharacter::ShowHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP)
{
	if (this->IsValid() && !this->IsBuff(331))
	{
		int range = 0, prevrange = 0;
		if(HP >= 2790) range = 1;
		if(HP >= 4960) range = 2;
		if(HP >= 7750) range = 3;
		if(HP >= 12090) range = 4;
		if(HP >= 20150) range = 5;
		if(HP >= 35030) range = 6;
		if(HP >= 44640) range = 7;
		if(HP >= 57970) range = 8;
		if(HP >= 78740) range = 9;
		if(HP >= 111600) range = 10;

		if(range > 0)
			prevrange = range - 1;

		CPlayer::Write(this->GetOffset(), 255, "dddddddddddddddddd",245,0,0,0,0,0,range,prevrange,HP,HK,HD,DKPW,DKPT,PLW,PLT,SVW,SVT,RP);
		CChar::WriteInSight(this->GetOffset(), 255, "ddd", 244, this->GetID(), range);
	}
}

int ICharacter::IsWarRelated()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 484);
	else
		return 0;
}

void ICharacter::SetBuffIcon(int Time,int Type,int nMsg,int Key)
{
	if (this->IsOnline() && this->GetType() == 0)
		CPlayer::Write(this->GetOffset(),0xFF,"dddddd",243,Time,5000,Type,nMsg,Key);
}

void ICharacter::RemoveBuffIcon(int Time,int Type,int nMsg,int Key)
{
	if (this->IsOnline() && this->GetType() == 0)
		CPlayer::Write(this->GetOffset(),0xFF,"dddddd",243,Time,6000,Type,nMsg,Key);
}

int ICharacter::GetBuffRemain(int BuffID)
{
	int Check = 0;

	if (this->IsOnline() && BuffID >= 0 && BuffID <= 7000)
	{
		Check = CChar::GetBuffRemain(this->GetOffset(),BuffID);

		if (Check > 0 && BuffID >= 119 && BuffID <= 155 && Check > time(0))
			Check = Check-time(0);

		if (Check > 0 && BuffID >= 256 && Check > GetTickCount())
			Check = (Check-GetTickCount())/1000;
	}

	return Check;
}

int ICharacter::GetSkillPoint()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 548);
	else
		return 0;
}

void ICharacter::RemoveSkillPoint(int amount)
{
	if (this->IsOnline())
	{
		if (this->GetSkillPoint() >= amount)
			(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 24, 0, amount);
	}
}

void ICharacter::AddSkillPoint(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 24, 1, amount);
}

int ICharacter::GetStatPoint()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 544);
	else
		return 0;
}

void ICharacter::AddStatPoint(int Amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 23, 1, Amount);
}

void ICharacter::RemoveStatPoint(int Amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 23, 0, Amount);
}

void ICharacter::IncreaseStat(int amount, int Type)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(this->GetOffset()) + 88))((int)(this->GetOffset()), Type, 1, amount);
}

void ICharacter::DecreaseStat(int amount, int Type)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(this->GetOffset()) + 88))((int)(this->GetOffset()), Type, 0, amount);
}

int ICharacter::GetStr()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 64);
	else
		return 0;
}

int ICharacter::GetHth()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 68);
	else
		return 0;
}

int ICharacter::GetInt()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 72);
	else
		return 0;
}

int ICharacter::GetWis()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 76);
	else
		return 0;
}

int ICharacter::GetAgi()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 80);
	else
		return 0;
}

int ICharacter::GetEva()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 124);
	else
		return 0;
}

int ICharacter::GetDef()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 144);
	else
		return 0;
}

int ICharacter::GetRage()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 580);
	else
		return 0;
}

void ICharacter::IncreaseRage(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 35, 1, amount);
}

void ICharacter::DecreaseRage(int amount)
{
	if (this->IsOnline())
	{
		if (this->GetRage() >= amount)
			(*(void (__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 35, 0, amount);
	}
}

void ICharacter::IncreaseHp(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		(*(void (__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 1, amount);
	}
}

void ICharacter::DecreaseHp(int amount)
{
	if (this->IsOnline())
	{
		if(this->GetCurHp() >= amount)
			(*(void (__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 0, amount);
	}
}

int ICharacter::GetObjectListAround(int range)
{
	if (this->IsValid() && this->GetX() > 0 && this->GetY() > 0)
		return CPlayer::GetObjectAround(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 324, range);
	else
		return 0;
}

__int64 ICharacter::GetGStateEx()
{
	if (this->IsOnline())
	{
		__int64 state = 0;
		if(this->IsBuff(283)) state += 1;
		if(this->IsBuff(299)) state += 2;
		if(this->IsBuff(307)) state += 8;
		if(this->IsBuff(329)) state += 16;
		if(this->IsBuff(358)) state += 32;
		if(this->IsBuff(356)) state += 64;
		if(this->IsBuff(357)) state += 128;
		if(this->IsBuff(346)) state += 256;
		if(this->IsBuff(333)) state += 1024;
		if(this->IsBuff(327)) state += 2048;
		if(this->IsBuff(348)) state += 32768;
		if(this->IsBuff(350)) state += 65536;
		if(this->IsBuff(342)) state += 131072;
		if(this->IsBuff(339)) state += 262144;
		if(this->IsBuff(406)) state += __int64(16384) << 32;
		return state;
	} else {
		return 0;
	}
}

bool ICharacter::IsGStateEx(__int64 state)
{
	if (this->IsOnline())
	{
		if(this->GetGStateEx() & state)
			return true;
	}

	return false;
}

void ICharacter::SendGStateExIceArrow(__int64 state)
{
	if (this->IsValid() && !this->IsBuff(331))
	{
		if (this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dI", this->GetID(), (__int64)0);

		if (!this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dI", this->GetID(), state);
	}
}

void ICharacter::SendGStateEx(__int64 state)
{
	if (this->IsValid() && !this->IsBuff(331))
	{
		if (this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dI", this->GetID(), (__int64)0);

		if (!this->IsBuff(159) && !this->IsBuff(5600) && !this->IsBuff(5601) && !this->IsBuff(5602) && !this->IsBuff(5603) && !this->IsBuff(5604) && !this->IsBuff(5605))
			CChar::WriteInSight(this->GetOffset(), 148, "dI", this->GetID(), state);
	}
}

int ICharacter::CheckHit(ICharacter Target, int value)
{
	if ( this->IsOnline() && this->IsValid() && Target.IsOnline() )
	{
		if(CChar::CheckHit(this->GetOffset(), Target.GetOffset(), value))
			return 1;

		return 0;
	} else {
		return 0;
	}
}

void ICharacter::CouldntExecuteSkill()
{
	if (this->IsValid() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(), 61, "db", *(DWORD *)((int)this->GetOffset() + 28), 0);
}

int ICharacter::GetAttack()
{
	if (this->IsOnline())
		return CChar::GetAttack(this->GetOffset());
	else
		return 0;
}

int ICharacter::_ShowBattleMiss(ICharacter Target, int skillID)
{
	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		(*(void (__thiscall **)(int, int))(*(DWORD*)Target.GetOffset() + 80))((int)Target.GetOffset(), (int)this->GetOffset());

		if (Target.IsBuff(159))
			return 0;
		else if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(),8192) )
			return 0;
		else if ( !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset()+ 320), (int)this->GetOffset()+ 332, 131072)  || !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID() )
			return 0;
		else
			return CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwb", skillID, this->GetID(), Target.GetID(), Target.GetType(), 1, 0, 0, false);
	} else {
		return 0;
	}
}

void ICharacter::SetDirection(ICharacter Target)
{
	if (this->IsOnline() && this->IsValid() && Target.IsOnline())
		CChar::SetDirection(this->GetOffset(),*(DWORD *)((int)Target.GetOffset() + 332) - *(DWORD *)((int)this->GetOffset() + 332),*(DWORD *)((int)Target.GetOffset() + 336) - *(DWORD *)((int)this->GetOffset() + 336));
}

int ICharacter::OktayDamageNoAgro(ICharacter Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return 0;

	bool GiveCrit = false;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if (Target.IsBuff(162))
			return 0;

		if (Target.IsBuff(163))
			return 0;

		if (Target.GetType() == 0)
		{
			if(Target.IsBuff(284) && Damage > 10)
				Damage = Damage / 10;
		}

		if (Target.GetType() == 0)
		{
			if(Target.IsBuff(283) && Damage > 10)
				Damage = ((Damage * 7) / 10);
		}

		if (Target.GetType() == 0)
		{
			if(Target.IsBuff(122) && Damage)
				Damage = ((Damage * 88) / 100);
		}

		if ( CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300 )
			return 0;

		if (this->GetMap() != Target.GetMap())
			return 0;

		if (this->GetClass() == 3 && !this->IsBuff(25) && !this->IsBuff(50))
		{
			int Crit = *((DWORD*)((int)this->GetOffset() + 624) + 4 + 2);
			int CritDamage = *((DWORD*)((int)this->GetOffset() + 624) + 5 + 2);
			int Rate = 950;

			if (Crit)
				Rate -= *(DWORD*)((int)Crit + 8) * 3;

			if (CritDamage && Damage >= 100)
				Damage += (Damage * *(DWORD*)((int)CritDamage + 8)) /100;

			if ((int)CTools::Rate(1,1000) >= Rate)
			{
				Damage *= 2;
				GiveCrit = true;
			}
		}

		if((*(int (__thiscall **)(void*))(*(DWORD *)(int)Target.GetOffset() + 0x40))(Target.GetOffset())) 
			*(DWORD*)((unsigned)(int)Target.GetOffset() + 0x1d8) = GetTickCount() + 20000;

		if(Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(),8192))
			return 0;

		if( !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset()+ 320), (int)this->GetOffset()+ 332, 131072)  || !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID() )
			return 0;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return 0;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target,SkillID);

		if (this->GetClass() == 4 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target,SkillID);

		if (Target.GetCurHp() < 1)
			*(DWORD *)((int)Target.GetOffset() + 272) = 1;

		if (Target.GetCurHp() == 1)
			return 0;

		if (Damage >= Target.GetCurHp())
			Damage = Target.GetCurHp() - 1;

		*(DWORD *)((int)Target.GetOffset() + 272) = Target.GetCurHp() - Damage;
		(*(void (__thiscall **)(int, int))(*(DWORD*)Target.GetOffset() + 80))((int)Target.GetOffset(), (int)this->GetOffset());

		if (GiveCrit == true)
			CChar::WriteInSight(this->GetOffset(), 63, "bddbbwwbd", SkillID, this->GetID(), Target.GetID(), 1, 1, Damage, 0, Target.GetType() + 2, 0);
		else
			CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", Target.GetType(), SkillID, this->GetID(), Target.GetID(), Damage, 0, 0);

		return Damage;
	} else {
		return 0;
	}
}

int ICharacter::OktayDamageSingle(ICharacter Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return 0;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if (this->IsValid() && this->GetClass() == 4 && this->GetSpecialty() == 23 && Damage)
		{
			int pSkill = this->GetSkillPointer(49);
			if (pSkill) Damage += (*(DWORD*)(pSkill + 8) * 50);
		}





		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return 0;

		if (this->GetMap() != Target.GetMap())
			return 0;

		if(Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(),8192))
			return 0;

		if( !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset()+ 320), (int)this->GetOffset()+ 332, 131072)  || !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID() )
			return 0;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return 0;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + 20 <= Target.GetLevel())&&SkillID!=73 &&SkillID!=74 && SkillID!=75)
			return this->_ShowBattleMiss(Target,SkillID);

		if (this->GetClass() == 4 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target,SkillID);

		if (this->GetClass() == 1 && SkillID == 74)
			Target.Buff(8, 2, 0);

		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int (__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());

		if ((this->GetClass() == 1 && SkillID == 67))
			EBDamage = 0;
		else if (SkillID == 115)
			EBDamage = 0;
		else
			EBDamage = GetASpeedValue * (*(int (__thiscall **)(void *, LONG))(*(DWORD *)this->GetOffset() + 168))(this->GetOffset(), (int)Target.GetOffset()) / GetAttackSpeed;
		
		Check = (*(int (__thiscall**)(LONG,void*,unsigned int,int*,int*,int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(),this->GetOffset(),GetASpeedValue * Damage / GetAttackSpeed,&NormalDamage,&DamageArgument,&EBDamage,0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;
		CChar::WriteInSight(this->GetOffset(), 63, "bddbbwwbd", SkillID, this->GetID(), Target.GetID(), 1, 1, NormalDamage, EBDamage, GetType, 0); //swapped
		return NormalDamage;
	} else {
		return 0;
	}
}

void ICharacter::OktayDamageArea(ICharacter Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if (this->IsValid() && this->GetClass() == 4 && this->GetSpecialty() == 23 && Damage)
		{
			int pSkill = this->GetSkillPointer(49);
			if (pSkill) Damage += (*(DWORD*)(pSkill + 8) * 50);
		}

		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return;

		if (this->GetMap() != Target.GetMap())
			return;

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(),8192))
			return;

		if(!CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset()+ 320), (int)this->GetOffset()+ 332, 131072)  || !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID() )
			return;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return;

		if (this->GetClass() == 4 && SkillID != 22 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return;

		if (this->GetClass() == 1 && SkillID == 66)
			Target.Buff(0,5,-100);

		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int (__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());
		
		if ((this->GetClass() == 1 && SkillID == 67))
			EBDamage = 0;
		else
			EBDamage = GetASpeedValue * (*(int (__thiscall **)(void *, LONG))(*(DWORD *)this->GetOffset() + 168))(this->GetOffset(), (int)Target.GetOffset()) / GetAttackSpeed;
		
		Check = (*(int (__thiscall**)(LONG,void*,unsigned int,int*,int*,int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(),this->GetOffset(),GetASpeedValue * Damage / GetAttackSpeed,&NormalDamage,&DamageArgument,&EBDamage,0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;
		CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", GetType, SkillID, this->GetID(), Target.GetID(), NormalDamage, EBDamage, 0);
	} else {
		return;
	}
}

void ICharacter::OktayDamageStorm(ICharacter Target, int Damage)
{
	if (Damage <= 0)
		return;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return;

		if (this->GetMap() != Target.GetMap())
			return;

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(),8192))
			return;

		if( !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset()+ 320), (int)this->GetOffset()+ 332, 131072)  || !CChar::IsGState((int)this->GetOffset(),128) && !CChar::IsGState((int)this->GetOffset(),1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID() )
			return;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return;

		if (this->GetClass() == 4 && (this->GetLevel() + 20 <= Target.GetLevel()))
			return;

		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int (__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());
		Check = (*(int (__thiscall**)(LONG,void*,unsigned int,int*,int*,int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(),this->GetOffset(),GetASpeedValue * Damage / GetAttackSpeed,&NormalDamage,&DamageArgument,&EBDamage,0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;
		CChar::WriteInSight(this->GetOffset(), 10, "bbddww", GetType, 500, this->GetID(), Target.GetID(), NormalDamage, 0);

		if((*(int (__thiscall **)(void*))(*(DWORD *)(int)Target.GetOffset() + 0x40))(Target.GetOffset())) 
			*(DWORD*)((unsigned)(int)Target.GetOffset() + 0x1d8) = GetTickCount() + 20000;

		Target.DecreaseHp(0);
	} else {
		return;
	}
}

int ICharacter::GetDeathBlow()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 184);
	else
		return 0;
}

void ICharacter::AddDeathBlow(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		if(this->GetDeathBlow() < 5)
			(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)(this->GetOffset()) + 92))((int)(this->GetOffset()), 36, 1, amount);
	}
}

void ICharacter::RemoveDeathBlow(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		if(this->GetDeathBlow() - amount <= 0) 
			amount = this->GetDeathBlow();

		(*(void (__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 36, 0, amount);
	}
}

int ICharacter::IsInRange(ICharacter Target, int maxRange)
{
	if (this->IsOnline() && Target.IsOnline())
	{
		if (CChar::GetRange((int)this->GetOffset() + 324, (int)Target.GetOffset() + 324) <= maxRange)
			return 1;
	}

	return 0;
}

void ICharacter::AddAbsorb(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),16,1,amount,amount);
}

void ICharacter::RemoveAbsorb(int amount)
{
	if (this->IsOnline())
		(*(int (__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(),16,0,amount,amount);
}

int ICharacter::GetMagic()
{
	if (this->IsOnline())
		return CChar::GetMagic(this->GetOffset());
	else
		return 0;
}

int ICharacter::IsMoved(int x, int y)
{
	if ( this->IsOnline() && this->IsValid() )
	{
		if(x == this->GetX() && y == this->GetY())
			return 0;

		return true;
	} else {
		return 0;
	}
}

DWORD ICharacter::UnAttack(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if ( amount )
			return *(DWORD *)((int)this->GetOffset() + 468) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 468) = 0;
	} else {
		return 0;
	}
}

DWORD ICharacter::Delay(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if ( amount )
			return *(DWORD *)((int)this->GetOffset() + 556) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 556) = 0;
	} else {
		return 0;
	}
}

void ICharacter::MonsterSummonWrite(int SafeZoneCheck,int Monster,int CellMapCoordinate)
{
	if (this->IsOnline())
	{
		if (SafeZoneCheck)
		{
			if ( !CSMap::IsOnTile(*(void **)(Monster + 320), Monster + 332, 131072) && Undefined::CellMapCheck(*(void **)(Monster + 320), Monster, (int)CellMapCoordinate) )
			{
				(*(void (__thiscall **)(int, DWORD))(*(DWORD *)Monster + 196))(Monster, 0);
				CChar::WriteInSight((void*)Monster,51,"wdddwddIIsbdsIIb",*(DWORD *)(*(DWORD *)(Monster + 440) + 60),*(DWORD*)(Monster+28),*(DWORD *)(Monster + 332),*(DWORD *)(Monster + 336),*(DWORD *)(Monster + 348),*(DWORD *)(Monster + 272),CChar::GetMaxHp(Monster),*(DWORD *)(Monster + 280),(unsigned __int64)*(DWORD *)(Monster + 288),*(DWORD *)(Monster + 292),(*(int (__thiscall **)(int))(*(DWORD *)Monster + 224))(Monster),*(DWORD *)(*(DWORD *)(Monster + 440) + 64) | 0x80,*(DWORD *)(Monster + 524),(*(int (__thiscall **)(int))(*(DWORD *)Monster + 240))(Monster),(__int64)0, (__int64)0, 0);
				CChar::Unlock((void *)Monster);
			} else {
				CChar::Unlock((void *)Monster);
				if ( Monster )
					(**(void (__thiscall ***)(DWORD, DWORD))Monster)(Monster, 1);
			}
		} else {
			if ( Undefined::CellMapCheck(*(void **)(Monster + 320), Monster, (int)CellMapCoordinate) )
			{
				(*(void (__thiscall **)(int, DWORD))(*(DWORD *)Monster + 196))(Monster, 0);
				CChar::WriteInSight((void*)Monster,51,"wdddwddIIsbdsIIb",*(DWORD *)(*(DWORD *)(Monster + 440) + 60),*(DWORD*)(Monster+28),*(DWORD *)(Monster + 332),*(DWORD *)(Monster + 336),*(DWORD *)(Monster + 348),*(DWORD *)(Monster + 272),CChar::GetMaxHp(Monster),*(DWORD *)(Monster + 280),(unsigned __int64)*(DWORD *)(Monster + 288),*(DWORD *)(Monster + 292),(*(int (__thiscall **)(int))(*(DWORD *)Monster + 224))(Monster),*(DWORD *)(*(DWORD *)(Monster + 440) + 64) | 0x80,*(DWORD *)(Monster + 524),(*(int (__thiscall **)(int))(*(DWORD *)Monster + 240))(Monster),(__int64)0, (__int64)0, 0);
				CChar::Unlock((void *)Monster);
			} else {
				CChar::Unlock((void *)Monster);
				if ( Monster )
					(**(void (__thiscall ***)(DWORD, DWORD))Monster)(Monster, 1);
			}
		}
	}
}

int ICharacter::GetMobTanker()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD*)((int)this->GetOffset() + 464);
	else
		return 0;
}

int ICharacter::GetMaxHp()
{
	if (this->IsOnline())
		return CChar::GetMaxHp((int)this->Offset);
	else
		return 0;
}

void ICharacter::OpenHTML(int html)
{
	if (this->IsOnline())
		CPlayer::Write(this->Offset, 74, "d", html);
}

void ICharacter::OpenWindow(std::string WindowName,int Type,int Time)
{
	if (this->IsOnline())
		CPlayer::Write(Offset, 0xFF, "dsdd", 237,WindowName.c_str(),Type,Time);
}

void ICharacter::CloseWindow(std::string WindowName)
{
	if (this->IsOnline())
		CPlayer::Write(Offset, 0xFF, "ds", 236,WindowName.c_str());
}

void ICharacter::Revive()
{
	if (this->IsOnline())
	{
		if (!CChar::IsGState((int)this->GetOffset(),2))
			return;

		if (CPlayer::IsEState((int)this->GetOffset(),8))
			CPlayer::SubEState((int)this->GetOffset(),8);

		CChar::CancelBuffParty(this->GetOffset(),256);
		*((DWORD *)this->GetOffset() + 69) = 0;
		(*(void (__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 7, 1, CChar::GetMaxHp((int)this->GetOffset()));
		(*(void (__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 8, 1, CChar::GetMaxMp((int)this->GetOffset()));
		(*(void (__thiscall **)(void *, signed int))(*(DWORD *)this->GetOffset() + 112))(this->GetOffset(),2);
		CChar::AddGState((int)this->GetOffset(),8192);
		*((DWORD *)this->GetOffset() + 362) = GetTickCount() + 10000;
	}
}

void ICharacter::SetBlue()
{
	if (this->IsValid() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(),46,"dI",this->GetID(),__int64(0x00040000) << 32);
}

void ICharacter::SetRed()
{
	if (this->IsValid() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(),46,"dI",this->GetID(),__int64(0x00020000) << 32);
}

void ICharacter::RemoveSetBlue()
{
	if (this->IsOnline() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(),46,"dI",this->GetID(),(__int64)0);
}

void ICharacter::RemoveSetRed()
{
	if (this->IsOnline() && !this->IsBuff(331))
		CChar::WriteInSight(this->GetOffset(),46,"dI",this->GetID(),(__int64)0);
}

int ICharacter::GetGID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->Offset + 480);
	else
		return 0;
}

int ICharacter::GetRectX()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->Offset + 324);
	else
		return 0;
}

int ICharacter::GetRectY()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->Offset + 328);
	else
		return 0;
}

void ICharacter::IncreaseCritRate(int Amount)
{
	if (this->IsOnline())
	{
		(*(void (__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 96))((int)this->Offset, 31, 1, Amount);
		(*(void (__thiscall **)(DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 104))((int)this->Offset, 16, 0);
	}
}

void ICharacter::DecreaseCritRate(int Amount)
{
	if (this->IsOnline())
	{
		(*(void (__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 96))((int)this->Offset, 31, 0, Amount);
		(*(void (__thiscall **)(DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 124))((int)this->Offset, 16, 0);
	}
}

void ICharacter::NewAnnouncement(std::string msg)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(),0xFF, "ds", 234, msg.c_str());
}

void ICharacter::ScreenTime(int Time)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(),0xFF, "dd", 233, Time);
}

void ICharacter::CloseScreenTime()
{
	if (this->IsOnline())
		this->CloseWindow("hell_time");
}

void ICharacter::Scenario3Score(int Time,int RedScore,int BlueScore)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(),106,"bdbb",8,Time,RedScore,BlueScore);
}

void ICharacter::CloseScenario3Score()
{
	if (this->IsOnline())
		this->CloseWindow("scenario3_timescore");
}

void ICharacter::Scenario3_3Score(int Time,int RedScore,int BlueScore)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(),0xFF,"dbddd",232,7,Time,RedScore,BlueScore);
}

void ICharacter::CloseScenario3_3Score()
{
	if (this->IsOnline())
		this->CloseWindow("Scenario3_3_timescore");
}

void ICharacter::SpScore(int Time,int Type,int RedScore,int BlueScore,int RedWin,int BlueWin)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(),122,"bdddbdb",1,Time,Type,BlueScore,RedScore,BlueWin,RedWin);
		CPlayer::Write(this->GetOffset(),122,"bddddbb",1,Time,Type,BlueScore,RedScore,BlueWin,RedWin);
	}
}

void ICharacter::CloseSpScore()
{
	if (this->IsOnline())
		this->CloseWindow("sp_timescore");
}

void ICharacter::SetRebirthTalisman(int Amount)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(),0xFF,"dbbbbb",231,6,0,0,0,Amount);
}

void ICharacter::CloseRebirthTalisman()
{
	if (this->IsOnline())
		this->CloseWindow("hell_life");
}

void ICharacter::IncreaseCritDamage(int Amount)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 180) += Amount;
}

void ICharacter::DecreaseCritDamage(int Amount)
{
	if (this->IsOnline())
	{
		if ((int)*(DWORD*)((int)this->GetOffset() + 180) >= Amount)
			*(DWORD*)((int)this->GetOffset() + 180) -= Amount;
	}
}

void ICharacter::SetMobHostility(int Amount)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 608) = Amount;
}

int ICharacter::GetAlliance()
{
	if (this->IsOnline())
		return *(DWORD*)(*(DWORD*)((int)this->Offset + 484) + 392);
	else
		return 0;
}

void ICharacter::SetAsAdmin()
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 456) = 11;
}


void ICharacter::IncreaseMovingSpeed(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD*)(int)this->GetOffset() + 96))((int)this->GetOffset(), 32, 1, amount);
}

void ICharacter::DecreaseMovingSpeed(int amount)
{
	if (this->IsOnline())
		(*(void (__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD*)(int)this->GetOffset() + 96))((int)this->GetOffset(), 32, 0, amount);
}

int ICharacter::GetRidingType()
{
	int state = 0;

	if (this->IsOnline())
	{
		if(this->IsBuff(3412)) state = 1;
		if(this->IsBuff(3413)) state = 2;
		if(this->IsBuff(3414)) state = 3;
		if(this->IsBuff(3415)) state = 4;
		if(this->IsBuff(3416)) state = 5;
		if(this->IsBuff(3417)) state = 6;
		if(this->IsBuff(3418)) state = 7;
		if(this->IsBuff(3419)) state = 8;
		if(this->IsBuff(4149)) state = 9;
		if(this->IsBuff(4150)) state = 10;
		if(this->IsBuff(4151)) state = 11;
		if(this->IsBuff(4152)) state = 14;
		if(this->IsBuff(4153)) state = 15;
		if(this->IsBuff(4156)) state = 12;
		if(this->IsBuff(4157)) state = 13;
		if(this->IsBuff(4158)) state = 16;
		if(this->IsBuff(4159)) state = 17;
		if(this->IsBuff(4160)) state = 18;
		if(this->IsBuff(6022)) state = 20;
		if(this->IsBuff(6021)) state = 21;
		if(this->IsBuff(6023)) state = 22;
		if(this->IsBuff(6024)) state = 23;
	}

	return state;
}

void ICharacter::EnableRiding(int Type)
{
	if (this->IsOnline() && !this->IsBuff(331))
	{
		this->Buff(349,1296000,0);
		CChar::WriteInSight(this->GetOffset(),198,"bdw",0,this->GetID(),Type);

		if (!this->IsBuff(347))
		{
			this->Buff(347,1296000,0);
			this->IncreaseMovingSpeed(75);
		}
	}
}

void ICharacter::DisableRiding()
{
	if (this->IsOnline() && !this->IsBuff(331))
	{
		this->CancelBuff(349);
		int Type = this->GetRidingType();
		CChar::WriteInSight(this->GetOffset(),198,"bdw",1,this->GetID(),Type);

		if (this->IsBuff(347))
		{
			this->CancelBuff(347);
			this->CancelBuff(Type+3411);
			this->DecreaseMovingSpeed(75);
		}
	}
}


int ICharacter::MaxInventorySize()
{
	if (this->IsOnline())
	{
		int Size = 72;
		if (this->IsBuff(172)) Size += 36;
		if (this->IsBuff(173)) Size += 36;
		if (this->IsBuff(174)) Size += 36;
		return Size;
	}

	return 0;
}

void ICharacter::AddMinPhysAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 11, 1, amount);
}

void ICharacter::AddMaxPhysAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 12, 1, amount);
}

void ICharacter::AddMinMagicAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 13, 1, amount);
}

void ICharacter::AddMaxMagicAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 96))((int)this->GetOffset(), 14, 1, static_cast<int>(amount * 0.41));
}

void ICharacter::RemoveMinPhysAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 11, 0, amount);
}

void ICharacter::RemoveMaxPhysAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 12, 0, amount);
}

void ICharacter::RemoveMinMagicAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 13, 0, amount);
}

void ICharacter::RemoveMaxMagicAttack(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 96))((int)this->GetOffset(), 14, 0, static_cast<int>(amount * 0.41));

}

int ICharacter::GetMoveSpeed()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 260);
	else
		return 0;
}


void ICharacter::SetAsSleep()
{
	if (this->IsOnline())
		Sleep(60000);
}

std::string ICharacter::GetIP()
{
	std::string Check = "error";
	if (this->IsOnline()) Check = inet_ntoa(*(struct in_addr*)(*(DWORD*)((int)this->GetOffset() + 1676) + 140));
	return Check;
}

void __fastcall ICharacter::ResetContinueSkill()
{
	if (this->IsOnline())
	{
		if (this->IsValid() && this->IsBuff(300))
			return;

		if (IConfig::CheckContinueSkill.count(this->GetPID()))
		{
			IConfig::CheckContinueSkill[this->GetPID()].PlayerX = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerY = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerTarget = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerSkillGrade = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerSkillID = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerSkillDelay = 0;
			IConfig::CheckContinueSkill[this->GetPID()].PlayerSkillCount = 0;
			this->CouldntExecuteSkill();
		}
	}
}

void __fastcall ICharacter::ResetFarContinueSkill()
{
}

void __fastcall ICharacter::ResetRuptureContinueSkill()
{
}

void __fastcall ICharacter::ResetContinueIceStorm()
{
}

void __fastcall ICharacter::ResetContinueThunderStorm()
{
}

void __fastcall ICharacter::ResetContinueFireStorm()
{
}
