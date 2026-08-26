/* 각 스마트 포인터에 해제 시기
RAII 원칙에 따라 해제가 결정 됨
*/
#include <iostream>
#include <memory>

using namespace std;
string* SharedTest();

class Foo {
   private:
   public:
    int a;
    int b;
};

class HeapTest {
   private:
   public:
    string* str;
    int a;
    HeapTest(string* str, int a) {
        this->str = str;
        this->a = a;
    }
    ~HeapTest() { cout << "HeapTest: 소멸자 호출" << endl; }
};

class SmartString {
   public:
    string str;
    SmartString(string str) { this->str = str; }
    ~SmartString() { cout << "SmartString: 소멸자 호출" << endl; }
};

class SmartHeapTest {
   private:
   public:
    unique_ptr<SmartString> str = nullptr;
    int a;
    SmartHeapTest(unique_ptr<SmartString> str, int a) {
        this->str = move(str);
        this->a = a;
    }
    ~SmartHeapTest() { cout << "SmartHeapTest: 소멸자 호출" << endl; }
};

void UniqueFunc() {
    unique_ptr<Foo> ptr = make_unique<Foo>();
    ptr->a = 10;
    ptr->b = 20;
    /* 사실상 안쓰이므로 이 시점에 해제 */
}

int main(int argc, char const* argv[]) {
    UniqueFunc();
    unique_ptr<Foo> ptr = make_unique<Foo>();
    ptr->a = 10;
    ptr->b = 20;
    Foo* fooPtr = ptr.get();
    ptr = nullptr;  // 자동 해제

    // 해제 되어서 이상한 값 나옴
    cout << fooPtr->a << endl;

    // 클래스 내부에 힙 영역으로 선언한 변수가(원시 포인터) 있는경우
    // 이 경우엔 여전히 스마트 포인터를 쓰더라도 해제 되지 못함
    string* str = new string("그러나");
    unique_ptr<HeapTest> htu = make_unique<HeapTest>(str, 10);
    htu.reset();
    cout << *str << endl;

    cout << "---부모 삭제 테스트(원시)---" << endl;

    // 이 경우에도 함수 인자로 전달할 변수를 unique_ptr로 선언하였지만
    // HeapTest에 전달된 변수는 unique_ptr이 가르키는 원시 포인터가 전달 되었다.
    // 이렇게 되면 부모에 소멸과 별개로 unique_ptr가진 스코프 규칙에 따라 소멸 된다.
    // unString에 해제 시점은 main 함수 return 이후다
    unique_ptr<string> unString = make_unique<string>("그러나");
    HeapTest* hts = new HeapTest(unString.get(), 10);
    delete hts;

    cout << *unString << endl;

    cout << "---부모 삭제 테스트(스마트)---" << endl;

    // 이렇게 내부 인자를 스마트 포인터로 해야 부모 해제시 연쇠적인 해제가 가능하다
    unique_ptr<SmartString> Shstr = make_unique<SmartString>("안녕 디지몬");
    unique_ptr<SmartHeapTest> smHeap = make_unique<SmartHeapTest>(move(Shstr), 10);
    smHeap.reset();
    // 부모는 원시 포인터여도 가능 하다
    // SmartHeapTest* smHeap = new SmartHeapTest(move(Shstr), 10);
    // delete smHeap;

    // cout << move(Shstr)->str << endl; (해제 되었으므로 애러 발생)
    cout << "---shared_ptr---" << endl;

    string* shStr = SharedTest();
    // 소멸 이후에 참조 되므로 이상한 값이 나옴
    cout << *shStr << endl;

    return 0;
}

string* SharedTest() {
    // shared_ptr에 경우에도 카운터 증,감 원칙은 unique_ptr과 동일하지만
    // 실제 원시포인터를 참조하는 객체가 소멸되어도, shared_ptr에 카운터가 감소하지 못함

    // 이러한 관계 때문에 예를들어 같은 원시 포인터로 shared_ptr를 2개 이상 만든 경우
    // 두 shared_ptr모두 카운트가 0이 되면 이중 해제 될 가능성이 존재함
    // 그걸 방지 하기위해 make_shared() 함수가 있는거임, 이건 무조건 복사로만 이루어짐으로 서로 별도에 카운터가 아니게
    // 되므로
    shared_ptr<SmartString> shaString = make_shared<SmartString>("시간이 지나도");
    cout << "원시 객체 참조전 count: " << shaString.use_count() << endl;
    // 원시 객체 참조랑 상관없이 최초 생성시 카운터는 무조건 1임
    HeapTest* shTs = new HeapTest(&shaString->str, 20);
    cout << "원시 객체 참조 후 count: " << shaString.use_count() << endl;

    // 부모 객체가 소멸 되더라도 카운트가 0이 되지 못함
    // shaString 변수를 기준으로 해당 변수가 nullptr 이거나, 블록에서 빠져 나오면 해제가 됨
    // 즉 shaString이 해제되는 시점은 해당 함수가 반환되는 시점임
    delete shTs;

    cout << shaString->str << endl;

    return &shaString->str;
}