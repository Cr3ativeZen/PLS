#ifndef _RAII_H_
#define _RAII_H_
#include "Resources.h"
#include "ServerFunctions.h"
class RAII
{
public:
	RAII(int nTargetID,int bType)
	:
	found(true)

	{
		switch (bType)
		{
		case TYPE_PLAYER:
			{
				pTarget = CPlayer::FindPlayer(nTargetID);
				break;
			}
		case TYPE_MONSTER:
			{
				pTarget = CMonster::FindMonster(nTargetID);
				break;
			}
		default:
		{
			found = false;
			break;
		}
		}

		if (!pTarget)
			found = false;

	}

	~RAII()
	{
		if(!found)
			CSkill::ObjectRelease(pTarget, (int)pTarget);
	}

	void* pTarget;
	bool found;
};

#endif
