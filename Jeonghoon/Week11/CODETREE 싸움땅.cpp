#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, m, k;
vector<int> map[22][22];
int pmap[22][22];
int gun[31];
int score[31];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

struct Player {
    int y, x;
    int d, s;
};

vector<Player> p;

bool cmp(int a, int b) {
    return a > b;
}

void input() {
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int g;
            cin >> g;
            map[i][j].push_back(g);
        }
    }

    p.push_back({});
    for (int i = 1; i <= m; i++) {
        int t1, t2, t3, t4;
        cin >> t1 >> t2 >> t3 >> t4;
        p.push_back({ t1,t2,t3,t4 });
        pmap[t1][t2] = i;
    }
}

void guncmp(int ind) {
    int temp = gun[ind];
    gun[ind] = map[p[ind].y][p[ind].x][0];
    map[p[ind].y][p[ind].x][0] = temp;
    sort(map[p[ind].y][p[ind].x].begin(), map[p[ind].y][p[ind].x].end(), cmp);
}

//����� �̵��ϴ� �Լ�
void lmove(int ind) {
    //�� �����α�
    if (gun[ind] != 0) {
        map[p[ind].y][p[ind].x].push_back(gun[ind]);
        sort(map[p[ind].y][p[ind].x].begin(), map[p[ind].y][p[ind].x].end(), cmp);
        gun[ind] = 0;
    }

    //�̵�
    for (int i = 0; i < 4; i++) {
        int ny = p[ind].y + dy[(p[ind].d + i) % 4];
        int nx = p[ind].x + dx[(p[ind].d + i) % 4];

        if (ny > n || nx > n || ny <= 0 || nx <= 0) continue;
        if (pmap[ny][nx] != 0) continue;

        pmap[ny][nx] = ind;
        p[ind].y = ny;
        p[ind].x = nx;

        if (map[p[ind].y][p[ind].x][0] > gun[ind]) {
            guncmp(ind);
        }
        p[ind].d = (p[ind].d + i) % 4;
        break;
    }
}

void fight(int p1, int p2) {

    int p1power = p[p1].s + gun[p1];
    int p2power = p[p2].s + gun[p2];

    //p1�� �̱�ٸ�
    if (p1power > p2power) {
        lmove(p2);
        pmap[p[p1].y][p[p1].x] = p1;
        score[p1] += p1power - p2power;
        if (map[p[p1].y][p[p1].x][0] > gun[p1]) {
            guncmp(p1);
        }
    }
    else if (p1power < p2power) {
        lmove(p1);
        score[p2] += p2power - p1power;
        if (map[p[p2].y][p[p2].x][0] > gun[p2]) {
            guncmp(p2);
        }
    }
    else {
        if (p[p1].s > p[p2].s) {
            lmove(p2);
            pmap[p[p1].y][p[p1].x] = p1;
            if (map[p[p1].y][p[p1].x][0] > gun[p1]) {
                guncmp(p1);
            }
        }
        else {
            lmove(p1);
            if (map[p[p2].y][p[p2].x][0] > gun[p2]) {
                guncmp(p2);
            }
        }
    }
}

void move(int ind) {
    //������ �������� �̵�
    int ny = p[ind].y + dy[p[ind].d];
    int nx = p[ind].x + dx[p[ind].d];

    //���̶�� �ݴ�������� �ٲ㼭 �̵�
    if (ny > n || nx > n || ny <= 0 || nx <= 0) {
        p[ind].d = (p[ind].d + 2) % 4;
        ny = p[ind].y + dy[p[ind].d];
        nx = p[ind].x + dx[p[ind].d];
    }

    //���� �ڸ� �����
    pmap[p[ind].y][p[ind].x] = 0;

    //�� ��ǥ�� �̵�
    p[ind].y = ny;
    p[ind].x = nx;

    //������ �Ѻ��� ���� ���� �� ���ϸ� ��ü
    if (pmap[p[ind].y][p[ind].x] == 0) {
        if (map[p[ind].y][p[ind].x][0] > gun[ind]) {
            guncmp(ind);
        }
        pmap[p[ind].y][p[ind].x] = ind;
    }
    //�ٸ� ����� ������ �ο�
    else {
        fight(ind, pmap[p[ind].y][p[ind].x]);
    }
}

void solve() {

    for (int turn = 1; turn <= k; turn++) {
        for (int i = 1; i < p.size(); i++) {
            move(i);
        }
    }
}

int main() {

    freopen("sample.txt", "r", stdin);

    input();
    solve();

    for (int i = 1; i <= m; i++) {
        cout << score[i] << " ";
    }

    return 0;
}