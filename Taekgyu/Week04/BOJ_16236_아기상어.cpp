#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include<queue>

using namespace std;
// ��� ©���ΰ�?
// 1. �Է¹ޱ�
// 2. copyMAP�� ����� �����ϱ�(�ڽź��� ũ�Ⱑ ū ������ ����)
// 3. copyMAP�� ������� disMAP �÷�������� �����
// 4. ������ �ִ� �����鸸 �Է� �� �Ÿ� ����
// 5. 6������ �����ϸ� ���� ���� �Ծ�� �ϴ� ����� ���� pop���� ����
// 6. �� dis������ ��� ���ϸ� �̵��ð��� ���´�.

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
        // ����� ���� �������
        //if (size > right.size) return true;
        //if (size < right.size) return false;

        // ����� ���� ��� �Ÿ� ��
        if (dis > right.dis) return true;
        if (dis < right.dis) return false;

        // ����� ���� ��� y ��
        if (y > right.y) return true;
        if (y < right.y) return false;

        // y�� ���� ��� x ��
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
    // ��� ũ�⺸�� ũ�� ��Ҹ� -1�� ����
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // -1�� ��ֹ� ��ġ
            if (copyMAP[i][j] > sharksize) {
                copyMAP[i][j] = -1;
            }
        }
    }

    // �÷������� ���� �Ÿ� ���� 
    // ���� ���� �� �ľ�
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
            // ���� �� �ִ� ������θ� PQ ����
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

        // ���� �Ʊ��� ��ġ���� ���� �� �ִ� ������ �ľ�
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
                // �Ʊ��� ó�� ��ġ ����
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