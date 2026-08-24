#include <iostream>

using namespace std;

/* 연산자 오버로딩 */
class Person {
   private:
    int c = 12;
    int a, b;

   public:
    // 연산자 오버로딩 함수 operator `+, -, ==, [], ()` 등 정의 가능
    // 객체끼리 연산 시 동작하는거 정의
    Person& operator+(Person& target) {
        this->a += target.a;
        this->b += target.b;
        return *this;
    };

    /* friend 사용법 */

    // 전역 함수에서 객체 클래스에 선언하여 접근 가능 하도록 함
    // 객체를 인자로 받는경우 해당 객체에 private 인스턴스에 접근하기위해
    // 해당 함수를 friend로 클래스에 등록 해서 쓰는 방식
    // 다만 접근 권한만 가지는거지 해당 함수가 클래스 맴버에 등록되는게 아님
    friend void friedTest(Person& target);

    // friend가 가장 필요할때가 operator 때문인데 operator 오버로딩은 그 특성상 매개변수를 자기 멋대로 바꾸지 못함
    // 하지만 예를들어 target * 3 이렇게 된다면 정상적으로 `operator*(double mul)` 함수가 수행 할꺼임
    // 연산자 자체가 왼쪽 피연산자인 target 이 객체를 호출해서 인자를 `double mul`로 사용하게됨
    Person& operator*(double mul);
    // Person operator*(double mul, const Person& origin); //이렇게 선언 하면 안됨

    // 그런데 3 * target 이러면 어떻게 되는가 3이 `operator*` 을 호출하게 되는데 이때 인자는 `target`이 된다
    // 그럼 `operator*(double mul)`이거로는 호출 오류가 난다,
    // 아까 말했다시피 operator오버로딩은 인자를 수정하기 어렵다.
    // 그러면 이걸 그냥 전역 변수로 빼가지고 이렇게 선언하면 되는데, 문제는 `target`에 내부 private인스턴스 접근이
    // 안된다. 이떄 쓰는게  friend 인것이다 (만약 public인스턴스만 접근할꺼라면 해당 선언 자체가 필요없음)
    friend Person& operator*(double mul, Person& target);

    // 만약 두 클래스가 밀접한 관계, Car객체 메소드 측에 Person을 인자로 받는경우 Person에 private에 접근할때
    // 아예 클래스 자체를 friend로 선언 가능
    friend class Car;

    Person(int a, int b) {
        this->a = a;
        this->b = b;
    }

    void Print() { cout << "a: " << this->a << " b: " << this->b << endl; };
};

class Car {
   private:
        void printCar(Person& target) {
            // friend로 클래스가 선언되어 private 인스턴스에 접근가능
            cout << target.c << endl;
        }
   public:
};

void friedTest(Person& target) {
    // friend 선언 안하면 target.c에 접근 불가
    cout << target.c << endl;
}

Person& Person::operator*(double mul) {
    this->a *= mul;
    this->b *= mul;
    return *this;
}
Person& operator*(double mul, Person& target) {
    target.a *= mul;
    target.b *= mul;
    return target;
}

int main(int argc, char const* argv[]) {
    // operator함수 호출
    Person p1(10, 20);
    Person p2(20, 30);
    p1 + p2;

    friedTest(p1);

    p1 * 3;
    // friend Person& operator*(double mul, Person& target)가 없으면 안되있으면 사용 안됨
    3 * p1;

    p1.Print();
    return 0;
}
