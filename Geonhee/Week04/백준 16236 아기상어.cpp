#include <iostream>
#include <queue>
using namespace std;
int n;
int baby_shark = 2; //아기 상어 크기
int map[21][21];
int dx[4] = { -1,0,1,0 }; //방향 위 -> 왼쪽 -> 아래 -> 오른쪽
int dy[4] = { 0,-1,0,1 };
int res = 0; // 최종 시간
int cnt = 0; // 물고기 먹은 횟수 
pair<int, int> now; //현재 아기 상어 위치
bool possible = false; //물고기 먹었을 때

void eat() {
    queue<pair<pair<int, int>, int>> q;
    q.push({ now,0 }); //현재 아기 상어 위치와 움직인 시간 넣어주기
    bool check[21][21] = { false };
    check[now.first][now.second] = true; //현재 위치 방문확인
    int temp = 0; //한마리 먹었을 때 걸린 시간

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int nowtime = q.front().second; //현재까지 시간
        //가장 위쪽 먼저 먹고 왼쪽을 먹도록 
        if (map[x][y] > 0 && map[x][y] < baby_shark && temp == nowtime) {
            if (now.first > x || (now.first == x && now.second > y)) {
                now = { x,y }; //물고기 먹은 아기 상어 위치 갱신
                continue;
            }
        }
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < n && nx >= 0 && ny < n && ny >= 0 && !check[nx][ny]) {
                if (map[nx][ny] <= baby_shark) {
                    if (map[nx][ny] > 0 && map[nx][ny] < baby_shark && !possible) {
                        possible = true; //한 마리 꿀꺽
                        now = { nx,ny }; // 물고기 먹은 위치로 갱신
                        temp = nowtime + 1; // 먹은 시간 +1
                        res += temp; // 최종 시간에 더해주기
                    }
                    else { //물고기 못먹었을 때 
                        q.push({ {nx,ny},nowtime + 1 });
                        check[nx][ny] = true;
                    }
                }
            }
        }
    }

}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 9) {
                map[i][j] = 0;
                now = { i,j };
            }
        }
    }
    while (true) {
        eat();
        if (possible) { //먹었을 때
            possible = false;
            cnt++; // 물고기 먹은 횟수 증가
            map[now.first][now.second] = 0; // 먹은 물고기 자리 0
            if (cnt == baby_shark) { //물고기 먹은 횟수가 크기와 같으면
                baby_shark += 1; // 아기 상어 크기 키워주기
                cnt = 0; //물고기 먹은 횟수 초기화
            }
        }
        else { //먹을 게 없을 때
            break; //엄마 상어 Help
        }
    }
    cout << res;
    return 0;
}