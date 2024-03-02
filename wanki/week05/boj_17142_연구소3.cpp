#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N, M;
int map[51][51];
int empty_space = 0;
int visit[10]; // ���̷��� ���� ���θ� �����ϴ� �迭
int mini = 21e8;
int dy[] = { 0, 0, -1, 1 }, dx[] = { 1, -1, 0, 0 };

struct point {
    int y, x;
};

vector<point> virus;
vector<point> q_insert;

// �Է�
void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                empty_space++;
            }
            else if (map[i][j] == 2) {
                virus.push_back({ i,j });
            }
        }
    }
}

// ���̷����� ������ �ð��� Ȯ��
int bfs() {
    queue<point> q;
    int visited[51][51] = { 0 };
    int empty = 1;

    for (point p : q_insert) {
        q.push(p);
        visited[p.y][p.x] = 1;
    }

    while (!q.empty()) {
        point now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = dx[i] + now.x;
            int ny = dy[i] + now.y;
            //�� ���� Ȯ��
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            // ���̷����� ��������
            // ������� �ƴϹǷ� empty�� ���� ��Ű�� ����
            // �ʸӼ��� ������� �����Ҽ� �ֱ⶧���� �����ó�� Ȱ��
            if (map[ny][nx] == 2 && visited[ny][nx] == 0) {
                visited[ny][nx] = visited[now.y][now.x] + 1;
                q.push({ ny,nx });
            }
            //���̰ų�, ������� �ƴҽ� �н�
            if (map[ny][nx] == 1 || visited[ny][nx] != 0) continue;

            visited[ny][nx] = visited[now.y][now.x] + 1;
            q.push({ ny,nx });
            empty++;
        }
    }

    /*cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
    cout << empty;*/

    // ��� �� ������ ���̷����� �����Ǿ����� Ȯ��
    if (empty <= empty_space) {
        return -1;
    }

    //���� ���̷����� �ִ� �ڸ��� 0���� ����
    //���̷����� �ڸ��� ���� �����Ǿ��ֱ⿡ �ִ밪�� ���ý�
    // 0�� �־� �����ν� �ִ밪�� ���
    for (point p : virus) {
        visited[p.y][p.x] = 0;
    }

    // visited�� �� Ȯ���ϸ鼭 �ִ밪�� ã�� 
    // -1�� ������ 1���� �����ϱ⿡ -1�� ��
    int maxi = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maxi = max(maxi, visited[i][j] - 1);
        }
    }
    return maxi;
}

// ���� �켱 Ž���� ���� ��� ���̷��� ������ ����� �ּ� �ð��� ����ϴ� �Լ�
void dfs(int node, int start) {
    //��������
    //M���� ���̷��� Ȱ��ȭ
    if (node == M) {
        int ret = bfs();
        //-1�� �ƴҶ��� �ּҰ��� ���ؼ� ����
        if (ret != -1) {
            mini = min(mini, ret);
        }
        return;
    }

    //start�� ���� 0���� �ϴ� �ͺ��� �ߺ� ��Ҹ� ���� �� ����
    for (int i = start; i < virus.size(); i++) {
        if (visit[i] == 1) continue;
        visit[i] = 1;
        q_insert.push_back(virus[i]);
        dfs(node + 1, i + 1);
        q_insert.pop_back();
        visit[i] = 0;
    }
}

int main() {
    input();
    dfs(0, 0);


    // mini���� ������ �ȉ������ ���� ������Ű�� ����� ���ٴ� ������ -1�� ���
    if (mini == 21e8) {
        cout << -1;
    }
    else {
        cout << mini;
    }

    return 0;
}
