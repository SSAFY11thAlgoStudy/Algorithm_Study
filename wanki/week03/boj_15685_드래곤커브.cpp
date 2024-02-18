#include<iostream>
#include<vector>

using namespace std;

/*
0: x좌표가 증가하는 방향(→)
1: y좌표가 감소하는 방향(↑)
2: x좌표가 감소하는 방향(←)
3: y좌표가 증가하는 방향(↓)
*/
int dy[] = { 0, -1, 0, 1 }, dx[] = { 1, 0, -1, 0 };
int N, x, y, d, g;
int map[101][101];
vector<int> path;

void draw_line() {
    //루트 초기화
    path.clear();
    //루트 삽입
    path.push_back(d);
    //시작 위치 삽입
    map[y][x] = 1;
    y += dy[d];
    x += dx[d];
    map[y][x] = 1;

    for (int gen = 1; gen <= g; gen++) { // 세대 확인 1이상만
        for (int i = path.size() - 1; i >= 0; i--) { //왔던루트 확인
            int nd = (path[i] + 1) % 4; // 왔던 루트에 +1만큼 턴
            y += dy[nd];
            x += dx[nd];
            map[y][x] = 1;
            path.push_back(nd);
        }
    }
}

int check_square() {
    int cnt = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1 && map[i + 1][j] == 1) {
                cnt++;
            }
        }
    }
    return cnt;
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x >> y >> d >> g;
        draw_line();
    }
}

int main() {
    input();
    cout << check_square();
    return 0;
}
