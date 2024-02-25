#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include<queue>

using namespace std;
// 어떻게 짤것인가?
// 1. 입력받기
// 2. copyMAP을 만들고 복사하기(자신보다 크기가 큰 물고기들 제외)
// 3. copyMAP을 기반으로 disMAP 플러드맵으로 만들기
// 4. 먹을수 있는 물고기들만 입력 후 거리 갱신
// 5. 6번까지 진행하면 가장 먼저 먹어야 하는 물고기 나옴 pop으로 제외
// 6. 그 dis값들을 모두 더하면 이동시간이 나온다.

struct Node {
    int y;
    int x;
};

struct pos {
    int y;
    int x;
    int dis;

    void setDistance(int _dis) {
        dis = _dis;
    }

    bool operator<(pos right) const {
        // 사이즈가 작은 순서대로
        //if (size > right.size) return true;
        //if (size < right.size) return false;

        // 사이즈가 같은 경우 거리 비교
        if (dis > right.dis) return true;
        if (dis < right.dis) return false;

        // 사이즈가 같은 경우 y 비교
        if (y > right.y) return true;
        if (y < right.y) return false;

        // y가 같은 경우 x 비교
        if (x > right.x) return true;
        if (x < right.x) return false;
        return false;
    };
};

int N;
int T;
int sy;
int sx;
int sharksize = 2;
int MAP[21][21];
int copyMAP[21][21];
int disMAP[21][21];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int visited[21][21];
int eatCnt;
int breakFor;
int notFirst;

priority_queue<pos>fish;
priority_queue<pos>DATfish;

void floodfill(int y, int x) {

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            copyMAP[i][j] = MAP[i][j];
        }
    }
    // 상어 크기보다 크면 요소를 -1로 변경
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // -1로 장애물 설치
            if (copyMAP[i][j] > sharksize) {
                copyMAP[i][j] = -1;
            }
        }
    }

    // 플러드필을 통해 거리 갱신 
    // 갈수 없는 곳 파악
    queue<Node>q;
    q.push({ y,x });
    visited[y][x] = 1;
    disMAP[y][x] = 1;

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
            if (visited[ny][nx] != 0)continue;
            if (copyMAP[ny][nx] == -1)continue;

            q.push({ ny,nx });
            visited[ny][nx] = visited[now.y][now.x] + 1;
            disMAP[ny][nx] = visited[ny][nx];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // 먹을 수 있는 물고기들로만 PQ 저장
            if (copyMAP[i][j] != 0 && disMAP[i][j] != 0 && copyMAP[i][j] != -1 && copyMAP[i][j] < sharksize) {
                fish.push({ i, j, 0 });
            }
        }
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            visited[i][j] = 0;
        }
    }

    if (fish.size() != 0) {

        // 지금 아기상어 위치에서 먹을 수 있는 물고기들 파악
        while (!fish.empty()) {
            notFirst = 1;
            pos current = fish.top();
            current.dis = disMAP[current.y][current.x] - 1;
            DATfish.push({ current.y, current.x, current.dis });
            fish.pop();
        }

        pos eatfish = DATfish.top();
        DATfish.pop();
        while (!DATfish.empty()) {
            DATfish.pop();
        }
        T += eatfish.dis;
        MAP[eatfish.y][eatfish.x] = 0;
        sy = eatfish.y;
        sx = eatfish.x;
        eatCnt++;
        if (eatCnt == sharksize) {
            sharksize++;
            eatCnt = 0;
        }
    }
    else {
        breakFor = 1;
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 9) {
                // 아기상어 처음 위치 저장
                MAP[i][j] = 0;
                sy = i;
                sx = j;
            }
        }
    }
    for (int i = 0; i < 400; i++)
    {
        if (breakFor == 1) {
            break;
        }
        floodfill(sy, sx);
    }
    cout << T;
}