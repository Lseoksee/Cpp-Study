#include <iostream>

using namespace std;

int main(int argc, char const* argv[]) {
    // 기본 배열 선언
    int arr[] = {1, 2, 3, 4, 5};

    // narrowing cast 문제
    // 자료형에 크기와 실제 데이터가 달라 발생하는 손실
    int naVar= 3.14; // 3밖에 안나옴
    cout << naVar << endl;
    // int naArray = {1, 2, 3}; 이거는 c++11 이후로 막힘

    // 포인터도 동일
    int* p = arr;
    cout << p[0] << endl;

    // 힙 메모리 동적할당
    int* space = new int;  // malloc()
    *space = 10;
    cout << "값: " << *space << endl;
    cout << "메모리 공간: " << sizeof(space) << endl;

    delete space;  // free()
    cout << "다시 참조: " << *space << endl;

    // 배열 힙 메모리
    int * arrptr  = new int[10]();
    int* arrptr2 = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "값: " << arrptr2[0] << endl;

    delete arrptr;
    delete arrptr2;
    return 0;
}
