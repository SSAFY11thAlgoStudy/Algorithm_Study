#include<iostream>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
//2^H의 노드 수,
//K각 노드별로 가지는 업무 갯수, 
//R업무가 수행되는 기한
//최종적으로 기간동안 완료된 업무번호의 합을 출력
int result = 0;
int H, K, R;
queue<int>v[2049];

void input() {
    int num;
    cin >> H >> K >> R;
    for (int i = pow(2, H); i < pow(2, H + 1); i++) {
        for (int j = 0; j < K; j++)
        {
            cin >> num;
            v[i].push(num);
        }
    }
}

void solve() {
    int today = 1;//업무 날짜


    while (today <= R) {
        if (!v[1].empty()) {
            result += v[1].front();
            v[1].pop();
        }
        if (today % 2 != 1) { //짝수날
            for (int i = 2; i < pow(2, H + 1); i++) {
                if (i % 2 != 0 || v[i].empty())continue;//왼쪽 노드
                v[i / 2].push(v[i].front());
                v[i].pop();
            }
        }
        else { //홀수날
            for (int i = 2; i < pow(2, H + 1); i++) {
                if (i % 2 == 0 || v[i].empty())continue;//오른쪽 노드
                v[(i - 1) / 2].push(v[i].front());
                v[i].pop();
            }
        }

        today++;
    }


}

int main(int argc, char** argv)
{
    input();
    solve();


    cout << result;
    return 0;
}