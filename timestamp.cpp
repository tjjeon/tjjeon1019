#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>


#include "timestamp.h"



Timestamp Timestamp::current() {
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    Timestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return ts;

}


std::string Timestamp::toString() const
{
    char buf[128];
    sprintf(buf, "%4d.%02d.%02d %02dΩ√%02d∫–%2d√ ",
        year, month, day, hour, minute, second
    );

    return buf;
}
