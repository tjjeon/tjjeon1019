#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>


#include "filetimestamp.h"



FileTimestamp FileTimestamp::current() {
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    FileTimestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour);
    return ts;

}


std::string FileTimestamp::toString() const
{
    char buf[128];
    sprintf(buf, "%4d.%02d.%02d %02d½Ã",
        year, month, day, hour
    );

    return buf;
}

