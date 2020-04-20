#ifndef CTHIEF_H
#define CTHIEF_H

#include "ICharacter.h"

class CThief : public ICharacter
{
public:
	CThief();
	CThief(void* offset);
	~CThief();

};

#endif