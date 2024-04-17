#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

int N;
int map[126][126];
int result;
int vis[126][126];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

struct Node {
    int y, x;
};

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vis[i][j] = 21e8;
        }
    }
}

void solve() {
    init();
    queue<Node> q;
    q.push({ 0,0 });
    vis[0][0] = map[0][0];

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

            if (vis[ny][nx] <= (vis[now.y][now.x] + map[ny][nx])) continue;

            vis[ny][nx] = vis[now.y][now.x] + map[ny][nx];
            q.push({ ny, nx });
        }
    }
    result = vis[N - 1][N - 1];
}

int main() {

    //freopen("sample.txt", "r", stdin);

    int cnt = 0;
    while (1) {
        cin >> N;
        if (N == 0) break;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
            }
        }
        cnt++;
        solve();
        cout << "Problem " << cnt << ": " << result << endl;
    }

    return 0;
}