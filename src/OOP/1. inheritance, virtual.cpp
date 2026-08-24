// 상속 (구조는 java와 비슷함)
#include <iostream>

/*
부모 클래스(parent class) = 기초 클래스(base class) = 상위 클래스(super class)
자식 클래스(child class)  = 파생 클래스(derived class) = 하위 클래스(sub class)
*/

/*
상속 규칙
1. 자식 클래스는 반드시 자신만의 생성자를 작성해야함.
2. 자식 클래스에는 부모 클래스의 접근할 수 있는 모든 멤버 변수, 함수들이 저장.
*/

/*
가상 함수란 파생클래스에서 재정의할 것으로 기대되는 맴버함수 (가상클래스라 함은 가상 함수가 포함된 클래스를 뜻함)
자신을 호출하는 객체의 동적 타입에따라 실제 함수가 결정
가상함수에 구현은 컴파일러마다 다른데 대게 가상함수 테이블을 통해 관리된다.
INFO: 이것때문에 오버해드가 존재하여 동적바인딩이 필요한 경우에만 virtual을 사용하도록 하자
*/

using namespace std;

class Person {
   private:
    int private_val = 0;
    void printPrivateVal();

   public:
    string name;
    int age;
    Person(string name, int age);
    void printPerson();
    // 포인터 문제로 인한 가상 함수 오버라이딩
    virtual void printPerson_virtual();
    // Student에서 소멸자를 바인딩 해서 쓰므로
    virtual ~Person() {};
};

Person::Person(string name, int age) {
    this->private_val++;
    this->name = name;
    this->age = age;
}

void Person::printPerson() { cout << "이름: " << name << ", 나이: " << age << endl; }
void Person::printPrivateVal() { cout << "private_val: " << private_val << endl; }
void Person::printPerson_virtual() {
    cout << "virtual" << endl;
    cout << "이름: " << name << ", 나이: " << age << endl;
}

// Person객체 상속
// 접근제어 지시자 기본은 private이고 public으로 설정하면, public 인스턴스만
// private로 선언하면, private 인스턴스만 접근가능
class Student : public Person {
   private:
   public:
    int std_id;
    void printStudnet();
    Student(string name, int age, int std_id, char* heap_char);
    // 오버라이딩을 위한 재정의
    void printPerson();
    // 포인터 문제로 인한 가상 함수 오버라이딩
    virtual void printPerson_virtual();
    // 힙 영역 동적 바인딩 해제 문제
    char* heap_char = nullptr;
    // heap_char는 힙메모리로 선언되므로 해제 하는코드가 필요
    ~Student() {
        if (heap_char != nullptr) {
            delete heap_char;
        }
    }
};

//  class final키워드= 상속 불가하게 만들기
class FinTest final {
   public:
    // 함수 final 키워드 = 오버라이딩 안되게 막기
    virtual void func() final {}
};

/* super 클래스에 생성자를 작성한 경우 자식은 무조건 부모 생성자 호출 해야함 */
Student::Student(string name, int age, int std_id, char* heap_char)
    : Person(name, age) /* 이렇게 부ㄹ모 생성자 호출 */ {
    this->std_id = std_id;
    this->heap_char = heap_char;
}

void Student::printStudnet() { cout << "학생코드: " << std_id << endl; }

/* 오버 라이딩 */
void Student::printPerson() {
    /* 부모의 printPerson도 출력  */
    Person::printPerson();
    cout << "학생이름: " << name << ", 학생나이: " << age << endl;
}

void Student::printPerson_virtual() {
    cout << "virtual" << endl;
    cout << "학생이름: " << name << ", 학생나이: " << age << endl;
}

int main(int argc, char const* argv[]) {
    /* 부모 */
    Person ps("아무개", 20);
    ps.age = 20;
    ps.name = "아무개";
    ps.printPerson();

    cout << "---자식부분---" << endl;

    /* 상속된 자식 */
    Student st("학생", 18, 1, nullptr);
    // st.std_id = 10; private 로 상속 선언한경우 사용가능
    st.age = 18;
    st.name = "학생";
    st.std_id = 1;
    st.printPerson();
    st.printStudnet();

    cout << "---포인터 문제---" << endl;

    Person* Person_p;
    Person_p = &ps;
    Person_p->printPerson();
    Person_p->printPerson_virtual();
    Person_p = &st;

    // 위에 Student객체에 printPerson가 오버라이딩 되어 `학생이름...` 이렇게 되어 출력되어야 하지만
    // Person에 printPerson()이 호출되고 있음
    // 포인터를 보면 `Person*` 로 초기화를 함 컴파일러가 해당 포인터에 타입을 기준으로 함
    // 형변환을 하면 해결 되지만 동적바인딩이 불가능함
    // (에초에 오버라이딩을 하는 이유가, 부모와 같은 타입을 공유하는 동일한 메소드를 부모에 관점에서 호출하기 위함이라)
    Person_p->printPerson();
    // Person_p->std_id (Person*이므로 당연히 호출 불가함)

    // 하지만 virtual키워드를 통해 가상함수로 만들어 오버라이딩 된경우 정상적으로 Student에 printPerson_virtual()이
    // 호출됨
    Person_p->printPerson_virtual();

    cout << "---힙 문제---" << endl;

    // 가장 문제가 이렇게 힙으로 초기화 한 경우가 문제임
    // delete를 통해 소멸자를 호출할때  `Person*` 초기화를 했기 때문에 Student에 소멸자가 아닌, Person 으로 소멸자가
    // 호출됨 Student에서 char_ptr을 힙으로 초기화 하므로 반드시 헤제가 필요 따라서 소멸자에 명시를 해두었으나,
    // Person소멸자가 호출되어 메모리 누수가 나버림 그럼 이때 Person에 소멸자를 virtual로 선언하여 문제를 해결하는 것
    char* char_ptr = new char[20]{"안녕하세요"};
    Person* PointerPerson = new Student("나는 포인터", 10, 1, char_ptr);
    delete PointerPerson;
    // Person에 생성자를 virtual로 안하면 정상적으로 출력이 됨
    cout << char_ptr << endl;

    return 0;
}
