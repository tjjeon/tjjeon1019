

// 1. ��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �˼� �־�� �Ѵ�.
// 2. �α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�./
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



enum severity {
	ERROR,
	WARN,
	INFO,
	DEBUG,
	TRACE
};
#define LOG(level)  logprint(level,__FILE__,__FUNCTION__,__LINE__);  



class fileclass {
	std::string log_info;
	std::string filePath;
	std::string information;
	std::string file_name;
	std::string func_name;
	std::string text_name;
	std::string time_info;
	int line_num;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	fileclass(std::string info, std::string fn, std::string fcn, int lnum) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		information = info;
		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;
		hour = tm.tm_hour;
		minute = tm.tm_min;
		second = tm.tm_sec;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		time_info = std::to_string(year) + "/" + std::to_string(month) + "/"
			+ std::to_string(day) + "/" + "]" + ".txt";

		text_name = information + "_" + std::to_string(year) + "." + std::to_string(month) +
			"." + std::to_string(day) + ".txt";

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[ date: " + std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day) + "/  time : " + std::to_string(hour) +
			"h" + std::to_string(minute) + "m" + std::to_string(second) + "s" + "]";
	}

	void Command() {

		 writefile(text_name);

	}

	void writefile(std::string filePath) {
		FILE* fp = fopen(filePath.c_str(), "a");
		if (fp == nullptr) {
			fprintf(stderr, "File Open Error\n");
		};
		std::cout << log_info << std::endl;
		fprintf(fp, log_info.c_str());
		fflush(fp);


	}

};

void logprint(int which_log, const char* filename, const char* funcname, const int& linenum) {
	std::string s;

	switch (which_log)
	{
	case(0): s = "ERROR"; break;
	case(1): s = "WARN"; break;
	case(2): s = "INFO"; break;
	case(3): s = "DEBUG"; break;
	case(4): s = "TRACE"; break;

	default:
		break;
	}
	

	fileclass* m = new fileclass(s, filename, funcname, linenum);
	m->Command();
}