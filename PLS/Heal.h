#include "ServerFunctions.h"
void __fastcall Heal(int Skill, int a4, int Player)
{

	IChar IPlayer((void*)Player);
	ISkill ISkill((void*)Skill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nHealAmount = HealBase + ((IPlayer.GetMaxHp() * (HealBasePercentage / 100)) + (IPlayer.GetMaxHp()*(ISkill.GetGrade()*HealPerGradePercentage / 100))+ CChar::GetWis((int)IPlayer.GetOffset())*HealWisdom);


	IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());
	IPlayer.IncreaseHp(nHealAmount);
	IPlayer.DecreaseMana((ISkill.GetGrade() * 4) + 16);
}