#ifndef CMAGE_H
#define CMAGE_H

#include "ICharacter.h"
class CMage : public ICharacter
{
public:
	CMage();
	CMage(void* offset);
	virtual ~CMage();
};

#endif