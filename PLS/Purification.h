#ifndef _PURIFICATION_H
#define _PURIFICATION_H
#include "ResetContinueSkill.h"
void __fastcall Purification(int pSkill, void *edx, int Player, int pPacket, int pPos)
{
	ICharacter IPlayer((void*)Player);
	ISkill ISkill((void*)pSkill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	ICharacter ITarget((void*)pTarget);
	if (pTarget && ITarget.IsValid() && IPlayer.IsValid())
	{

		if (ITarget.IsBuff(350))
		{
			ITarget.CancelBuff(350);
			for (auto it = CheckRuptureContinueSkill.begin(); it != CheckRuptureContinueSkill.end(); ++it)
			{
				if (it->second.PlayerTarget == ITarget.GetOffset())
				{

						ICharacter Caster(it->second.CasterOffset);
						if (Caster.IsOnline())
						{
							ResetRuptureContinueSkill(Caster);
							Caster.CancelBuff(5577);
							Caster.CancelBuff(353);
						}
				}
			}
		}
		if (ITarget.IsBuff(348))
		{
			ITarget.CancelBuff(348);
			for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
			{
				if (it->second.PlayerTarget == ITarget.GetOffset())
				{

						ICharacter Caster(it->second.CasterOffset);
						if (Caster.IsOnline())
						{
							ResetFarContinueSkill(Caster);
							Caster.CancelBuff(5576);
						}
				}
			}
		}
		if (ITarget.IsBuff(339) || ITarget.IsBuff(340))
		{
			if(ITarget.IsBuff(339))
				ITarget.CancelBuff(339);

			if (ITarget.IsBuff(340))
				ITarget.CancelBuff(340);

			ITarget.RemoveBuffIcon(0, 0, 0, 219);

			for (auto it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); ++it)
			{
				if (it->second.PlayerTarget == ITarget.GetOffset())
				{

					ICharacter Caster(it->second.CasterOffset);
					if (Caster.IsOnline())
					{
						ResetFarContinueSkill(Caster);
						Caster.CancelBuff(5578);
						Caster.CancelBuff(341);
					}
				}
			}
		}

		ITarget.CancelBuff(307);
		ITarget.CancelBuff(342);
		ITarget.CancelBuff(346);
		ITarget.CancelBuff(356);
		ITarget.CancelBuff(390);
		ITarget.CancelBuff(391);
		ITarget.CancelBuff(358);
		ITarget.CancelBuff(359);
		ITarget.CancelBuff(40);
		ITarget.CancelBuff(4002);
		ITarget.CancelBuff(4001);
		ITarget.CancelBuff(4003);
		ITarget.CancelBuff(790);
		ITarget.RemoveBuffIcon(0, 0, 0, 225);
		ITarget.RemoveBuffIcon(0, 0, 0, 224);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);

}
#endif