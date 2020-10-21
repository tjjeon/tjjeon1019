

// 1. 모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
// 2. 로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다./
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


void logprint(int which_log, const char* filename, const char* funcname, const int& linenum);