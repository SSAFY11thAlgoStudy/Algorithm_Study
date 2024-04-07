#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;
/*
N: �������� ũ�� (3��N��50)
M: ���� �� �� (1��M��1000)
P: ��Ÿ�� �� (1��P��30)
C: �絹���� �� (1��C��N)
D: ��Ÿ�� �� (1��D��N)
*/
int N, C, D, M, P;
int out_count = 0; //turn  
int map[101][101] = { 0 }; //(1,1) ~ (N,N)
int santa_diry[4] = { -1,0,1,0 }, santa_dirx[4] = { 0,1,0,-1 };

struct point {
    int num;
    int y, x;
    int state; // ������ �� �ִ� ��Ȳ�̰ų� ���� �������� Ȯ���ϱ����� ����
    int score;
};
bool sorted(point a, point b) {
    return a.num < b.num;
}
struct closepoint {
    int y, x;
    int dist;
};
struct cmp {
    bool operator() (closepoint a, closepoint b) {
        if (a.dist == b.dist) {
            if (a.y == b.y) {
                return a.x < b.x;
            }
            return a.y < b.y;
        }
        return a.dist > b.dist;
    }
};

vector<point>santas;
point rudolf;

//�Է�
void input() {
    santas.push_back({ 0,0,0,0,0 });
    cin >> N >> M >> P >> C >> D;
    cin >> rudolf.y >> rudolf.x;
    for (int i = 1; i <= P; i++)
    {
        int num, y, x;
        cin >> num >> y >> x;
        santas.push_back({ num,y,x,0,0 });
        map[y][x] = num;
    }
    sort(santas.begin(), santas.end(), sorted);
}

void bound(int num, int y, int x) {
    int next = map[santas[num].y][santas[num].x];
    map[santas[next].y][santas[next].x] = 0;
    santas[next].y += y;
    santas[next].x += x;
    if (santas[next].y <= 0 || santas[next].y > N || santas[next].x <= 0 || santas[next].x > N) {
        santas[next].state = -1;
        out_count++;
        return;
    }
    if (map[santas[next].y][santas[next].x] != 0) {
        bound(next, y, x);
    }
    map[santas[next].y][santas[next].x] = next;
}

//�絹�� �̵�
void rudolf_move() {
    priority_queue<closepoint, vector<closepoint>, cmp>pq;
    int dist;
    for (int i = 1; i <= P; i++)
    {
        if (santas[i].state == -1) continue;
        dist = pow(rudolf.y - santas[i].y, 2) + pow(rudolf.x - santas[i].x, 2);

        pq.push({ santas[i].y , santas[i].x ,dist });
    }

    closepoint tar = pq.top();
    int y = 0, x = 0;
    if ((rudolf.y - tar.y) < 0) { y = 1; }
    else if ((rudolf.y - tar.y) > 0) { y = -1; }
    if ((rudolf.x - tar.x) < 0) { x = 1; }
    else if ((rudolf.x - tar.x) > 0) { x = -1; }

    rudolf.x += x;
    rudolf.y += y;

    if (map[rudolf.y][rudolf.x] != 0) {
        int num = map[rudolf.y][rudolf.x];
        map[rudolf.y][rudolf.x] = 0;
        santas[num].score += C;
        santas[num].y += y * C;
        santas[num].x += x * C;
        if (santas[num].y <= 0 || santas[num].y > N || santas[num].x <= 0 || santas[num].x > N) {
            santas[num].state = -1;
            out_count++;
            return;
        }
        santas[num].state = 2;
        if (map[santas[num].y][santas[num].x] != 0) {
            bound(num, y, x);
        }
        map[santas[num].y][santas[num].x] = num;
    }

}

// ��Ÿ�� �̵�
void santa_move(int num) {
    int dist, dir = -1, ny, nx, near_dist;
    near_dist = pow(rudolf.y - santas[num].y, 2) + pow(rudolf.x - santas[num].x, 2);
    for (int i = 0; i < 4; i++) {
        ny = santas[num].y + santa_diry[i];
        nx = santas[num].x + santa_dirx[i];
        if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
        if (map[ny][nx] != 0) continue;
        dist = pow(rudolf.y - ny, 2) + pow(rudolf.x - nx, 2);
        if (near_dist > dist) {
            near_dist = dist;
            dir = i;
        }
    }
    if (dir != -1) {
        map[santas[num].y][santas[num].x] = 0;
        ny = santas[num].y + santa_diry[dir];
        nx = santas[num].x + santa_dirx[dir];
        santas[num].y = ny;
        santas[num].x = nx;

        // �浹 �˻�
        if (rudolf.y == ny && rudolf.x == nx) {
            santas[num].score += D;
            santas[num].y += santa_diry[(dir + 2) % 4] * D;
            santas[num].x += santa_dirx[(dir + 2) % 4] * D;
            if (santas[num].y <= 0 || santas[num].y > N || santas[num].x <= 0 || santas[num].x > N) {
                santas[num].state = -1;
                out_count++;
                return;
            }
            santas[num].state = 2;
            if (map[santas[num].y][santas[num].x] != 0) {
                bound(num, santa_diry[(dir + 2) % 4], santa_dirx[(dir + 2) % 4]);
            }
        }
        map[santas[num].y][santas[num].x] = num;
    }
}


int main() {
    //�Է�
    input();

    for (int k = 1; k <= M; k++) {// �Է��� �ϸ�ŭ ����
        if (out_count >= P) {
            //P ���� ��Ÿ�� ��� ���ӿ��� Ż���ϰ� �ȴٸ� �� ��� ������ ����
            break;
        }
        // �絹�� �̵�
        rudolf_move();
        //P���� ��Ÿ �̵�

        for (int i = 1; i <= P; i++)
        {
            if (santas[i].state == 0) {
                santa_move(i);
            }
        }

        //�� �� ���� ���� Ż������ ���� ��Ÿ�鿡�Դ� 1������ �߰��� �ο��մϴ�.
        for (int i = 1; i <= P; i++) {
            if (santas[i].state > 0) {
                santas[i].state--;
            }
            if (santas[i].state != -1) {
                santas[i].score++;
            }
        }

    }

    //���
    for (int i = 1; i <= P; i++) {
        cout << santas[i].score << " ";
    }
    return 0;
}