/*
컨테이너 어댑터: 기존 컨테이너의 인터페이스를 제한하여 기능이 제한되거나 변형된
반복자를 지원하지 않아 알고리즘 계산은 안됨

종류
- stack
- queue
- priority_queue
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/*
스택은 vector 에서 인터페이스를 제한하여 사용
*/
void stackTest() {
    stack<int> st;
    st.push(20);
    st.push(60);
    st.push(80);
    for (; !st.empty();) {
        cout << st.top() << endl;
        st.pop();
    }
}

/*
큐는 deque 에서 인터페이스를 제한하여 사용
priority_queue는 우선 순위 큐
*/
void queueTest() {
    queue<int> qu;
    qu.push(20);
    qu.push(60);
    qu.push(80);
    for (; !qu.empty();) {
        cout << qu.front() << endl;
        qu.pop();
    }
}

int main(int argc, char const *argv[]) {
    cout << "---stackTest---" << endl;
    stackTest();
    cout << "---queueTest---" << endl;
    queueTest();
    return 0;
}
