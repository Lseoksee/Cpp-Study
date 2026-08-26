/*
시퀀스 컨테이너: 일반적인 선형 컨테이너, 특별한 제약은 없음

종류:
- vector
- deque
- list
- forward_list
*/
#include <deque>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

/* vector 컨테이너는 동적 배열의 클래스 템플릿 표현이라 볼 수 있음
벡터 객체는 요소가 추가되거나 삭제될 때마다 자동으로 메모리를 재할당하여 크기를 동적으로 변경
임의 접근을 제공하는 가장 간단한 시퀀스 컨테이너 */
void vectorTest() {
    vector<string> vc = {"언", "젠", "가"};
    // 현재 배열 요소 개수 반환
    cout << vc.size() << endl;
    // 현재 할당 받은 메모리 크기 반환
    cout << vc.capacity() << endl;
    cout << vc[0] << endl;

    // 배열 요소 추가
    vc.push_back("그러나");

    // 이렇게 백터를 포인터 접근하 듯 for-loop로 순회 가능한데
    // 이것이 바로 iterator에 역할이다
    // 객체 내부적으로 참조 연산자가 오버라이딩 되어있고 다른 여러 조건도 만족한다면, 그게 iterator객체인 것
    for (int i; i < vc.size(); i++) {
        cout << vc[i] << endl;  // 입력 반복자 사용
    }

    // range for-loop 사용
    // 내부적으로 begin() 함수를 호출하여 iterator를 참조함
    for (string item : vc) {
        cout << item << endl;
    }

    /* 컨테이너의 첫 요소를 가르키는 반복자 반환 */
    // vc.begin();
    /* 컨테이너의 첫 요소를 가르키는 반복자 반환 */
    // vc.end();
}

/* deque 구현 컨테이너 */
void dequeTest() {
    deque<string> dq;
    dq.push_front("빈");
    dq.push_front("지");
    dq.push_front("노");
    dq.pop_back();

    for (string item : dq) {
        cout << item << endl;
    }
}

/* 이중 연결 리스트의 클래스 템플릿
(단방향 연결리스트는 forward_list 사용가능)
*/
void listTest() {
    list<int> ls = {10, 30, 50};
    ls.push_back(70);
    ls.push_back(120);

    /* 연결리스트에 중간 삽입 */
    auto ft = ls.begin();
    // 포인터 주소를 앞으로 2칸 전진
    std::advance(ft, 2);
    ls.emplace(ft, 728);

    for (int item : ls) {
        cout << item << endl;
    }
}


int main(int argc, char const *argv[]) {
    cout << "---vectorTest---" << endl;
    vectorTest();
    cout << "---dequeTest---" << endl;
    dequeTest();
    cout << "---listTest---" << endl;
    listTest();
    return 0;
}
