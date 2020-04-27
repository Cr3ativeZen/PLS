#ifndef _RAII_H_
#define _RAII_H_
#include "Resources.h"
#include "ServerFunctions.h"
class RAII
{
public:
	RAII(int pPacket,int pPos)
	:
	pTarget(0)

	{
		int nTargetID = 0;
		char bType = 0;

		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

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
				break;
			}
		}


	}

	~RAII()
	{
		if(!pTarget)
			CSkill::ObjectRelease(pTarget, (int)pTarget + 352);
	}

	void* pTarget;
};

#endif
