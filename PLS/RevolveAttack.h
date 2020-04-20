#ifndef REVOLVEATTACK_H
#define REVOLVEATTACK_H

void __fastcall RevolveAttack(ICharacter IPlayer)
{
	if (IsValid() && GetRage() >= 15000)
	{
		int Around = GetObjectListAround(2);

		while (Around)
		{
			ICharacter Object((void*)*(DWORD*)Around);

			if (Object.IsValid() && IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)GetOffset() + 176))((int)GetOffset(), (int)Object.GetOffset(), 0))
			{
				int nDmg = (GetMagic() + GetAttack())*RABaseDmgMultiPvE;


				if (Object.GetType() == 0)
					nDmg = (GetMagic() + GetAttack())*RABaseDmgMultiPvP;

				OktayDamageSingle(Object, nDmg, 113);
			}

			Around = CBaseList::Pop((void*)Around);
		}

		DecreaseRage(15000);
	}
}


#endif