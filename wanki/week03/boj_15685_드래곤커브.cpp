#include<iostream>
#include<vector>

using namespace std;

/*
0: x��ǥ�� �����ϴ� ����(��)
1: y��ǥ�� �����ϴ� ����(��)
2: x��ǥ�� �����ϴ� ����(��)
3: y��ǥ�� �����ϴ� ����(��)
*/
int dy[] = { 0, -1, 0, 1 }, dx[] = { 1, 0, -1, 0 };
int N, x, y, d, g;
int map[101][101];
vector<int> path;

void draw_line() {
    //��Ʈ �ʱ�ȭ
    path.clear();
    //��Ʈ ����
    path.push_back(d);
    //���� ��ġ ����
    map[y][x] = 1;
    y += dy[d];
    x += dx[d];
    map[y][x] = 1;

    for (int gen = 1; gen <= g; gen++) { // ���� Ȯ�� 1�̻�
        for (int i = path.size() - 1; i >= 0; i--) { //�Դ���Ʈ Ȯ��
            int nd = (path[i] + 1) % 4; // �Դ� ��Ʈ�� +1��ŭ ��
            y += dy[nd];
            x += dx[nd];
            map[y][x] = 1;
            path.push_back(nd);
        }
    }
}

int check_square() {
    int cnt = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            if (map[i][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1 && map[i + 1][j] == 1) {
                cnt++;
            }
        }
    }
    return cnt;
}

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x >> y >> d >> g;
        draw_line();
    }
}

int main() {
    input();
    cout << check_square();
    return 0;
}
