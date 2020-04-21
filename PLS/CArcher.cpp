#include "CArcher.h"

void __fastcall CArcher::BlowUpArrow(int pPacket, int pPos)
{
	ICharacter IPlayer(pPlayer);
	ISkill ISkill((void*)pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	int nTargetID = 0; char bType = 0; void* pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType == 0 && nTargetID)
		pTarget = CPlayer::FindPlayer(nTargetID);

	if (bType == 1 && nTargetID)
		pTarget = CMonster::FindMonster(nTargetID);

	if (bType >= 2 || !pTarget || pTarget == IPlayer.GetOffset() || IPlayer.GetCurMp() < nMana)
		return;


	ICharacter Target(pTarget);

	if (!IPlayer.IsInRange(Target, 20))
	{
		CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
		return;
	}

	if (bType == 0)
	{

		if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{
			if (IPlayer.CheckHit(Target, 14))
			{
				//int nDmg = (IPlayer.GetAttack() * BlowUpBaseDmgMultiPvP) + (CChar::GetDex((int)IPlayer.GetOffset()) * BlowUpAgiMultiPvP) + (CChar::GetStr((int)IPlayer.GetOffset()) * BlowUpStrMultiPvP) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvP);
				int nDmg = 5000;
				IPlayer.OktayDamageSingle(Target, nDmg, 14);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 14);
			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 14);
			}
		}
	}
	if (bType == 1)
	{
		int Around = Target.GetObjectListAround(3);
		if (IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 2))
		{

			if (IPlayer.CheckHit(Target, 14))
			{

				//int nDmge = (IPlayer.GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
				int nDmge = 5000;
				IPlayer.OktayDamageSingle(Target, nDmge, 14);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 14);

			}
			else
			{
				IPlayer._ShowBattleMiss(Target, 14);
			}
		}
		int i = 0;
		while (Around && i < 2)
		{

			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.GetType() == 1 && Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall**)(int, int, DWORD))(*(DWORD*)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 2))
			{

				if (Object.GetOffset() != Target.GetOffset() && CChar::IsNormal((int)Object.GetOffset()))
				{

					if (IPlayer.CheckHit(Object, 14))
					{
						//int nDmg = (IPlayer.GetAttack() * BlowUpBaseDmgMultiPvE) + (CChar::GetDex((int)IPlayer.GetOffset()) * BlowUpAgiMultiPvE) + (CChar::GetStr((int)IPlayer.GetOffset()) * BlowUpStrMultiPvE) + (ISkill.GetGrade() * BlowUpPerGradeMultiPvE);
						int nDmg = 5000;
						IPlayer.OktayDamageSingle(Object, nDmg, 14);
						IPlayer._ShowBattleAnimation(Object, 14);
						i++;
					}
					else
					{
						IPlayer._ShowBattleMiss(Object, 14);
						i++;
					}
				}

			}
			Around = CBaseList::Pop((void*)Around);
		}
	}
	IPlayer.DecreaseMana(nMana);
	CSkill::ObjectRelease(Target.GetOffset(), (int)pTarget + 352);
}
