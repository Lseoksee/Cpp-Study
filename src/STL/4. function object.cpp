/* 
STL에 알고리즘을 전달할때 쓸 수 있는 표현 식들

- 함수 포인터
- 함수 객체
- 람다 표현식

그 중 함수 객체는 객체변수 자체를 호출연산자() 를 사용하는 객체를 의미
펑크터(functor) 라고도 불림

해당 클래스에서 호출연산자() 를 오버로딩 하여 구현 함
*/

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    // 구조체 포인터로 구성 되어있으며, 내부적으로 호출연산자()를 오버로딩 함
    plus<int> add;

    cout << add(10, 20) << endl;
    return 0;
}
