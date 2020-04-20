#ifndef CARCHER_H
#define CARCHER_H

#include "ICharacter.h"

class CArcher : public ICharacter
{
public:
	CArcher();
	CArcher(void* offset);
	~CArcher();
};

#endif