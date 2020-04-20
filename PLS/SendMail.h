#ifndef SENDMAIL_H
#define SENDMAIL_H

int __fastcall SendMail(void* Player, void *edx, int a1, int a2, char* ReceiverName, const char *Text, int a5, int a6, int Index, int a8, int Amount, int Price)
{
	if (Logs == true)
	{
	ICharacter IPlayer(Player);
	ICharacter plss((void*)a1);
	time_t now = time(0);
	//char* dt = ctime(&now);
	char dt;
	ctime_s(&dt, 1, &now);

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



		std::string to_file2 = "MAIL IS RECIVED! --- RECIVED BY: ";
		to_file2 += ReceiverName;
		to_file2 += "ITEM SENT BY: ";
		to_file2 += IPlayer.GetName();
		to_file2 += "---ITEM ID: ";
		to_file2 += Int2String(Index);
		to_file2 += "---ITEM AMOUNT: ";
		to_file2 += Int2String(Amount);
		to_file2 += "--- ";
		to_file2 += dt;

		std::string FilePath = ("./ZenLogs/Characters/");
		std::string type_for_dir;
		std::string type_for_file;
		time_t now2 = time(0);
		tm* timePtr = localtime(&now2);
		std::string date = Int2String(timePtr->tm_mday) + "_" + Int2String(timePtr->tm_mon) + "_" + Int2String(timePtr->tm_year + 1900) + "_" + Int2String(timePtr->tm_hour);

		type_for_dir = "\\Mails";
		type_for_file = "/Mails/Mails-";
		type_for_file += date;
		type_for_file += ".txt";
		FilePath += ReceiverName;
		FilePath += type_for_file;

		std::ofstream Folders;
		std::string FileN = "C:\\Users\\root\\Desktop\\Server Side\\ZenLogs\\Characters\\";
		//std::string FileN = "C:\\Users\\Admin\\Desktop\\kal\\Shaman ServSide\\ZenLogs\\Characters\\";
		FileN += ReceiverName;


		char* file = new char[FileN.size() + 1];
		strcpy_s(file, FileN.size() + 1, FileN.c_str());
		if (!dirExists(FileN))
		{
			_mkdir(file);
		}

		delete[] file;
		FileN += type_for_dir;
		file = new char[FileN.size() + 1];
		strcpy_s(file, FileN.size() + 1, FileN.c_str());

		if (!dirExists(FileN))
		{
			_mkdir(file);
		}
		Folders.open(FilePath, std::ios_base::out | std::ios::app);
		if (Folders)
		{
			Folders << to_file2;
		}

		Folders.close();
		delete[] file;
	}
	return CPlayer::SendMail(Player, a1, a2, ReceiverName, Text, a5, a6, Index, a8, Amount, Price);
}

#endif