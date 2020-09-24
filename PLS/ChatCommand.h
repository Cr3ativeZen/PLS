#ifndef CHATCOMMAND_H_
#define CHATCOMMAND_H_
#include "ServerFunctions.h"
void __fastcall ChatCommand(int Player, void *edx, const char *command)
{
	if (!strlen(command))
		return;

	std::string cmd = (std::string)command;
	ICharacter IPlayer((void*)Player);


	if (IPlayer.IsOnline() && cmd.substr(0, 10) == "/zenconfig" && IPlayer.GetAdmin() >= 8)
	{
		IPlayer.SystemMessage("Zen skill config reloaded successfully", IConfig::TEXTCOLOR_GREEN);
		CONFIG.LoadConfigs();
	}
	if (IPlayer.IsOnline() && cmd.substr(0, 4) == "/atk" && IPlayer.GetAdmin() >= 8)
	{
		IPlayer.AddMinMagicAttack(IPlayer.GetMaxMagAttack() - IPlayer.GetMinMagAttack());
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 9) == "/zeninsta" && IPlayer.GetAdmin() >= 8)
	{

		if(CONFIG.LoadInstanceConfig())
			IPlayer.SystemMessage("Zen instance config reloaded successfully", IConfig::TEXTCOLOR_GREEN);
		else
			IPlayer.SystemMessage("Can't reload instance while it's running!", IConfig::TEXTCOLOR_RED);
	}

	CPlayer::ChatCommand(Player, command);
}
#endif