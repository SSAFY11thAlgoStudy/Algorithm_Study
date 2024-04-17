#include <iostream>

using namespace std;

int n, m, k;
int map[11][11];
int next_map[11][11];
pair<int, int> player[11];
pair<int, int> exits;
int ans;
int sx, sy, square_size;

// 모든 참가자를 이동시킵니다.
void All_player_move() {
    for (int i = 1; i <= m; i++) {
        if (player[i].first == exits.first && player[i].second == exits.second)
            continue;
        if (player[i].first != exits.first) {
            int nx = player[i].first;
            int ny = player[i].second;

            if (exits.first > nx) nx++;
            else nx--;
            if (!map[nx][ny]) {
                player[i].first = nx;
                player[i].second = ny;
                ans++;
                continue;
            }
        }
        if (player[i].second != exits.second) {
            int nx = player[i].first;
            int ny = player[i].second;

            if (exits.second > ny) ny++;
            else ny--;
            if (!map[nx][ny]) {
                player[i].first = nx;
                player[i].second = ny;
                ans++;
                continue;
            }
        }
    }
}


void min_square() {
    for (int sz = 2; sz <= n; sz++) {
        for (int x1 = 1; x1 <= n - sz + 1; x1++) {
            for (int y1 = 1; y1 <= n - sz + 1; y1++) {
                int x2 = x1 + sz - 1;
                int y2 = y1 + sz - 1;

                if (!(x1 <= exits.first && exits.first <= x2 && y1 <= exits.second && exits.second <= y2)) {
                    continue;
                }
                bool is_traveler_in = false;
                for (int l = 1; l <= m; l++) {
                    if (x1 <= player[l].first && player[l].first <= x2 && y1 <= player[l].second && player[l].second <= y2) {
                        if (!(player[l].first == exits.first && player[l].second == exits.second)) {
                            is_traveler_in = true;
                        }
                    }
                }
                if (is_traveler_in) {
                    sx = x1;
                    sy = y1;
                    square_size = sz;

                    return;
                }
            }
        }
    }
}

// 정사각형 내부의 벽을 회전시킵니다.
void Roll() {
    for (int x = sx; x < sx + square_size; x++)
        for (int y = sy; y < sy + square_size; y++) {
            if (map[x][y]) map[x][y]--;
        }
    for (int x = sx; x < sx + square_size; x++)
        for (int y = sy; y < sy + square_size; y++) {
            int ox = x - sx, oy = y - sy;
            int rx = oy, ry = square_size - ox - 1;
            next_map[rx + sx][ry + sy] = map[x][y];
        }
    for (int x = sx; x < sx + square_size; x++)
        for (int y = sy; y < sy + square_size; y++) {
            map[x][y] = next_map[x][y];
        }
}

//플레이어 회전
void spin_player_exit() {
    for (int i = 1; i <= m; i++) {
        int x = player[i].first;
        int y = player[i].second;
        //플레이어 회전
        if (sx <= x && x < sx + square_size && sy <= y && y < sy + square_size) {
            int ox = x - sx, oy = y - sy;
            int rx = oy, ry = square_size - ox - 1;
            player[i] = make_pair(rx + sx, ry + sy);
        }
    }

    // 출구 회전
    int x = exits.first;
    int y = exits.second;
    if (sx <= x && x < sx + square_size && sy <= y && y < sy + square_size) {
        int ox = x - sx, oy = y - sy;
        int rx = oy, ry = square_size - ox - 1;
        exits = make_pair(rx + sx, ry + sy);
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];

    for (int i = 1; i <= m; i++) {
        cin >> player[i].first;
        cin >> player[i].second;
    }

    cin >> exits.first;
    cin >> exits.second;

    while (k--) {
        All_player_move();
        bool is_valid = true;
        for (int i = 1; i <= m; i++) {
            if (!(player[i].first == exits.first && player[i].second == exits.second)) {
                is_valid = false;
            }
        }
        if (is_valid) break;
        min_square();
        Roll();
        spin_player_exit();
    }

    cout << ans << "\n";
    cout << exits.first << " " << exits.second;
}