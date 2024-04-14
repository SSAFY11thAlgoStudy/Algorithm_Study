#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, P, C, D;
int t = 1;
int map[52][52];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int d_cnt;

struct Santa {
    int num, y, x;
};

vector<Santa> s;
Santa rd;
int score[32];
int stun[32];
int isalive[32];

bool cmp(Santa a, Santa b) {
    return a.num < b.num;
}

void input() {

    cin >> N >> M >> P >> C >> D;

    cin >> rd.y >> rd.x;
    map[rd.y][rd.x] = -1;

    s.push_back({ 0,0,0 });
    for (int i = 1; i <= P; i++) {
        int t_n, t_y, t_x;
        cin >> t_n >> t_y >> t_x;
        s.push_back({ t_n, t_y, t_x });
        map[t_y][t_x] = t_n;
    }

    sort(s.begin(), s.end(), cmp);
}

void inter(int sy, int sx, int diry, int dirx, int flag) {

    int num = map[sy][sx];
    int nx = 0;
    int ny = 0;

    if (map[sy][sx] > 0) {

        if (flag == 1) {
            nx = sx + dirx;
            ny = sy + diry;
        }

        if (flag == 0) {
            nx = sx - dirx;
            ny = sy - diry;
        }

        if (ny > N || nx > N || ny <= 0 || nx <= 0) {
            isalive[num] = 1;
            s[map[ny][nx]].x = 0;
            s[map[ny][nx]].y = 0;
        }
        else {
            inter(ny, nx, diry, dirx, flag);
            s[num].x = nx;
            s[num].y = ny;
            map[ny][nx] = map[sy][sx];
        }
    }

}

void moveRd(int ty, int tx, int ind) {

    //���� ���ϱ�
    int dirx = 0;
    if (rd.x > tx) {
        dirx = -1;
    }
    else if (rd.x < tx) {
        dirx = 1;
    }

    int diry = 0;
    if (rd.y > ty) {
        diry = -1;
    }
    else if (rd.y < ty) {
        diry = 1;
    }

    //�̵�
    map[rd.y][rd.x] = 0;
    rd.x += dirx;
    rd.y += diry;
    map[rd.y][rd.x] = -1;

    //�絹���� ��Ÿ �浹
    if (rd.x == tx && rd.y == ty) {
        int nx = tx + C * dirx;
        int ny = ty + C * diry;

        stun[ind] = t + 2;
        score[ind] += C;

        //���� ����� ����
        if (ny > N || nx > N || ny <= 0 || nx <= 0) {
            isalive[ind] = 1;
            s[ind].x = 0;
            s[ind].y = 0;
            d_cnt++;
        }
        else {//������ ����� ���� ���

            if (map[ny][nx] != 0) {
                inter(ny, nx, diry, dirx, 1);
                s[ind].x = nx;
                s[ind].y = ny;
                map[ny][nx] = s[ind].num;
            }
            else {
                map[ny][nx] = s[ind].num;
                s[ind].x = nx;
                s[ind].y = ny;
            }
        }
    }
}

void moveSt() {

    for (int i = 1; i <= P; i++) {

        //������ ������ �Ѿ
        if (t < stun[i]) continue;
        if (isalive[i] == 1) continue;

        int dist = (rd.x - s[i].x) * (rd.x - s[i].x) + (rd.y - s[i].y) * (rd.y - s[i].y);

        //��Ÿ ����
        int dirx = 0;
        int diry = 0;

        int ny = 0;
        int nx = 0;

        for (int j = 0; j < 4; j++) {

            ny = s[i].y + dy[j];
            nx = s[i].x + dx[j];

            //��
            if (ny > N || nx > N || ny <= 0 || nx <= 0) continue;

            //�ٸ� ��Ÿ
            if (map[ny][nx] > 0) continue;

            //�̵��� ���� �絹�� �Ÿ�
            int ndist = (rd.x - nx) * (rd.x - nx) + (rd.y - ny) * (rd.y - ny);

            if (dist > ndist) {
                dist = ndist;
                dirx = dx[j];
                diry = dy[j];
            }
        }

        ny = s[i].y + diry;
        nx = s[i].x + dirx;

        if (dirx != 0 || diry != 0) {
            //���� �ִ� �ڸ� ���
            map[s[i].y][s[i].x] = 0;

            if (rd.x == nx && rd.y == ny) {
                stun[i] = t + 2;
                score[i] += D;

                ny -= diry * D;
                nx -= dirx * D;

                //���� ����� ����
                if (ny > N || nx > N || ny <= 0 || nx <= 0) {
                    isalive[i] = 1;
                    s[i].x = 0;
                    s[i].y = 0;
                    d_cnt++;
                }
                else {//������ ����� ���� ���

                    //�ٸ� ��Ÿ�� ������ ��ȣ�ۿ�
                    if (map[ny][nx] != 0) {
                        inter(ny, nx, diry, dirx, 0);
                        s[i].x = nx;
                        s[i].y = ny;
                        map[ny][nx] = s[i].num;
                    }
                    else {
                        map[ny][nx] = s[i].num;
                        s[i].x = nx;
                        s[i].y = ny;
                    }
                }
            }
            else {
                map[ny][nx] = s[i].num;
                s[i].x = nx;
                s[i].y = ny;
            }
        }
    }
}

void solve() {

    while (t <= M) {

        //Ÿ��ã��
        int mindist = 6000;
        int tar_x = 0;
        int tar_y = 0;
        int tar_ind = 0;

        for (int i = 1; i <= P; i++) {

            if (isalive[i] == 1) continue;

            int dist_x = (rd.x - s[i].x);
            int dist_y = (rd.y - s[i].y);
            int dist = (dist_x * dist_x) + (dist_y * dist_y);

            if (dist < mindist) {
                mindist = dist;
                tar_x = s[i].x;
                tar_y = s[i].y;
                tar_ind = i;
            }
            else if (dist == mindist) {

                if (tar_y < s[i].y) {
                    tar_x = s[i].x;
                    tar_y = s[i].y;
                    tar_ind = i;
                }
                else if (tar_y == s[i].y) {
                    if (tar_x < s[i].x) {
                        tar_x = s[i].x;
                        tar_y = s[i].y;
                        tar_ind = i;
                    }
                }
            }
        }

        //�絹�� �̵�
        moveRd(tar_y, tar_x, tar_ind);
        //��Ÿ�̵�
        moveSt();

        //��Ƴ��� ��� ������ ��
        if (d_cnt == P)break;

        //��Ƴ��� ��� ���� ����
        for (int i = 1; i <= P; i++) {
            if (isalive[i] == 1)continue;
            score[s[i].num]++;
        }

        //�ð� ����
        t++;
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);
    input();
    solve();
    for (int i = 1; i <= P; i++) {
        cout << score[i] << " ";
    }
    return 0;
}