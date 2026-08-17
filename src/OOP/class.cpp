#include <iostream>

using namespace std;

class Person {
   private:
    /* private 수준에 인스턴스 선언 */
    int a, b;

    int culr(int a, int b) {
        // this는 Person* (자기 자신을 호출한 인스턴스)
        cout << this->a + this->b << endl;
        return a + b;
    };

    // 단순 구조만 선언
    void test(string name);

   public:
    /* public 수준에 인스턴스 선언  */
    int plus(int a, int b) { return culr(a, b); };  // 당연하지만 class 내부에서는 private으로 선언된 매소드 사용가능

    // static 메소드
    static void name(string sc) { cout << sc << endl; }

    // 상수 맴버 함수, 함수 내부에서 객체내 변수는 수정 불가하고 오로지 읽기만 가능하게
    void constName(string sc) const { cout << sc << endl; }

    // 생성자
    Person(int a, int b);

    // 생성자를 추가하면 원래있던 기본 생성자 Person()은 사라짐
    Person();

    // 소멸자 (인자, 반환형 static 선언 안됨)
    // 객체 수명이 끝날때 호출
    ~Person() { cout << "소멸됨" << endl; };

    // private 모든 권환과 파생클래스(상속)인 경우 접근 가능
   protected:
    int c;
};

// 보통 실무에서는 해더파일에 class선언, 맴버변수와 함수원형만 두고
// 구현은 따로 cpp에 해두고 해더파일을 통해 클래스에 접근하도록 분리함
void Person::test(string name) {
    // 클래스 내부 취급으로 맴버변수 접근이 가능하다
    int range = a;
    cout << name << endl;
}

Person::Person() {
    this->a = 10;
    this->b = 20;
}

Person::Person(int a, int b = 20) {
    this->a = a;
    this->b = b;
}

int main(int argc, char const* argv[]) {
    // 객채 생성 (기본생성자)
    Person pd;
    // 객채 생성
    Person ps = {40, 50};
    // Person ps(40, 50) 이렇게도 가능
    int a = ps.plus(10, 20);
    cout << a << endl;
    // static 메소드 사용
    Person::name("하이");

    // 힙영역으로
    Person* heapPerson = new Person(10, 20);
    heapPerson->plus(50, 50);
    delete heapPerson;

    /* 객체 복사 */

    // 복사 대입 연산자 Person& operator= 사용
    // 대입 연산자를 통한 복사는 얕은 복사로 수행
    // 값을 복사하는것이 아닌 값을 가르키는 포인터를 복사함
    // 이 경우 객체 내부에 힙으로 초기화한 인스턴스가 있다면 이중해제 문제가 발생할 수 있음 (컴파일러가 operator= 함수를
    // 정의할때 힙을 해제 하기 떄문)
    pd = ps;

    // 복사 생성자 Person(const Person &) 사용
    // 기본적으로 컴파일러가 자동으로 생성
    // 다른 객체를 인자로 받아 그 정보를 바탕으로 자기 자신을 초기화 하여 새롭게 만듬
    // 이 경우 delete 된 힙 영역은 그냥 없는 변수로 치게되어 조금더 안전한 복사가 가능
    Person cpyObj(ps);
    // Person cpyObj = ps 이렇게도 가능 (위 대입 연산 복사랑 구분 잘해야함)
    cpyObj.plus(0, 0);

    return 0;
}
