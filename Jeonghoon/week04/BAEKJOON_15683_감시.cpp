#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int N, M;
int map[8][8];
struct Point {
    int x, y;
};

vector<Point> cam;
int ans = 21e8;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void input() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] > 0 && map[i][j] < 6)
                cam.push_back({ i, j });
        }
    }
}

void check(int y, int x, int dir) {
    dir = dir % 4;
    while (1) {
        //다음 방향을 감시 가능한지 확인하는 과정
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        x = nx;
        y = ny;

        if (nx < 0 || ny < 0 || nx >= M || ny >= N) return;
        if (map[ny][nx] == 6) return;
        if (map[ny][nx] != 0) continue;

        //감시 가능한 공간을 7로 변경
        map[ny][nx] = 7;
    }
}

void dfs(int level) {
    //카메라의 수와 level이 동일하다면 리턴
    //리턴하기 전 지금까지 감시 가능한 공간 확인
    if (level == cam.size()) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 0) cnt++;
            }
        }
        if (ans > cnt) {
            ans = cnt;
        }
        return;
    }

    int x = cam[level].x;
    int y = cam[level].y;

    //각 제귀단계의 맵 상태 저장
    int tmp[9][9];

    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                tmp[i][j] = map[i][j];
            }
        }

        if (map[x][y] == 1) check(x, y, dir);

        else if (map[x][y] == 2) {
            check(x, y, dir);
            check(x, y, dir + 2);
        }
        else if (map[x][y] == 3) {
            check(x, y, dir);
            check(x, y, dir + 1);
        }
        else if (map[x][y] == 4) {
            check(x, y, dir);
            check(x, y, dir + 1);
            check(x, y, dir + 2);
        }
        else if (map[x][y] == 5) {
            check(x, y, dir);
            check(x, y, dir + 1);
            check(x, y, dir + 2);
            check(x, y, dir + 3);
        }

        dfs(level + 1);
        // case 종료이므로 초기화
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = tmp[i][j];
            }
        }
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    cin >> N >> M;
    input();
    dfs(0);
    cout << ans;

    return 0;
}