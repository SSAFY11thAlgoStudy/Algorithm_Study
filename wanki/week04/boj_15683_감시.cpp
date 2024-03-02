#include<iostream>
#include<vector>
#include<string>

using namespace std;

int N, M;
int map[8][8];
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }; // 상 우 하 좌;
int MIN = 65;
//1 한쪽방향, 4
//2 두방향(반대 방향) 가지수 2
//3 두방향 직각 가지수 4
//4 3방향 가지수4
//5 4방향 가지수 1
//6 벽
struct point
{
    int y;
    int x;
};

vector<point>v;

//출력
int counting() {
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] == 0) {
                cnt++;
            }
        }
    }
    return cnt;
}

void watch_check(int x, int y, int dir) {
    dir %= 4;
    for (int i = 0; i < 8; i++)
    {
        //다음 방향 * 끝까지
        int nx = x + dx[dir] * i;
        int ny = y + dy[dir] * i;
        //범위 
        if (nx < 0 || ny < 0 || nx >= N || ny >= M) return;
        //벽
        if (map[nx][ny] == 6) return;
        //다른 CCTV확인시 패스
        if (map[nx][ny] != 0) continue;
        map[nx][ny] = -1;
    }
}

void dfs(int node) {
    //모든 카메라를 다 확인했으면 최소값을 확인하고 리턴
    if (node == v.size()) {
        MIN = min(MIN, counting());
        return;
    }

    int y = v[node].y;
    int x = v[node].x;
    int temp[8][8];
    for (int dir = 0; dir < 4; dir++) {
        //temp배열에 백트레킹전의 상태를 저장
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                temp[i][j] = map[i][j];
            }
        }

        //1 한쪽방향
        if (map[x][y] == 1) {
            watch_check(x, y, dir);
        }

        //2 두방향(반대 방향)
        else if (map[x][y] == 2) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 2);
        }

        //3 두방향 직각
        else if (map[x][y] == 3) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
        }

        //4 3방향
        else if (map[x][y] == 4) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
            watch_check(x, y, dir + 2);
        }

        //5 4방향
        else if (map[x][y] == 5) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
            watch_check(x, y, dir + 2);
            watch_check(x, y, dir + 3);
        }
        //재귀
        dfs(node + 1);

        //기존 값 복원
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = temp[i][j];
            }
        }
    }
}

//입력
void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
            if (map[i][j] >= 1 && map[i][j] < 6) {
                v.push_back({ i,j });
            }
        }
    }
}


int main() {
    input();
    //시작 노드는 0부터, 카메라위치 배열은 0부터시작
    dfs(0);
    cout << MIN;
}