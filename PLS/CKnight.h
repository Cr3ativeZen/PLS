#ifndef CKNIGHT_H
#define CKNIGHT_H

#include "ICharacter.h"

class CKnight: public ICharacter
{
public:
	CKnight();
	CKnight(void* offset);
	~CKnight();
};

#endif