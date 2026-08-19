// 다중상속
#include <iostream>

using namespace std;

/*
웬만해서는 다중상속은 안하는게 맞음

다중 상속 문제점

1. 상속받은 여러 기초 클래스에 같은 이름의 멤버 존재 가능
2. 하나의 클래스를 간접적으로 두 번 이상 상속받을 가능성 존재
3. 가상 클래스가 아닌 부모를 다중 상속하면, 부모타입에 포인터로 자식클래스를 가르킬 수 없음
*/

class Person {
   private:
    int private_val = 0;
    void printPrivateVal();

   public:
    string name;
    int age;
    void printPerson();
};

void Person::printPerson() { cout << "이름: " << name << ", 나이: " << age << endl; }
void Person::printPrivateVal() { cout << "private_val: " << private_val << endl; }

class Object {
   private:
    int private_val = 0;

   public:
    string name = "그냥";
    string obj_name;
    int size;
    void printObject();
};

void Object::printObject() { cout << "객체이름: " << obj_name << ", 크기: " << size << endl; }

// 다중상속
class Sub : public Person, public Object {
   private:
   public:
    void printSub();
};

void Sub::printSub() {
    printObject();
    printPerson();
    // cout << name << endl; (이렇게 되면 Person, Object 둘중 누구 `name`을 가르키는 건질 모름)
    cout << Person::name << Object::name << obj_name << endl;
}

int main(int argc, char const *argv[]) {
    Sub sb;
    sb.age = 20;
    // sb.name = "하이"; (이것도 위와 같음)
    sb.Object::name = "오브젝트";
    sb.Person::name = "사람";
    sb.size = 20;
    sb.printSub();
    return 0;
}
