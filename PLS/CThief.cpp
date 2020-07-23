#include "CThief.h"

void __fastcall CThief::DanceOfKilling()
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_THIEF_DANCEOFKILLING));

	SystemMessage("HWETGWEF", IConfig::TEXTCOLOR_RED);
	if (!ISkill.GetGrade() || GetCurMp() < ISkill.GetGrade() * 20 + 80)
		return;

	if (!IsBuff(333))
		SendGStateEx(GetGStateEx() + 1024);

	Buff(333, ISkill.GetGrade() * 15, 0);
	SetBuffIcon(ISkill.GetGrade() * 15000, 0, 2013, 155);
	Buff(20, ISkill.GetGrade() * 15, 300);
	//RemoveBuffIcon(0, 0, 699, 34);
	DecreaseMana(ISkill.GetGrade() * 20 + 80);
	_ShowBattleAnimation(GetOffset(), 13, ISkill.GetGrade());
}

void __fastcall CThief::ShadowSlash(int pPacket, int pPos)
{
	ISkill ISkill((void*)GetSkillPointer(SKILL_THIEF_SHADOWSLASH));

	if (!ISkill.GetGrade() || GetCurMp() < static_cast<long long>(230 + (((GetLevel() + ISkill.GetGrade()) * ISkill.GetGrade()) * 0.63)))
		return;

	RAII raii(pPacket, pPos);

	if (!raii.pTarget || raii.pTarget == GetOffset())
		return;

	ICharacter Target(raii.pTarget);


	DamageMultiple(ISkill, Target, 4, 999, false, false);

}
