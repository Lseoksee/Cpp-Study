#include <iostream>

using namespace std;

typedef struct Person {
    int weight;
    int lenth;
} Person;

int main(int argc, char const* argv[]) {
    Person ps;
    ps.lenth = 170;
    ps.weight = 65;
    cout << ps.lenth << ps.weight << endl;

    // new 이용
    // Person* poPerson = new Person{170, 50};
    Person* poPerson = new Person;
    poPerson->lenth = 170;
    poPerson->weight = 65;
    cout << poPerson->lenth << " " << poPerson->weight << endl;
    delete poPerson;

    return 0;
}
