#ifndef _PURIFICATION_H
#define _PURIFICATION_H
#include "ResetContinueSkill.h"
void __fastcall Purification(int pSkill, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	ISkill ISkill((void*)pSkill);

	int nTargetID = 0;
	char bType = 0;
	void *pTarget = 0;
	CPacket::Read((char*)Target, (char*)a3, "bd", &bType, &nTargetID);
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

		//if (ITarget.IsBuff(348))
		//{
		//	std::map<int, PlayerFarContinueSkill>::iterator it;
		//	for (it = CheckFarContinueSkill.begin(); it != CheckFarContinueSkill.end(); it++)
		//	{
		//		if (it->second.PlayerTarget == ITarget.GetOffset())
		//		{
		//			IChar Attacker((void*)it->first);
		//		ResetFarContinueSkill(Attacker);
		//			break;
		//		}
		//	}
		//}


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