#ifndef INFODIE_H
#define INFODIE_H


void __fastcall InfoDie(void* Player,void* Target)
{
	IChar IPlayer(Player);
	IChar ITarget(Target);
	if (ITarget.GetType() == 0)
	{
		ITarget.SystemMessage("kappaqwerfq", TEXTCOLOR_RED);
	}
	IPlayer.SystemMessage("kappa", TEXTCOLOR_RED);
	
}



#endif