#ifndef _MUSCLESOLIDATION_H
#define _MUSCLESOLIDATION_H

void __fastcall MuscleSolidation(IChar IPlayer)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(10));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IPlayer._ShowBattleAnimation(IPlayer, ISkill.GetIndex());


	IPlayer.Buff(10, 900, 0);
	IPlayer.Buff(500, 910, static_cast<int>(IPlayer.GetMinPhyAttack()*0.10));
	IPlayer.Buff(501, 910, static_cast<int>(IPlayer.GetMaxPhyAttack()*0.10));

	IPlayer.AddMinPhysAttack(static_cast<int>(IPlayer.GetMinPhyAttack()*0.10));
	IPlayer.AddMaxPhysAttack(static_cast<int>(IPlayer.GetMaxPhyAttack()*0.10));
}
#endif