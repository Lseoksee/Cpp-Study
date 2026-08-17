#include <iostream>

using namespace std;

// 글로벌 정적 변수
// 다른 파일에서 쓰려면 extern 키워드 필요
int staticGB = 10;

/*
c++ 변수 종류
1. 자동 변수(automatic variable)
2. 레지스터 변수(register variable) // c++17 이후로는 deprecated 컴파일러가 알아서 지정
3. 정적 변수(static variable)
*/

// 자동 변수 = 지역 변수 및 함수 인자등
int autoFunc(int a) {
    int b = a;

    // CPU 레지스터 영역에 선언되는 변수
    return b;
}

int main(int argc, char const* argv[]) {
    autoFunc(1);

    // c++17 deprecated  register가장 빠른 메모리 접근이 가능
    // register int reg = 10;

    // 정적 변수
    static int stVal = 20;
    return 0;
}
