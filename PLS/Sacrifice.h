#ifndef _SACRIFICE_H
#define _SACRIFICE_H
#include "ServerFunctions.h"

void __fastcall Sacrifice(int pSkill, void *edx, int Player, int pPacket, int pPos)
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

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2 || !pTarget || pTarget == GetOffset())
		return;

	ICharacter ITarget((void*)pTarget);



	double nHealAmountSacrifice = SacrificeBaseHeal + (ITarget.GetMaxHp()*SacrificeBasePercentageHeal / 100) + (ITarget.GetMaxHp()*(ISkill.GetGrade()*SacrificeHealPerGradePercentage / 100));
	
	double nHpLossSacrifice = SacrificeBaseLoss + (GetMaxHp()*SacrificeBasePercentageLoss / 100) + (GetMaxHp()*(ISkill.GetGrade()*SacrificeLossPerGradePercentage / 100));


	if (pTarget && ITarget.IsValid() && IsValid())
	{
		if (GetCurHp() - nHpLossSacrifice <= 0)
		{
			SystemMessage("Your HP is too low to use this skill", TEXTCOLOR_RED);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}
		else
		{
			DecreaseHp(static_cast<int>(nHpLossSacrifice));
			ITarget.IncreaseHp(static_cast<int>(nHealAmountSacrifice));
			_ShowBattleAnimation(IPlayer, 26);
			CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
			return;
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}
#endif