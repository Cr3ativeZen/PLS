#pragma comment(lib, "detours.lib")

#undef UNICODE
#include <cstdio>
#include <windows.h>
#include "detours.h"
#include <process.h>
#include <fstream>
#include <map>
#include <vector>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <random>
#include <algorithm>
#include <math.h>
#include <direct.h>
#include <set>


std::string Int2String(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}

int String2Int(std::string String)
{
	int Integer;
	std::istringstream iss(String);
	iss >> Integer;
	return Integer;
}


struct CheckConfigCooldown
{
	int CooldownConfig;
	int DelayConfig;
};


enum ToFile
{
	SpeedHack = 1,
	SkillLogs = 2,
	Mails = 3,
	WoodenBox = 4,
	SkillHacks = 5
};


std::map<std::pair<void*, void*>, int> ::iterator boss;
std::map<std::pair<void*, void*>, int>BossRNG;
std::map<int, int> PlayerBlockCheck;
std::map<int, DWORD> MonsterDisappear;


std::map<int, CheckConfigCooldown> CheckCooldownConfig;
std::map<int, int> CooldownTable;




enum TextColor
{
	TEXTCOLOR_GENERAL = RGB(255, 255, 255),
	TEXTCOLOR_INFOMSG = RGB(70, 227, 232),
	TEXTCOLOR_SHUTDOWN = RGB(240, 116, 15),
	TEXTCOLOR_ORANGE = RGB(255, 128, 64),
	TEXTCOLOR_BLUE = RGB(0, 128, 255),
	TEXTCOLOR_YELLOW = RGB(255, 255, 128),
	TEXTCOLOR_RED = RGB(255, 0, 0),
	TEXTCOLOR_PARTY = RGB(210, 64, 0),
	TEXTCOLOR_GUILD = RGB(10, 255, 229),
	TEXTCOLOR_ALLIANCE = RGB(128, 128, 192),
	TEXTCOLOR_GREEN = RGB(0, 255, 0),
	TEXTCOLOR_DARKGREEN = RGB(0, 170, 0),
	TEXTCOLOR_FAILED = RGB(250, 210, 0),
	TEXTCOLOR_CLASSMATE = RGB(0, 128, 0),
	TEXTCOLOR_PUPIL = RGB(255, 128, 64),
	TEXTCOLOR_PINK = RGB(255, 155, 255),
};




#pragma pack(1)
#include <string>
#include "ServerFunctions.h"
#include "ICharacter.h"
#include "IQuest.h"
#include "IItem.h"
#include "ExecuteSkill.h"
#include "ChatCommand.h"
#include "InstaConfig.h"
#include "Player.h"
#include "Packet.h"
#include "Resources.h"
#include "IConfig.h"




void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	CIOServer::Start(Start, hostshort);
	ZenConfig();

	CONFIG.LoadSkillFormulas();
	ConsoleWriteBlue("CreativeZen's DLL loaded successfully");
	Sleep(500);

}


int __fastcall Hooked_MainServer_Stop(int stop)
{
	return MainServer::Stop(stop);
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)CIOServer::Start, Start);
		DetourAttach(&(PVOID&)MainServer::Stop, Hooked_MainServer_Stop);
		DetourAttach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
		DetourAttach(&(PVOID&)CPlayer::Tick, Tick);
		DetourAttach(&(PVOID&)CPlayer::Process, Packet);
		DetourTransactionCommit();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)CIOServer::Start, Start);
		DetourDetach(&(PVOID&)MainServer::Stop, Hooked_MainServer_Stop);
		DetourDetach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
		DetourDetach(&(PVOID&)CPlayer::Tick, Tick);
		DetourDetach(&(PVOID&)CPlayer::Process, Packet);
		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}