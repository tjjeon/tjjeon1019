#define _CRT_SECURE_NO_WARNINGS



// '기능 구현'
#include <iostream>
#include <string>
#include <time.h>
#include "logging.h"

using namespace std;


int main() {


	LOG(INFO, "info메시지");
	LOG(DEBUG, "debug메시지");
	LOG(WARN, "warn메시지");
	LOG(ERROR, "error메시지");
}
