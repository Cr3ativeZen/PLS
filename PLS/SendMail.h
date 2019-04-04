#ifndef SENDMAIL_H
#define SENDMAIL_H

int __fastcall SendMail(void* Player, void *edx, int a1, int a2, char* ReceiverName, const char *Text, int a5, int a6, int Index, int a8, int Amount, int Price)
{
	IChar IPlayer(Player);
	IChar plss((void*)a1);
	time_t now = time(0);

	char* dt = ctime(&now);

	/*IPlayer.SystemMessage(ReceiverName, TEXTCOLOR_RED);
	IPlayer.SystemMessage(Text, TEXTCOLOR_RED);
	IPlayer.SystemMessage(Int2String(Index), TEXTCOLOR_BLUE);
	IPlayer.SystemMessage(Int2String(a8), TEXTCOLOR_BLUE);
	IPlayer.SystemMessage(Int2String(Amount), TEXTCOLOR_BLUE);
	IPlayer.SystemMessage(Int2String(Price), TEXTCOLOR_BLUE);*/

	std::string to_file = "MAIL IS SENT! ---SENT BY: ";
	to_file += IPlayer.GetName();
	to_file += "---ITEM SENT TO: ";
	to_file += ReceiverName;
	to_file += "---ITEM ID: ";
	to_file += Int2String(Index);
	to_file += "---ITEM AMOUNT: ";
	to_file += Int2String(Amount);
	to_file += "--- ";
	to_file += dt;
	WritePacketToFile(IPlayer, Mails, to_file);




	return CPlayer::SendMail(Player, a1, a2, ReceiverName, Text, a5, a6, Index, a8, Amount, Price);
}

#endif