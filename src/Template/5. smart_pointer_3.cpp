/*
weak_ptr의 순환 참조 해결 방법

순환 참조란 두 스마트 포인터 객체가 서로를 참조하여 참조 카운터가
감소 하지 못하여 영원히 소멸되지 못하는 현상
*/

#include <iostream>
#include <memory>

using namespace std;

class ClassA;
class ClassB;
class ClassA_weak;
class ClassB_weak;

class ClassA {
   private:
    shared_ptr<ClassB> ptr;

   public:
    string name;
    void setClassB(shared_ptr<ClassB> ptr) { this->ptr = ptr; };
    ClassA(string name) { this->name = name; }
};

class ClassB {
   private:
    shared_ptr<ClassA> ptr;

   public:
    void setClassA(shared_ptr<ClassA> ptr) { this->ptr = ptr; };
};

class ClassA_weak {
   private:
    shared_ptr<ClassB_weak> ptr;

   public:
    string name;
    void setClassB(shared_ptr<ClassB_weak> ptr) { this->ptr = ptr; };
    ClassA_weak(string name) { this->name = name; }
};

class ClassB_weak {
   private:
    // 클래스 A 순환 참조를 weak_ptr바꿈
    weak_ptr<ClassA_weak> ptr;

   public:
    void setClassA(weak_ptr<ClassA_weak> ptr) { this->ptr = ptr; };
};

// 순환 참조 문제 함수
string* loopRefreceIessue() {
    shared_ptr<ClassA> ptr_a = make_shared<ClassA>("해제 안되잖아");
    shared_ptr<ClassB> ptr_b = make_shared<ClassB>();
    // 이렇게 내부적으로 서로 참조 되는경우 ptr_a, b 둘다 카운터가 1씩 상승해버림
    ptr_a->setClassB(ptr_b);
    ptr_b->setClassA(ptr_a);

    // 두 카운트 모두 2가 나옴
    cout << "ptr_a Count: " << ptr_a.use_count() << endl;
    cout << "ptr_b Count: " << ptr_b.use_count() << endl;

    // 함수가 반환 될때 ptr_a, ptr_b의 스코프가 끝나므로 카운트가 1 감소할 것이다.
    // 그러나 문제는 클래스 내부적으로 서로 참조하는 부분이 남아 있어서
    // 함수 반환 이후 ptr_a, ptr_b변수에 접근이 불가 하면 영원이 해제 되지 못하는 상황이 발생한다.
    return &ptr_a->name;
}

// 순환참조 문제 해결 함수
string* loopRefreceSolve() {
    // ClassA를 weak로 만듬
    // ClassB는 그대로 shared로
    shared_ptr<ClassA_weak> ptr_a_sha = make_shared<ClassA_weak>("해제 안되잖아");
    weak_ptr<ClassA_weak> ptr_a = ptr_a_sha;
    shared_ptr<ClassB_weak> ptr_b = make_shared<ClassB_weak>();

    // 마찬가지로 서로를 참조하게 만들어 봄
    ptr_a_sha->setClassB(ptr_b);
    ptr_b->setClassA(ptr_a);

    // a에 경우 강한 참조1번 약한 참조 1번임
    cout << "ptr_a Count: " << ptr_a_sha.use_count() << endl;

    // b에 경우 ptr_a 에서 강한 참조가 일어나서 총 2번임
    cout << "ptr_b Count: " << ptr_b.use_count() << endl;

    // 함수가 반환이 되면 ptr_a_sha, ptr_b가 정리되어 각각 강한카운트 1이 감소 할꺼임
    // 이때 a가 카운트가 0이 되어 헤제 되고 weak_ptr상태는 expired일꺼임
    // 그러면 a가 참조하고 있던 b도 소멸되어 참조가 없어지고 b에 카운트가 1감소할꺼임
    // 그럼 모두가 정상적으로 메모리 헤제가 되는것
    return &ptr_a_sha->name;

    // 만약 두 클래스 모두 weak_ptr이 되버리면 클래스 내부 지역변수 참조와 관계없이
    // 함수 반환이 되버리면 expired 되어 참조가 불가능 해버릴꺼임 (그저 지역 변수에 좌지우지 됨)
    // 즉 약한 참조와 강한 참조가 별게인 부분이라 순환 참조가 필요한데, 메모리 해제가 문제라면
    // 둘중 하나만 weak_ptr로 만드는게 정배라는 것
}

int main(int argc, char const* argv[]) {
    string* name_iessue = loopRefreceIessue();
    // 순환 참조문제로 해제가 되지 못하여 값이 출력됨
    cout << *name_iessue << endl;

    cout << "---loopRefreceSolve---" << endl;

    string* name_solve = loopRefreceSolve();
    // 순환 참조가 해결되어 정상적 해제가 되어서 해결이 됨
    cout << *name_solve << endl;

    return 0;
}
