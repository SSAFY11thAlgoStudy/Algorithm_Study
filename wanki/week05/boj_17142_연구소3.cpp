#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N, M;
int map[51][51];
int empty_space = 0;
int visit[10]; // 바이러스 선택 여부를 저장하는 배열
int mini = 21e8;
int dy[] = { 0, 0, -1, 1 }, dx[] = { 1, -1, 0, 0 };

struct point {
    int y, x;
};

vector<point> virus;
vector<point> q_insert;

// 입력
void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                empty_space++;
            }
            else if (map[i][j] == 2) {
                virus.push_back({ i,j });
            }
        }
    }
}

// 바이러스가 퍼지는 시간을 확인
int bfs() {
    queue<point> q;
    int visited[51][51] = { 0 };
    int empty = 1;

    for (point p : q_insert) {
        q.push(p);
        visited[p.y][p.x] = 1;
    }

    while (!q.empty()) {
        point now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = dx[i] + now.x;
            int ny = dy[i] + now.y;
            //맵 유무 확인
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            // 바이러스를 만났을때
            // 빈공간이 아니므로 empty를 증가 시키지 않음
            // 너머서도 빈공간이 존재할수 있기때문에 빈공간처럼 활용
            if (map[ny][nx] == 2 && visited[ny][nx] == 0) {
                visited[ny][nx] = visited[now.y][now.x] + 1;
                q.push({ ny,nx });
            }
            //벽이거나, 빈공간이 아닐시 패스
            if (map[ny][nx] == 1 || visited[ny][nx] != 0) continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny,nx });
            empty++;
        }
    }

    /*cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
    cout << empty;*/

    // 모든 빈 공간이 바이러스로 감염되었는지 확인
    if (empty <= empty_space) {
        return -1;
    }

    //원래 바이러스가 있던 자리는 0으로 만듬
    //바이러스의 자리는 원래 감염되어있기에 최대값이 나올시
    // 0을 넣어 줌으로써 최대값을 벗어남
    for (point p : virus) {
        visited[p.y][p.x] = 0;
    }

    // visited를 다 확인하면서 최대값을 찾음 
    // -1인 이유는 1부터 시작하기에 -1을 함
    int maxi = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maxi = max(maxi, visited[i][j] - 1);
        }
    }
    return maxi;
}

// 깊이 우선 탐색을 통해 모든 바이러스 조합을 만들고 최소 시간을 계산하는 함수
void dfs(int node, int start) {
    //기저조건
    //M개의 바이러스 활성화
    if (node == M) {
        int ret = bfs();
        //-1이 아닐때는 최소값을 비교해서 저장
        if (ret != -1) {
            mini = min(mini, ret);
        }
        return;
    }

    //start를 통해 0부터 하는 것보다 중복 요소를 줄일 수 있음
    for (int i = start; i < virus.size(); i++) {
        if (visit[i] == 1) continue;
        visit[i] = 1;
        q_insert.push_back(virus[i]);
        dfs(node + 1, i + 1);
        q_insert.pop_back();
        visit[i] = 0;
    }
}

int main() {
    input();
    dfs(0, 0);


    // mini값이 갱신이 안됬을경우 전부 감염시키는 방법이 없다는 것으로 -1을 출력
    if (mini == 21e8) {
        cout << -1;
    }
    else {
        cout << mini;
    }

    return 0;
}
