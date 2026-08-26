/** 
@see https://dhpark1212.tistory.com/entry/fopen-fread-fwrite-fstream-ifstream-ofstream
*/

#include <fstream>
#include <iostream>

using namespace std;

/* 파일 입출력

ios_base::in	파일을 오로지 읽는 것만 가능한 모드로 개방함.
ios_base::out	파일을 쓰는 것만이 가능한 모드로 개방함.
ios_base::ate	파일을 개방할 때 파일의 끝으로 파일 포인터를 이동시킴.
ios_base::app	해당 파일의 맨 끝에서부터 데이터를 추가함.
ios_base::trunc	파일이 있으면 해당 파일의 모든 데이터를 지우고 개방함.
ios_base::binary	바이너리 모드로 개방함
*/

int main(int argc, char const *argv[]) {
    /* 파일 읽을 때만 */
    // ifstream

    /* 파일 쓸때만 */
    // ofstream

    /* 걍 둘다 할때 */
    fstream file;

    file.open("test.txt", ios_base::out);
    if (file.is_open()) {
        while (true) {
            string buf;
            getline(cin, buf);
            if (buf == "exit") { /* 왜인지 모르겠지만 compare() 를 쓰면 한글처리가 잘 안된다 */
                break;
            };
            file << buf << endl;
        }
    } else {
        cout << "파일 안열림" << endl;
    }

    file.close();
    file.open("test.txt", ios_base::in);

    if (file.is_open()) {
        string str;
        while (!file.eof()) {
            getline(file, str);
            cout << str << endl;
        }

    } else {
        cout << "파일 안열림" << endl;
    }

    return 0;
}
