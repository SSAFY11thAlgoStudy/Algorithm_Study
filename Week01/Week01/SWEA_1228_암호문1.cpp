#include <iostream>
#include <vector>
#include <queue>
using namespace std;




int main() {

    int t = 10;
    for (int i = 1; i <= t; i++) {

        // N : 원본 암호문의 개수 (10<=N<=20)
        // num : 원본 암호문
        // M : 명령어의 개수 (5<=M<=10)
        // c, x, y, s : 
        // c : 명령어 종류(현재는 삽입(I)만 존재), 
        // x : 삽입하고자 하는 위치
        // y : 삽입하고자 하는 수의 개수
        // s : 삽입하고자 하는 수들
        int N, num, M, x, y, s;
        char c;
        vector<int>v;

        cin >> N;
        for (int j = 0; j < N; j++) {
            cin >> num;
            v.push_back(num);
        }
        cin >> M;

        for (int j = 0; j < M; j++) {
            vector<int>temp;
            cin >> c >> x >> y;
            for (int k = 0; k < y; k++) {
                cin >> s;
                temp.push_back(s);
            }
            // v벡터의 x지점에 temp의 시작부터 y번째까지 값을 삽입하겠다.
            v.insert(v.begin() + x, temp.begin(), temp.begin() + y);
        }
        cout << "#" << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << v[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}