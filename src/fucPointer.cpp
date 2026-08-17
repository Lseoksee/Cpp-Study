#include <iostream>

using namespace std;

// int (*funPointer)(int, int)
typedef int (*TypeFunPointer)(int,  int); 

int ref_fun(int a, int b) {
    return a+b;
}

int main(int argc, char const* argv[]) {
    // 함수 포인터 설정 (반환값=int 인자=int, int)
    int (*funPointer)(int, int) = nullptr;
    funPointer = ref_fun;
    // 함수는 그 자체로 주소를 가르킴 즉 ref_fun 으로 호출하면 사실상 &ref_fun로 호출된것
    std::printf("%p\n", funPointer);
    cout << funPointer(10, 20) << endl;
    // typedef 호출
    TypeFunPointer tfp = ref_fun;
    cout << tfp(20, 30) << endl;
    
    // 오른쪽 대입값을보고 유추 가능하면 auto를 도입하는 것도 좋다
    auto afp = ref_fun;
    cout << afp(20, 40) << endl;

    return 0;
}
