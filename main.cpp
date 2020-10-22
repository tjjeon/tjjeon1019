#define _CRT_SECURE_NO_WARNINGS
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif
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
#include <direct.h>		//mkdir
#include <errno.h>		//errno
#include "context.h"
#include "timestamp.h"
#include "filetimestamp.h"

//using namespace std;

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
       
        return fopen(filename.c_str(), writemode);
    }

    void write(const std::string& dir, Level level, const std::string& message, const Context& context, const Timestamp& timestamp, const FileTimestamp& filetimestamp) {
        
        
        int MaxSize = 200;
        int filenum = 0;
        //int i;
        

        // INFO 2020.10.20 10:30:22 foo:30> 
        std::string header = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();


        //std::string filename = getLevelString(level) + " " + timestamp.toString() + " " + context.toString();
        const char* cdir = dir.c_str();
        //char strFolderPath[] = { cdir};

        int nResult = _mkdir(cdir);

        char strfilenum[128];
        sprintf(strfilenum, "%02d", filenum);
        filename = dir.c_str()+getLevelString(level) + " " + filetimestamp.toString() + "no." + strfilenum + ".log";
        int filesize = getSize(level, filename);
        while (getSize(level, filename) > MaxSize)
        {
            ++filenum;
            sprintf(strfilenum, "%02d", filenum);
            filename = dir.c_str() + getLevelString(level) + " " + filetimestamp.toString() + "no." + strfilenum + ".log";
            printf("���Ϲ�ȣ : %d", filenum);
        }
            
        
        //std::cout << filename << std::endl;
        
        FILE* fp = getFile(level, "a", filename);

        if (printToStdout) {
            printf("%s> %s\n", header.c_str(), message.c_str());
        }
        fprintf(fp, "%s> %s\n", header.c_str(), message.c_str());

        fclose(fp);
    }

    int getSize(Level level, std::string filename) const {

        int size = 0;

        FILE* fp = getFile(level, "r", filename);
        if (fp == nullptr) {
            return 0;
        }

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);

        fclose(fp);
        //printf("File size : %d bytes\n", size);
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

#define LOG(dir, level, message) Logger::getInstance().write(dir, level, message, Context(__func__, __LINE__), Timestamp::current(), FileTimestamp::current());
#define PRINTDISPLAY(print) Logger::getInstance().setPrintToStdout(print);

int main() {

    
    PRINTDISPLAY(true);
	LOG("", INFO, "info�޽���");
	LOG("LOG\\",DEBUG, "debug�޽���");
	LOG("D:\\LOG\\",WARN, "warn�޽���");
	LOG("LOG\\",ERROR, "error�޽���");
}
