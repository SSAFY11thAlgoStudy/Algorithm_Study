#include <iostream>
using namespace std;

int n, m, r, c, d, cnt = 0; // cnt = 청소하는 칸의 개수
int robot[50][50];
bool check[50][50] = { false };
int dx[4] = { -1, 0, 1, 0 };  // d=0북, d=1동,d=2남,d=3서
int dy[4] = { 0, 1, 0, -1 };

int main() {
    cin >> n >> m >> r >> c >> d;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> robot[i][j];
        }
    }

    check[r][c] = true; //r,c방문 체크
    cnt = 1; // 1개 청소 완료

    while (true) { //작동 멈출 때 까지
        int x = 0; // 청소했는지 안했는지 판별

        for (int k = 0; k < 4; k++) {
            d = (d + 3) % 4; // (0->3), (3->2), (2->1),(1->0)반시계 90도 회전
            int nx = r + dx[d]; // 방향에 맞게 이동 좌표 업데이트
            int ny = c + dy[d];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || check[nx][ny] || robot[nx][ny] == 1) {
                continue;  // 범위를 벗어나면 continue
            }

            check[nx][ny] = true; //청소 칸 업데이트
            cnt++;  //칸수도 +1
            r = nx; // 다음좌표 업데이트 
            c = ny;
            x = 1; // 청소 확인 
            break;
        }

        if (x == 0) { //청소할 칸이 없을때
            int nx = r - dx[d]; // 방향에 맞게 후진 좌표 업데이트
            int ny = c - dy[d];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || robot[nx][ny] == 1) {
                break; // 벽이거나 범위 넘어가면 바로 종료
            }

            r = nx;  //그게 아니라면 후진
            c = ny;
        }
    }

    cout << cnt;

    return 0;
}