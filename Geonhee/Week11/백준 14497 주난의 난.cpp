#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
int sy, sx, ey, ex;
char map[304][304];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int res = 0;
bool check = false;

void bfs() {
    //�湮�迭�� ���� ���� �� ���� �ʱ�ȭ
    //0�� ��ġ�鵵 �ٽ� ���ƾ��ϹǷ�
    bool visited[304][304];
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    //�ֳ����� ��ġ�� ������
    q.push({ sy,sx });
    visited[sy][sx] = true;

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];
            //���� ��ġ �����ϸ� check�ϰ� return
            if (ny == ey && nx == ex) {
                check = true;
                return;
            }
            //�����ȿ� �ְ� �湮���� �ʾҴ����
            if (ny <= n && ny >= 1 && nx <= m && nx >= 1 && !visited[ny][nx]) {
                //�湮Ȯ���ϰ�
                visited[ny][nx] = true;
                //1�̶�� 0���� �ٲ��ְ�
                if (map[ny][nx] == '1') {
                    map[ny][nx] = '0';
                }
                //0�̶�� ��� Ž���ؾ��ϹǷ� q�� push���ֱ�
                else if (map[ny][nx] == '0') {
                    q.push({ ny,nx });
                }
            }
        }
    }
}

int main() {

    cin >> n >> m >> sy >> sx >> ey >> ex;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
        }
    }
    //ã���� ���� ��������
    while (1) {
        res++;
        bfs();
        if (check)break;
    }
    cout << res;
    return 0;
}
