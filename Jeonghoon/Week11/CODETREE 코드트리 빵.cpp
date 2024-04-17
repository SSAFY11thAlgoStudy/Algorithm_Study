#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int n, m;
//�ð�
int t = 1;
int map[17][17];
bool isarrived[32];
int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { -1, 0, 0, 1 };

struct Node {
    int ty, tx, y, x;
};

struct Point {
    int y, x;
};

vector<Node> p;

void input() {
    cin >> n >> m;

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (i == 0 || j == 0 || i == n + 1 || j == n + 1) {
                map[i][j] = 2;
            }
            else {
                cin >> map[i][j];
            }
        }
    }

    p.push_back({ 0,0 });
    for (int i = 1; i <= m; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        p.push_back({ t1,t2, 0, 0 });
    }
}

void movep(int ind) {
    for (int i = 1; i <= ind; i++) {

        if (isarrived[i] == true) continue;

        //���� ��ġ
        int sx = p[i].x;
        int sy = p[i].y;
        int dir = 0;

        Point visited[17][17] = { {0,0}, };
        queue<Point> q;
        q.push({ sy,sx });
        visited[sy][sx] = { 0,0 };

        while (!q.empty()) {

            Point now = q.front();
            q.pop();

            if (now.y == p[i].ty && now.x == p[i].tx) {
                while (1) {
                    int oldx = visited[now.y][now.x].x;
                    int oldy = visited[now.y][now.x].y;

                    if (oldx == sx && oldy == sy) {
                        if ((now.y - sy) == -1) {
                            dir = 0;
                        }
                        else if ((now.x - sx) == -1) {
                            dir = 1;
                        }
                        else if ((now.x - sx) == 1) {
                            dir = 2;
                        }
                        else if ((now.y - sy) == 1) {
                            dir = 3;
                        }
                        break;
                    }
                    now.x = oldx;
                    now.y = oldy;
                }
                break;
            }

            for (int d = 0; d < 4; d++) {
                int ny = now.y + dy[d];
                int nx = now.x + dx[d];

                if (map[ny][nx] == 2) continue;
                if (visited[ny][nx].x != 0 && visited[ny][nx].y != 0) continue;

                q.push({ ny,nx });
                visited[ny][nx] = { now.y, now.x };
            }
        }
        p[i].x = p[i].x + dx[dir];
        p[i].y = p[i].y + dy[dir];

        if (p[i].x == p[i].tx && p[i].y == p[i].ty) {
            isarrived[i] = true;
        }
    }
}

void putp(int ind) {
    int mindist = 10000;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == 1) {
                int visited[17][17] = { 0, };
                queue<Point> q;
                q.push({ i,j });
                visited[i][j] = 1;

                while (!q.empty()) {
                    Point now = q.front();
                    q.pop();

                    if (now.y == p[ind].ty && now.x == p[ind].tx) {
                        if (mindist > visited[now.y][now.x]) {
                            mindist = visited[now.y][now.x];
                            p[ind].x = j;
                            p[ind].y = i;
                        }
                        break;
                    }

                    for (int d = 0; d < 4; d++) {
                        int ny = now.y + dy[d];
                        int nx = now.x + dx[d];

                        if (map[ny][nx] == 2 || visited[ny][nx] != 0) continue;

                        q.push({ ny,nx });
                        visited[ny][nx] = visited[now.y][now.x] + 1;
                    }
                }
            }
            if (mindist == 1) break;
        }
        if (mindist == 1) break;
    }
    //����� ���̽�ķ�� ������ ó��
    map[p[ind].y][p[ind].x] = 2;
}

void checkarrive() {
    for (int i = 1; i <= m; i++) {
        if (isarrived[i] == true) map[p[i].ty][p[i].tx] = 2;
    }
}

bool checkend() {
    for (int i = 1; i <= m; i++) {
        if (isarrived[i] == false) return false;
    }
    return true;
}

void solve() {

    while (1) {
        //2�� ���� �����̴� ����� ����
        if (t > 1) {
            //t�� m�� �Ѿ�� m�� �����̸� �Ǵ� m������ �̵�
            if (t > m) movep(m);
            //t-1�������� ����� ���̽�ķ���� �����Ƿ� �̵�����
            else movep(t - 1);
        }

        checkarrive();
        //m�� ���Ŀ��� ���̽�ķ���� �־��� �ʿ䰡 ����
        if (t <= m) {
            //t�� ����� ���̽�ķ���� �ֱ�
            putp(t);
        }

        if (checkend()) break;
        t++;
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();
    solve();
    cout << t;

    return 0;
}