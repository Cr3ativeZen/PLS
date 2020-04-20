#ifndef _MUSCLESOLIDATION_H
#define _MUSCLESOLIDATION_H

void __fastcall MuscleSolidation(int Skill, int a6, int Player)
{
	ICharacter IPlayer((void*)Player);
	ISkill ISkill((void*)Skill);

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	_ShowBattleAnimation(IPlayer, ISkill.GetIndex());


	Buff(10, 900, 0);
	Buff(500, 910, static_cast<int>(GetMinPhyAttack()*0.10));
	Buff(501, 910, static_cast<int>(GetMaxPhyAttack()*0.10));

	AddMinPhysAttack(static_cast<int>(GetMinPhyAttack()*0.10));
	AddMaxPhysAttack(static_cast<int>(GetMaxPhyAttack()*0.10));
}
#endif