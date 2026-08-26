/*
연관 컨테이너: key-value 쌍

종류
- set
- multiset
- map
- multimap

C++11 부터 순서가 지정되지 않는 연관 컨테이너가 추가됨
동작은 같지만, 해시 테이블 기반하므로 더 빠른 동작이 가능함

종류
- unordered_set
- unordered_multiset
- unordered_map
- unordered_multimap
*/

#include <iostream>
#include <map>
#include <set>

using namespace std;

/* set에 컨테이너 구현, 중복 허용 없고 오름차순 정렬된 위치에 삽입으로 검색 속도가 빠름
multiset에 경우 중복울 허용함
*/
void setTest() {
    set<int> se = {12, 324, 6, 32};
    se.insert(35);
    se.insert(1);
    se.insert(324);  // 중복이라 안들어감

    for (int item : se) {
        cout << item << endl;
    }
}

/* map에 컨테이너 구현, 키-쌍 으로 이뤄진구조
multimap은 하나의 키로 여러 값과 연관 될 수 있음
*/
void mapTest() {
    map<string, int> mp;
    // pair 라는 구조체 템플릿을 활용해서 인자를 넣음
    mp.insert(pair<string, int>("pas", 10));
    // 이런식으로 첨자 연산도 사용 가능
    mp["iwa"] = 40;

    for (auto be = mp.begin(); be != mp.end(); be++) {
        cout << "key: " << be->first << "value: " << be->second << endl;
    };

    // iterator객체를 직접 사용할 수 있음
    map<string, int>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++) {
        cout << "key: " << it->first << "value: " << it->second << endl;
    }
}

int main(int argc, char const *argv[]) {
    cout << "---setTest---" << endl;
    setTest();
    cout << "---mapTest---" << endl;
    mapTest();
    return 0;
}
