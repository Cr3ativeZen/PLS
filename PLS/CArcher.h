
#ifndef _CARCHER_H_
#define _CARCHER_H_

#include "ICharacter.h"

class CArcher : public ICharacter
{
public:
	CArcher();
	CArcher(void* offset);
	~CArcher();
};

#endif // _CARCHER_H_