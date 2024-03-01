#include <iostream>
#include <queue>
#include <vector>
#include <cmath> 
#include <cstring> 
using namespace std;

int n, l, r;
int map[50][50];
bool visited[50][50];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };


bool bfs(int x, int y) {
    queue<pair<int, int>> q;
    vector<pair<int, int>> united; //좌표값 넣을 벡터
    int temp = 0; //연합 국가인구 수
    int cnt = 0; // 연합 국가 수

    q.push({ x, y });
    visited[x][y] = true; // 현재 나라 방문체크
    united.push_back({ x, y }); // 좌표 벡터에 넣어주기
    temp += map[x][y]; // 총 국가 인구 수에 더해주고
    cnt++; //국가 수 ++

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

            if (!visited[nx][ny]) {
                if (abs(map[x][y] - map[nx][ny]) >= l && abs(map[x][y] - map[nx][ny]) <= r) {
                    q.push({ nx, ny });
                    visited[nx][ny] = true; //방문체크
                    united.push_back({ nx, ny }); //연합 나라 좌표 벡터에 넣어주기
                    temp += map[nx][ny]; //현재 나라 인구 수 더해주고
                    cnt++; //국가 수 ++
                }
            }
        }
    }

    if (cnt > 1) { //연합이 있다면
        int avg = temp / cnt; // 평균 구해서
        for (auto i : united) {
            map[i.first][i.second] = avg; //좌표 꺼내서 모두 넣어주기
        }
        return true;
    }
    else { //연합이 없다면 인구이동 x
        return false;
    }
}



int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }

    int res = 0; //며칠 동안 발생하는지 저장
    bool possible = true; // 인구 이동이 발생할 수 있는가

    while (possible) {
        possible = false;
        memset(visited, false, sizeof(visited)); //인구이동하고 초기화 

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) { //방문안한 것에 대해
                    if (bfs(i, j)) { // true를 반환하면
                        possible = true; // 인구 이동이 가능하다.
                    }
                }
            }
        }

        if (possible) res++; // true이면 인구이동한 것이므로 res++
    }
    cout << res;

    return 0;
}
