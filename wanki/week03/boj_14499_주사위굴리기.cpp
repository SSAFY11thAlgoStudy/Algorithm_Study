#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//동쪽 1, 서쪽 2, 북쪽3, 남쪽4
int dy[] = { 0,0,0,-1,1 }, dx[] = { 0,1,-1,0,0 };
int N, M, x, y, K;
int map[21][21];
int dice[7] = { 0 };
queue<int> q;


void moveDice(int dir) {
    int temp;
    if (dir == 1) { // 동쪽 이동
        temp = dice[6];
        dice[6] = dice[3];
        dice[3] = dice[1];
        dice[1] = dice[4];
        dice[4] = temp;
    }
    else if (dir == 2) { // 서쪽 이동
        temp = dice[4];
        dice[4] = dice[1];
        dice[1] = dice[3];
        dice[3] = dice[6];
        dice[6] = temp;
    }
    else if (dir == 3) { // 북쪽 이동
        temp = dice[2];
        dice[2] = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[6];
        dice[6] = temp;
    }
    else if (dir == 4) { // 남쪽 이동
        temp = dice[6];
        dice[6] = dice[5];
        dice[5] = dice[1];
        dice[1] = dice[2];
        dice[2] = temp;
    }
}

void solve() {
    //처음 위치 삽입
    dice[1] = map[y][x];

    //q 명령어를 담음, 명령어가 끝날때까지 동작
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        //범위 유효성 검사
        int ny = y + dy[now];
        int nx = x + dx[now];

        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;

        y = ny;
        x = nx;


        moveDice(now); // 주사위 이동


//1. 주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면,
//  주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 
//2. 0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며,
// 칸에 쓰여 있는 수는 0이 된다.
        if (map[y][x] == 0) {
            map[y][x] = dice[1];
        }
        else {
            dice[1] = map[y][x];
            map[y][x] = 0;
        }

        //출력
        cout << dice[6] << " \n";
    }
}


void input() {
    //첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1≤ N, M ≤ 20),
    //주사위를 놓은 곳의 좌표 x, y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1),
    //그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.
    int cmd;
    cin >> N >> M >> y >> x >> K;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < K; i++)
    {
        cin >> cmd;
        q.push(cmd);
    }
}


int main() {
    input();
    solve();

    return 0;
}