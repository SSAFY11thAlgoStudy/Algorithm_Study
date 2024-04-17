#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int N, M, K;
int map[12][12];
int ex, ey;
int rx, ry;
int minr;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

struct Player {
    int y, x;
};

vector<Player>p;
bool isexit[12];
int pmove[12];

void input() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }

    p.push_back({ 0,0 });
    for (int i = 1; i <= M; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        p.push_back({ t1, t2 });
    }

    cin >> ey >> ex;
    map[ey][ex] = -1;
}

void movep() {
    for (int j = 1; j <= M; j++) {
        if (isexit[j] == true) continue;
        int mindist = abs(ex - p[j].x) + abs(ey - p[j].y);

        int newy = 0;
        int newx = 0;

        for (int i = 0; i < 4; i++) {
            int ny = p[j].y + dy[i];
            int nx = p[j].x + dx[i];

            if (ny < 1 || nx < 1 || ny > N || nx > N) continue;
            if (map[ny][nx] > 0) continue;

            if (map[ny][nx] == -1) {
                isexit[j] = true;
                p[j].x = 0;
                p[j].y = 0;
                newy = ny;
                newx = nx;
                break;
            }

            int dist = abs(ex - nx) + abs(ey - ny);

            if (mindist > dist) {
                mindist = dist;
                newy = ny;
                newx = nx;
            }
        }

        if (newy != 0 && newx != 0) {
            pmove[j]++;
            p[j].x = newx;
            p[j].y = newy;
        }
    }
}

void findfield() {
    for (int sz = 2; sz <= N; sz++) {
        for (int y1 = 1; y1 <= N - sz + 1; y1++) {
            for (int x1 = 1; x1 <= N - sz + 1; x1++) {
                int x2 = x1 + sz - 1;
                int y2 = y1 + sz - 1;

                if (!(x1 <= ex && ex <= x2 && y1 <= ey && ey <= y2)) {
                    continue;
                }

                bool is_traveler_in = false;
                for (int l = 1; l <= M; l++) {
                    if (isexit[l] == true) continue;
                    if (x1 <= p[l].x && p[l].x <= x2 && y1 <= p[l].y && p[l].y <= y2) {
                        is_traveler_in = true;
                    }
                }

                // 만약 한 명 이상의 참가자가 해당 정사각형 안에 있다면
                // sx, sy, sqaure_size 정보를 갱신하고 종료합니다.
                if (is_traveler_in) {
                    rx = x1;
                    ry = y1;
                    minr = sz;

                    return;
                }
            }
        }
    }
}

void rotate() {
    //맵회전
    int tmpmap[12][12] = { 0, };
    for (int i = ry; i < ry + minr; i++) {
        for (int j = rx; j < rx + minr; j++) {
            int oy = i - ry;
            int ox = j - rx;
            int ty = ox;
            int tx = minr - oy - 1;
            tmpmap[ry + ty][rx + tx] = map[i][j];
        }
    }

    for (int i = ry; i < ry + minr; i++) {
        for (int j = rx; j < rx + minr; j++) {
            map[i][j] = tmpmap[i][j];
            if (map[i][j] > 0) map[i][j]--;
            if (map[i][j] == -1) {
                ey = i;
                ex = j;
            }
        }
    }

    for (int i = 1; i <= M; i++) {
        int x = p[i].x;
        int y = p[i].y;

        if (rx <= x && x < rx + minr && ry <= y && y < ry + minr) {
            int oy = y - ry;
            int ox = x - rx;
            int ty = ox;
            int tx = minr - oy - 1;
            p[i].x = rx + tx;
            p[i].y = ry + ty;
        }
    }
}

bool checkend() {
    for (int i = 1; i <= M; i++) {
        if (isexit[i] == false) return false;
    }
    return true;
}

void print() {
    int pmap[12][12] = { 0, };
    for (int i = 1; i <= M; i++) {
        pmap[p[i].y][p[i].x] = i;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << pmap[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void solve() {
    for (int i = 1; i <= K; i++) {
        //참자가자 움직이는 함수
        movep();
        //남은 참여자 확인하고 모두 탈출했으면 끝
        if (checkend()) return;
        //회전할 구역 찾기
        findfield();
        //회전, 내구도 --
        rotate();
        //print();
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();
    solve();

    int result = 0;
    for (int i = 1; i <= M; i++) {
        result += pmove[i];
    }
    cout << result << "\n" << ey << " " << ex;

    return 0;
}