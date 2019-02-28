#ifndef REVOLVEATTACK_H
#define REVOLVEATTACK_H

void __fastcall RevolveAttack(IChar IPlayer)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000)
	{
		int Around = IPlayer.GetObjectListAround(2);

		while (Around)
		{
			IChar Object((void*)*(DWORD*)Around);

			if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
			{
				int nDmg = (IPlayer.GetMagic() + IPlayer.GetAttack())*RABaseDmgMultiPvE;


				if (Object.GetType() == 0)
					nDmg = (IPlayer.GetMagic() + IPlayer.GetAttack())*RABaseDmgMultiPvP;

				IPlayer.OktayDamageSingle(Object, nDmg, 113);
			}

			Around = CBaseList::Pop((void*)Around);
		}

		IPlayer.DecreaseRage(15000);
	}
}


#endif