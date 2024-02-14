#include <iostream>
#include <queue>
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
using namespace std;
int main() {
    int n, k;
    int bam[102][102] = { 0 };
    bool check[102][102] = { false };
    cin >> n >> k;
    int a, b;
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        bam[a - 1][b - 1] = 1;  //(1,1)부터 시작인데 (0,0)부터로 시작으로 바꿔주려고
    }
    int cnt = 0; // 게임진행시간
    char c;

    int d = 0; // 방향변환정보
    int x = 0, y = 0; // 시작 좌표
    queue<pair<int, int>> q;
    q.push({ x,y });// 시작 좌표 값 큐에 넣기
    int l;
    cin >> l;
    int t1;
    for (int i = 0; i < l; i++) {
        cin >> t1 >> c;

        while (cnt < t1 || i == l - 1) { //cnt < t1 : 뱀이 아직 이동해야할 시간이 남아 있는 경우
            // i == l-1 : t1을 넘어서도 게임 안끝났으면 게임 끝날 떄 까지 이동해야하므로 
            cnt++;
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < n && nx >= 0 && ny < n && ny >= 0 && !check[nx][ny]) { // 게임 진행 조건
                if (bam[nx][ny] == 1) { //사과를 먹을때
                    bam[nx][ny] = 0;  // 사과 먹어주고
                    q.push({ nx,ny });  // 몸 좌표 추가
                    check[nx][ny] = true; //몸 자리 true
                }
                else { //사과 없을때
                    q.push({ nx,ny });
                    check[nx][ny] = true; // 몸자리 true
                    check[q.front().first][q.front().second] = false; //꼬리 좌표 false
                    q.pop(); //꼬리 좌표 pop
                }
            }
            else { //게임 진행 조건 만족안하면 게임이 끝난 것
                cout << cnt;
                return 0;
            }
            x = nx; //x,y좌표 업데이트
            y = ny;
            if (cnt == t1) { //시간과 같다면
                if (c == 'D') {  // 오른쪽 방향
                    d = (d + 1) % 4; //(0,1) -> (1,0) -> (0,-1) -> (-1,0)
                }
                else { //왼쪽 방향
                    d = (d + 3) % 4; // (0,1) -> (-1,0) -> (0,-1) -> (1,0)
                }
            }
        }
    }
    return 0;
}