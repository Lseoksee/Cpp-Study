#include <iostream>

using namespace std;  // std:: 생략 가능하게 함 :: 는 namespace 내부 프러퍼티 들을 사용할 수 있음

int main() {
    // 표준 입력
    char stdinStr[255];
    
    //cin에 경우 띄어쓰기 \n을 구분자로함
    //따라서 123 456 이렇게 입력하면 첫번째 stdinStr값은 123이 되고 두번째 stdinStr값은 456이됨
    cout << "값 입력: ";
    cin >> stdinStr;
    cout << "입력한 값: " << stdinStr << endl;

    cout << "값 입력: ";
    cin >> stdinStr;
    cout << "입력한 값: " << stdinStr << endl;

    // cin >> 은 cin 버퍼에 \n이 남아있어 getline() 호출하면 입력이 바로 넘어감
    // 따라서 getline() 호출하기 전에 버퍼를 비움
    cin.ignore();

    cout << "string 이용: ";
    // std::string
    string str;
    // getline \n 이전 까지 읽음 따라서 띄어쓰기가 가능
    std::getline(std::cin, str);
    cout << str << endl;

    string str2;
    cout << "string 이용2: ";
    std::getline(std::cin, str2);
    cout << str2 << endl;

    return 0;
}