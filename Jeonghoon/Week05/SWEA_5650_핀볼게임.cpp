#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

struct Node {
    int y, x;
};

vector<Node> warm[11];

int score, N;
int map[101][101];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
int dir;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];

            if (map[i][j] > 5) {
                warm[map[i][j]].push_back({ i,j });
            }
        }
    }
}

/*
    0 - 좌, 1 - 상, 2 - 우, 3 - 하

    블럭 1 : 3 -> 2, 0 -> 1
    블럭 2 : 0 -> 3, 1 -> 2
    블럭 3 : 1 -> 0, 2 -> 3
    블럭 4 : 2 -> 1, 3 -> 4
*/

void change_dir(int block) {

    //5번 블록은 무조건 반대 방향으로
    if (block == 5) {
        dir = (dir + 2) % 4;
        return;
    }

    //시계방향으로 방향이 바뀌는 경우
    if (block == dir + 1) {
        dir = (dir + 1) % 4;
        return;
    }
    else if ((block + 2) % 4 == dir) {
        if (dir == 0) {
            dir = 4;
        }
        dir = dir - 1;
        return;
    }
    else {
        dir = (dir + 2) % 4;
        return;
    }
}

Node warmhole(int hole, int y, int x) {

    if (warm[hole][0].x == x && warm[hole][0].y == y) {
        return { warm[hole][1].y , warm[hole][1].x };
    }
    else {
        return { warm[hole][0].y, warm[hole][0].x };
    }

}

int game(int sy, int sx) {

    int x = sx;
    int y = sy;
    int cnt = 0;

    while (1) {

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        //종료조건 2개
        if (ny == sy && nx == sx) break;
        if (map[ny][nx] == -1) break;

        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            cnt++;
            dir = (dir + 2) % 4;
            x = nx;
            y = ny;
            continue;
        }

        //벽 맞고 점수 +
        //방향 변환
        if (map[ny][nx] > 0 && map[ny][nx] < 6) {
            cnt++;
            change_dir(map[ny][nx]);
        }

        //웜홀
        else if (map[ny][nx] > 5) {
            Node pnew = {};
            pnew = warmhole(map[ny][nx], ny, nx);

            x = pnew.x;
            y = pnew.y;
            continue;
        }

        x = nx;
        y = ny;

    }
    return cnt;
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (map[i][j] != 0) continue;

            for (int k = 0; k < 4; k++) {
                int sp_x = j + dx[k];
                int sp_y = i + dy[k];

                if (sp_x < 0 || sp_x > N || sp_y < 0 || sp_y > N) {
                    continue;
                }

                dir = k;
                int game_score = game(i, j);

                if (game_score > score) {
                    score = game_score;
                }
            }
        }
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        score = 0;
        memset(map, 0, sizeof(map));

        for (int i = 6; i < 11; i++) {
            warm[i].clear();
        }

        input();
        solve();
        cout << "#" << tc << " " << score << '\n';
    }

    return 0;
}