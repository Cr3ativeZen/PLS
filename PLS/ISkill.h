#ifndef _ISKILL_H
#define _ISKILL_H
#include "ServerFunctions.h"

class ISkill
{

public:
	void *Offset;

public:

	ISkill(void *Packet);
	virtual ~ISkill();

	void *GetOffset();
	int GetIndex();
	int GetGrade();
	int DecreaseMana();
	void *GetPlayer();
};
#endif