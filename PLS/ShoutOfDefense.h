#ifndef SHOUTOFDEFENSE_H
#define SHOUTOFDEFENSE_H

void __fastcall ShoutOfDefense(ICharacter IPlayer)
{
	if (IsBuff(380))
		return;


	if (IsValid())
	{
		int pSkill = GetSkillPointer(90);
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int Mana = (20 + GetLevel()) + ((20 + (GetLevel() * 4)) / 10);

		if (GetCurMp() <= Mana)
			return;

		if (pSkill && IsValid() && !IsBuff(380))
		{
			AddFxToTarget("island_boss03", 1, 0, 0);
			DecreaseMana(Mana);

			Buff(379, 25, 0);
			Buff(380, 3600, 0);
			//_ShowBattleAnimation(IPlayer, 90);
			SetBuffIcon(25000, 0, 4240, 948);
			AddDef(50 + (xSkill.GetGrade() * 50));
		}
	}
}

#endif