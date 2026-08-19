#include <iostream>

using namespace std;
/*
virtual이 오버라이딩 가능한 함수선언 이라면 `순수 가상 함수`는 추상클래스
즉 반드시 오버라이딩 해야하는 함수를 선언

java에서는 abstract class ~name 형태로 선언했지만, c++은 그냥 추상메소드가 있으면 추상 클래스로 취급

--추상클래스 제한 사항--
1. 변수 또는 멤버 변수에 타입으로써 초기화
2. 함수의 전달되는 인수 타입
3. 함수의 반환 타입
4. 명시적 타입 변환의 타입
즉 타입으로써 활용이 불가능
*/

class Animal {
   public:
    int i = 10;
    virtual ~Animal() {}
    virtual void Cry() = 0;  // 순수 가상함수 (추상클래스) 선언
};

class Cat : public Animal {
   private:
   public:
    void State() { cout << "고먐미" << endl; }
    /* 오버라이딩 안하면 오류 */
    virtual void Cry() { cout << "야옹" << endl; }
};

int main(int argc, char const *argv[]) {
    // Animal al; (추상클래스 이므로 초기화 불가)
    Cat cat;
    cat.State();
    cat.Cry();
    cout << cat.i << endl;
    return 0;
}
