
#ifndef _BUFFREMOVER_H
#define _BUFFREMOVER_H
void __fastcall BuffRemover(IChar IPlayer,int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(45));

	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1)
		return;

	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
		return;

	IChar ITarget((void*)pTarget);

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid())
	{
		ITarget.CancelBuff(282);
		ITarget.CancelBuff(283);
		ITarget.CancelBuff(284);
		ITarget.CancelBuff(24);
		ITarget.CancelBuff(305);
		ITarget.CancelBuff(306);
		ITarget.CancelBuff(379);
		ITarget.CancelBuff(380);
		ITarget.CancelBuff(381);
		ITarget.CancelBuff(382);
		ITarget.CancelBuff(383);
		ITarget.CancelBuff(384);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
}
#endif