
#ifndef _ISKILL_H_
#define _ISKILL_H_

#include "ServerFunctions.h"


class ISkill
{
protected:
	
	void* m_Offset;

public:

	ISkill();
	ISkill(void* offset);
	virtual ~ISkill();

	void *GetOffset();
	int GetIndex();
	int GetGrade();
	int DecreaseMana();
	void *GetPlayer();

	// COMMON SKILL
	// ONLY MAGE SKILLS
	// ONLY ARCHER SKILLS
	// ONLY KNIGHT SKILLS
	// ONLY THIEF SKILLS
};

#endif // _ISKILL_H_