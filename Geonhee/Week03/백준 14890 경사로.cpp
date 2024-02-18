#include <iostream>
using namespace std;

int map[101][101];
int n, l;
int res = 0;

void row(int x, int y, int cnt) {  // cnt : 경사로를 놓을 수 있나 없나 판단할 길의 갯수
    int cur = map[x][y]; // 현재 좌표
    int next = map[x][y + 1]; // 다음 좌표
    if (y + 1 == n) { // y+1좌표가 n이면 길을 다 건너온 것이므로 res++
        res++;
        return;
    }
    if (cur == next) {  // 현재 좌표와 다음 좌표가 같다면
        row(x, y + 1, cnt + 1); // 그냥 넘어가면 됨
    }
    else if (cur + 1 == next) { // 현재 좌표보다 다음 좌표가 1 더 크다면
        if (cnt >= l) // 경사로를 놓을 수 있으면
            row(x, y + 1, 1); // 다음좌표로 가되 경사로를 놨으므로 cnt는 1로 초기화
        return;
    }
    else if (cur == next + 1) { // 현재 좌표가 다음 좌표보다 1 크다면
        if (y + l < n) { // 범위가 벗어나지 않는다면
            for (int i = y + 1; i < y + 1 + l; i++) { // 다음좌표부터 l개까지의 좌표가 같아야 경사로를 놓을 수 있으므로
                if (next != map[x][i]) return; // 다르다면 놓지 못하므로 return
            }
            row(x, y + l, 0); // 위에를 만족하면 l을 더한 다음좌표로 가고 경사로를 놓고 내려갔으므로 cnt는 0으로 초기화
        }
    }
}

void col(int x, int y, int cnt) {
    int cur = map[x][y];
    int next = map[x + 1][y];
    if (x + 1 == n) {
        res++;
        return;
    }
    if (cur == next) {
        col(x + 1, y, cnt + 1);
    }
    else if (cur + 1 == next) {
        if (cnt >= l)
            col(x + 1, y, 1);
        return;
    }
    else if (cur == next + 1) {
        if (x + l < n) {
            for (int i = x + 1; i < x + 1 + l; i++) {
                if (next != map[i][y]) return;
            }
            col(x + l, y, 0);
        }
    }
}

int main() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        row(i, 0, 1); // 행 판단시 x좌표 고정 y좌표 이동 cnt는 1개 먹고 시작
        col(0, i, 1); // 열 판단시 y좌표 고정 x좌표 이동 cnt는 1개 먹고 시작
    }
    cout << res;
    return 0;
}