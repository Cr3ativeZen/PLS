#ifndef RESETCONTINUESKILL_H
#define RESETCONTINUESKILL_H
void __fastcall ResetContinueSkill(ICharacter IPlayer)
{
	if (IPlayer.IsOnline())
	{
		if (IPlayer.IsValid() && IPlayer.IsBuff(300))
			return;

		if (CheckContinueSkill.count(IPlayer.GetPID()))
		{
			CheckContinueSkill[IPlayer.GetPID()].PlayerX = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerY = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
			IPlayer.CouldntExecuteSkill();
		}
	}
}

void __fastcall ResetFarContinueSkill(ICharacter IPlayer)
{
	if (IPlayer.IsOnline())
	{
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerDamage = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
		CheckFarContinueSkill[IPlayer.GetPID()].CasterOffset = 0;
	}
}

void __fastcall ResetRuptureContinueSkill(ICharacter IPlayer)
{
	if (IPlayer.IsOnline())
	{
		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
		CheckRuptureContinueSkill[IPlayer.GetPID()].CasterOffset = 0;
	}
}

void __fastcall ResetContinueIceStorm(ICharacter IPlayer)
{
	CheckContinueIceStorm[IPlayer.GetPID()].PlayerTarget = 0;
	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillID = 0;
	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
}

void __fastcall ResetContinueThunderStorm(ICharacter IPlayer)
{
	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerTarget = 0;
	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillID = 0;
	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
}

void __fastcall ResetContinueFireStorm(ICharacter IPlayer)
{
	CheckContinueFireStorm[IPlayer.GetPID()].PlayerTarget = 0;
	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillID = 0;
	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
}

#endif