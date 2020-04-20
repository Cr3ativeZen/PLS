
#ifndef _CKNIGHT_H_
#define _CKNIGHT_H_

#include "ICharacter.h"

class CKnight: public ICharacter
{
public:
	CKnight();
	CKnight(void* offset);
	virtual ~CKnight();

	// SKILLS
	//void __fastcall PowerfulUpwardSlash(void* pSkill, void* pPacket, void* pPos);
};

#endif // _CKNIGHT_H_