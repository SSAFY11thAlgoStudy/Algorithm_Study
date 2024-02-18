#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
(1,1)부터 (R,C)까지!!!!!!!!!!!!

1. 미세먼지가 확산된다. 확산은 미세먼지가 있는 모든 칸에서 동시에 일어난다.
    a.(r, c)에 있는 미세먼지는 인접한 네 방향으로 확산된다.
    b.인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
    c.확산되는 양은 Ar,c/5이고 소수점은 버린다. 즉, ?Ar,c/5?이다.
    d.(r, c)에 남은 미세먼지의 양은 Ar,c - ?Ar,c/5?×(확산된 방향의 개수) 이다.
2.공기청정기가 작동한다. 공기청정기에서는 바람이 나온다.
    a.위쪽 공기청정기의 바람은 반시계방향으로 순환하고, 아래쪽 공기청정기의 바람은 시계방향으로 순환한다.
    b.바람이 불면 미세먼지가 바람의 방향대로 모두 한 칸씩 이동한다.
    c.공기청정기에서 부는 바람은 미세먼지가 없는 바람이고, 공기청정기로 들어간 미세먼지는 모두 정화된다.
*/

struct position {
    int y;
    int x;
    int d = 0;
};
int R, C, T;
int map[51][51];
int dy[] = { 0,-1,0,1 }, dx[] = { 1,0,-1,0 };
position luftreiniger[2];

void print() {
    cout << "\n";
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void fxxking_china() {
    int dust_extend[51][51] = { 0 };

    // 배열 분리
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            int spread = map[i][j] / 5;
            int cnt = 0;

            for (int d = 0; d < 4; d++) {
                int ny = i + dy[d];
                int nx = j + dx[d];

                if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                if (map[ny][nx] == -1) continue;

                dust_extend[ny][nx] += spread;
                cnt++;
            }

            dust_extend[i][j] += map[i][j] - (spread * cnt);
        }
    }

    // 다시 채워넣기
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            map[i][j] = dust_extend[i][j];
        }
    }


}

void samsung() {

    // 위쪽 공기청정기
    int y = luftreiniger[0].y;
    for (int i = y - 1; i > 1; --i) {
        map[i][1] = map[i - 1][1];
    }
    for (int i = 1; i < C; ++i) {
        map[1][i] = map[1][i + 1];
    }
    for (int i = 1; i < y; ++i) {
        map[i][C] = map[i + 1][C];
    }
    for (int i = C; i > 2; --i) {
        map[y][i] = map[y][i - 1];
    }
    map[y][2] = 0;

    // 아래쪽 공기청정기
    y = luftreiniger[1].y;
    for (int i = y + 1; i < R; ++i) {
        map[i][1] = map[i + 1][1];
    }
    for (int i = 1; i < C; ++i) {
        map[R][i] = map[R][i + 1];
    }
    for (int i = R; i > y; --i) {
        map[i][C] = map[i - 1][C];
    }
    for (int i = C; i > 2; --i) {
        map[y][i] = map[y][i - 1];
    }
    map[y][2] = 0;

}
void solve() {
    for (int tc = 0; tc < T; tc++)
    {
        fxxking_china();
        samsung();
        //print();
    }

    int total = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (map[i][j] > 0) {
                total += map[i][j];
            }
        }
    }
    cout << total << '\n';
}
void input() {
    int c = 0;
    cin >> R >> C >> T;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == -1) {
                luftreiniger[c].y = i;
                luftreiniger[c++].x = j;
            }
        }
    }
}


int main() {
    input();
    solve();

    return 0;
}
