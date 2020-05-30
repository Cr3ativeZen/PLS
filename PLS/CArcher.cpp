#include "CArcher.h"

void __fastcall CArcher::BlowUpArrow(int pPacket, int pPos)
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BLOWUPARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	if (Target.GetType() == TYPE_PLAYER)
		DamageSingle(ISkill, Target, false, true);
	else if (Target.GetType() == TYPE_MONSTER)
	{
		DamageMultiple(ISkill, Target, 1, 1, false, true);
	}

}

void __fastcall CArcher::FlamyArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FLAMYARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);


}

void __fastcall CArcher::MuscleSolidation()
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MUSCLESOLIDATION));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;


	_ShowBattleAnimation(GetOffset(), ISkill.GetIndex());

	Buff(10, 900, 0);
	Buff(500, 910, static_cast<int>(GetMinPhyAttack() * 0.10));
	Buff(501, 910, static_cast<int>(GetMaxPhyAttack() * 0.10));

	AddMinPhysAttack(static_cast<int>(GetMinPhyAttack() * 0.10));
	AddMaxPhysAttack(static_cast<int>(GetMaxPhyAttack() * 0.10));
}

void __fastcall CArcher::PassiveAttack(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_PASSIVEATTACK));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);

}

void __fastcall CArcher::BuffRemover(int pPacket, int pPos)
{

	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_BUFFREMOVER));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);


	if (IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)GetOffset() + 176))((int)GetOffset(), (int)Target.GetOffset(), 0))
	{
		Target.CancelBuff(282);
		Target.CancelBuff(283);
		Target.CancelBuff(284);
		Target.CancelBuff(24);
		Target.CancelBuff(305);
		Target.CancelBuff(306);
		Target.CancelBuff(379);
		Target.CancelBuff(380);
		Target.CancelBuff(381);
		Target.CancelBuff(382);
		Target.CancelBuff(383);
		Target.CancelBuff(384);
	}
}

void __fastcall CArcher::FocusShot(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_FOCUSSHOT));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);

	
}

void __fastcall CArcher::MysteriousArrow(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_ARCHER_MYSTERIOUSARROW));

	if (!ISkill.GetGrade() || GetCurMp() < ISkill.DecreaseMana())
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);

	DamageSingle(ISkill, Target, false, true);

}



