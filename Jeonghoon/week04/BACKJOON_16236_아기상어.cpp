#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

/*
1. �Է��� �����鼭 ������ ũ��� ��ġ�� ���Ϳ� �����Ѵ�.
2. �ڽź��� ���� ũ���� ������ ��ġ�� �����Ѵ�.
3. ť�� �̿��� BFS�� �̵��Ѵ�
4. �̵��Ҷ� �ɸ��� �ð��� ���� �����Ѵ�.
5. �̵��ϸ鼭 ���ϴ� ��� �����Ѵ�.
6. Ÿ����ġ�� �̵��ؼ� ������ ������ �ð��� ��ü �ð��� �����Ѵ�.
7. ���� ���� ���� ũ��� ������ Ȯ���ϰ� ũ�⸦ �ø���.
*/

using namespace std;

struct target {
    int y, x, sz, dist;
};

struct Point {
    int y, x;
};

vector<target> t;

int N, M;
int map[20][20];
int sp_x, sp_y;
int s_sz = 2;
int flag, cnt;
int eat_cnt;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, -1, 0, 1 };

//������ �ٽ�
//�־��� ���Ǵ�� �����ϱ�
//�Ÿ� - y��ǥ - x��ǥ
bool cmp(target a, target b) {
    if (a.dist == b.dist) {
        if (a.y == b.y) {
            return a.x < b.x;
        }
        return a.y < b.y;
    }
    return a.dist < b.dist;
}

void input() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];

            //����� �������� �����ϰ� �� �ڸ��� 0���� �ٲ� �� �� �ִ� �ڸ��� ����� ��
            if (map[i][j] == 9) {
                sp_x = j;
                sp_y = i;
                map[i][j] = 0;
            }
        }
    }
}

void init(int y, int x) {
    // �ܰ踶�� �Ÿ��� �ٽ� �Է��� ����ϹǷ�
    //�ʱ�ȭ�� ����
    t.clear();

    //queue�� �̿��� BFS
    queue<Point> tp;
    tp.push({ y,x });

    int vis[20][20] = {};

    //���������� 1�� ǥ��
    vis[y][x] = 1;
    while (!tp.empty()) {
        Point now = tp.front();
        tp.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (nx >= N || ny >= N || nx < 0 || ny < 0) continue;

            if (map[ny][nx] > s_sz) continue;

            if (vis[ny][nx] != 0) continue;

            //����Ⱑ ������ ���Ϳ� y, x, ũ��, �Ÿ� �Է�
            if (map[ny][nx] != 0) {
                int dist = vis[now.y][now.x];
                t.push_back({ ny, nx , map[ny][nx], dist });
            }

            //���� �ڸ��� �Ÿ�+1�Ͽ� ����
            vis[ny][nx] = vis[now.y][now.x] + 1;
            tp.push({ ny,nx });
        }
    }

    //���� ����Ⱑ ������ �ݺ��� ���Ḧ ���� flag=1
    if (t.size() == 0) {
        flag = 1;
        return;
    }
}

void solve() {
    target eat = {};

    //Ÿ�� ã��
    //���� ����� �Ÿ��� ���� �� �ִ� ����⸦ ã���� break
    for (int i = 0; i < t.size(); i++) {
        if (t[i].sz < s_sz) {
            eat.x = t[i].x;
            eat.y = t[i].y;
            eat.sz = t[i].sz;
            eat.dist = t[i].dist;
            t.erase(t.begin() + i);
            break;
        }
    }

    //������ ������ ���� �� �ִ°��� ������ ������� 0�ϰ����Ƿ�
    //�̶� ���������� flag =1
    if (eat.sz == 0) {
        flag = 1;
        return;
    }

    //�԰��� ũ�� ���� ���� Ȯ��
    eat_cnt++;
    if (eat_cnt == s_sz) {
        s_sz++;
        eat_cnt = 0;
    }

    //���ο� ���� ����Ʈ ����
    sp_y = eat.y;
    sp_x = eat.x;

    //���� �ڸ��� 0���� ������ֱ�
    map[eat.y][eat.x] = 0;

    //���ݱ��� �̵��� �ð��� �� �ڸ����� ���� �Ÿ� ���ϱ�
    cnt = cnt + eat.dist;
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();

    while (flag == 0) {
        init(sp_y, sp_x);
        //Ÿ�ٵ� �����ϱ�
        sort(t.begin(), t.end(), cmp);
        solve();
    }

    cout << cnt;

    return 0;
}