#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int map[4][4];
bool visited[4][4] = { false };
int res = 0;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
vector<pair<int, int>> car;

void dfs(int y, int x, int cnt) {
    // y,x�� ��ó�� �� ������ �´� ��ǥ�̰�
    if (y == car[cnt].first && x == car[cnt].second) {
        // cnt ���� ������� ������ ���ľ� �� �� �� ��ģ ���̹Ƿ�
        if (cnt == car.size() - 1) {
            //res�� 1�����ְ� �ٸ� �ó����� ã���� return
            res++;
            return;
        }
        //������ ��ĥ ���� �ƴ϶�� ���ľ��� �� ���� 1�����ֱ�
        else cnt++;
    }
    //���� ��ǥ �湮 üũ
    visited[y][x] = true;
    for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];

        if (ny >= n || ny < 0 || nx >= n || nx < 0 || visited[ny][nx] || map[ny][nx] == 1) continue;
        dfs(ny, nx, cnt);
    }
    // �ٸ� �ó������� ���ƾ� �ϹǷ� �湮üũ ����
    visited[y][x] = false;
    return;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        //��ó�� �� �� ���Ϳ� �ֱ�
        car.push_back({ a - 1,b - 1 });
    }
    //ù��° ���� ����, ���ľ� �� �� ����
    dfs(car[0].first, car[0].second, 1);
    cout << res;
    return 0;
}
