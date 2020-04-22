#ifndef _ICONFIG_H_
#define _ICONFIG_H_
#include <map>
#include <windows.h>
#include "ServerFunctions.h"




class IConfig
{
private:
	IConfig()
	{

	}
	~IConfig()
	{

	}
public:



	static void LoadConfigs();
	

	static std::map<int, PlayerContinueSkill> CheckContinueSkill;

};

struct PlayerContinueSkill
{
	int PlayerX;
	int PlayerY;
	void* PlayerTarget;
	int PlayerSkillGrade;
	int PlayerSkillID;
	DWORD PlayerSkillDelay;
	int PlayerSkillCount;
};

#endif //_ICONFIG_H_