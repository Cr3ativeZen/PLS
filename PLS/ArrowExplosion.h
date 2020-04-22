#ifndef ARROWEXPLOSION_H
#define ARROWEXPLOSION_H
#include "ServerFunctions.h"
void __fastcall ContinueArrowExplosion(ICharacter IPlayer)
{
	if (IPlayer.IsValid())
	{
		IPlayer.CancelBuff(300);
		void *pTarget = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerTarget;
		int nSkillGrade = CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillGrade;

		if (nSkillGrade && pTarget && CheckContinueSkill.find(IPlayer.GetPID())->second.PlayerSkillCount)
		{
			CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount--;
			ICharacter Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target,300))
				{
					ResetContinueSkill(IPlayer);
					IPlayer.CancelBuff(5566);
					return;
				}

				int Around = Target.GetObjectListAround(3);
				Target.AddFxToTarget("davi_ef131_05", 1, 0, 0);
				while(Around)
				{
					ICharacter Object((void*)*(DWORD*)Around);

					if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack()*AEBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset())*AEAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset())*AEStrMultiPvE) + (nSkillGrade*AEPerGradeMultiPvE);


						if (Object.GetType() == 0)
							nDmg = (IPlayer.GetAttack()*AEBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset())*AEAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset())*AEStrMultiPvP) + (nSkillGrade*AEPerGradeMultiPvP);


						IPlayer.OktayDamageArea(Object,nDmg,49);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	IPlayer.CancelBuff(5566);
	return;
}

void __fastcall ArrowExplosion(ICharacter IPlayer, int pPacket, int pPos)
{
	
}
#endif