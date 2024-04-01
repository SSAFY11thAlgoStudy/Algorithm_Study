#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int map[4][4];
bool visited[4][4] = { false };
int res = 0;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
vector<pair<int, int>> car;

void dfs(int y, int x, int cnt) {
    // y,x가 거처야 할 순서에 맞는 좌표이고
    if (y == car[cnt].first && x == car[cnt].second) {
        // cnt 벡터 사이즈와 같으면 거쳐야 할 곳 다 거친 것이므로
        if (cnt == car.size() - 1) {
            //res에 1더해주고 다른 시나리오 찾으러 return
            res++;
            return;
        }
        //마지막 거칠 곳이 아니라면 거쳐야할 곳 갯수 1더해주기
        else cnt++;
    }
    //현재 좌표 방문 체크
    visited[y][x] = true;
    for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];

        if (ny >= n || ny < 0 || nx >= n || nx < 0 || visited[ny][nx] || map[ny][nx] == 1) continue;
        dfs(ny, nx, cnt);
    }
    // 다른 시나리오도 돌아야 하므로 방문체크 해제
    visited[y][x] = false;
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        //거처야 할 곳 벡터에 넣기
        car.push_back({ a - 1,b - 1 });
    }
    //첫번째 부터 시작, 거쳐야 할 곳 갯수
    dfs(car[0].first, car[0].second, 1);
    cout << res;
    return 0;
}
