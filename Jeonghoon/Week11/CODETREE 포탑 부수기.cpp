#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K;
int map[12][12];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int dirx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int diry[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int flag;
bool isattacked[12][12];
int rec[12][12];

struct Node {
    int y, x;
};

struct Tower {
    int y, x, hp, t;
};

vector<Tower> t;

//행 y, 열 x
bool cmp(Tower a, Tower b) {
    if (a.hp == b.hp) {
        if (a.t == b.t) {
            //열 내림차순
            if ((a.x + a.y) == (b.x + b.y)) return a.x > b.x;
            //행+열 내림차순
            else return (a.x + a.y) > (b.x + b.y);
        }
        //시간 내림차순
        else return a.t > b.t;
    }
    //체력 오름차순
    else return a.hp < b.hp;
}

void input() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
            if (map[i][j] != 0) {
                t.push_back({ i,j,map[i][j],0 });
            }
        }
    }
}

void init() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            isattacked[i][j] = false;
        }
    }
    flag = 0;
}

void lazer() {
    Node tmap[12][12] = { {0,0}, };
    queue<Node> q;
    q.push({ t[0].y, t[0].x });
    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        //타겟에 도착했다면 공격
        if (now.x == t[t.size() - 1].x && now.y == t[t.size() - 1].y) {
            map[now.y][now.x] -= map[t[0].y][t[0].x];
            isattacked[now.y][now.x] = true;

            if (map[now.y][now.x] < 0) {
                map[now.y][now.x] = 0;
            }

            while (1) {
                int oldx = tmap[now.y][now.x].x;
                int oldy = tmap[now.y][now.x].y;

                if (oldx == t[0].x && oldy == t[0].y) return;

                map[oldy][oldx] -= (map[t[0].y][t[0].x] / 2);
                isattacked[oldy][oldx] = true;

                if (map[oldy][oldx] < 0) {
                    map[oldy][oldx] = 0;
                }
                now.x = oldx;
                now.y = oldy;
            }
        }

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            //좌표 넘기기
            if (ny > N) ny %= N;
            if (ny < 1) ny = N;
            if (nx > M) nx %= M;
            if (nx < 1) nx = M;

            //시작점이면 continue
            if (ny == t[0].y && nx == t[0].x) continue;
            //벽이면 continue
            if (map[ny][nx] == 0) continue;
            //이동한 자리에 다른 좌표가 있으면 continue
            if (tmap[ny][nx].y != 0 && tmap[ny][nx].x != 0) continue;

            //큐에 넣고
            q.push({ ny, nx });
            //다음 좌표에 이전에 출발한 좌표 넣기
            tmap[ny][nx] = { now.y, now.x };
        }
    }
    flag = 1;
    return;
}

void cannon() {

    map[t[t.size() - 1].y][t[t.size() - 1].x] -= map[t[0].y][t[0].x];
    isattacked[t[t.size() - 1].y][t[t.size() - 1].x] = true;
    if (map[t[t.size() - 1].y][t[t.size() - 1].x] < 0) {
        map[t[t.size() - 1].y][t[t.size() - 1].x] = 0;
    }

    for (int i = 0; i < 8; i++) {
        int ny = t[t.size() - 1].y + diry[i];
        int nx = t[t.size() - 1].x + dirx[i];

        //좌표 넘기기
        if (ny > N) ny %= N;
        if (ny < 1) ny = N;
        if (nx > M) nx %= M;
        if (nx < 1) nx = M;

        if (ny == t[0].y && nx == t[0].x) continue;

        map[ny][nx] -= (map[t[0].y][t[0].x] / 2);
        isattacked[ny][nx] = true;
        if (map[ny][nx] < 0) {
            map[ny][nx] = 0;
        }
    }
}

void attack() {

    lazer();
    if (flag == 1) {
        cannon();
    }
}

void repair() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] <= 0) continue;
            if (isattacked[i][j] == false) {
                map[i][j] = map[i][j] + 1;
            }
        }
    }
}

void makev() {
    t.clear();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] > 0) {
                t.push_back({ i,j,map[i][j],rec[i][j] });
            }
        }
    }
}

void print() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {

    for (int i = 1; i <= K; i++) {

        if (t.size() == 1) return;

        sort(t.begin(), t.end(), cmp);
        //공격할 타워 공격력, 시간 갱신
        map[t[0].y][t[0].x] += (N + M);
        rec[t[0].y][t[0].x] = i;

        init();
        isattacked[t[0].y][t[0].x] = true;
        attack();
        repair();
        //print();
        if (i < K) makev();
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();
    //print();
    solve();

    int result = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] > result) {
                result = map[i][j];
            }
        }
    }
    cout << result;

    return 0;
}