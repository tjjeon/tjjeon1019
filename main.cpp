#define _CRT_SECURE_NO_WARNINGS

// �䱸����
// 1. ��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �˼� �־�� �Ѵ�.
// 2. �α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�.
// 3. �α��� ��� ������ ������ �� �־�� �Ѵ�.
// 4. �α��� ��Ȯ�� ��¥�� �ð��� ����� �� �־�� �Ѵ�.
// 5. �α��� ��¥�� �ð����� �ٸ� ���Ϸ� ����� ��.
// 6. �α� ������ ������ ũ�⸦ �Ѿ ���, �ڵ����� �ٸ� ���Ͽ� ����� �� �־�� �Ѵ�.


// '��� ����'
#include <iostream>
#include <string>
#include <time.h>
//#include "logging.h"
//#include "Timestamp.h"
#include "context.h"
//#include "logger.h"
#include "Timestamp.h"

using namespace std;

enum Level {
    INFO,
    WARN,
    DEBUG,
    ERROR
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

    FILE* getFile(Level level, const char* writemode, std::string filename) const {
        
        switch (level) {
        case INFO:
            //filename = "info" + std::to_string(filenumber) + ".log";
            //char filenum = (char*)filenumber;
            //const char* filech = filenumber + "info.log"; .
            return fopen(filename.c_str(), writemode);
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

    void write(Level level, const std::string& message, const Context& context, const Timestamp& timestamp, const FileTimestamp& filetimestamp) {
        
        

        // INFO 2020.10.20 10:30:22 foo:30> 
        std::string header = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();
        std::string info = getLevelString(level);

        //std::string filename = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();
        filename = getLevelString(level) + " " + filetimestamp.toString() + ".log";
        //filename = "info.log";
        cout << filename << endl;
        //filename = "info.log";
        FILE* fp = getFile(level, "a", filename);

        if (printToStdout) {
            printf("%s> %s\n", header.c_str(), message.c_str());
        }
        fprintf(fp, "%s> %s\n", header.c_str(), message.c_str());

        fclose(fp);
    }

    int GetSize(Level level, int filenumber) {

        int size = 0;

        FILE* fp = getFile(level, "r", filename);
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

    std::string filename;

};



static Timestamp current();

#define LOG(level, message) Logger::getInstance().write(level, message, Context(__func__, __LINE__), Timestamp::current(), FileTimestamp::current());
int main() {

    Logger::getInstance().setPrintToStdout(true);
	LOG(INFO, "info�޽���");
	LOG(DEBUG, "debug�޽���");
	LOG(WARN, "warn�޽���");
	LOG(ERROR, "error�޽���");
}
