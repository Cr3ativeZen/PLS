#ifndef _SUMMONS_H
#define _SUMMONS_H
#include "ServerFunctions.h"
void __fastcall Summons(int pSkill, void *edx, int Player, int pPacket, int pPos)
{
	ICharacter IPlayer((void*)Player);
	ISkill ISkill((void*)pSkill);

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

	if (bType >= 2 || !pTarget || pTarget == GetOffset() || GetCurMp() < nMana)
		return;

	ICharacter ITarget((void*)pTarget);

	if (IsValid())
	{
		if (ITarget.IsParty()&&CChar::IsGState((int)ITarget.GetOffset(), 2))
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					ICharacter IMembers((void*)*(DWORD*)((void*)i));


					if (CChar::IsGState((int)IMembers.GetOffset(), 2)&& (IsInRange(IMembers, 10)))
					{
						_ShowBattleAnimation(IMembers, 34);
						IMembers.Revive();
						IMembers.Buff(4, 60, -50);
					}
				}
			}
		}
		else
		{
			if (CChar::IsGState((int)ITarget.GetOffset(), 2) && (IsInRange(ITarget, 10)))
			{
				_ShowBattleAnimation(ITarget, 34);
				ITarget.Revive();
				ITarget.Buff(4, 60,-50);
			}
		}
	}
	CSkill::ObjectRelease(ITarget.GetOffset(), (int)pTarget + 352);
	DecreaseMana(nMana);
}
#endif