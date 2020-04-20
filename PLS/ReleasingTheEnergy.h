#ifndef RELEASINGTHEENERGY_H
#define RELEASINGTHEENERGY_H

void __fastcall ReleasingTheEnergy(ICharacter IPlayer)
{
	if (IsBuff(391))
		return;

	int pSkill = GetSkillPointer(92);

	if (IsOnline() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int Mana = (15 + (xSkill.GetGrade() * 5));

		if (GetCurMp() < Mana)
			return;

		if (IsValid() && !IsBuff(391))
		{
			AddFxToTarget("island_boss_m", 1, 0, 0);
			DecreaseMana(Mana);
			Buff(390, 10 * xSkill.GetGrade(), 0);
			Buff(391, 3600, 0);
			_ShowBattleAnimation(IPlayer, 92);
			SetBuffIcon(10000 * xSkill.GetGrade(), 0, 4244, 952);
			IncreaseMaxHp(500 * xSkill.GetGrade());
			IncreaseHp(500 * xSkill.GetGrade());
			AddMaxAttack(100 * xSkill.GetGrade());
			AddMinAttack(100 * xSkill.GetGrade());
		}
	}
}
#endif