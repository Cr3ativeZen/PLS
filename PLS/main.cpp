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


#pragma pack(1)
#include <string>
#include "ServerFunctions.h"
#include "ICharacter.h"
#include "IQuest.h"
#include "IItem.h"
#include "ExecuteSkill.h"
#include "ChatCommand.h"
#include "Player.h"
#include "Packet.h"
#include "Resources.h"
#include "IConfig.h"
#include "SummonDie.h"
#include "FinalDamage.h"
#include "CDungeon.h"
#include "Summon.h"
#include "LeaveParty.h"


void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	CIOServer::Start(Start, hostshort);

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
		DetourAttach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourAttach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourAttach(&(PVOID&)CPlayer::LeaveParty, LeaveParty);

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
		DetourDetach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourDetach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourDetach(&(PVOID&)CPlayer::LeaveParty, LeaveParty);
		
		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}