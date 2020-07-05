#include "CThief.h"

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
