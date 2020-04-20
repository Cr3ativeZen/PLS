#ifndef CKNIGHT_H
#define CKNIGHT_H

#include "ICharacter.h"

class CKnight: public ICharacter
{
public:
	CKnight();
	CKnight(void* offset);
<<<<<<< HEAD
	virtual ~CKnight();

	// SKILLS
	//void __fastcall PowerfulUpwardSlash(void* pSkill, void* pPacket, void* pPos);
=======
	~CKnight();
>>>>>>> parent of 815c893... comicik
};

#endif