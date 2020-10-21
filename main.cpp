// 1. 모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
// 2. 로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다.
// 3. 로깅의 출력 레벨을 조정할 수 있어야 한다.
// 4. 로깅의 정확한 날짜와 시간을 기록할 수 있어야 한다.
// 5. 로깅을 날짜별 시간별로 다른 파일로 기록할 것.
// 6. 로그 파일이 지정된 크기를 넘어설 경우, 자동으로 다른 파일에 기록할 수 있어야 한다.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

#include "logging.h"

using std::cout;
using std::endl;
using std::cin;


int keyinput() {

    while (1) {
        getchar();
        getchar();
        LOG(ERROR);
        LOG(WARN);
        LOG(INFO);
        LOG(DEBUG);
        LOG(TRACE);
    }
}
//int fileinput();

class BaseMenu {
    std::string title;
public:
    BaseMenu(const std::string& s) : title(s) {}
    virtual ~BaseMenu() {}

    std::string getTitle() const { 
        if (title == "키보드 입력 로깅")
        {
            //cout << "키보드" << endl;

            //getchar();
            //LOG(INFO);
            keyinput();
        }
        else if (title == "파일 입력 로깅")
        {
            cout << "파일" << endl;
            //fileinput();
        }
        return title; }

    virtual void command() = 0;
};

class MenuItem : public BaseMenu {
public:
    MenuItem(const std::string& s) : BaseMenu(s) {}

    void command() override {
        cout << getTitle() << "이 선택됨" << endl;
        char key =getchar();
        //getchar();
        //fflush(keyinput);
    }
};

class PopupMenu : public BaseMenu {
    std::vector<BaseMenu*> v;          
public:
    PopupMenu(const std::string& s) : BaseMenu(s) {}

    void addMenu(BaseMenu* p) { v.push_back(p); }

    void command() override {
        while (1) {
            system("cls"); 
            int sz = v.size();
            for (int i = 0; i < sz; ++i) {
                cout << i + 1 << ". " << v[i]->getTitle() << endl;
            }
            cout << sz + 1 << ". 상위 메뉴로" << endl;

            cout << "메뉴를 선택하세요 >> ";
            int cmd;
            cin >> cmd;

            if (cmd == sz + 1)
            {
               // cout << "cmd : " << cmd << endl;
                break;
            }

            if (cmd < 1 || cmd > sz + 1) 
            { 
                //cout << "cmd : " << cmd << endl;
                continue;
            }

          
            v[cmd - 1]->command();  
           
        }
        
    }
};

int main() {
    PopupMenu* menubar = new PopupMenu("MENUBAR");
    PopupMenu* p1 = new PopupMenu("로깅");
    PopupMenu* p2 = new PopupMenu("로깅 출력 레벨 조정");
    PopupMenu* p3 = new PopupMenu("로깅 파일 저장 위치 설정");
    PopupMenu* p4 = new PopupMenu("도움말");


    menubar->addMenu(p1);
    menubar->addMenu(p2);
    menubar->addMenu(p3);

    p1->addMenu(new MenuItem("키보드 입력 로깅"));
    p1->addMenu(new MenuItem("랜덤 입력 로깅"));
    p1->addMenu(new MenuItem("파일 입력 로깅"));

    p2->addMenu(new MenuItem("ERROR 메시지만 출력"));
    p2->addMenu(new MenuItem("WARN,ERROR 메시지 출력"));
    p2->addMenu(new MenuItem("INFO, WARN,ERROR 메시지 출력"));
    p2->addMenu(new MenuItem("DEBUG, INFO, WARN,ERROR 메시지 출력"));
    p2->addMenu(new MenuItem("TRACE, DEBUG, INFO, WARN,ERROR 메시지 출력"));

    p3->addMenu(new MenuItem("기본저장소"));
    p3->addMenu(new MenuItem("외장디스크"));
    p3->addMenu(new MenuItem("파일에 경로 지정"));
    
    p4->addMenu(new MenuItem("로깅 메시지 띄우는 법"));
    p4->addMenu(new MenuItem("로그 레벨"));



    menubar->command();
    
}
