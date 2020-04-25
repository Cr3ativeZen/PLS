#include "IConfig.h"

void IConfig::LoadConfigs()
{
}

int IConfig::CallRANGE = 20;

int IConfig::AEBaseDmgMultiPvE = 0;
int IConfig::AEAgiMultiPvE = 0;
int IConfig::AEStrMultiPvE = 0;
int IConfig::AEPerGradeMultiPvE = 0;

int IConfig::AEBaseDmgMultiPvP = 0;
int IConfig::AEAgiMultiPvP = 0;
int IConfig::AEStrMultiPvP = 0;
int IConfig::AEPerGradeMultiPvP = 0;
bool IConfig::ArrowExplosionON = true;
bool IConfig::ArrowRainON = true;

std::map<int, IConfig::ConfigIceArrow> IConfig::CheckIceArrow;
std::map<int, IConfig::ConfigShiny> IConfig::CheckShiny;
std::map<int, int> IConfig::MageMICheck;

std::map<int, IConfig::PlayerContinueSkill> IConfig::CheckContinueSkill;
std::map<int, IConfig::PlayerFarContinueSkill> IConfig::CheckFarContinueSkill;

std::map<int, IConfig::CallCheck>IConfig::CallOfEvasionOTP;
std::map<int, IConfig::CallCheck>IConfig::CallOfDefense;
std::map<int, IConfig::CallCheck>IConfig::CallOfPhysicalAttack;
std::map<int, IConfig::CallCheck>IConfig::CallOfRecovery;


std::map<int, IConfig::PlayerContinueIceStorm>IConfig::CheckContinueIceStorm;
std::map<int, IConfig::PlayerContinueFireStorm>IConfig::CheckContinueFireStorm;
std::map<int, IConfig::PlayerContinueThunderStorm>IConfig::CheckContinueThunderStorm;