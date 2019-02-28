#ifndef _SACRIFICE_H
#define _SACRIFICE_H
#include "ServerFunctions.h"

void __fastcall Sacrifice(int pSkill, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	ISkill ISkill((void*)pSkill);

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)Target, (char*)a3, "bd", &bType, &nTargetID);

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);



	double nHealAmountSacrifice = SacrificeBaseHeal + (ITarget.GetMaxHp()*SacrificeBasePercentageHeal / 100) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*SacrificeHealPerGradePercentage / 100));
	
	double nHpLossSacrifice = SacrificeBaseLoss + (IPlayer.GetMaxHp()*SacrificeBasePercentageLoss / 100) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*SacrificeLossPerGradePercentage / 100));


	if (pTarget && ITarget.IsValid() && IPlayer.IsValid())
	{
		if (IPlayer.GetCurHp() - nHpLossSacrifice <= 0)
		{
			IPlayer.SystemMessage("Your HP is too low to use this skill", TEXTCOLOR_RED);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}
		else
		{
			IPlayer.DecreaseHp(static_cast<int>(nHpLossSacrifice));
			ITarget.IncreaseHp(static_cast<int>(nHealAmountSacrifice));
			IPlayer._ShowBattleAnimation(IPlayer, 26);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}
	}

}
#endif