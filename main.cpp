#define _CRT_SECURE_NO_WARNINGS
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif
// 요구사항
// 1. 모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
// 2. 로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다.
// 3. 로깅의 출력 레벨을 조정할 수 있어야 한다.
// 4. 로깅의 정확한 날짜와 시간을 기록할 수 있어야 한다.
// 5. 로깅을 날짜별 시간별로 다른 파일로 기록할 것.
// 6. 로그 파일이 지정된 크기를 넘어설 경우, 자동으로 다른 파일에 기록할 수 있어야 한다.


// '기능 구현'
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
            printf("파일번호 : %d", filenum);
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

    // 싱글톤 복사와 대입금지기법
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    std::string filename;

};



static Timestamp current();

#define LOG(dir, level, message) Logger::getInstance().write(dir, level, message, Context(__func__, __LINE__), Timestamp::current(), FileTimestamp::current());
#define PRINTDISPLAY(print) Logger::getInstance().setPrintToStdout(print);

int main() {

    
    PRINTDISPLAY(true);
	LOG("", INFO, "info메시지");
	LOG("LOG\\",DEBUG, "debug메시지");
	LOG("D:\\LOG\\",WARN, "warn메시지");
	LOG("LOG\\",ERROR, "error메시지");
}
