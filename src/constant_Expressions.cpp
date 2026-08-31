/**
@see https://modoocode.com/293,
https://namu.wiki/w/C%2B%2B/%EB%AC%B8%EB%B2%95/%EC%83%81%EC%88%98%20%ED%91%9C%ED%98%84%EC%8B%9D
*/

#include <chrono>
#include <iostream>

using namespace std;

// 컴파일 시 해당 함수가 미리 계산이 됨
constexpr int Factorial(int n) {
    int total = 1;
    for (int i = 1; i <= n; i++) {
        total *= i;
    }
    /* constexpr 함수 안에서는 같은 constexpr 함수만 호출가능 */
    return total;
}

template <int N>
struct A {
    int operator()() { return N; }
};

template <typename T>
void show_value(T t) {
    /* if (is_pointer<T>::value) { */
        // 만일 T에 포인터가 아닌 타입이 전달되면
        // 컴파일 될때 템플릿이 인스턴스화 되면서 자연스럽게 해당 타입으로 변환됨
        // 이때 타입이 포인터가 아니므로 *t가 오류가 나게됨
    if constexpr (is_pointer<T>::value) {
        // 이렇게 if 앞게 constexpr를 붙이면 컴파일 타임에 평가가 들어가게되어
        // 템플릿이 인스턴스화 되기 이전에 평가가 가능함
        // if-constexpr에 경우 조건에 참,거짓 에 따라 특정 부분만 컴파일 됨
        // 즉 if 부분이 참이면 else 부분은 아예 컴파일 되지 못함

        cout << "포인터 이다 : " << *t << endl;
    } else {
        cout << "포인터가 아니다 : " << t << endl;
    }
}

int main(int argc, char const *argv[]) {
    // 정수 상수 식 (컴파일 타임에 정해지므로 진짜 불변 상수라 할수 있음)
    constexpr int a = 10;
    cout << a << endl;

    // const에 경우 특정 변수를 통한 상수 선언이 가능하다.
    // 하지만 constexpr에 경우에는 컴파일 타임 이므로 해당 문법 선언이 안된다.
    int b = 10;
    const int b_c = a;

    // Factorial 함수가 constexpr로 선언이 안되있으면 오류가 날꺼임(명확한 상수가 아니므로)
    // 런타임에서는 선언이 A<3628800>랑 같은거임
    // Factorial() 함수인자에 상수가 아닌 변수가 들어가면 오류가 남 constexpr 어디 까지나, 컴파일 타임에 추론으로
    // 흘러가니 사실 Factorial(10)을 미리 계산해서 A<3628800>로 표현 해도 되는데 당연히 가독성 떨어지니 이런거는
    // constexpr로 선언하여 런타임 시간 복잡도 문제도 해결하고, 코드 가독성 문제도 해결하는 그런 효과
    auto start = chrono::system_clock::now();
    A<Factorial(10)> t;
    // A<Factorial(b)> t; (안됨)
    // t() 에 마우스를 갔다 대면 A<3628800> 이렇게 나올꺼임, ide가 컴파일 추론을 해서 나온 결과인거
    cout << t() << endl;
    auto end = chrono::system_clock::now();

    cout << "경과시간: " << (chrono::duration<double>(end - start).count()) * 1000 << "ms" << endl;
    end = chrono::system_clock::now();

    // 변수사용 가능하다
    // 물론 이때는 그냥 일반 함수로 작동한다
    cout << Factorial(b) << endl;

    int x = 3;
    show_value<int>(x);
    show_value<int*>(&x);
    return 0;
}

// 0.007185ms
