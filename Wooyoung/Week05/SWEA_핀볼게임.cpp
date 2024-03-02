#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

struct Pos {
    int y, x;
};

int t, n, ans;
int map[101][101];
// 상 하 좌 우
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int directions[5][5] = {
    {1,3,0,2},
    {3,0,1,2},
    {2,0,3,1},
    {1,2,3,0},
    {1,0,3,2}
};
vector<Pos>start;
Pos worm_hole[6][2];
void init() {
    ans = 0;
    start.clear();
    for (int i = 0; i < 6; i++) {
        worm_hole[i][0].y = -1;
        worm_hole[i][0].x = -1;
        worm_hole[i][1].y = -1;
        worm_hole[i][1].x = -1;

    }
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                start.push_back({ i,j });
            }
            else if (map[i][j] >= 6 && map[i][j] <= 10) {
                int num = map[i][j] - 6;
                if (worm_hole[num][0].y == -1 && worm_hole[num][0].x == -1) {
                    worm_hole[num][1].y = i;
                    worm_hole[num][1].x = j;
                    worm_hole[num][0].y = 0;
                    worm_hole[num][0].x = 0;
                }
                else {
                    worm_hole[num][0].y = i;
                    worm_hole[num][0].x = j;
                }
            }
        }
    }
}

bool isReverse(int y, int x) {
    return y<0 || x<0 || y>n - 1 || x>n - 1 || map[y][x] == 5;
}

void func(Pos now, int dir) {

    int start_y = now.y;
    int start_x = now.x;

    int now_y = now.y;
    int now_x = now.x;
    int score = 0;



    while (1) {

        now_y += dy[dir];
        now_x += dx[dir];

        int num = map[now_y][now_x];

        // 블랙홀 or 시작지점
        if (num == -1 ||
            (now_y == start_y && now_x == start_x)) {
            ans = max(ans, score);
            //cout << start_y<<" "<<start_x<<" "<<ans << "\n";
            return;
        }

        // 벽 또는 블럭 (5번) -> dir 반대로
        if (isReverse(now_y, now_x)) {
            // now_y -= dy[dir];
             //now_x -= dx[dir];
            dir = directions[4][dir];
            score++;
        }

        // 삼각형

        else if (num >= 1 && num <= 4) {

            dir = directions[num - 1][dir];
            score++;
        }

        // 직진
        else if (num == 0) {
            continue;
        }

        // 웜홀
        else if (num >= 6 && num <= 10) {
            num -= 6;
            if (worm_hole[num][0].y == now_y &&
                worm_hole[num][0].x == now_x) {
                now_y = worm_hole[num][1].y;
                now_x = worm_hole[num][1].x;
            }
            else {
                now_y = worm_hole[num][0].y;
                now_x = worm_hole[num][0].x;
            }
        }

    }

}

int main() {
    //freopen("input.txt", "r", stdin);
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        init();
        input();
        for (int i = 0; i < start.size(); i++) {
            for (int j = 0; j < 4; j++) {
                func(start[i], j);
            }
        }
        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}