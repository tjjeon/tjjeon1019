#define _CRT_SECURE_NO_WARNINGS



// '��� ����'
#include <iostream>
#include <string>
#include <time.h>
#include "logging.h"

using namespace std;


int main() {


	LOG(INFO, "info�޽���");
	LOG(DEBUG, "debug�޽���");
	LOG(WARN, "warn�޽���");
	LOG(ERROR, "error�޽���");
}
