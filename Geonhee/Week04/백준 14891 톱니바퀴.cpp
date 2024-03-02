#include <iostream>
#include <algorithm>
#include<cmath>
using namespace std;
int gear[4][8];

void run(int g, int d) {
    if (d == 1) { //시계방향
        int temp = gear[g][7];
        for (int i = 7; i > 0; i--) {
            gear[g][i] = gear[g][i - 1];
        }
        gear[g][0] = temp;
    }
    else { //반시계 방향
        int temp = gear[g][0];
        for (int i = 0; i < 7; i++) {
            gear[g][i] = gear[g][i + 1];
        }
        gear[g][7] = temp;
    }
}

void right(int x, int d) {
    if (x > 2) return;//3부터는 오른쪽 비교 안해도 되므로
    if (gear[x][2] != gear[x + 1][6]) { //다를때만 회전시켜주면됨
        right(x + 1, -d); //갈 수 있는 곳까지 가야함, 방향 바꿔주기
        //먼저 돌려주면 값 비교가 달라지기 때문에 
        run(x + 1, -d); // 재귀 돌아와서 제일 오른쪽 톱니부터
        //방향에 맞게 톱니바퀴 돌려주기
    }
    return;
}

void left(int x, int d) {
    if (x < 1) return; //0부터는 왼쪽 비교 안해도 되므로
    if (gear[x][6] != gear[x - 1][2]) {
        left(x - 1, -d);
        run(x - 1, -d);
    }
    return;
}
int main() {
    for (int i = 0; i < 4; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            gear[i][j] = s[j] - '0';
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        right(a - 1, b); //오른쪽
        left(a - 1, b); //왼쪽
        run(a - 1, b); //해당 톱니바퀴도 돌려줘야함
    }
    int res = 0;
    for (int i = 0; i < 4; i++) {
        if (gear[i][0]) res += pow(2, i); //규칙이 2의(i-1)제곱
    }
    cout << res;
    return 0;
}