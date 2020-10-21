// 1. ��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �˼� �־�� �Ѵ�.
// 2. �α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�.
// 3. �α��� ��� ������ ������ �� �־�� �Ѵ�.
// 4. �α��� ��Ȯ�� ��¥�� �ð��� ����� �� �־�� �Ѵ�.
// 5. �α��� ��¥�� �ð����� �ٸ� ���Ϸ� ����� ��.
// 6. �α� ������ ������ ũ�⸦ �Ѿ ���, �ڵ����� �ٸ� ���Ͽ� ����� �� �־�� �Ѵ�.
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
        if (title == "Ű���� �Է� �α�")
        {
            //cout << "Ű����" << endl;

            //getchar();
            //LOG(INFO);
            keyinput();
        }
        else if (title == "���� �Է� �α�")
        {
            cout << "����" << endl;
            //fileinput();
        }
        return title; }

    virtual void command() = 0;
};

class MenuItem : public BaseMenu {
public:
    MenuItem(const std::string& s) : BaseMenu(s) {}

    void command() override {
        cout << getTitle() << "�� ���õ�" << endl;
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
            cout << sz + 1 << ". ���� �޴���" << endl;

            cout << "�޴��� �����ϼ��� >> ";
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
    PopupMenu* p1 = new PopupMenu("�α�");
    PopupMenu* p2 = new PopupMenu("�α� ��� ���� ����");
    PopupMenu* p3 = new PopupMenu("�α� ���� ���� ��ġ ����");
    PopupMenu* p4 = new PopupMenu("����");


    menubar->addMenu(p1);
    menubar->addMenu(p2);
    menubar->addMenu(p3);

    p1->addMenu(new MenuItem("Ű���� �Է� �α�"));
    p1->addMenu(new MenuItem("���� �Է� �α�"));
    p1->addMenu(new MenuItem("���� �Է� �α�"));

    p2->addMenu(new MenuItem("ERROR �޽����� ���"));
    p2->addMenu(new MenuItem("WARN,ERROR �޽��� ���"));
    p2->addMenu(new MenuItem("INFO, WARN,ERROR �޽��� ���"));
    p2->addMenu(new MenuItem("DEBUG, INFO, WARN,ERROR �޽��� ���"));
    p2->addMenu(new MenuItem("TRACE, DEBUG, INFO, WARN,ERROR �޽��� ���"));

    p3->addMenu(new MenuItem("�⺻�����"));
    p3->addMenu(new MenuItem("�����ũ"));
    p3->addMenu(new MenuItem("���Ͽ� ��� ����"));
    
    p4->addMenu(new MenuItem("�α� �޽��� ���� ��"));
    p4->addMenu(new MenuItem("�α� ����"));



    menubar->command();
    
}
