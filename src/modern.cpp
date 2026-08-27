// 모던 c++ 문법 정리
#include <chrono>
#include <iostream>

using namespace std;
int main(int argc, char const* argv[]) {
    int arr[] = {10, 20, 30, 40};
    /* 범위 기반 for-loop */
    for (int item : arr) {
        cout << item << endl;
    }

    /* 람다식 */
    auto sum = [](int a, int b) { return a + b; };
    cout << sum(10, 20) << endl;

    /*  chrono 라이브러리
    알고리즘 시간 측정 라이브러리로, 나노초 까지 셀수 있음*/
    auto start = chrono::system_clock::now();
    for (int i = 0; i < 100; i++) {
    };
    auto end = chrono::system_clock::now();
    cout << "경과시간: " << (chrono::duration<double>(end - start).count()) * 1000 << "ms" << endl;

    /* C++17이상 if 초기화 기능
    이렇게 초기화와 동시에 조건 파악 가능 */
    if (int* ptr = new int; ptr != nullptr) {
        *ptr = 5;
        delete ptr;
    } else {
        delete ptr;
    };
    // delete ptr; (ptr은 위 if 블록에 지역변수)

    /* C++17이상 switch-case 초기화 기능 */
    switch (int caseValue = 10; caseValue) {
        case 10:
            cout << "10임" << endl;
            break;
        default:
            break;
    }

    return 0;
}
