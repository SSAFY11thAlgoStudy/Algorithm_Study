#include <iostream>
#include <algorithm>
using namespace std;
int t, n, cnt = 0; // cnt = queen을 놓을 수 있는 경우의 수 
int d[11]; // queen 놓을 배열 
bool check(int x) {
    for (int i = 0; i < x; i++) {  // x번 까지 만족하는지 확인
        if (d[x] == d[i] || abs(d[x] - d[i]) == x - i)
            return false;  // d[x] == d[i]이면 같은열에 놓인 경우
        // abs(d[x]-d[i]) == x - i 는 대각선에 놓인 경우 
    }
    return true;
}
void dfs(int x) {
    if (x == n) {  // n개 놔졌으면 퀸을 정상적으로 놨으므로 
        cnt++;
        return;
    }
    else {
        for (int i = 0; i < n; i++) { // 0~n-1까지 queen을 놔야하므로
            d[x] = i; // d[x]자리에 i 놓기
            if (check(x)) // x까지에 대해서  queen 배열 check해주기
                dfs(x + 1); //true면 맞게 배치했으므로 x+1개로 넘어가기
        }
    }

}
int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cnt = 0; // t만큼 돌아야하므로 cnt = 0으로 항상 초기화
        dfs(0);  // 0부터 n-1까지 돌리면 되므로 0부터 시작
        cout << "#" << i + 1 << " " << cnt << '\n';
    }
    return 0;
}