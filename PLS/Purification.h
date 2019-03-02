#ifndef _PURIFICATION_H
#define _PURIFICATION_H
#include "ResetContinueSkill.h"
void __fastcall Purification(IChar IPlayer,int pPacket, int pPos)
{
	ISkill ISkill((void*)IPlayer.GetSkillPointer(54));

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

	if (bType >= 2)
		return;

	IChar ITarget((void*)pTarget);
	if (pTarget && ITarget.IsValid() && IPlayer.IsValid())
	{

		//ITarget.CancelBuff(350);
		//ITarget.CancelBuff(339);
		//ITarget.CancelBuff(340);
		ITarget.CancelBuff(307);
		ITarget.CancelBuff(342);
		ITarget.CancelBuff(346);
		ITarget.CancelBuff(348);
		ITarget.CancelBuff(356);
		ITarget.CancelBuff(390);
		ITarget.CancelBuff(391);
		ITarget.CancelBuff(358);
		ITarget.CancelBuff(359);
		ITarget.CancelBuff(40);
		ITarget.CancelBuff(4002);
		ITarget.CancelBuff(4001);
		ITarget.CancelBuff(4003);
		ITarget.CancelBuff(790);
		ITarget.RemoveBuffIcon(0, 0, 0, 225);
		ITarget.RemoveBuffIcon(0, 0, 0, 224);
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);

}
#endif