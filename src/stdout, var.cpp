#include <iostream>
using namespace std;  // std:: 생략 가능하게 함 :: 는 namespace 내부 프러퍼티 들을 사용할 수 있음

int main() {
    // 객체에 대한 사용은 .이 아닌 :: 사용
    cout << "하이" << endl;
    // endl 은 문장 끝 이라는것 \n으로 대채해도 됨

    int a = 10;
    // 여기서 << 의 의미는 표준 출력 스트림 삽입 연산자 임
    cout << a << "변수" << endl;

    const char* str2 = "그러나";
    cout << str2 << endl;

    // c에는 별도 라이브러리로 있던 bool이 공식 자료형이됨
    bool sd = true;

    // 유니코드 확장용 2~3바이트 자료형
    // 현재 c/c++ 에 char* 에 한글을 저장하면 자동으로 wchar로 변환후 char로 다시 변환하여 출력됨
    setlocale(LC_ALL, "ko_KR.UTF-8");  // 바이트 해석을 위해 locale()이 필수적
    const wchar_t* str = L"헤잉";
    wcout << str[0] << endl;

    // 이렇게 그냥 char를 쓰면 [0]를 불러오면 저장된 1바이트만 가져오므로 한글이 깨짐
    const char* dj = "안녕하세요";
    cout << dj[0] << endl;

    // 표준 출력
    char stdoutStr[255];
    cin >> stdoutStr;
    cout << "입력한 값: " << stdoutStr << endl;

    return 0;
}