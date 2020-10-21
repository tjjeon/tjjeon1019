#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>


class Timestamp {
public:
    Timestamp(int y, int m, int d, int h, int mi, int s)
        : year(y), month(m), day(d), hour(h), minute(mi), second(s) {}

    static Timestamp current();
        

    // "2020.10.20 08:20:35"
    std::string toString() const;

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

class FileTimestamp {
public:
    FileTimestamp(int y, int m, int d, int h)
        : year(y), month(m), day(d), hour(h) {}

    static FileTimestamp current();


    // "2020.10.20 08:20:35"
    std::string toString() const;

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};