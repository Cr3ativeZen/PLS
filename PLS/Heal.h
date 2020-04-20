#include "ServerFunctions.h"
void __fastcall Heal(int Skill, int a4, int Player)
{

	ICharacter IPlayer((void*)Player);
	ISkill ISkill((void*)Skill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nHealAmount = HealBase + ((GetMaxHp() * (HealBasePercentage / 100)) + (GetMaxHp()*(ISkill.GetGrade()*HealPerGradePercentage / 100))+ CChar::GetWis((int)GetOffset())*HealWisdom);


	_ShowBattleAnimation(IPlayer, ISkill.GetIndex());
	IncreaseHp(nHealAmount);
	DecreaseMana((ISkill.GetGrade() * 4) + 16);
}