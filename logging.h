//#ifndef _LOGGING_H_
//#define _LOGGING_H_


// �䱸����
// 1. ��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �˼� �־�� �Ѵ�.
// 2. �α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�.
// 3. �α��� ��� ������ ������ �� �־�� �Ѵ�.
// 4. �α��� ��Ȯ�� ��¥�� �ð��� ����� �� �־�� �Ѵ�.
// 5. �α��� ��¥�� �ð����� �ٸ� ���Ϸ� ����� ��.
// 6. �α� ������ ������ ũ�⸦ �Ѿ ���, �ڵ����� �ٸ� ���Ͽ� ����� �� �־�� �Ѵ�.


#define _CRT_SECURE_NO_WARNINGS




// '��� ����'
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

enum Level {
    INFO,
    WARN,
    DEBUG,
    ERROR
};

class Context {
public:
    Context(const std::string& f, int l) : function(f), line(l) {}

    // foo:42
    std::string toString() const {
        return function + ":" + std::to_string(line);
    }

private:
    std::string function;
    int line;
};

class Timestamp {
public:
    Timestamp(int y, int m, int d, int h, int mi, int s)
        : year(y), month(m), day(d), hour(h), minute(mi), second(s) {}

    static Timestamp current() {
        time_t current = time(nullptr);
        struct tm* t = localtime(&current);

        Timestamp ts(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        return ts;
    }

    // "2020.10.20 08:20:35"
    std::string toString() const {
        char buf[128];
        sprintf(buf, "%4d.%02d.%02d %02d:%02d:%2d",
            year, month, day, hour, minute, second
        );

        return buf;
    }
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

class Logger {
public:
    
  
    Logger() : printToStdout(false) {}

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setPrintToStdout(bool b) {
        printToStdout = b;
    }

    std::string getLevelString(Level level) const {
        switch (level) {
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case DEBUG:
            return "DEBUG";
        case ERROR:
            return "ERROR";
            
        default:
            return "";
        }
    }

    FILE* getFile(Level level, int filenumber, const char* writemode) const {
        std::string filename;
        switch (level) {
        case INFO:
            //filename = "info" + std::to_string(filenumber) + ".log";
            //char filenum = (char*)filenumber;
            //const char* filech = filenumber + "info.log"; .
            return fopen("info.log", writemode);
        case WARN:
            
            return fopen("warn.log", writemode);
        case DEBUG:
            return fopen("debug.log", writemode);
        case ERROR:
            return fopen("error.log", writemode);
        default:
            return nullptr;
        }
    }

    void write(Level level, const std::string& message, const Context& context, const Timestamp& timestamp) {
        int filenum = 0;
        int i;
        for (i = 0; i < 10; ++i)
        {
            int filesize = GetSize(level, i);
            if (filesize > 2000)
            {
                filenum = i+1;
                printf("���Ϲ�ȣ : %d", filenum);
            }
            
                
        }
        FILE* fp = getFile(level, filenum, "a");

        // INFO 2020.10.20 10:30:22 foo:30> 
        std::string header = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();
        
        
        //std::string filename = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();


        if (printToStdout) {
            printf("%s> %s\n", header.c_str(), message.c_str());
        }
        fprintf(fp, "%s> %s\n", header.c_str(), message.c_str());

        fclose(fp);
    }

    int GetSize(Level level, int filenumber) {

        int size = 0;
        
        FILE* fp = getFile(level, filenumber,  "r");
        if (fp == nullptr) {
            return 0;
        }

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);

        fclose(fp);
        printf("File size : % d\n", size);
        return size;
    }

private:
    bool printToStdout;

    // �̱��� ����� ���Ա������
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

};




#define LOG(level, message) Logger::getInstance().write(level, message, Context(__func__, __LINE__), Timestamp::current());
