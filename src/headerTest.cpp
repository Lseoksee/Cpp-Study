/**
@see https://devshovelinglife.tistory.com/116, https://blog.naver.com/techref/222232021003

컴파일러별 미리 정의된 메크로:
MSVC: https://learn.microsoft.com/ko-kr/cpp/preprocessor/predefined-macros?view=msvc-170
GCC: https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
*/

#include <iostream>

// ifdef를 써도 되지만 defined()가 쫌더 최신식 (논리 연산자로 조합이 가능)  */
// 이런식으로 전처리기에는 메크로 함수가 와도 되지만 일반적인 함수가 와도됨
#if defined(__WIN32) || defined(__WIN64)
void OS() { std::cout << "윈도우임" << std::endl; }
#elif defined(__unix__)
void OS() { std::cout << "리눅스임" << std::endl; }
#else
// 컴파일 과정에서 오류메시지 보내고 종료시킴
#error 이상한 컴파일러 쓰지마
#endif


// ifndef = if의 역
// 만약 header.h 정의가 없을때 header를 정의하라
// #pragma once를 고전적으로 쓰는 방식, header파일에 중복 include를 막음
#ifndef HEADER
#define HEADER
#endif

int main(int argc, char const *argv[]) {
    OS();
    // 컴파일러 과정에서 메시지 (전처리기는 코드 내부에서도 가능)
    #pragma message("여기가 컴파일 됨")
    return 0;
}
