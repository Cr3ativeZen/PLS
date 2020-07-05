#ifndef ONTIMER_H_
#define ONTIMER_H_
#include <chrono>

std::string CurrentTime();

void __fastcall OnTimer(void* Value, void* edx, int Argument)
{
	CCalendar::OnTimer(Value, Argument);


}

std::string CurrentTime()
{
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(p);
    char tab[26];
    ctime_s(tab, sizeof tab, &t);
    std::string ret;

    for (int i = 11; i < 19; i++)
        ret += tab[i];

    return ret;
}


#endif