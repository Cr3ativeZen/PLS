
#include <windows.h>
#include "ServerFunctions.h"
#include "ISkill.h"


ISkill::ISkill() : m_Offset(nullptr)
{
}

ISkill::ISkill(void* offset) : m_Offset(offset)
{
}

ISkill::~ISkill()
{
}

void *ISkill::GetOffset()
{
	return this->m_Offset;
}

int ISkill::GetIndex()
{
	if (this->GetOffset())
		return *(DWORD*)((int)(this->m_Offset) + 4);
	else
		return 0;
}

int ISkill::GetGrade()
{
	if (this->GetOffset())
		return *(DWORD*)((int)(this->m_Offset) + 8);
	else
		return 0;
}

int ISkill::DecreaseMana()
{
	if (this->GetOffset())
		return (*(int (__thiscall **)(void*, DWORD))(*(DWORD *)this->m_Offset + 0x20))(this->m_Offset, 0);
	else
		return 0;
}

void* ISkill::GetPlayer()
{
	if (this->GetOffset())
		return (void*)*(DWORD*)(int)(this->m_Offset);
	else
		return 0;
}
