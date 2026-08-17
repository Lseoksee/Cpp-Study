#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const* argv[]) {
    //std::string
    string str = "대충 이렇게 쓴";

    //c++ 문자열은 java처럼 객체 취급
    cout << str << endl;
    cout << str.length() << endl; // java 수준에 string 메소드 지원

    // strcpy() 같은 복사 함수 쓰지 않고 단순 대입으로 처리 가능
    string  str2 = str;
    cout << str2 << endl;
    
    // 합치는것도 연산으로 가능
    str += str2;
    cout << str << endl;

    return 0;
}
