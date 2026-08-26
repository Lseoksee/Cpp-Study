/** 
@see https://tcpschool.com/cpp/cpp_exception_class
*/
#include <iostream>

using namespace std;

/* 자바와는 다르게 상위 호출 스택 함수 쪽에서 throw를 할 필요 없이 무조건 던저짐
예외가 발생하면 스택 최하단 에서 부터 최상단까지 예외처리 구문을 찾아 처리
즉, try-catch를 만나기 전까지 계속 전달됨
이것을 `스택풀기` 라고함
*/

int IncreaseNumber(int n) {
    if (n < 0)
        throw n;
    else if (n == 0)
        throw "0은 입력할 수 없습니다.";
    return ++n;
}

/* 예외 클래스를 사용하여 전달 */
int exceptionClass(int n) {
    if (n < 0)
        throw logic_error("뭔가 뭔가여");
    else if (n == 0)
        throw bad_typeid();
    return ++n;
}

int main(int argc, char const* argv[]) {
    try {
        IncreaseNumber(-1);
    } catch (const char* err) /* 예외 변수는 throw 타입과 일치해야한다  */ {
        cout << err << endl;
    } catch (int err) /* 만약 - 인 입력 값은 throw가 int 형 이므로 여기서 처리된다  */ {
        cout << err << endl;
    }

    cout << "처리되지?" << endl;

    try {
        exceptionClass(-1);
    } catch (logic_error ex) {
        cout << ex.what() << endl;
    }
    /* 예외 클래스를 사용한 경우 exception 하나를 통해 모든 예외 처리 가능 (즉 자바처럼) */
    catch (exception ex) {
        cout << ex.what() << endl;
    }

    cout << "처리되지?" << endl;

    return 0;
}
