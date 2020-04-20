#ifndef THERAPEUTICTOUCH_H
#define THERAPEUTICTOUCH_H
void __fastcall TherapeuticTouch(ICharacter IPlayer, int pPacket, int pPos)
{
	int pSkill = GetSkillPointer(72);

	if (IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);

		int nSkillGrade = xSkill.GetGrade();

		if (!nSkillGrade)
			return;

		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 50) * xSkill.GetGrade()) + 100) * 1.98);

		if (bType == 0 && nTargetID)
			pTarget = CPlayer::FindPlayer(nTargetID);

		if (bType >= 1)
			return;

		if (bType >= 2 || !pTarget || GetCurMp() < nMana)
			return;

		if (pTarget && IsValid())
		{
			ICharacter Target(pTarget);

			if (!IsInRange(Target, 20))
			{
				CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
				return;
			}

			if (IsValid() && Target.IsValid())
			{
				Target.Buff(45, TTDuration, TTBaseHeal+ xSkill.GetGrade() *TTPerGradeHeal + CChar::GetWis((int)GetOffset())*TTWisdom);
				Target.RemoveBuffIcon(0, 0, 803, 59);
				_ShowBattleAnimation(Target, 72);
				DecreaseMana(nMana);
			}
			CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		}
	}
}
#endif