#include <iostream>

using namespace std;

// 참조자 `&` 롤 통한 인자 전달 (call by reference)
// c 에서는 함수 인자를 int* 로 두고 호출할때 &val로 주소를 참조하도록 하였지만
// c++ 에서는 함수 인자를 int& 로 선언하여 호출할떄는 값으로 전달하고, 함수 인자가 주소를 참조하도록 할 수 있다

// 다만 int&는 주소를 참고 하고 있는게 아님, 참조 하고 있는변수(주소)에 값을 참조하고 있는것
// 즉 변수에 상태는 *value 인 상황인 것이다. 따라서 value에 ++ 을 하면 주소를 건드는게 아닌 해당 주소에 값을 건드는것

// INFO: 솔직히 그냥 코드 작성할떄는 직관성을 위해 안쓰는게 좋을듯

/* 유의사항
1. 참조자의 타입은 대상이 되는 변수의 타입과 일치해야 합니다.
2. 참조자는 선언과 동시에 초기화되어야 합니다.
3. 참조자는 한 번 초기화되면, 참조하는 대상을 변경할 수 없습니다.
 */
void refFunc(int& value) {
    value++;

    cout << "BeforRefFunc: " << value << endl;
    // 인자가 참조하고 있는 주소를 얻으려면
    int* p = &value;
    (*p)++;
    cout << "AfterRefFunc: " << value << endl;
}

// 상단에 원형을 선언 해야 되는경우 int cul(int a = 10); 이렇게 하고
// 실제 구현에는 int cul(int a); 이렇게 해야함

/*
1. 디폴트 인수는 함수의 원형에만 지정할 수 있습니다.
2. 디폴트 인수는 가장 오른쪽부터 시작하여 순서대로만 지정할 수 있습니다.
3. 가운데 인수들만 별도로 디폴트 인수를 지정할 수는 없습니다.
*/
int cul(/* int a = 10 오류남*/ int a, int b, int c = 20, int d = 10) { return a + b + c + d; }

// 함수 오버로딩
int cul(int a) { return a*2; }


// 인라인 함수
// 컴파일러가 해당 함수를 해체 시켜 main에다 선언시켜 함수 스택 호출 오버해드를 줄일 수 있음
// 예를들어 호출 빈도가 많은경우 최적화를 위해 사용하기도 함 
// 매크로 함수와 다른게 있다면 매크로는 치환에 가깝다면 인라인은 호출된 자리에 코드를 삽입해준다는것에 가까움 
inline void in_func() {
    cout << "인라인 ㅎㅇ" << endl;
}

// 다른 소스에서 참고하지 못하게 하기 위함
static int add_one() {
    return 0;
}

// int main(void) == main() 다만 완전히 인자가 없다는 의미에서 main(void)로 쓰기도함
int main() {
    int a = 10;

    // 당연하지만 참조자를 그냥 변수로 선언해도 됨
    int& ref_a = a;
    ref_a++;

    cout << a << endl;

    // 값=11
    refFunc(a);
    cout << a << endl;
    
    cout << "---기본인자---" << endl;
    cout << cul(10, 30) << endl;
    cout << "---오버로딩---" << endl;
    cout << cul(10) << endl;
    return 0;
}