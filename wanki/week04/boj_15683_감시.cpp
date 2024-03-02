#include<iostream>
#include<vector>
#include<string>

using namespace std;

int N, M;
int map[8][8];
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 }; // �� �� �� ��;
int MIN = 65;
//1 ���ʹ���, 4
//2 �ι���(�ݴ� ����) ������ 2
//3 �ι��� ���� ������ 4
//4 3���� ������4
//5 4���� ������ 1
//6 ��
struct point
{
    int y;
    int x;
};

vector<point>v;

//���
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
        //���� ���� * ������
        int nx = x + dx[dir] * i;
        int ny = y + dy[dir] * i;
        //���� 
        if (nx < 0 || ny < 0 || nx >= N || ny >= M) return;
        //��
        if (map[nx][ny] == 6) return;
        //�ٸ� CCTVȮ�ν� �н�
        if (map[nx][ny] != 0) continue;
        map[nx][ny] = -1;
    }
}

void dfs(int node) {
    //��� ī�޶� �� Ȯ�������� �ּҰ��� Ȯ���ϰ� ����
    if (node == v.size()) {
        MIN = min(MIN, counting());
        return;
    }

    int y = v[node].y;
    int x = v[node].x;
    int temp[8][8];
    for (int dir = 0; dir < 4; dir++) {
        //temp�迭�� ��Ʈ��ŷ���� ���¸� ����
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                temp[i][j] = map[i][j];
            }
        }

        //1 ���ʹ���
        if (map[x][y] == 1) {
            watch_check(x, y, dir);
        }

        //2 �ι���(�ݴ� ����)
        else if (map[x][y] == 2) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 2);
        }

        //3 �ι��� ����
        else if (map[x][y] == 3) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
        }

        //4 3����
        else if (map[x][y] == 4) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
            watch_check(x, y, dir + 2);
        }

        //5 4����
        else if (map[x][y] == 5) {
            watch_check(x, y, dir);
            watch_check(x, y, dir + 1);
            watch_check(x, y, dir + 2);
            watch_check(x, y, dir + 3);
        }
        //���
        dfs(node + 1);

        //���� �� ����
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = temp[i][j];
            }
        }
    }
}

//�Է�
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
    //���� ���� 0����, ī�޶���ġ �迭�� 0���ͽ���
    dfs(0);
    cout << MIN;
}