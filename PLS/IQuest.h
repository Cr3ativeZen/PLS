#ifndef _IQUEST_H
#define _IQUEST_H
class IQuest
{
	public:
		void *Offset;

	public:
        
    IQuest(void *Object);
    virtual ~IQuest();
    
    void *GetOffset();
    int GetIndex();
	int GetFlag();
};
#endif