#include <iostream>

using namespace std;

// 템플릿 클래스
template <class T = int /* 기본타입 명시 */>
class Object {
   private:
   public:
    void printValue(T a, T b) {
        cout << a << endl;
        cout << b << endl;
    }
    /* 중첩 클래스 */
    template <class B>
    class ObjectSub {
       private:
       public:
        // T, B 둘다 가능
        void printValueSub(B a, T b) {
            cout << a << endl;
            cout << b << endl;
        }
    };
};

// 명시적 특수화
template <>
class Object<double> {
   private:
   public:
};

template<class T, class B> class OBJ  {
   private:
   public:
};

// B에 대해서만 진행하는 명시적 특수화
template <class T> class OBJ<T, double> {
   private:
   public:
};

int main(int argc, char const *argv[]) {
    Object<string> ob;
    ob.printValue("디스크", "파티");
    // 중첩 클래스 선택은 지시자로
    Object<string>::ObjectSub<int> sa;
    sa.printValueSub(10, "그것");

    return 0;
}
