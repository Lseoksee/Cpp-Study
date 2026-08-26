#include <iostream>
#include <memory>

// 스마트 포인터는 포인터 처럼 동작하는 클래스 템플릿, 사용이 끝난 메모리 자동 해제
// new 로 생성하여 힙에 할당한 영역을 스마트 포인터가 자동으로 해제

/*
c++11 이전 = auto_ptr
c++11 이후 = unique_ptr, shared_ptr, weak_ptr
*/

using namespace std;

class Person {
   private:
    int private_val = 0;
    string name;
    int age;

   public:
    Person(int private_val, string name, int age) {
        this->private_val = private_val;
        this->name = name;
        this->age = age;
    };
    string getName() { return name; };
};

using namespace std;

int main(int argc, char const *argv[]) {
    /*
    unique_ptr: 하나의 스마트 포인터만이 특정 객체를 소유할 수 있도록
    객체에 소유권을 도입, 즉 여러 포인터가 중복 접근하는 것을 막음
    */

    /* new int(5) 는 5를 초기값으로 하는 변수를 힙 영역으로 초기화 */
    unique_ptr<int> uPtr(new int(5));
    cout << *uPtr << endl;
    // 소유권 이전된 unique_ptr를 `dangling pointer`라 함

    // nPtr에 소유권 이전 (복사는 불가함)
    unique_ptr<int> nPtr = move(uPtr);

    // uPtr.get() (소유권을 이전했으므로 작동안됨)

    // 메모리 영역삭제 (사실 자동으로 해제 하므로 필요 없음)
    uPtr.reset();
    nPtr.reset();

    // make_unique를 사용하여 객체 타입만큼 안전하게 힙에 할당하고, 초기화 가능
    // 영역 만큼 할당이 아니라 객체 할당이면 나름 쓸만할듯
    unique_ptr<Person> safePtr = make_unique<Person>(10, "아사람", 50);
    cout << safePtr->getName() << endl;

    cout << "---shared_ptr---" << endl;

    /*
    shared_ptr: 레퍼런스 카운트를 이용하는 방법 특정 객체를 참조하고 있는 스마트 카운터가
    총 몇개인지 파악하고 0이 되면 해제 하는 방식
    */

    // make_shared를 안쓰면 객체 복사생성자 사용 시 얕은 복사만 사용되므로 오류 발생 가능성 있음
    // 참조 포인터를 관리하는 추가적인 값을 힙에 선언됨
    shared_ptr<Person> shPtr = make_shared<Person>(10, "언젱가", 50);
    cout << "count: " << shPtr.use_count() << endl;
    auto shPtr_2 = shPtr;
    cout << "count: " << shPtr.use_count() << endl;
    shPtr_2.reset();
    cout << "count: " << shPtr.use_count() << endl;
    shPtr.reset();
    // cout << shPtr->getName() << endl; (헤제 되었으므로 불가능)

    cout << "---weak_ptr---" << endl;

    /*
    weak_ptr: 다른 스마트 포인터와 달리 단독 사용 불가하고, shared_ptr를
    먼저 초기화 한 뒤 사용 가능 하고 ->, * 처럼 원시포인터 같이 사용도 불가능
    shared_ptr는 강한 참조에 카운터를 올리지만, weak_ptr는 약한 참조에 카운터를 올림

    즉 weak_ptr은 약한 참조를 하는 포인터다 라고 말할 수 있다.
    약한 참조는 메모리 헤제 하고는 관련이 없다. 횟수가 100이든 0이든 상관없고
    만일 강한 참조가 0이되면 메모리 해제가 되면서 weak_ptr에 상태는 `expired` 가 되는데.
    이 의미는 더이상 유요하지 않다 라는 뜻이다.

    약한포인터에 용도는 힙 메모리상에 두 개체가 서로 강한 참조를 하여 자동으로 해제 되지 못하는
    순환 참조를 해결하기 위한 방법이다.

    */
    shared_ptr<Person> shPtr_weak = make_shared<Person>(10, "언젱가", 50);
    cout << "count: " << shPtr_weak.use_count() << endl;
    weak_ptr<Person> weakPtr = shPtr_weak;  // 내부적으로 shared_ptr에 원시 포인터를 참조

    // weak_ptr이 참조를 하면 약한 참조에 카운터가 올라감, 즉 shPtr_weak.use_count()는 강한 참조에 카운터를 보여주는 것
    cout << "count: " << shPtr_weak.use_count() << endl;

    // weak_ptr.use_count()는 약한 참조에 카운터를 보여줌
    cout << "count: " << weakPtr.use_count() << endl;
    // cout << weakPtr->getName() << endl; (불가능)

    // shared_ptr로 형변환 하고, 원시 포인터를 가르킴 즉 강한 참조 카운팅이 1 상승
    // 작업중에 다른 공유포인터가 소멸되더라도 강한참조 카운팅 1은 최소 확보 하므로 안전하게 사용가능
    auto lockWeak = weakPtr.lock();
    cout << lockWeak->getName() << endl;
    cout << "count: " << weakPtr.use_count() << endl;

    weakPtr.reset();
    cout << "count: " << weakPtr.use_count() << endl;

    // 만약 다른 공유 포인터가 전부 소멸 당하면 weak_ptr은 expired 상태게 되므로 이걸 통해 null 참조를 막을 수 있다.
    if (!weakPtr.expired() /* !weakPtr 도 가능 */ ) {
        auto lockWeak = weakPtr.lock();
        cout << lockWeak->getName() << endl;
    }
    
    shared_ptr<Person> newShared = make_shared<Person>(10, "언젱가", 50);
    weak_ptr<Person> newWeak = newShared;  // 내부적으로 shared_ptr에 원시 포인터를 참조
    cout << "count: " << newShared.use_count() << endl;

    // 약한 참조 카운팅을 감소 시킴, 일방적으로 참조를 끊는것 
    weakPtr.reset();
    // weakPtr.lock()->getName(); 접근 불가
    // 강한 참조 카운팅은 동일 
    cout << "count: " << newShared.use_count() << endl;

    return 0;
}
