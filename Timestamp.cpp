#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>


#include "Timestamp.h"



Timestamp Timestamp::current() {
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    Timestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return ts;

}


std::string Timestamp::toString() const
{
    char buf[128];
    sprintf(buf, "%4d.%02d.%02d %02d시%02d분%2d초",
        year, month, day, hour, minute, second
    );

    return buf;
}

FileTimestamp FileTimestamp::current() {
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    FileTimestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour);
    return ts;

}


std::string FileTimestamp::toString() const
{
    char buf[128];
    sprintf(buf, "%4d.%02d.%02d %02d시",
        year, month, day, hour
    );

    return buf;
}

/*
std::string Timestamp::current()
{
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    Timestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return ts;
}

std::string Timestamp::toString() const {
    char buf[128];
    sprintf(buf, "%4d.%02d.%02d %02d:%02d:%2d",
        year, month, day, hour, minute, second
    );

    return buf;
}
*/