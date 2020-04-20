#ifndef RESETCONTINUESKILL_H
#define RESETCONTINUESKILL_H
void __fastcall ResetContinueSkill(ICharacter IPlayer)
{
	if (IsOnline())
	{
		if (IsValid() && IsBuff(300))
			return;

		if (CheckContinueSkill.count(GetPID()))
		{
			CheckContinueSkill[GetPID()].PlayerX = 0;
			CheckContinueSkill[GetPID()].PlayerY = 0;
			CheckContinueSkill[GetPID()].PlayerTarget = 0;
			CheckContinueSkill[GetPID()].PlayerSkillGrade = 0;
			CheckContinueSkill[GetPID()].PlayerSkillID = 0;
			CheckContinueSkill[GetPID()].PlayerSkillDelay = 0;
			CheckContinueSkill[GetPID()].PlayerSkillCount = 0;
			CouldntExecuteSkill();
		}
	}
}

void __fastcall ResetFarContinueSkill(ICharacter IPlayer)
{
	if (IsOnline())
	{
		CheckFarContinueSkill[GetPID()].PlayerTarget = 0;
		CheckFarContinueSkill[GetPID()].PlayerSkillID = 0;
		CheckFarContinueSkill[GetPID()].PlayerSkillCount = 0;
		CheckFarContinueSkill[GetPID()].PlayerDamage = 0;
		CheckFarContinueSkill[GetPID()].PlayerSkillDelay = 0;
		CheckFarContinueSkill[GetPID()].PlayerSkillGrade = 0;
		CheckFarContinueSkill[GetPID()].CasterOffset = 0;
	}
}

void __fastcall ResetRuptureContinueSkill(ICharacter IPlayer)
{
	if (IsOnline())
	{
		CheckRuptureContinueSkill[GetPID()].PlayerTarget = 0;
		CheckRuptureContinueSkill[GetPID()].PlayerSkillID = 0;
		CheckRuptureContinueSkill[GetPID()].PlayerSkillCount = 0;
		CheckRuptureContinueSkill[GetPID()].PlayerSkillDelay = 0;
		CheckRuptureContinueSkill[GetPID()].PlayerSkillGrade = 0;
		CheckRuptureContinueSkill[GetPID()].CasterOffset = 0;
	}
}

void __fastcall ResetContinueIceStorm(ICharacter IPlayer)
{
	CheckContinueIceStorm[GetPID()].PlayerTarget = 0;
	CheckContinueIceStorm[GetPID()].PlayerSkillID = 0;
	CheckContinueIceStorm[GetPID()].PlayerSkillCount = 0;
	CheckContinueIceStorm[GetPID()].PlayerSkillDelay = 0;
	CheckContinueIceStorm[GetPID()].PlayerSkillGrade = 0;
}

void __fastcall ResetContinueThunderStorm(ICharacter IPlayer)
{
	CheckContinueThunderStorm[GetPID()].PlayerTarget = 0;
	CheckContinueThunderStorm[GetPID()].PlayerSkillID = 0;
	CheckContinueThunderStorm[GetPID()].PlayerSkillCount = 0;
	CheckContinueThunderStorm[GetPID()].PlayerSkillDelay = 0;
	CheckContinueThunderStorm[GetPID()].PlayerSkillGrade = 0;
}

void __fastcall ResetContinueFireStorm(ICharacter IPlayer)
{
	CheckContinueFireStorm[GetPID()].PlayerTarget = 0;
	CheckContinueFireStorm[GetPID()].PlayerSkillID = 0;
	CheckContinueFireStorm[GetPID()].PlayerSkillCount = 0;
	CheckContinueFireStorm[GetPID()].PlayerSkillDelay = 0;
	CheckContinueFireStorm[GetPID()].PlayerSkillGrade = 0;
}

#endif