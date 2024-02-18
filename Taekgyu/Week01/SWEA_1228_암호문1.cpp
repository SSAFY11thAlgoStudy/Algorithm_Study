#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

//원본 숫자 개수
int N1;

//명령어 개수
int N2;

char frontC;
int pos; //위치변수
int Num; //삽입 숫자 개수

int main() {

    freopen("sample_input.txt", "r", stdin);

    for (int tc = 1; tc <= 10; tc++) {
        cin >> N1;
        vector<int> v;
        // 원본 암호문 입력
        for (int i = 0; i < N1; i++) {
            int origin = 0;
            cin >> origin;
            v.push_back(origin);
        }

        cin >> N2;
        vector<int> cv;
        // 명령어 입력
        for (int i = 0; i < N2; i++) {
            cin >> frontC >> pos >> Num;

            if (frontC == 'I') {
                for (int j = 0; j < Num; j++) {
                    int ins = 0;
                    cin >> ins;
                    cv.push_back(ins);
                }
                // 원본 암호문에 명령어 삽입
                v.insert(v.begin() + pos, cv.begin(), cv.end());
                // 명령어 초기화
                cv.clear();

            }
        }

        cout << "#" << tc << " ";
        for (int i = 0; i < 10; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
        // 출력 후 원본 암호문 초기화
        v.clear();
    }

    return 0;
}