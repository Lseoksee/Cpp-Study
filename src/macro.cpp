// TODO: 추가 공부 필요
#include <iostream>

using namespace std;

// 메크로 함수, inline 과 비슷한 역할을 함
// 단순히 Double(x) 라는걸 x * 2 로 치환 한다는 개념
#define SQR(X) X* X

// 결과안전을 위해 괄호를 무조건 치는게 좋다
#define SAFE_SQR(X) ((X) * (X))

int main(int argc, char const* argv[]) {
    cout << SQR(10) << endl;
    cout << SQR(5) << endl;

    // 이렇게 매크로 호출내부에서 연산을 수행하면 이상한 값이 나올 수 있음
    // 치환 하는 과정에서 값이 꼬여 버린것
    cout << SQR(5 + 3) << endl;
    cout << SAFE_SQR(5 + 3) << endl;
    return 0;
}
