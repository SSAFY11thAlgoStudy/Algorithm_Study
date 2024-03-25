#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n, m;
int map[5][5]; 
/*2 <= n <= 4 ������ 
��ġ ����Ʈ�� ��ǥ�� 1,1���� �����ϱ⿡
��ü������ 1,1���� �������� �ϵ��� ����*/
vector<pair<int, int>>point;
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
int visit[5][5] = { 0, };
int cnt = 0;

//�Է�
void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }
    int y, x;
    for (int i = 0; i < m; i++) {
        cin >> y >> x;
        point.push_back({ y,x });
    }
}

void solve(int y, int x, int node) {
    //��� ����Ʈ�� �������� �� node�� m�̵ȴ�.
    if (node == m) {
        cnt++;
        return;
    }
    //�湮�� ����Ʈ�� ���� �Ҷ�����  node�� ���� ��Ŵ
    if (point[node].first == y && point[node].second == x) {
        solve(y, x, node + 1);
        return;
        //���� ������ �����Ƿ� �ٷ� �����ϸ鼭 ������������ �ٷ� �����ش�.
    }

    for (int i = 0; i < 4; i++) {
        int ny = dy[i] + y;
        int nx = dx[i] + x;

        // map���� �˻�
        if (ny <= 0 || nx <= 0 || ny > n || nx > n)continue;
        if (map[ny][nx] == 1)continue; // ��
        if (visit[ny][nx] == 1)continue; //�湮 Ȯ��
        visit[ny][nx] = 1;
        //���� ��ġ�� ���� dfs�� �����Ѵ�.
        solve(ny, nx, node);
        visit[ny][nx] = 0;
    }

}

int main(int argc, char** argv)
{
    input();
    //ó�� �������� ��ġ�� �ٽ� ���ư��� �ʵ��� visit�� 1ó�� ���ش�.
    visit[point[0].first][point[0].second] = 1;
    solve(point[0].first, point[0].second, 1);
    cout << cnt;
    return 0;
}