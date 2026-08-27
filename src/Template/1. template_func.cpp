#include <iostream>
/*
템플릿이란 자바에 제네릭 하고 비슷한 개념
일반화 프로그래밍에 기반이 됨
*/

using namespace std;

/* 템플릿 메소드를 사용하면 타입에 구해받지 않고 서로다른 타입에서 동작하는 알고리즘을 만들 수있음  */
// <typename T>도 가능
template <typename T>  // 한줄에 쓰면 template <typename T> void swap(T* a, T* b)
void MySwap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

/* 명시적 특수화  (일종의 템플릿 오버로딩)
특정 타입에 대해서는 다른 동작을 하게 만들 수있음
*/
template <>
void MySwap<double>(double* a, double* b) {
    cout << "double은 안바꿀꺼임 ㅅㄱ" << endl;
}

int main(int argc, char const* argv[]) {
    int a = 30;
    int b = 20;

    MySwap(&a, &b);
    cout << "a: " << a << ", b: " << b << endl;
    string c = "야";
    string d = "안녕";
    MySwap(&c, &d);
    cout << "c: " << c << ", d: " << d << endl;
    /* int e = 10;
    string f = "야";
    MySwap(&e, &f);
    다른 타입끼리는 안됨
    */

    double a_db = 1.1;
    double b_db = 2.3;
    // 명시적 특수화 되어있으므로 다른동작이 될꺼임
    MySwap(&a_db, &b_db);

    return 0;
}
