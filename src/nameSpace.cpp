#include <iostream>

// 함수, 변수, 구조체, 클래스 등 이름중복을 피하기 위해 존재하는 집합
// namespace를 따로 지정하지 않으면(globla namespace)라는 파일 수준에 자동 포함
namespace Person {
    int sum(int a, int b) { return a + b; };
    int value;
}

using namespace std;
using namespace Person;

int main(int argc, char const* argv[]) {
    int a = Person::sum(10, 20);
    Person::value = a;
    cout << value << endl;
    return 0;
}
