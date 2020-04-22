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

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}



#pragma pack(1)
#include <string>
#include "ServerFunctions.h"
#include "ICharacter.h"
#include "IQuest.h"
#include "IItem.h"
#include "Heal.h"
#include "Cure.h"
#include "ExecuteSkill.h"
#include "ChatCommand.h"
#include "Summon.h"
#include "Player.h"
#include "D4Instance.h"
#include "BlowUpArrow.h"
#include "Calls.h"
#include "MuscleSolidation.h"
#include "Sacrifice.h"
#include "Amnesia.h"
#include "FocusShot.h"
#include "MysteriousArrow.h"
#include "PassiveAttack.h"
#include "FlamyArrow.h"
#include "Summons.h"
#include "Player.h"
#include "ShieldAttack.h"
#include "LightningSlash.h"
#include "TranscendentalBlow.h"
#include "Purification.h"
#include "BuffRemover.h"
#include "MonsterTick.h"
#include "PKKill.h"
#include "UpdateProperty.h"
#include "FinalDamage.h"
#include "ShadowSlash.h"
#include "ArrowRain.h"
#include "ResetContinueSkill.h"
#include "CombativeSpirit.h"
#include "ArrowExplosion.h"
#include "VirulentArrow.h"
#include "LightningSlashThief.h"
#include "SpinBlade.h"
#include "SpinSlash.h"
#include "SwordDance.h"
#include "ProvocationOfBlow.h"
#include "TherapeuticTouch.h"
#include "Icicle.h"
#include "FlameInjection.h"
#include "Thunderbolt.h"
#include "IceArrow.h"
#include "Fireball.h"
#include "LightningArrow.h"
#include "SpinAttack.h"
#include "ArmorBreaker.h"
#include "CanAttack.h"
#include "TwinBladeStrike.h"
#include "AnkleAmputate.h"
#include "FatalWound.h"
#include "FinalBlow.h"
#include "SuicidalBlow.h"
#include "Rupture.h"
#include "VitalStrike.h"
#include "PowerfulUpwardSlash.h"
#include "BrutalAttack.h"
#include "HalfSwing.h"
#include "LifeAbsorption.h"
#include "Packet.h"
#include "ChainLightning.h"
#include "ThunderStorm.h"
#include "IceStorm.h"
#include "FireStorm.h"
#include "WhirlwindFeather.h"
#include "RevolveAttack.h"
#include "EggThunderbolt.h"
#include "BloodSuction.h"
#include "OneHitStrike.h"
#include "ArrowsoftheMaster.h"
#include "MassiveFire.h"
#include "SpiritOfTheArrows.h"
#include "TheBoomofEarth.h"
#include "ThewaveofEarth.h"
#include "ShoutOfDefense.h"
#include "ShoutOfFightingSpirit.h"
#include "ReleasingTheEnergy.h"
#include "Punishment.h"
#include "Bombing.h"
#include "Incapacitation.h"
#include "CriticalDiffusion.h"
#include "CriticalStrike.h"
#include "StrikeOfGod.h"
#include "DestroyingArmor.h"
#include "SoulDestruction.h"
#include "PowerfulWideningWound.h"
#include "SendMail.h"
#include "Resources.h"


void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	CIOServer::Start(Start, hostshort);
	InstaConfig();
	ZenConfig();
	RiftConfig();
	MautaretaConfig();
	ConsoleWriteBlue("CreativeZen's DLL loaded successfully");
	Sleep(500);


}


int __fastcall Hooked_MainServer_Stop(int stop)
{
	return MainServer::Stop(stop);
	SkillLog.close();
	SpeedHackLog.close();
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
		DetourAttach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourAttach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
		DetourAttach(&(PVOID&)CMonsterReal::Die, MonsterDie);
		DetourAttach(&(PVOID&)CPlayer::PKKill, PKKill);
		DetourAttach(&(PVOID&)CPlayer::UpdateProperty, UpdateProperty);
		DetourAttach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourAttach(&(PVOID&)CPlayer::Process, Packet);
		DetourAttach(&(PVOID&)CPlayer::CanAttack, CanAttack);
		DetourAttach(&(PVOID&)CPlayer::SendMail, SendMail);
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
		DetourDetach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
		DetourDetach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
		DetourDetach(&(PVOID&)CMonsterReal::Die, MonsterDie);
		DetourDetach(&(PVOID&)CPlayer::PKKill, PKKill);
		DetourDetach(&(PVOID&)CPlayer::UpdateProperty, UpdateProperty);
		DetourDetach(&(PVOID&)CChar::GetFinalDamage, FinalDamage);
		DetourDetach(&(PVOID&)CPlayer::Process, Packet);
		DetourDetach(&(PVOID&)CPlayer::CanAttack, CanAttack);
		DetourDetach(&(PVOID&)CPlayer::SendMail, SendMail);
		DetourTransactionCommit();
		break;
	}
	}

	return TRUE;
}