#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n, m;
int map[5][5]; 
/*2 <= n <= 4 이지만 
위치 포인트의 좌표는 1,1부터 연산하기에
전체적으로 1,1부터 연산으로 하도록 만듬*/
vector<pair<int, int>>point;
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
int visit[5][5] = { 0, };
int cnt = 0;

//입력
void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }
    int y, x;
    for (int i = 0; i < m; i++) {
        cin >> y >> x;
        point.push_back({ y,x });
    }
}

void solve(int y, int x, int node) {
    //모든 포인트에 도달했을 때 node는 m이된다.
    if (node == m) {
        cnt++;
        return;
    }
    //방문한 포인트에 도달 할때마다  node를 증가 시킴
    if (point[node].first == y && point[node].second == x) {
        solve(y, x, node + 1);
        return;
        //다음 연산이 없으므로 바로 리턴하면서 다음연산으로 바로 보내준다.
    }

    for (int i = 0; i < 4; i++) {
        int ny = dy[i] + y;
        int nx = dx[i] + x;

        // map범위 검사
        if (ny <= 0 || nx <= 0 || ny > n || nx > n)continue;
        if (map[ny][nx] == 1)continue; // 벽
        if (visit[ny][nx] == 1)continue; //방문 확인
        visit[ny][nx] = 1;
        //다음 위치에 대한 dfs를 연산한다.
        solve(ny, nx, node);
        visit[ny][nx] = 0;
    }

}

int main(int argc, char** argv)
{
    input();
    //처음 시작점의 위치는 다시 돌아가지 않도록 visit을 1처리 해준다.
    visit[point[0].first][point[0].second] = 1;
    solve(point[0].first, point[0].second, 1);
    cout << cnt;
    return 0;
}