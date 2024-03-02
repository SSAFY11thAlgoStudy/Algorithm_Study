#include <iostream>
#include <queue>
#include <vector>
#include <cmath> 
#include <cstring> 
using namespace std;

int n, l, r;
int map[50][50];
bool visited[50][50];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };


bool bfs(int x, int y) {
    queue<pair<int, int>> q;
    vector<pair<int, int>> united; //��ǥ�� ���� ����
    int temp = 0; //���� �����α� ��
    int cnt = 0; // ���� ���� ��

    q.push({ x, y });
    visited[x][y] = true; // ���� ���� �湮üũ
    united.push_back({ x, y }); // ��ǥ ���Ϳ� �־��ֱ�
    temp += map[x][y]; // �� ���� �α� ���� �����ְ�
    cnt++; //���� �� ++

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

            if (!visited[nx][ny]) {
                if (abs(map[x][y] - map[nx][ny]) >= l && abs(map[x][y] - map[nx][ny]) <= r) {
                    q.push({ nx, ny });
                    visited[nx][ny] = true; //�湮üũ
                    united.push_back({ nx, ny }); //���� ���� ��ǥ ���Ϳ� �־��ֱ�
                    temp += map[nx][ny]; //���� ���� �α� �� �����ְ�
                    cnt++; //���� �� ++
                }
            }
        }
    }

    if (cnt > 1) { //������ �ִٸ�
        int avg = temp / cnt; // ��� ���ؼ�
        for (auto i : united) {
            map[i.first][i.second] = avg; //��ǥ ������ ��� �־��ֱ�
        }
        return true;
    }
    else { //������ ���ٸ� �α��̵� x
        return false;
    }
}



int main() {
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }

    int res = 0; //��ĥ ���� �߻��ϴ��� ����
    bool possible = true; // �α� �̵��� �߻��� �� �ִ°�

    while (possible) {
        possible = false;
        memset(visited, false, sizeof(visited)); //�α��̵��ϰ� �ʱ�ȭ 

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) { //�湮���� �Ϳ� ����
                    if (bfs(i, j)) { // true�� ��ȯ�ϸ�
                        possible = true; // �α� �̵��� �����ϴ�.
                    }
                }
            }
        }

        if (possible) res++; // true�̸� �α��̵��� ���̹Ƿ� res++
    }
    cout << res;

    return 0;
}
