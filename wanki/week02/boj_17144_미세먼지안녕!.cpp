#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
(1,1)���� (R,C)����!!!!!!!!!!!!

1. �̼������� Ȯ��ȴ�. Ȯ���� �̼������� �ִ� ��� ĭ���� ���ÿ� �Ͼ��.
    a.(r, c)�� �ִ� �̼������� ������ �� �������� Ȯ��ȴ�.
    b.������ ���⿡ ����û���Ⱑ �ְų�, ĭ�� ������ �� �������δ� Ȯ���� �Ͼ�� �ʴ´�.
    c.Ȯ��Ǵ� ���� Ar,c/5�̰� �Ҽ����� ������. ��, ?Ar,c/5?�̴�.
    d.(r, c)�� ���� �̼������� ���� Ar,c - ?Ar,c/5?��(Ȯ��� ������ ����) �̴�.
2.����û���Ⱑ �۵��Ѵ�. ����û���⿡���� �ٶ��� ���´�.
    a.���� ����û������ �ٶ��� �ݽð�������� ��ȯ�ϰ�, �Ʒ��� ����û������ �ٶ��� �ð�������� ��ȯ�Ѵ�.
    b.�ٶ��� �Ҹ� �̼������� �ٶ��� ������ ��� �� ĭ�� �̵��Ѵ�.
    c.����û���⿡�� �δ� �ٶ��� �̼������� ���� �ٶ��̰�, ����û����� �� �̼������� ��� ��ȭ�ȴ�.
*/

struct position {
    int y;
    int x;
    int d = 0;
};
int R, C, T;
int map[51][51];
int dy[] = { 0,-1,0,1 }, dx[] = { 1,0,-1,0 };
position luftreiniger[2];

void print() {
    cout << "\n";
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void fxxking_china() {
    int dust_extend[51][51] = { 0 };

    // �迭 �и�
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            int spread = map[i][j] / 5;
            int cnt = 0;

            for (int d = 0; d < 4; d++) {
                int ny = i + dy[d];
                int nx = j + dx[d];

                if (ny < 1 || ny > R || nx < 1 || nx > C) continue;
                if (map[ny][nx] == -1) continue;

                dust_extend[ny][nx] += spread;
                cnt++;
            }

            dust_extend[i][j] += map[i][j] - (spread * cnt);
        }
    }

    // �ٽ� ä���ֱ�
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            map[i][j] = dust_extend[i][j];
        }
    }


}

void samsung() {

    // ���� ����û����
    int y = luftreiniger[0].y;
    for (int i = y - 1; i > 1; --i) {
        map[i][1] = map[i - 1][1];
    }
    for (int i = 1; i < C; ++i) {
        map[1][i] = map[1][i + 1];
    }
    for (int i = 1; i < y; ++i) {
        map[i][C] = map[i + 1][C];
    }
    for (int i = C; i > 2; --i) {
        map[y][i] = map[y][i - 1];
    }
    map[y][2] = 0;

    // �Ʒ��� ����û����
    y = luftreiniger[1].y;
    for (int i = y + 1; i < R; ++i) {
        map[i][1] = map[i + 1][1];
    }
    for (int i = 1; i < C; ++i) {
        map[R][i] = map[R][i + 1];
    }
    for (int i = R; i > y; --i) {
        map[i][C] = map[i - 1][C];
    }
    for (int i = C; i > 2; --i) {
        map[y][i] = map[y][i - 1];
    }
    map[y][2] = 0;

}
void solve() {
    for (int tc = 0; tc < T; tc++)
    {
        fxxking_china();
        samsung();
        //print();
    }

    int total = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (map[i][j] > 0) {
                total += map[i][j];
            }
        }
    }
    cout << total << '\n';
}
void input() {
    int c = 0;
    cin >> R >> C >> T;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == -1) {
                luftreiniger[c].y = i;
                luftreiniger[c++].x = j;
            }
        }
    }
}


int main() {
    input();
    solve();

    return 0;
}
