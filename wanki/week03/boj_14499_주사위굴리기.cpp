#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//���� 1, ���� 2, ����3, ����4
int dy[] = { 0,0,0,-1,1 }, dx[] = { 0,1,-1,0,0 };
int N, M, x, y, K;
int map[21][21];
int dice[7] = { 0 };
queue<int> q;


void moveDice(int dir) {
    int temp;
    if (dir == 1) { // ���� �̵�
        temp = dice[6];
        dice[6] = dice[3];
        dice[3] = dice[1];
        dice[1] = dice[4];
        dice[4] = temp;
    }
    else if (dir == 2) { // ���� �̵�
        temp = dice[4];
        dice[4] = dice[1];
        dice[1] = dice[3];
        dice[3] = dice[6];
        dice[6] = temp;
    }
    else if (dir == 3) { // ���� �̵�
        temp = dice[2];
        dice[2] = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[6];
        dice[6] = temp;
    }
    else if (dir == 4) { // ���� �̵�
        temp = dice[6];
        dice[6] = dice[5];
        dice[5] = dice[1];
        dice[1] = dice[2];
        dice[2] = temp;
    }
}

void solve() {
    //ó�� ��ġ ����
    dice[1] = map[y][x];

    //q ��ɾ ����, ��ɾ ���������� ����
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        //���� ��ȿ�� �˻�
        int ny = y + dy[now];
        int nx = x + dx[now];

        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;

        y = ny;
        x = nx;


        moveDice(now); // �ֻ��� �̵�


//1. �ֻ����� ������ ��, �̵��� ĭ�� ���� �ִ� ���� 0�̸�,
//  �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����ȴ�. 
//2. 0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�,
// ĭ�� ���� �ִ� ���� 0�� �ȴ�.
        if (map[y][x] == 0) {
            map[y][x] = dice[1];
        }
        else {
            dice[1] = map[y][x];
            map[y][x] = 0;
        }

        //���
        cout << dice[6] << " \n";
    }
}


void input() {
    //ù° �ٿ� ������ ���� ũ�� N, ���� ũ�� M (1�� N, M �� 20),
    //�ֻ����� ���� ���� ��ǥ x, y(0 �� x �� N-1, 0 �� y �� M-1),
    //�׸��� ����� ���� K (1 �� K �� 1,000)�� �־�����.
    int cmd;
    cin >> N >> M >> y >> x >> K;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < K; i++)
    {
        cin >> cmd;
        q.push(cmd);
    }
}


int main() {
    input();
    solve();

    return 0;
}