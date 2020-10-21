#define _CRT_SECURE_NO_WARNINGS



// '��� ����'
#include <iostream>
#include <string>
#include <time.h>
#include "logging.h"

using namespace std;


int main() {

#if 0
	Logger l;
	l.setPrintToStdout(true);

	l.write(INFO, "hello", Context(__func__, __LINE__), Timestamp::current());
#endif
	Logger::getInstance().setPrintToStdout(true);
	Logger::getInstance().write(INFO, "hello", Context(__func__, __LINE__), Timestamp::current());

	LOG(INFO, "hello");
	LOG(DEBUG, "debug�޽���");
	LOG(WARN, "warn�޽���");
	LOG(ERROR, "error�޽���");
}
