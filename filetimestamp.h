#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>


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