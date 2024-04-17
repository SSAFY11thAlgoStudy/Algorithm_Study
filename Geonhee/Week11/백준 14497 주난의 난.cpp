#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
int sy, sx, ey, ex;
char map[304][304];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int res = 0;
bool check = false;

void bfs() {
    //방문배열은 새로 들어올 때 마다 초기화
    //0인 위치들도 다시 돌아야하므로
    bool visited[304][304];
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    //주난이의 위치가 시작점
    q.push({ sy,sx });
    visited[sy][sx] = true;

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];
            //범인 위치 도달하면 check하고 return
            if (ny == ey && nx == ex) {
                check = true;
                return;
            }
            //범위안에 있고 방문하지 않았더라면
            if (ny <= n && ny >= 1 && nx <= m && nx >= 1 && !visited[ny][nx]) {
                //방문확인하고
                visited[ny][nx] = true;
                //1이라면 0으로 바꿔주고
                if (map[ny][nx] == '1') {
                    map[ny][nx] = '0';
                }
                //0이라면 계속 탐색해야하므로 q에 push해주기
                else if (map[ny][nx] == '0') {
                    q.push({ ny,nx });
                }
            }
        }
    }
}

int main() {

    cin >> n >> m >> sy >> sx >> ey >> ex;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
        }
    }
    //찾을때 까지 돌려야함
    while (1) {
        res++;
        bfs();
        if (check)break;
    }
    cout << res;
    return 0;
}
