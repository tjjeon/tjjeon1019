#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
using namespace std;

#define LOG_DEBUG	logdisp(DEBUG		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_TRACE	logdisp(TRACE		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_INFO	logdisp(INFO		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_WARNING logdisp(WARNING		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_ERROR	logdisp(ERROR		,__FILE__,__FUNCTION__,__LINE__)
#define LOG_FATAL	logdisp(FATAL		,__FILE__,__FUNCTION__,__LINE__)


void logdisp(const int& s, const char* fileName_, const char* funcName_, const int& line_) {
    Log* m = new Log(fileName_, funcName_, line_);
    m->Logprint();
}


enum LogLevel {
    DEBUG = 0,
    TRACE = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

class LoggingEvent : public ostringstream {
private:
    string _module;
    LogLevel _level;
    string _file;
    string _func;
    int _line;

    // Prohibit invocation of default constructor
    LoggingEvent();

public:
    LoggingEvent(
        const char* mod, LogLevel lvl, const char* file,
        const char* func, int line,
        const char* msg = ""
    ) :
        ostringstream(), _module(mod), _level(lvl), _file(file), _func(func), _line(line)
    {
        *this << msg;
    }

 

};

