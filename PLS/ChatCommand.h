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
		CONFIG.LoadSkillFormulas();
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 12) == "/zeninstance" && IPlayer.GetAdmin() >= 8)
	{
		IPlayer.SystemMessage("Zen instance config reloaded successfully", IConfig::TEXTCOLOR_GREEN);
		CONFIG.LoadInstanceSystem();
	}

	CPlayer::ChatCommand(Player, command);
}
#endif